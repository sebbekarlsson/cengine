exec = a.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic -lglfw -lGLEW -lGL -lcglm -lpng -std=c99


libcengine.a: $(objects)
	ar rcs $@ $^

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	mkdir -p /usr/local/share/cengine/res
	cp -r ./res/* /usr/local/share/cengine/res
	make
	make libcengine.a
	mkdir -p /usr/local/include/cengine
	cp -r ./src/include/* /usr/local/include/cengine/.
	cp ./libcengine.a /usr/local/lib/.
	cp ./cengine.out /usr/local/bin/cengine

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o

lint:
	clang-tidy src/*.c src/include/*.h
