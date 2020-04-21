exec = a.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = `pkg-config --cflags cengine`
libs = `pkg-config --libs cengine`


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec) $(libs)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@ $(libs)

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o
