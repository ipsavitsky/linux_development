set pagination off

# find a better way to set this breakpoint other than line number
break 6 if i % 5 == 0

command 1
    printf "start=%d stop=%d step=%d i=%d\n", start, stop, step, i
    continue
end

run 1 12
quit
