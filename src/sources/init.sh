#!/bin/bash
docker rm `docker ps -a -q`
docker rmi `docker images -a -q`
docker run -it --name fzc_slave -v /usr/bin:/usr/hosts/bin -v /usr/lib:/usr/hosts/lib -v /var/run:/var/run -v /home/td_dev/docker:/home/td_dev/docker --net=host 172.18.194.116:5000/fztest/slave:latest
