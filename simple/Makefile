CC=riscv64-unknown-elf-gcc
RISCV=/home/bwilliams/xbgas-tools
SRCS= $(wildcard *.c)
OBJS = $(SRCS:.c=.exe)
CFLAGS = -std=c11 -I$(RISCV)/include -L$(RISCV)/lib/
LIBS = -lxbrtime -lm


all: $(OBJS)

%.exe:%.c
	$(CC) $(CFLAGS) -o $@ $^  $(LIBS)

clean:
	rm -f ./*.o ./*.exe
