.PHONY: clean distclean
TRASH = *.o *~ o.* *.log
GENERATES = prog-a prog prog-so liboutput_static.a liboutput.so
CFLAGS = -fPIC

all: prog prog-a prog-so

fun.o prog.o:  outlib.h

liboutput_static.a: liboutput_static.a(const.o fun.o)

liboutput.so: fun.o const.o
	$(CC) $^ -o $@ -shared

prog-a: prog.o liboutput_static.a
	$(CC) $^ -o $@

prog-so: prog.o liboutput.so
	$(CC) $< -L. -loutput -o $@

prog:   prog.o const.o fun.o

test: prog-a prog-so prog
	./prog > prog.log 2>&1
	./prog-a > prog-a.log 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > prog-so.log 2>&1

	./prog a >> prog.log
	./prog-a a >> prog-a.log
	LD_LIBRARY_PATH=`pwd` ./prog-so a >> prog-so.log

	./prog a b c >> prog.log
	./prog-a a b c >> prog-a.log
	LD_LIBRARY_PATH=`pwd` ./prog-so a b c >> prog-so.log

	diff prog.log prog-a.log
	diff prog-a.log prog-so.log

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)
