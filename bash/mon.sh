#!/bin/sh
time=`date +"%Y.%m.%d %H:%M"	`

disk=`df -hP /|tail -1|awk '{print $4}'`

ram=`free -h --si|grep Mem|awk '{print $7}'`

temp=`cat /sys/class/thermal/thermal_zone*/temp|sort|tail -1`
temp=$(( temp / 1000 ))
temp=$temp"°"

cpu=$(vmstat 1 2|tail -1|awk '{print $15}')
cpu=$(( 100 - cpu ))
cpu=$cpu"%"

pad="   "
cpu=`printf "%s%s" "${pad:${#cpu}}" $cpu`
echo " $cpu $temp $ram $disk $time "
