#include<SDL.h>
#include<SDL_image.h>
#include<iostream>

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		// Create a texture from an existing surface
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}

// zmiana animacji przy zmianie kierunku ruchu ludzika
void Tyl(SDL_Rect& playerRect, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = 0;
	playerRect.y = (textureHeight / 4) * 3;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

void Prawo(SDL_Rect& playerRect, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = 0;
	playerRect.y = (textureHeight / 4) * 2;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

void Lewo(SDL_Rect& playerRect, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = 0;
	playerRect.y = (textureHeight / 4) * 1;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

void Przod(SDL_Rect& playerRect, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = 0;
	playerRect.y = (textureHeight / 4) * 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

//zatrzymanie siê animacji ludzika

void TylStop(SDL_Rect& playerRect, int textureWidth, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = (textureWidth / 3) * 1;
	playerRect.y = (textureHeight / 4) * 3;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

void PrawoStop(SDL_Rect& playerRect, int textureWidth, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = (textureWidth / 3) * 1;
	playerRect.y = (textureHeight / 4) * 2;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

void LewoStop(SDL_Rect& playerRect, int textureWidth, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = (textureWidth / 3) * 1;
	playerRect.y = (textureHeight / 4) * 1;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

void PrzodStop(SDL_Rect& playerRect, int textureWidth, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = (textureWidth / 3) * 1;
	playerRect.y = (textureHeight / 4) * 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}



int main(int argc, char* argv[])
{
	// Initializing and loading variables
	SDL_Window* window = nullptr;
	SDL_Texture* currentImage = nullptr;
	SDL_Texture* currentImage1 = nullptr;
	// black box
	SDL_Texture* blackBoxImage = nullptr;
	SDL_Renderer* renderTarget = nullptr;
	SDL_Rect playerRect;
	// black box rectangle
	SDL_Rect blackBoxRect;
	blackBoxRect.x = 0;
	blackBoxRect.y = 0;
	blackBoxRect.w = 100;
	blackBoxRect.h = 100;
	
	// position of the player
	SDL_Rect playerPosition;
	playerPosition.x = playerPosition.y = 0;
	playerPosition.w = playerPosition.h = 32;
	int frameWidth, frameHeight;
	int textureWidth, textureHeight;
	// player frame counter
	int frameTime = 0;
	// time of exposition of the player's frame
	// (speed of player's animation)
	const int PLAYER_ANIMATION_SPEED = 15;
	// player coordinates 
	int x = 0;
	int y = 0;
	// black box position
	SDL_Rect blackBoxPosition;
	blackBoxPosition.x = 100;
	blackBoxPosition.y = 100;
	blackBoxPosition.w = 100;
	blackBoxPosition.h = 100;

	SDL_Init(SDL_INIT_VIDEO);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(imgFlags) != imgFlags)
		std::cout << "Error: " << IMG_GetError() << std::endl;

	// Create a window with the specified position, dimensions, and flags.
	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	// Create a 2D rendering context for a window.
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// Create a texture from an existing surface (image)
	currentImage = LoadTexture("sprite-sheet.png", renderTarget);
	currentImage1 = LoadTexture("tlo.png", renderTarget);
	blackBoxImage = LoadTexture("blackBox.png", renderTarget);

	// gets textureWidth and textureHeight from texture of the player	
	SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight);

	// wycinamy fragment z pliku z animacjami ludzika sprite-sheet.png: 3 obazki  x 4 obrazki
	// w zależności od tego który fragment weźmiemy ludzik chodzi w prawo, lewo, do przodu, do tyłu

	// gets dimensions of the player's frame from player's texture
	frameWidth = textureWidth / 3;
	frameHeight = textureHeight / 4;

	// Set the color used for drawing operations (Rect, Line and Clear)
	//SDL_SetRenderDrawColor(renderTarget, 0xFF, 0, 0, 0xFF);

	bool isRunning = true;
	SDL_Event ev;

	// game loop
	while (isRunning)
	{
		// event loop
		while (SDL_PollEvent(&ev) != 0)
		{
			// Getting the events
			//
			// event of pressing the cross
			if (ev.type == SDL_QUIT)
				isRunning = false;

			// player's move by keyboard
			else if (ev.type == SDL_KEYDOWN)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_RIGHT:
					Prawo(playerRect, textureHeight, frameWidth, frameHeight);
					x += 10;
					if (x > 630)
						x = -20;
					break;

				case SDLK_LEFT:
					Lewo(playerRect, textureHeight, frameWidth, frameHeight);
					x -= 10;
					if (x < -25)
						x = 630;
					break;

				case SDLK_UP:
					Tyl(playerRect, textureHeight, frameWidth, frameHeight);
					y -= 10;
					if (y < -37)
						y = 470;
					break;

				case SDLK_DOWN:
					Przod(playerRect, textureHeight, frameWidth, frameHeight);
					y += 10;
					if (y > 475)
						y = -25;
					break;
				}
			}

			// player's stop
			else if (ev.type == SDL_KEYUP)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_RIGHT:
					PrawoStop(playerRect, textureWidth, textureHeight, frameWidth, frameHeight);

					break;

				case SDLK_LEFT:
					LewoStop(playerRect, textureWidth, textureHeight, frameWidth, frameHeight);
					x -= 0;
					break;

				case SDLK_UP:
					TylStop(playerRect, textureWidth, textureHeight, frameWidth, frameHeight);
					y -= 0;
					break;

				case SDLK_DOWN:
					PrzodStop(playerRect, textureWidth, textureHeight, frameWidth, frameHeight);
					y += 0;
					break;
				}
			}

		}

		// inkrementing frame counter 
		frameTime++;

		// changing frame of animation
		if (frameTime >= PLAYER_ANIMATION_SPEED)
		{
			// reset frame counter
			frameTime = 0;
			// next frame of animation
			playerRect.x += frameWidth;
			// we can't go out of texture
			// so we reset animation's position
			if (playerRect.x >= textureWidth)
				// first frame of animation
				playerRect.x = 0;
		}

		// wpółrzędne kwadratu (blackBoxa)
		int x1 = 100;
		int x2 = 200;
		int y1 = 100;
		int y2 = 200;
		bool left = (x > x1) && (y > y1) && (y < y2);
		bool right = (x < x2) && (y > y1) && (y < y2);
		bool up = (y > y1) && (x > x1) && (x < x2);
		bool down = (y < y2) && (x > x1) && (x < x2);
		
		// jeśli dotkniesz blackBoxa wracasz do poczatku
		if (left && right && up && down) {
			x = 10;
			y = 10;
		}

		// update player's position
		playerPosition.x = x;
		playerPosition.y = y;

		// Clear the current rendering target with the drawing color
		//SDL_RenderClear(renderTarget);

		// Copy a portion of the texture to the current rendering target
		// in this case copy background image
		SDL_RenderCopy(renderTarget, currentImage1, NULL, NULL);
		// add blackBox
		SDL_RenderCopy(renderTarget, blackBoxImage, &blackBoxRect, &blackBoxPosition);
		//SDL_RenderCopy(renderTarget, currentImage2, NULL, &blackBoxRect);
		// copy playerRect to target at playerPosition
		SDL_RenderCopy(renderTarget, currentImage, &playerRect, &playerPosition);


		// Update the screen with any rendering performed since the previous call
		SDL_RenderPresent(renderTarget);
	}

	// clean
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(currentImage);
	SDL_DestroyRenderer(renderTarget);
	window = nullptr;
	currentImage = nullptr;
	renderTarget = nullptr;

	SDL_Quit();

	return 0;
}

