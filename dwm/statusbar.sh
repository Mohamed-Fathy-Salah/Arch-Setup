#!/bin/zsh

get_date() {
    date="$(LC_ALL=C date "+%a %d %b")"
    echo -ne "  ${date} "
}

get_time() {
    time="$(date "+%I:%M %p")"
    echo -ne "  ${time} "
}

get_wifi() {
    wifiperc="$(grep "^\s*w" /proc/net/wireless | awk '{ print int($3 * 100 / 70) "%" }')"
    echo -ne "  ${wifiperc}"
}

get_language(){
    case "$(xset -q|grep LED| awk '{ print $10 }')" in
        "00000000") echo -ne "en" ;;
        "00001004") echo -ne "ar" ;;
        *) echo -ne "un" ;;
    esac
}

get_volume() {
    curStatus=$(pactl get-sink-mute 0)
    volume=$(pactl get-sink-volume 0 | tail -n 2 | sed -e 's,.* \([0-9][0-9]*\)%.*,\1,' | head -n 1)

    if [ "${curStatus}" = 'Mute: yes' ]
    then
        echo -ne " $volume%"
    else
        echo -ne " $volume%"
    fi
}

while true
do
    BAT=$(cat /sys/class/power_supply/BAT0/capacity)
    MEM=$(free -h --kilo | awk '/^Mem:/ {print $3 "/" $2}')
    CPU=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1}' )
    TEMP=$(sensors|grep 'Core 0'|awk '{print $3}' )

    xsetroot -name "$(get_date)  |  $(get_time)  |  $(get_volume)  |     $MEM  |    $CPU%  |    $TEMP  |  $(get_language)  |  $(get_wifi)  |  $BAT% "
    sleep 2
done
