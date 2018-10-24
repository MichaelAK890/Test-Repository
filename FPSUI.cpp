#include "FPSUI.h"
#include "Body.h"
#include <SDL.h>

FPSUI::FPSUI() {

}

FPSUI::~FPSUI() {
}

bool FPSUI::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
												//the window screen size
	/*projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);*/
	// the bodies are the images with there x & y position for where they would appeare on the UI
	bodies[0] = new Body("Health.bmp", Vec3(0.0f, 16.0f, 0.0f));
	bodies[1] = new Body("crosshair.bmp", Vec3(12.1f, 10.5f, 0.0f));
	bodies[2] = new Body("FPSmap.bmp", Vec3(0.0f, 5.5f, 0.0f));
	for (int i = 0; i < 2; i++)
		if (bodies[i] == nullptr) {
			return false;
		}
	return true;
}

void FPSUI::OnDestroy() {

}

void FPSUI::Update(const float time) {

	SDL_Event UIchanger;
	bool SelectedUI = true;

	while (SelectedUI == true)
	{
		if (SDL_PollEvent(&UIchanger))
		{
			if (SDL_KEYDOWN)
			{

				if (UIchanger.key.keysym.sym == SDLK_1)
				{

					Createdui->OnDestroy();
					Createdui = new FPSUI();
					Createdui->OnCreate();
				}
			}
		}
	}

}
// the render function gets the location on the screen for eace image 
void FPSUI::Render(SDL_Surface * Surface) {

	Vec3 screenCoords = /*projectionMatrix **/ bodies[0]->pos;
	Vec3 screenCoords2 = /*projectionMatrix **/ bodies[1]->pos;
	Vec3 screenCoords3 = /*projectionMatrix **/ bodies[2]->pos;

	SDL_Rect imageRectangle;
	imageRectangle.h = bodies[0]->getImage()->h;
	imageRectangle.w = bodies[0]->getImage()->w;
	imageRectangle.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
	imageRectangle.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning

	SDL_Rect imageRectangle2;
	imageRectangle2.h = bodies[1]->getImage()->h;
	imageRectangle2.w = bodies[1]->getImage()->w;
	imageRectangle2.x = screenCoords2.x; /// implicit type conversions BAD - probably causes a compiler warning
	imageRectangle2.y = screenCoords2.y; /// implicit type conversions BAD - probably causes a compiler warning

	SDL_Rect imageRectangle3;
	imageRectangle3.h = bodies[2]->getImage()->h;
	imageRectangle3.w = bodies[2]->getImage()->w;
	imageRectangle3.x = screenCoords3.x; /// implicit type conversions BAD - probably causes a compiler warning
	imageRectangle3.y = screenCoords3.y; /// implicit type conversions BAD - probably causes a compiler warning

	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
	SDL_BlitSurface(bodies[0]->getImage(), nullptr, screenSurface, &imageRectangle);
	SDL_BlitSurface(bodies[1]->getImage(), nullptr, screenSurface, &imageRectangle2);
	SDL_BlitSurface(bodies[2]->getImage(), nullptr, screenSurface, &imageRectangle3);
	SDL_UpdateWindowSurface(window);

}
