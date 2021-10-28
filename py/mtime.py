import os
import time
import datetime
import sys

year = 2019
month = 11
day = 5
hour = 19
minute = 50
second = 0

date = datetime.datetime(year=year, month=month, day=day, hour=hour, minute=minute, second=second)
mtime = time.mktime(date.timetuple())

for subdir, dirs, files in os.walk(sys.argv[1]):
    for filename in files:
        filepath = os.path.join(subdir, filename)
        stat = os.stat(filepath)
        timestamp = time.strftime(
            "%Y%m%d%H%M%S", time.localtime(stat.st_mtime))
        os.utime(filepath, (mtime, mtime))
        print("%s>%d%02d%02d%02d%02d%02d %s"%(timestamp,year,month,day,hour,minute,second,filepath))

