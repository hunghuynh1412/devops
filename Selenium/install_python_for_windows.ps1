Set-ExecutionPolicy RemoteSigned -Force -Confirm:$false


# Log file path
$LOGFILE = ".\InstallLog.txt"

# Log current time and date
Add-Content $LOGFILE "$(Get-Date)"

# Get Windows version
$VERSION = (Get-WmiObject Win32_OperatingSystem).Version

# Log the detected Windows version
Add-Content $LOGFILE "Detected Windows version: $VERSION"

# Choose Python installer based on Windows version
if ([version]$VERSION -ge [version]"6.2") {
    Add-Content $LOGFILE "Choosing Python 3.7 installer"
    $PYTHON_INSTALLER = ".\python-3.7.17.exe"
    $PYTHON_VERSION = "3.7.17"
    $PYTHON_PATH = "$env:USERPROFILE\AppData\Local\Programs\Python\Python37-32"
} else {
    Add-Content $LOGFILE "Choosing Python 2.7 installer"
    $PYTHON_INSTALLER = ".\python-2.7.18.msi"
    $PYTHON_VERSION = "2.7.18"
    $PYTHON_PATH = "C:\Python27"
}

# Check if Python installer exists
if (-Not (Test-Path $PYTHON_INSTALLER)) {
    Add-Content $LOGFILE "Python installer not found."
    Exit 1
}

# Check current Python versions
$pythonInstalled = $False
$pythonPaths = Get-Command python -ErrorAction SilentlyContinue
foreach ($path in $pythonPaths) {
    $versionOutput = & $path --version 2>&1
    if ($versionOutput -match "Python $PYTHON_VERSION") {
        $pythonInstalled = $True
        break
    }
}

if ($pythonInstalled) {
    Add-Content $LOGFILE "Python $PYTHON_VERSION already installed."
    Exit 0
}

# Install Python
Add-Content $LOGFILE "Installing Python..."
Start-Process $PYTHON_INSTALLER -Wait -ArgumentList '/quiet InstallAllUsers=1 PrependPath=1'

if ($LASTEXITCODE -ne 0) {
    Add-Content $LOGFILE "Error during Python installation."
    Exit $LASTEXITCODE
}

# Create Virtual Environment
Add-Content $LOGFILE "Creating Virtual Environment..."
$venvPath = ".\myenv"
python -m venv $venvPath

# Activate Virtual Environment
Add-Content $LOGFILE "Activating Virtual Environment..."
Invoke-Expression "$venvPath\Scripts\Activate"

if ($LASTEXITCODE -ne 0) {
    Add-Content $LOGFILE "Error during Virtual Environment activation."
    Exit $LASTEXITCODE
}
