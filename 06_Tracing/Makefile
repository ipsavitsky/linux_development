CFLAGS = -fPIC
all: move

test_files/protect.so: test_files/protect.c
	$(CC) $^ -o $@ -shared

test_preload: test_files/protect.so move
	LD_PRELOAD=`pwd`/test_files/protect.so ./move test_files/source_PROTECT test_files/destination

test: move
	-strace -e openat -P test_files/source -e fault=openat:error=EPERM:when=1 ./$^ test_files/source test_files/destination
	-strace -e openat -P test_files/destination -e fault=openat:error=EPERM:when=1 ./$^ test_files/source test_files/destination
