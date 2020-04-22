# Game Engine Framework for C
> A simple Game Engine framework,  
> to make games with in C.

## Running the example
> To run the example game:
```bash
./run_example.sh 2dvoxel
```

## Creating an application
> Here is all you need to create a scene, with a banana drawn in the center:
```C
#include <cengine/main.h>
#include <cengine/application.h>


extern application_T* APP;


scene_T* init_main_scene()
{
    scene_T* scene = init_scene();

    texture_T* texture = texture_get("res/banana.png");

    actor_T* actor = init_actor(
        (APP->width / 2) - texture->width / 2,
        (APP->height / 2) - texture->height / 2,
        0
    );

    actor->sprite = init_sprite_with_texture(texture);

    scene_add_actor(scene, actor);

    return scene;
}


int main(int argc, char* argv[])
{
    APP = init_application(640, 480, "App"); 

    application_add_scene(APP, init_main_scene());

    return cengine_main(argc, argv);
}
```
> It can be compiled using this Makefile:
```make
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
```
