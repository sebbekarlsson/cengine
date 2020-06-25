exec = a.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = `pkg-config --cflags cengine`
libs = `pkg-config --libs cengine`


$(exec): $(objects)
	gcc $(objects) $(flags) $(libs) -o $(exec) 

%.o: %.c include/%.h
	gcc -c $(flags) $< $(libs) -o $@

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o
