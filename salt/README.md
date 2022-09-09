```bash
python3 -m virtualenv x
. x/bin/activate
pip install salt
pip install markupsafe==2.0.1 jinja2==3.0 # иначе трабл
```

```bash
sed -Ei 's|(alpine.*/)|alpine/edge/|g' /etc/apk/repositories # switch to edge
sed -i '/community/s/#//g' /etc/apk/repositories # enable community
apk -U upgrade # update + upgrade
apk add salt-minion
/etc/init.d/salt-minion start
```

```bash
salt -c `pwd` '*' test.version
salt -c `pwd` '*' grains.ls
salt -c `pwd` '*' grains.items
salt -c `pwd` -G 'os:Alpine' test.version
salt -c `pwd` -G 'cpuarch:i686' grains.item num_cpus
salt -c `pwd` -G 'kernelrelease:5.15*' grains.item kernelrelease
```

```
#/etc/salt/minion.d/grains.conf
grains:
  deployment: datacenter4
  cabinet: 14
  switch_port: 4
  roles:
    - web
    - app1
    - dev
```

```bash
salt -G 'roles:app1' test.ping
```

