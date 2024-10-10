TRASH = *.o test*
CFLAGS = -O0 -g
LDFLAGS = -g

range: range.o

.PHONY: clean

test: range
	gdb -x test1.gdb ./range --batch | grep "out>" | sed "s/out>//" > test1
	gdb -x test2.gdb ./range --batch | grep "out>" | sed "s/out>//" > test2
	diff test1 out1
	diff test2 out2

clean:
	rm -f $(TRASH) range
