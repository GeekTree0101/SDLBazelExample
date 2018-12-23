#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <math.h> 

#include <SDL2/SDL.h> 
#include <SDL2/SDL_opengl.h> 

#define SHADED_CUBE 

static SDL_GLContext ctx; 
static SDL_Window* window; 

static void quit(int rc) 
{ 
    if (ctx) { 
        SDL_GL_DeleteContext(ctx); 
    } 
    SDL_DestroyWindow( window ); 
    SDL_Quit(); 
    exit(rc); 
} 

static void renderCube() 
{ 
    static float color[8][3] = { 
        {1.0, 1.0, 0.0}, 
        {1.0, 0.0, 0.0}, 
        {0.0, 0.0, 0.0}, 
        {0.0, 1.0, 0.0}, 
        {0.0, 1.0, 1.0}, 
        {1.0, 1.0, 1.0}, 
        {1.0, 0.0, 1.0}, 
        {0.0, 0.0, 1.0} 
    }; 
    static float cube[8][3] = { 
        {0.5, 0.5, -0.5}, 
        {0.5, -0.5, -0.5}, 
        {-0.5, -0.5, -0.5}, 
        {-0.5, 0.5, -0.5}, 
        {-0.5, 0.5, 0.5}, 
        {0.5, 0.5, 0.5}, 
        {0.5, -0.5, 0.5}, 
        {-0.5, -0.5, 0.5} 
    }; 
    
    /* Do our drawing, too. */ 
    glClearColor(0.0, 0.0, 0.0, 1.0); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    
    glBegin(GL_QUADS); 
    
#ifdef SHADED_CUBE 
    glColor3fv(color[0]); 
    glVertex3fv(cube[0]); 
    glColor3fv(color[1]); 
    glVertex3fv(cube[1]); 
    glColor3fv(color[2]); 
    glVertex3fv(cube[2]); 
    glColor3fv(color[3]); 
    glVertex3fv(cube[3]); 
    
    glColor3fv(color[3]); 
    glVertex3fv(cube[3]); 
    glColor3fv(color[4]); 
    glVertex3fv(cube[4]); 
    glColor3fv(color[7]); 
    glVertex3fv(cube[7]); 
    glColor3fv(color[2]); 
    glVertex3fv(cube[2]); 
    
    glColor3fv(color[0]); 
    glVertex3fv(cube[0]); 
    glColor3fv(color[5]); 
    glVertex3fv(cube[5]); 
    glColor3fv(color[6]); 
    glVertex3fv(cube[6]); 
    glColor3fv(color[1]); 
    glVertex3fv(cube[1]); 
    
    glColor3fv(color[5]); 
    glVertex3fv(cube[5]); 
    glColor3fv(color[4]); 
    glVertex3fv(cube[4]); 
    glColor3fv(color[7]); 
    glVertex3fv(cube[7]); 
    glColor3fv(color[6]); 
    glVertex3fv(cube[6]); 
    
    glColor3fv(color[5]); 
    glVertex3fv(cube[5]); 
    glColor3fv(color[0]); 
    glVertex3fv(cube[0]); 
    glColor3fv(color[3]); 
    glVertex3fv(cube[3]); 
    glColor3fv(color[4]); 
    glVertex3fv(cube[4]); 
    
    glColor3fv(color[6]); 
    glVertex3fv(cube[6]); 
    glColor3fv(color[1]); 
    glVertex3fv(cube[1]); 
    glColor3fv(color[2]); 
    glVertex3fv(cube[2]); 
    glColor3fv(color[7]); 
    glVertex3fv(cube[7]); 
#else /* flat cube */ 
    glColor3f(1.0, 0.0, 0.0); 
    glVertex3fv(cube[0]); 
    glVertex3fv(cube[1]); 
    glVertex3fv(cube[2]); 
    glVertex3fv(cube[3]); 
    
    glColor3f(0.0, 1.0, 0.0); 
    glVertex3fv(cube[3]); 
    glVertex3fv(cube[4]); 
    glVertex3fv(cube[7]); 
    glVertex3fv(cube[2]); 
    
    glColor3f(0.0, 0.0, 1.0); 
    glVertex3fv(cube[0]); 
    glVertex3fv(cube[5]); 
    glVertex3fv(cube[6]); 
    glVertex3fv(cube[1]); 
    
    glColor3f(0.0, 1.0, 1.0); 
    glVertex3fv(cube[5]); 
    glVertex3fv(cube[4]); 
    glVertex3fv(cube[7]); 
    glVertex3fv(cube[6]); 
    
    glColor3f(1.0, 1.0, 0.0); 
    glVertex3fv(cube[5]); 
    glVertex3fv(cube[0]); 
    glVertex3fv(cube[3]); 
    glVertex3fv(cube[4]); 
    
    glColor3f(1.0, 0.0, 1.0); 
    glVertex3fv(cube[6]); 
    glVertex3fv(cube[1]); 
    glVertex3fv(cube[2]); 
    glVertex3fv(cube[7]); 
#endif /* SHADED_CUBE */ 
    
    glEnd(); 
    
    glMatrixMode(GL_MODELVIEW); 
    glRotatef(1.0, 1.0, 1.0, 1.0); 
} 
int run() {
    GLint xOffset = 0;
    GLint yOffset = 0;
    int value; 
    int i, done; 
    SDL_DisplayMode mode; 
    SDL_Event event; 
    Uint32 then, now, frames; 
    int status; 

    //Initialize SDL 
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
    { 
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
        return 1; 
    } 
    
    //Create window 
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); 
    window = SDL_CreateWindow 
    ( 
     "SDL x Bazel Example", 
     SDL_WINDOWPOS_UNDEFINED,
     SDL_WINDOWPOS_UNDEFINED, 
     500,
     500, 
     SDL_WINDOW_OPENGL 
     ); 
    
    if( window == NULL ) 
    { 
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); 
        return 1; 
    } 
    
    //creating new context 
    ctx = SDL_GL_CreateContext(window); 
    SDL_GL_SetSwapInterval(1.0); 
    
    /* Set rendering settings */ 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0); 
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 
    glEnable(GL_DEPTH_TEST); 
    glDepthFunc(GL_LESS); 
    glShadeModel(GL_SMOOTH); 
    
    /* Main render loop */ 
    frames = 0; 
    then = SDL_GetTicks(); 
    done = 0; 
    while (!done) { 
        /* Check for events */ 
        ++frames;

        SDL_Event ev; 
        while( SDL_PollEvent( &ev ) ) 
        { 
            if( ( SDL_QUIT == ev.type ) || 
               ( SDL_KEYDOWN == ev.type && SDLK_ESCAPE == ev.key.keysym.sym ) ) 
            { 
              quit(0);
            } 

            if ( SDL_KEYDOWN == ev.type && SDLK_DOWN == ev.key.keysym.sym ) {
              yOffset -= 20;
            }

            if ( SDL_KEYDOWN == ev.type && SDLK_UP == ev.key.keysym.sym ) {
              yOffset += 20;
            }

            if ( SDL_KEYDOWN == ev.type && SDLK_LEFT == ev.key.keysym.sym ) {
              xOffset -= 20;
            }

            if ( SDL_KEYDOWN == ev.type && SDLK_RIGHT == ev.key.keysym.sym ) {
              xOffset += 20;
            }
        } 
        int w, h; 
        SDL_GL_MakeCurrent(window, ctx); 
        SDL_GetWindowSize(window, &w, &h); 
        glViewport(xOffset, yOffset, w, h); 
        renderCube(); 
        SDL_GL_SwapWindow(window); 
    } 
    
    quit(0); 
    return 0; 
}
