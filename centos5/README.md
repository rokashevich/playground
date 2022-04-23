```bash
chkconfig --list|grep -v sshd|grep -v network|awk '{print "chkconfig "$1" off"}'|sh
```
