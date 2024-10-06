if [ -z "$1" ]; then
    printf "Missing the sleep duration parameter"
    exit 1
fi

X=0
Y=0

while read -r -N 1 char; do
    encoded_char=$(printf "%s" "$char" | hexdump --format '"%x"')
    if [ "$encoded_char" = 'a' ]; then
        X=0
        Y=$((Y+1))
    elif [ "$encoded_char" = "20" ]; then
        X=$((X+1))
    else
        coords="$X $Y $encoded_char
$coords"
        X=$((X+1))
    fi
done

shuffled_lines=$(shuf <<< "${coords::-1}")

tput clear

while IFS=' ' read -r cur_x cur_y ch; do
    sleep "$1"
    # ch=$(iconv -f UCS2 -t UTF-8 <<< "$ch")
    tput cup "$cur_y" "$cur_x"
    printf "\x$ch"
done <<< "$shuffled_lines"

last_line=$(stty size < /dev/tty)

tput cup $(read x y <<< $last_line; printf "%s" $((x-2))) 0
