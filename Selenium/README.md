Selenium + Python User Behavior Simulation
This repository provides automation scripts for simulating user behaviors using Selenium and Python.

Prerequisites
Python 3.7.17 (Note: For older versions of Windows, Python 2.7.18 will be used)
Chromedriver version 101.0.4951.15
Selenium 4.11.2

Installation
Python Installation Scripts
Depending on your operating system, run the corresponding script to install Python:

    For Linux (CentOS 7/8 and Ubuntu 22): install_python_for_linux.sh
    For Windows (Windows 8/ Windows Server 2012): install_python_for_windows.ps1
Command powershell:
```
#Install python
Start-Process '.\tools\python-3.7.0.exe' -Wait -ArgumentList '/quiet InstallAllUsers=1 PrependPath=1'
```

Setting up Selenium Environment
Navigate to the directory containing the source code, labeled as SELENIUM.


** Error install by script powershell **
*** note: Run powershell as administrator 

BE support allow permission for execute powershell
```Set-ExecutionPolicy RemoteSigned -Force -Confirm:$false```

Check install python by powercli
```Get-WmiObject -Query "SELECT * FROM Win32_Product WHERE (Name LIKE 'Python 3.7%')"```
Uninstall python by powercli
```Get-WmiObject -Query "SELECT * FROM Win32_Product WHERE (Name LIKE 'Python 3.7%')" | ForEach-Object { $_.Uninstall() }```

1. Create a Python virtual environment:

For Windows:

    py -3.7 -m venv myenv
    .\myenv\Scripts\Activate

For Linux

    python3.7 -m venv myenv
    source myenv/bin/activate

2. Install the required packages:

pip install selenium==4.11.2
pip install pyautogui

## Setup virtual enviroment
```
# Create Virtual Environment

$venvPath = ".\myenv"

python -m venv $venvPath

# Activate Virtual Environment

Invoke-Expression "$venvPath\Scripts\Activate"
```
Usage
Run your Selenium script to simulate the user behavior you intend to mimic.
    python3 main.py

Sending Emails Without a Browser
If you wish to send emails without using a browser, use the scripts located in the SELENIUM/script folder.
Module Send email
```
    "folder_path": "C:\\temp", //path in windows '\\' and path in linux '/'
```
