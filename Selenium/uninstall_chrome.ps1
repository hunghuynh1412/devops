 
$KEY = 'HKLM:\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall\Google Chrome'
#chrome 32
(Get-ItemProperty -path $KEY).version | ForEach-Object {& ${env:ProgramFiles(x86)}\Google\Chrome\Application\$_\Installer\setup.exe --uninstall --multi-install --chrome --system-level --force-uninstall -force -Confirm:$false}
#chrome 64
(Get-ItemProperty -path $KEY).version | ForEach-Object {& ${env:ProgramFiles}\Google\Chrome\Application\$_\Installer\setup.exe --uninstall --multi-install --chrome --system-level --force-uninstall -force -Confirm:$false}