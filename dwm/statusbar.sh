#!/bin/zsh

get_date() {
    date +'%a | %b %d | %r'
}

get_battery() {
     cat /sys/class/power_supply/BAT0/capacity
}

get_netspeed(){}

get_language(){
    setxkbmap -query | awk '/layout/ {print $2}'
}

get_sound(){}

while true
do
    xsetroot -name "$(get_date)    [$(get_language)]    $(get_battery)%"
    sleep 1
done
