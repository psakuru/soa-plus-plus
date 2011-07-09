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
#wget http://soa-plus-plus.googlecode.com/files/soa-plus-plus-test.tar.gz
cecho ":: estrazione " $green
cecho "\t$> tar -xzvf soa-plus-plus-test.tar.gz" $blue

exit 0
