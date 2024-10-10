set pagination off

# find a better way to set this breakpoint other than line number
break 6

ignore 1 27

set $i = 0

command 1
    while $i < 8
        echo out>
        printf "start=%d stop=%d step=%d i=%d\n", start, stop, step, i
        set $i = $i + 1
        continue
    end
end

run -100 100 3 > /dev/null
quit
