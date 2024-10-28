CFLAGS = -fPIC
all: move

test_files/protect.so: test_files/protect.c
	$(CC) $^ -o $@ -shared

test: test_files/protect.so move
	LD_PRELOAD=`pwd`/test_files/protect.so ./move test_files/source_PROTECT test_files/destination
