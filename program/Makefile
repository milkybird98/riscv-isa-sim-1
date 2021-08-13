CROSS_COMPILE=riscv64-unknown-elf-
CC=$(CROSS_COMPILE)gcc
CFLAGS=-c -nostdlib -march=rv64g
LD=$(CROSS_COMPILE)ld
LDFLAGS=-Tlinker.ld -melf64lriscv
SPIKE=spike

run: all
	$(SPIKE) -d --isa=rv64gh test.out

all: clean page_table.o init.o csr.o end.o
	$(LD) $(LDFLAGS) -o test.out init.o csr.o end.o page_table.o

page_table.o: page_table.c
	$(CC) $(CFLAGS) page_table.c -o page_table.o

init.o: init.s
	$(CC) $(CFLAGS) init.s -o init.o

csr.o: csr.c
	$(CC) $(CFLAGS) csr.c -o csr.o

end.o: end.c
	$(CC) $(CFLAGS) end.c -o end.o

clean:
	rm -f *.o
	rm -f *.out