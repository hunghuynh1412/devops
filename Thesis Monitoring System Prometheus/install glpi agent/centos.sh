#!/bin/bash
#script for centos

#install requirement package
yum update && upgrade -y
yum install wget -y 
yum install perl -y

# wget package
cd /opt
mkdir glpi
cd glpi/
wget https://nightly.glpi-project.org/glpi-agent/glpi-agent-1.2-git07a840ed-linux-installer.pl
perl glpi-agent-1.2-git07a840ed-linux-installer.pl -s http://172.27.228.133/glpi/front/inventory.php

# edit agent.cfg
cd /etc/glpi-agent
echo "server = http://172.27.228.133/glpi/front/inventory.php" >> agent.cfg

# start service
systemctl daemon-reload
systemctl enable glpi-agent
systemctl start glpi-agent

# force
glpi-agent -f
