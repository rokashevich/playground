FROM debian:stable
RUN \
  apt-get -q update && apt-get -qy dist-upgrade \
  && apt-get -qy install curl \
  && curl -fsSL -o /usr/share/keyrings/salt-archive-keyring.gpg https://repo.saltproject.io/py3/ubuntu/20.04/amd64/latest/salt-archive-keyring.gpg \
  && echo "deb [signed-by=/usr/share/keyrings/salt-archive-keyring.gpg] https://repo.saltproject.io/py3/ubuntu/20.04/amd64/latest focal main" \
    > /etc/apt/sources.list.d/salt.list \
  && apt-get -q update && apt-get install -qy salt-master \
  && apt-get -qy autopurge && apt-get clean && rm -rf /var/lib/apt/lists
