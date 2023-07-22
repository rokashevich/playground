import argparse
import os
import pathlib
import sys

from multiprocessing import shared_memory

import paramiko

from scp import SCPClient

def execute(ssh_transport, ssh_command):
    session = ssh_transport.open_channel(kind='session')
    session.exec_command(ssh_command)
    stdout_data = []
    stderr_data = []
    n = 4096
    while True:
        if session.recv_ready():
            stdout_data.append(session.recv(n))
        if session.recv_stderr_ready():
            stderr_data.append(session.recv_stderr(n))
        if session.exit_status_ready():
            break
    print(stdout_data)
    print(stderr_data)
    return session.recv_exit_status()

# Завершаем скрипт, если уже работает одна копия.
try:
    shm = shared_memory.SharedMemory(name='sshtool_shm', create=True, size=1)
except:
    sys.exit(1)
shm.close()
shm.unlink()

parser = argparse.ArgumentParser(description='Program can copy files to remote host and execute commands there.')
parser.add_argument('-i', '--ip', help='remote host ip', required=True)
parser.add_argument('-u', '--username', help='ssh user name', required=True)
parser.add_argument('-p', '--password', help='ssh user password', required=True)
parser.add_argument('-c', '--content', nargs=2, help='copy file or files destination on a remote host',
                    default=(None, None))
parser.add_argument('-b', '--command_begin', help='a command to be executed without nohup in the beginning', default=None)
parser.add_argument('-e', '--command_end', help='a command to be executed with nohup in the end', default=None)
args = parser.parse_args()

ip = args.ip
username = args.username
password = args.password

if args.content:
    content_path = args.content[0]
    content_copy_destination = args.content[1]
if args.command_begin:
    command_on_begin = args.command_begin
if args.command_end:
    command_on_end = args.command_end
    
transport = paramiko.Transport((ip, 22))
transport.connect(username=username, password=password)
scp = SCPClient(transport)

if command_on_begin:
    execute(transport, command_on_begin)

if content_path and content_copy_destination:
    if execute(transport, "mkdir -p %s; cd \"%s\"; rm -rf *"%(content_copy_destination,content_copy_destination)) != 0:
        sys.exit(1)
    for filename in os.listdir(content_path):
        scp.put(os.path.join(content_path, filename), recursive=True, remote_path=content_copy_destination)

if command_on_end:
    execute(transport, command_on_end)
