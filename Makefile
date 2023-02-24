CC	:= gcc
exec 	:= LK14
sources := $(wildcard src/*.c)
objects := $(sources:.c=.o)
flags 	:= -g -Wall

$(exec): $(objects)
	$(CC) $(objects) -o $(exec)

%.o: %.c include/%.h
	$(CC) -c $(floags) $< -o $@

install:
	make
	cp ./$(exec) /usr/local/bin/silverboss

clean:
	-rm $(exec)
	-rm *.o
	-rm src/*o
