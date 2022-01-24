#!/bin/zsh

get_date() {
    date +'%a | %b %d | %I:%M %p'
}

get_battery() {
    "
    BAT_ICON=""
    ICON=""
    capacity=$(cat /sys/class/power_supply/BAT0/capacity)
    charging=$(cat /sys/class/power_supply/BAT0/status)
    if [[ "$charging" == "Charging" ]]; then
        ICON=' '
    elif [[ $capacity -le 25 ]]; then
        ICON=' '
    fi

    if [[ $capacity -ge $FULL_AT ]]; then
        BAT_ICON=''
    elif [[ $capacity -le 25 ]]; then
        BAT_ICON=''
    elif [[ $capacity -le 60 ]]; then
        BAT_ICON=''
    elif [[ $capacity -le 98 ]]; then
        BAT_ICON=''
    fi
    echo "$ICON$BAT_ICON  $capacity%"
    "
    cat /sys/class/power_supply/BAT0/capacity
}

get_netspeed(){}

get_language(){
    setxkbmap -query | awk '/layout/ {print $2}'
}

get_volume() {
    curStatus=$(pactl get-sink-mute 0)
    volume=$(pactl get-sink-volume 0 | tail -n 2 | sed -e 's,.* \([0-9][0-9]*\)%.*,\1,' | head -n 1)

    if [ "${curStatus}" = 'Mute: yes' ]
    then
        echo " $volume%"
    else
        echo " $volume%"
    fi
}

while true
do
    xsetroot -name "$(get_date)    [$(get_volume)]    [$(get_language)]    [$(get_battery)%]"
    sleep 1
done
