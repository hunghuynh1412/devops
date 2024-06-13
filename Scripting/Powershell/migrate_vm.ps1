function refactorInvalidCharacter {
    param ($in)
    
    $output = $in.replace('[','[[]*')

    return $output
}

#Define user login vCenter
$UserName = 'administrator@cb.systems'
$Password = '***************'
$Domain = 'cb.systems'
$Server = 'vc-stg.cb.systems'
Connect-VIServer -Server $Server -User $UserName -Password $Password



$Folder_Name = Get-Folder -Name 'Template_Department'
# $Template = Get-Template -Location $Folder_Name
# #Convert template to VM
# $Template | foreach{
#     Set-Template -Template $_ -ToVM
# }

$Datastore_Destination = Get-Datastore -Name 'vsanDatastore'
$Destination_Portgroup = Get-VDPortgroup -VDSwitch 'STG_DSwitch' -Name 'NET-192.168.199.0-Imported'

# Migrate template to vSan

$VM_Source = Get-VM -Location $Folder_Name

$VM_Source | foreach{
    $Network_Adapter = get-Networkadapter -VM $_

    move-VM -VM $_ -Destination 10.9.1.11 -Datastore $Datastore_Destination -NetworkAdapter $Network_Adapter -PortGroup $Destination_Portgroup
    # move-VM -VM $_ -Datastore $Datastore_Destination
}
