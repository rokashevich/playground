#!/bin/sh
wget -qO- https://www.bimradio.ru/bim-almet/|sed '271q;d'|sed 's/<.*>//g'|awk '{$1=$1};1'
