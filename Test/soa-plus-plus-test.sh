#!/bin/bash
black='\E[1;30m'
red='\E[1;31m'
green='\E[1;32m'
yellow='\E[1;33m'
blue='\E[1;34m'
magenta='\E[1;35m'
cyan='\E[1;36m'
white='\E[1;37m'
redbkg='\033[41m'
greenbkg='\033[42m'
yellowbkg='\033[43m'
bluebkg='\033[44m'

cecho ()
{
local default_msg="No message passed."
message=${1:-$default_msg}
color=${2:-$black}
echo -e "$color"
echo -e "$message"
tput sgr0
return
}

cecho "--------------------------------------------------------------------------------" $red
cecho "                                 << soa-plus-plus >>" $green
cecho "                                     library test" $green
cecho "--------------------------------------------------------------------------------" $red
echo -e "\E[1;32m:: download dei sorgenti dal repository \e[1;34mG\e[1;31mo\e[1;33mo\e[1;34mg\e[1;32ml\e[1;31me \e[1;34mcode\e[00m"
cecho "\t$> wget http://soa-plus-plus.googlecode.com/files/soa-plus-plus-test.tar.gz" $blue
wget http://soa-plus-plus.googlecode.com/files/soa-plus-plus-test.tar.gz
cecho ":: estrazione dei sorgenti" $green
cecho "\t$> tar -xzvf soa-plus-plus-test.tar.gz" $blue
tar -xzvf soa-plus-plus-test.tar.gz
cecho ":: compilazione dei sorgenti" $green
cecho "\t$> cd soa-plus-plus/Test/Client" $blue
cd soa-plus-plus/Test/Client
cecho "\t$> ./makeClient.sh" $blue
./makeClient.sh
cp client client0/
cp client client1/
cp client client2/
cp client client3/
cp client client4/
cecho "\t$> cd ../Servers" $blue
cd ../Servers
cecho "\t$> ./makeRegister.sh" $blue
./makeRegister.sh
cecho "\t$> ./makeHorizontalFlipServer.sh" $blue
./makeHorizontalFlipServer.sh
cecho "\t$> ./makeRotateImageServer.sh" $blue
./makeRotateImageServer.sh
cecho "\t$> ./makeImageRegisterServer.sh" $blue
./makeImageRegisterServer.sh
cecho ":: compilazione terminata, eseguibili prodotti:" $green
cecho "\t Service Register: Services/register" $blue
cecho "\t Horizontal Flip Server: Services/horizontalFlipServer" $blue
cecho "\t Rotate Image Server: Services/rotateImageServer" $blue
cecho "\t Image Register: Services/imageRegisterServer" $blue
cecho "\t Clients: Client/client{0,1,2,3,4}/client" $blue
exit 0

