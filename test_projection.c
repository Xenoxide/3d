// Modified version of ../SDL2/10_drawing_lines.c
#include <SDL2/SDL.h>

// cube.h includes all the required libraries, and matrix.h
#include "cube.h"

#define NO_FLAGS 0
#define WIDTH 640
#define HEIGHT 480
#define INC 0.03

// To shift stuff into the middle instead of being in the top left corner.
// This also resolves the issue with negative numbers.
void debug_draw_line(SDL_Renderer * _renderer, int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
    // printf("Drew line from (%d, %d) to (%d, %d)\n", x1, y1, x2, y2); debug code

}

float dx(float x)
{
    return WIDTH/2 + x;
}

float dy(float y)
{
    return HEIGHT/2 + y;
}

int main(void)
{
    struct mousepos {
        int x;
        int y;
    } mousePos;

    int quit = 0;
    int leftMouseButtonDown;


    SDL_Event event;

    VECTOR angles = (VECTOR) {{0, 0, 0}};
    VECTOR displacement = (VECTOR) {{0, 0, 1}};
    VECTOR camera = (VECTOR) {{0, 0, -1}};
    VECTOR camera_orientation = (VECTOR) {{0, 0, 0}};
    VECTOR display_surface = (VECTOR) {{0, 0, -4}};

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("cube moment",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, NO_FLAGS);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, NO_FLAGS);
 
    // handle events
    while (!quit)
    {
        SDL_PollEvent(&event);
 
        switch (event.type)
        {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_q: angles.m[0] += INC; break;
                    case SDLK_a: angles.m[0] -= INC; break;
                    case SDLK_w: angles.m[1] += INC; break;
                    case SDLK_s: angles.m[1] -= INC; break;
                    case SDLK_e: angles.m[2] += INC; break;
                    case SDLK_d: angles.m[2] -= INC; break;
                }
            break;
            case SDL_MOUSEMOTION:
                {
                    

                    if (leftMouseButtonDown)
                    {
                        if (mousePos.x < event.motion.x)
                            camera_orientation.m[0] -= INC;
                        else if (mousePos.x > event.motion.x)
                            camera_orientation.m[0] += INC;
                        if (mousePos.y < event.motion.y)
                            camera_orientation.m[1] -= INC;
                        else if (mousePos.y > event.motion.y)
                            camera_orientation.m[1] += INC;
                        mousePos.x = event.motion.x;
                        mousePos.y = event.motion.y;
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT)
                {
                    leftMouseButtonDown = 0;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (!leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT)
                {
                    leftMouseButtonDown = 1;
                }
            break;
        }
 
        // clear window
        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);
 
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        VECTOR_2 points[CUBE_NUM_lines];
        int i;
        for (i = 0; i < CUBE_NUM_points; i++)
        {
            MATRIX_FULL_TRANSFORM(CUBE_points[i], angles, displacement, &points[i]);
            // printf("%d: Created point (%f, %f)\n", i, points[i].m[0], points[i].m[1]); debug
        }
        for (i = 0; i < CUBE_NUM_points; i++)
        {
            SDL_RenderDrawPoint(renderer, dx(points[i].m[0]) * 100, dy(points[i].m[1]) * 100);
        }

        for (i = 0; i < CUBE_NUM_lines; i++)
        {
            debug_draw_line(renderer, 
                dx(points[CUBE_lines[i].m[0]].m[0] * 100),
                dy(points[CUBE_lines[i].m[0]].m[1] * 100),
                dx(points[CUBE_lines[i].m[1]].m[0] * 100),
                dy(points[CUBE_lines[i].m[1]].m[1] * 100)
            );
            printf("%d: Drew the line from (%f, %f) to (%f, %f).\n", i, dx(points[CUBE_lines[i].m[0]].m[0] * 100),
                dy(points[CUBE_lines[i].m[0]].m[1] * 100),
                dx(points[CUBE_lines[i].m[1]].m[0] * 100),
                dy(points[CUBE_lines[i].m[1]].m[1] * 100));
        }
        SDL_RenderPresent(renderer);
        }
    
    // cleanup memory
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
 
    return 0;
}