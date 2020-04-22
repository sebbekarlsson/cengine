exec = a.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = `pkg-config --cflags cengine`
libs = `pkg-config --libs cengine`


%.o: %.c
	gcc -c $(flags) $< -o $@ $(libs)

$(exec): main.o
	gcc main.c $(flags) -o $(exec) $(libs)

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o
