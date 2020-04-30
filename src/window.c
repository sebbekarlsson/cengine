#include "include/window.h"
#include "include/application.h"
#include <stdio.h>
#include <stdlib.h>


extern application_T* APP;


static void window_error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

window_T* init_window(int width, int height, const char* title)
{
    window_T* w = calloc(1, sizeof(struct WINDOW_STRUCT));
    w->width = width;
    w->height = height;

    glfwSetErrorCallback(window_error_callback);
 
    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_FLOATING, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
 
    w->window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!w->window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    window_recalc(w, width, height);
 
    glfwSetKeyCallback(w->window, window_key_callback);
    glfwSetFramebufferSizeCallback(w->window, framebuffer_size_callback);
 
    glfwMakeContextCurrent(w->window);
    
    GLenum err = glewInit();

    if (GLEW_OK != err)
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));


    glViewport(0, 0, w->width, w->height);

    glfwSwapInterval(1);

    return w;
}

void window_recalc(window_T* window, int width, int height)
{
    window->width = width;
    window->height = height;
    window->blit_w = window->height * ((float)RES_WIDTH) / ((float)RES_HEIGHT);
    window->blit_h = window->height;
    window->blit_start_x = (window->width / 2) - (window->blit_w / 2);
    window->blit_start_y = 0;

    printf("width: %d\n", window->width);
    printf("height: %d\n", window->height);
    printf("window_blit_w: %d\n", window->blit_w);
    printf("window_blit_h: %d\n", window->blit_h);
    printf("window_blit_start_x: %d\n", window->blit_start_x);
    printf("window_blit_start_y: %d\n", window->blit_start_y);
}

/**
 * Called when the window is resized.
 *
 * @param GLFWwindow* window
 * @param int width
 * @param int height
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    window_recalc(APP->window, width, height);
    // glViewport((width / 2) - (WINDOW_WIDTH / 2), (height / 2) - (WINDOW_HEIGHT / 2), 640, 480);
}

unsigned int window_generate_framebuffer()
{
    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
    GLuint FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

    // The texture we're going to render to
    GLuint renderedTexture;
    glGenTextures(1, &renderedTexture);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, renderedTexture);

    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, RES_WIDTH, RES_HEIGHT, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // The depth buffer
    GLuint depthrenderbuffer;
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, RES_WIDTH, RES_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Could not create framebuffer.\n");
        exit(1);
    }

    return FramebufferName;
}

double window_mouse_get_x()
{
    double xpos, ypos;
    glfwGetCursorPos(APP->window->window, &xpos, &ypos);

    return xpos;
}

double window_mouse_get_y()
{
    double xpos, ypos;
    glfwGetCursorPos(APP->window->window, &xpos, &ypos);

    return ypos;
}
