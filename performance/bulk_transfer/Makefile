CC=$(RVCC)
SRCS= $(wildcard *.c)
OBJS = $(SRCS:.c=.exe)
REV_FLAGS = -march=rv64gc_zifencei -mcmodel=medany -static -std=gnu11 -fno-common -fno-builtin-printf -w
CFLAGS = -I$(REV)/common/syscalls -I$(XBGAS_RUNTIME)/include -L$(XBGAS_RUNTIME)/lib/
LIBS = -lxbrtime -lm


all: $(OBJS)

%.exe:%.c
	$(CC) $(REV_FLAGS) $(CFLAGS) -o $@ $^  $(LIBS)
	
clean:
	rm -f ./*.o ./*.exe