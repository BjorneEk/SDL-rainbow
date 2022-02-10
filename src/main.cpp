
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include <sdl/SDL.h>
#include <iostream>
#include <math.h>

#define WIDTH  2500
#define HEIGHT 1400

#define HW 1250
#define HH 700


using namespace std;

SDL_Window   * window   = NULL;
SDL_Renderer * renderer = NULL;

typedef struct color {
	float r;
	float g;
	float b;
} color_t;

float offset = 0.0f;

color_t from_angle3(float a, float off)
{
	return (color_t) {
		.r    = (abs(tan(0.3f * (a + off)       )) * 255.0),
		.g    = (abs(tan(0.3f * (a + off) + 2.0f)) * 255.0),
		.b    = (abs(tan(0.3f * (a + off) + 4.0f)) * 255.0)
	};
}

color_t from_angle2(float a, float off)
{
	return (color_t) {
		.r    = (sqrt(abs(sin(0.3f * (a + off)       ))) * 255.0),
		.g    = (sqrt(abs(sin(0.3f * (a + off) + 2.0f))) * 255.0),
		.b    = (sqrt(abs(sin(0.3f * (a + off) + 4.0f))) * 255.0)
	};
}

color_t from_angle(float a, float off)
{
	return (color_t) {
		.r    = (abs(sin(0.3f * (a + off) + 0.0f))*abs(sin(0.3f * (a + off) + 0.0f)) * 255.0),
		.g    = (abs(sin(0.3f * (a + off) + 2.0f))*abs(sin(0.3f * (a + off) + 2.0f)) * 255.0),
		.b    = (abs(sin(0.3f * (a + off) + 4.0f))*abs(sin(0.3f * (a + off) + 4.0f)) * 255.0)
	};
}

void init_window()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);

	if(window == NULL)
	{
		fprintf(stderr, "Failed to initialize SDL2 window\n");
		return;
	}
	SDL_SetWindowTitle(window, "raytracer");
}

void event_loop(SDL_Event * event)
{
int running = 1;
int paused = 0;
while (running)
{
	if (!paused)
	{
		for (size_t i = 0; i < WIDTH; i+=2)
		{
			for (size_t j = 0; j < HEIGHT; j+=2)
			{
				color_t c = from_angle3((((float) pow(((float)HW-abs(i-((float)HW))), 4)*
												  pow(((float)HH-abs(j-((float)HH))), 3)
												  /(float)(pow(offset, 8)))), offset);
				float dist = sqrt(abs( (((float)HW - i) * ((float)WIDTH/2.0 - i)) + (((float)HH - j) * ((float)HH - j)) ))/((float)HH);
				if (dist > 1.0) dist = 1.0;
				SDL_SetRenderDrawColor(renderer, c.r*dist, c.g*dist, c.b*dist, 0);
				//SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 0);
				SDL_Rect bg = (SDL_Rect){.y=j,.x=i,.h=2,.w=2};
				SDL_RenderFillRect(renderer, &bg);
			}
		}
		SDL_RenderPresent(renderer);
		offset += 0.5;
		if (offset > (float)31415926.5) {
			offset = 0;
		}
	}

	while ( SDL_PollEvent( event ) )
	{
		switch ( (*event).type )
		{
			case SDL_QUIT: running = 0; break;
			case SDL_KEYDOWN:
				if ((*event).key.keysym.scancode == 0x2C) paused = !paused;
				break;
		}
	}
}
}

int main(int argc, char const *argv[])
{
	SDL_Event event;

	init_window();
	event_loop(&event);


	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);

	return 0;
}
