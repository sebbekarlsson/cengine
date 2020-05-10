exec = a.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = `pkg-config --cflags cengine`
libs = `pkg-config --libs cengine`


ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif


libcengine.a: $(objects)
	ar rcs $@ $^

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@ $(libs)

install:
	install -d $(DESTDIR)$(PREFIX)/lib/
	install -d $(DESTDIR)$(PREFIX)/include/cengine
	install -d $(DESTDIR)$(PREFIX)/share/cengine/
	install -d $(DESTDIR)$(PREFIX)/share/cengine/res
	install -d $(DESTDIR)$(PREFIX)/share/pkgconfig/
	\
	cp ./cengine.pc $(DESTDIR)$(PREFIX)/share/pkgconfig/
	cp -r ./res/* $(DESTDIR)$(PREFIX)/share/cengine/res
	\
	make
	make libcengine.a
	\
	cp -r ./src/include/* $(DESTDIR)$(PREFIX)/include/cengine/.
	\
	install -m 644 ./libcengine.a $(DESTDIR)$(PREFIX)/lib/.
	\
	./install_generator.sh

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o

lint:
	clang-tidy src/*.c src/include/*.h
