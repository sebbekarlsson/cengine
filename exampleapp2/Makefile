exec = a.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic -lglfw -lGLEW -lGL -lcglm -lpng -I/usr/local/include/freetype2 -I/usr/include/freetype2 -lfreetype -lcengine -std=c99


$(exec): main.o
	gcc main.c $(flags) -o $(exec)

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o
