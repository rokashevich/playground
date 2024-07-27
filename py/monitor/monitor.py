import argparse
import asyncio
from dataclasses import dataclass
import os
import shlex
import sys



# print(f"\033[31m red\033[0m")
# print(f"\033[32m green\033[0m")
# print(f"\033[33m yellow\033[0m")




from http.server import BaseHTTPRequestHandler, HTTPServer
from socketserver import ThreadingMixIn
import json
class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == "/metrics":
            self.send_response(200)
            self.send_header("Content-type", "application/json")
            self.end_headers()

            # Retrieve shared data
            self.wfile.write(json.dumps({"a":1}).encode())

class ThreadedHTTPServer(ThreadingMixIn, HTTPServer):
    """Handle requests in a separate thread."""

@dataclass
class App:
    cmd: str
    name: str = ''
    args: tuple = ()
    killable: bool = False
    process: asyncio.subprocess.Process = None
    enabled: bool = True
    task: asyncio.Task = None
    stdout_task: asyncio.Task = None
    stderr_task: asyncio.Task = None
    restarts: int = 0
    fgcolor: str = ''
    def __post_init__(self):
        shlexed = shlex.split(self.cmd)
        self.name = shlexed[0]
        self.args = shlexed[1:]
        fgcolors = {'red':31,'green':32,'yellow':33,'blue':34,'magenta':34,'cyan':36,'white':37}

async def run_app(app):
    while True:
        os.environ["PYTHONUNBUFFERED"] = "1"
        app.process = await asyncio.create_subprocess_exec(
            app.name,
            *app.args,
            stdout=asyncio.subprocess.PIPE,
            stderr=asyncio.subprocess.PIPE,
        )

        print(f"Started {app.name} with PID {app.process.pid}")

        async def read_stream(stream, callback):
            while True:
                line = await stream.readline()
                if not line:
                    break
                callback(line.decode().strip())

        app.stdout_task = asyncio.create_task(read_stream(app.process.stdout, lambda line: print(f"[{app.name} stdout] {line}")))
        app.stderr_task = asyncio.create_task(read_stream(app.process.stderr, lambda line: print(f"[{app.name} stderr] {line}")))

        await asyncio.wait([app.stdout_task, app.stderr_task])
        await app.process.wait()


async def main(apps):
    httpd = ThreadedHTTPServer(('', 8000), RequestHandler)
    loop = asyncio.get_event_loop().run_in_executor(None, httpd.serve_forever)
    while True:
        # if os.path.exists("/tmp/a"):
        #     apps["./script2.py"].enabled = False
        #     apps["./script2.py"].task.cancel()
        #     apps["./script2.py"].process = None
        # else:
        #     apps["./script2.py"].enabled = True

        for app in apps:
            if app.enabled and not app.process:
                app.task = asyncio.create_task(run_app(app))
        await asyncio.sleep(1)


# hash_value = hash(s)
# return (hash_value % N) + 1

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-c', action='append', type=str, help='command', default=[])
    parser.add_argument('-k', action='append', type=str, help='killable', default=[])
    args = parser.parse_args()

    apps = []
    for cmd in args.c:
        apps.append(App(cmd))
    for cmd in args.k:
        apps.append(App(cmd, killable=True))

    asyncio.run(main(apps))
