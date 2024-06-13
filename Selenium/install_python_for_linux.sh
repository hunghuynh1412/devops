#!/bin/bash
# Download the package and dependent packages from the CentOS 7 machine with internet before copying to the destination machine where python needs to be installed:
    # yumdownloader --resolve --destdir=/path/to/save/centos7_packages openssl-devel bzip2-devel libffi-devel gcc make
# Download the package and dependent packages from the CentOS 8 machine with internet before copying to the destination machine where python needs to be installed:
    # dnf download --resolve --destdir=/path/to/save/centos8_packages openssl-devel bzip2-devel libffi-devel gcc make
# Download the package and dependent packages from the Ubuntu 22 machine with internet before copying to the destination machine where python needs to be installed:
    # mkdir -p /path/to/save/ubuntu22_packages
    # sudo apt-get install --download-only -o Dir::Cache::archives="/path/to/save/ubuntu22_packages" build-essential libssl-dev libffi-dev libbz2-dev
# Download the package and dependent packages from the Kali 22 machine with internet before copying to the destination machine where python needs to be installed:
    # mkdir -p /path/to/save/kali22_packages
    # sudo apt-get install --download-only -o Dir::Cache::archives="/path/to/save/kali22_packages" build-essential libssl-dev libffi-dev libbz2-dev



LOGFILE="/var/log/InstallLog.txt"

# Log the current time and date
echo $(date) >> $LOGFILE

# Check if the user is a sudoer
if [ "$(id -u)" -ne 0 ]; then
  echo "This script must be run as root or with sudo privileges." | tee -a $LOGFILE
  exit 1
fi

# Determine the OS and package manager
PKG_PATH=""
PKG_MANAGER=""
PKG_FILES=""

if grep -q -i "release 7" /etc/redhat-release ; then
  OS="CentOS 7"
  PKG_MANAGER="yum localinstall"
  PKG_PATH="/path/to/save/centos7_packages"
  PKG_FILES="*.rpm"
elif grep -q -i "release 8" /etc/redhat-release ; then
  OS="CentOS 8"
  PKG_MANAGER="dnf localinstall"
  PKG_PATH="/path/to/save/centos8_packages"
  PKG_FILES="*.rpm"
elif lsb_release -d | grep -q "Ubuntu 22"; then
  OS="Ubuntu 22"
  PKG_MANAGER="dpkg -i"
  PKG_PATH="/path/to/save/ubuntu22_packages"
  PKG_FILES="*.deb"
elif grep -q "Kali GNU/Linux 22" /etc/os-release ; then
  OS="Kali 22"
  PKG_MANAGER="dpkg -i"
  PKG_PATH="/path/to/save/kali22_packages"
  PKG_FILES="*.deb"
else
  echo "Operating system not supported." | tee -a $LOGFILE
  exit 1
fi

# Check if the packages directory exists
if [ ! -d "$PKG_PATH" ]; then
  echo "Package directory not found." | tee -a $LOGFILE
  exit 1
fi

echo "Installing dependent packages..." | tee -a $LOGFILE
$PKG_MANAGER $PKG_PATH/$PKG_FILES >> $LOGFILE 2>&1

# Install Python
TAR_FILE="/path/to/Python-3.7.17.tar.xz"

# Check if the tar file exists
if [ ! -f "$TAR_FILE" ]; then
  echo "Python tar file not found." | tee -a $LOGFILE
  exit 1
fi

# Extract the tar file
tar -xf $TAR_FILE -C /tmp | tee -a $LOGFILE 2>&1

# Compile and install Python
cd /tmp/Python-3.7.17 || exit
./configure --enable-optimizations | tee -a $LOGFILE 2>&1
make -j "$(nproc)" | tee -a $LOGFILE 2>&1
make altinstall | tee -a $LOGFILE 2>&1

# Update the PATH variable
echo 'export PATH=/usr/local/bin/python3.7:$PATH' >> ~/.bashrc
source ~/.bashrc

# Check the Python version
if python3.7 --version 2>&1 | grep -q "Python 3.7.17"; then
  echo "Installed Python 3.7.17 successfully." | tee -a $LOGFILE
else
  echo "Installation of Python 3.7.17 failed." | tee -a $LOGFILE
  exit 1
fi
