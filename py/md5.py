import os
import sys
import time
import hashlib


def md5(filepath):
    hash_md5 = hashlib.md5()
    with open(filepath, "rb") as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hash_md5.update(chunk)
    return hash_md5.hexdigest()


for subdir, dirs, files in os.walk(sys.argv[1]):
    for filename in files:
        filepath = os.path.join(subdir, filename)
        md5sum = md5(filepath)
        stat = os.stat(filepath)
        timestamp = time.strftime(
            "%d-%m-%Y_%H:%M", time.localtime(stat.st_ctime))
        size = stat.st_size
        print(md5sum, filepath, timestamp, size)
