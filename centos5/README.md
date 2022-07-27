```bash
chkconfig --list|grep -v sshd|grep -v network|awk '{print "chkconfig "$1" off"}'|sh # disable unnecessary services
rm -rf /var/cache/yum # clean up
yum install zlib zlib-devel # to build python 3.10
```
