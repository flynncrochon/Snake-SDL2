// Flynn crochon
//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();
//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;
int dirx = 0;
int diry = 0;
int actdirx = 1;
int actdiry = 0;
bool inputflag = false;
bool inputflag2 = true;
int posx = 100;
int posy = 100;
int gridposx;
int gridposy;
int candyx = 200;
int candyy = 200;
int snakelength = 1;
int gameSpeed = 5;
int randomFoodPosition; 
int freeSpace[50][30] = { 0 };
std::vector<int>freespacex;
std::vector<int>freespacey;
int freespacecount = 0;
int headvert = 20;
int headhor = 20;
int tailvert = 20;
int tailhor = 20;
int headtailx = 20;
int headtaily = 20;
int bodyvert = 20;
int bodyhor = 20;
int offcentx = 1;
int offcenty = 1;
int snakeIncrement = 1;;
int previousSnakeLength;
int lifeCounter =1;
bool pauseGame = true;
int pausegameCount = 1;
std::vector<int>hororver;
std::vector<int>hororver2;
std::vector<int>snakexx;
std::vector<int>snakeyy;
std::vector<int>bodysnakexx;
std::vector<int>bodysnakeyy;
bool init() {
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}
		//Create window
		gWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}
bool loadMedia() {
	//Loading success flag
	bool success = true;
	//Nothing to load
	return success;
}
void close() {
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
SDL_Texture* loadTexture(std::string path) {
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
int main(int argc, char* args[]) {
	const int FPS = 60;
	int frameDelay = 300 / FPS;
	Uint32 frameStart;
	int frameTime;
	for (int i = 0; i < 50; i++) {
		snakexx.push_back(0);
		snakeyy.push_back(0);
		bodysnakexx.push_back(0);
		bodysnakeyy.push_back(0);
		hororver.push_back(0);
		hororver2.push_back(0);
		freespacex.push_back(0);
		freespacey.push_back(0);
	}
	//Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		//Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			//Main loop flag
			bool quit = false;
			//Event handler
			SDL_Event e;
			//While application is running
			while (!quit) { // -------------------------------------------------------------------=====================================---------------------- >>>>>>>>>>>>>>
				frameStart = SDL_GetTicks();
				/*
				while (SDL_PollEvent(&e != 0)) {

				}
				*/
				SDL_PollEvent(&e);
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				if (e.type == SDL_KEYDOWN) {
					if (inputflag2) {
						switch (e.key.keysym.sym) {
							// KEYPAD  =================================================================================================
						case SDLK_UP:
							if (diry != -1 & diry != 1) {
								diry = -1;
								dirx = 0;
								inputflag = true;
							}
							break;
						case SDLK_DOWN:
							if (diry != 1 & diry != -1) {
								diry = 1;
								dirx = 0;
								inputflag = true;
							}
							break;
						case SDLK_LEFT:
							if (dirx != -1 & dirx != 1) {
								dirx = -1;
								diry = 0;
								inputflag = true;
							}
							break;
						case SDLK_RIGHT:
							if (dirx != 1 & dirx != -1) {
								dirx = 1;
								diry = 0;
								inputflag = true;
							}
							break;
							// WASD =================================================================================================
						case SDLK_F1:
							frameDelay = 200 / FPS;
							break;
						case SDLK_F2:
							frameDelay = 300 / FPS;
							break;
						case SDLK_F3:
							frameDelay = 500 / FPS;
							break;
						case SDLK_1:
							snakeIncrement = 1;
							break;
						case SDLK_2:
							snakeIncrement = 2;
							break;
						case SDLK_3:
							snakeIncrement = 3;
							break;
						case SDLK_4:
							snakeIncrement = 4;
							break;
						case SDLK_5:
							snakeIncrement = 5;
							break;
						case SDLK_6:
							snakeIncrement = 6;
							break;
						case SDLK_7:
							snakeIncrement = 7;
							break;
						case SDLK_8:
							snakeIncrement = 8;
							break;
						case SDLK_9:
							snakeIncrement = 9;
							break;
						case SDLK_SPACE:
							pausegameCount = pausegameCount + 1;
							if (pausegameCount % 2 == 0) {
								pauseGame = false;
							}
							else {
								pauseGame = true;
							}
							break;
						case SDLK_p:
							snakelength = previousSnakeLength;
							lifeCounter = lifeCounter + 1;
							std::string s = "Snake || Score: " + std::to_string(snakelength) + " || Life Counter: " + std::to_string(lifeCounter);
							char const* pchar = s.c_str();
							SDL_SetWindowTitle(gWindow, pchar);
							break;
						}
					}
				}
				if (pauseGame) {

					if (inputflag) {
						inputflag2 = false;
						// this updates the direction when input has been done 
						// only for y direction, such as when diry = -1, or diry = 1;
						if (posy % 20 == 0 & actdiry != 0) {
							actdirx = dirx;
							actdiry = 0;
							inputflag = false;
							inputflag2 = true;
						}
						else if (posx % 20 == 0 & actdirx != 0) {
							actdiry = diry;
							actdirx = 0;
							inputflag = false;
							inputflag2 = true;
						}
					}
					posx = posx + actdirx;
					posy = posy + actdiry;
					if (posx == candyx & posy == candyy) { //check if snake on candy and then spawn new candy
						for (int i = 0; i < 50; i++) {
							for (int j = 0; j < 30; j++) {
								if (freeSpace[i][j] == 0) { // 1 returns full 0 returns empty 
									freespacex.push_back(i);
									freespacey.push_back(j);
									freespacecount = freespacecount + 1;
								}
							}
						}
						if (snakelength == 1) {
							lifeCounter = 1;
						}
						randomFoodPosition = rand() % freespacecount;
						candyx = 20 * freespacex[freespacex.size() - 1 - randomFoodPosition]; // returns the i value or x random coordinate of free space 
						candyy = 20 * freespacey[freespacey.size() - 1 - randomFoodPosition];
						freespacecount = 0;
						snakelength = snakelength + snakeIncrement;
						std::string s = "Snake || Score: " + std::to_string(snakelength) + " || Life Counter: " + std::to_string(lifeCounter);
						char const* pchar = s.c_str();
						SDL_SetWindowTitle(gWindow, pchar);

					}
					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
					SDL_RenderClear(gRenderer);
					if (posx % 20 == 0 & posy % 20 == 0) { //check if on grid // returns gridposx and gridposy
						gridposx = posx;
						gridposy = posy;
						bodysnakexx.push_back(posx);
						bodysnakeyy.push_back(posy);
						if (actdirx == 1) {
							hororver.push_back(4); // value 4 returns horizontal movement
							hororver2.push_back(4); // value 4 returns horizontal movement
						}
						else if (actdirx == -1) {
							hororver.push_back(8); // value 8 returns horizontal movement
							hororver2.push_back(8); // value 8 returns horizontal movement
						}
						else if (actdiry == 1) {
							hororver.push_back(3); // value 3 returns vertical movement
							hororver2.push_back(3); // value 3 returns vertical movement
						}
						else if (actdiry == -1) {
							hororver.push_back(6); // value 6 returns vertical movement
							hororver2.push_back(6); // value 6 returns vertical movement
						}
						// corner nodes yikes
						if (hororver[hororver.size() - 1] % 4 == 0 & hororver[hororver.size() - 2] % 3 == 0 || hororver[hororver.size() - 2] % 3 == 0 & hororver[hororver.size() - 1] % 4 == 0) {
							hororver[hororver.size() - 2] = 21;
						}
						if (hororver[hororver.size() - 1] % 3 == 0 & hororver[hororver.size() - 2] % 4 == 0 || hororver[hororver.size() - 2] % 4 == 0 & hororver[hororver.size() - 1] % 3 == 0) { // check corner and set body hor and body
							hororver[hororver.size() - 2] = 21;
						}
					}
					snakexx.push_back(posx);
					snakeyy.push_back(posy);
					// checking if snake head is travelling horizontal or vertical
					if (hororver[hororver.size() - 1] % 4 == 0) { //vertical movement
						headhor = 20;
						headvert = 18;
					}
					if (hororver[hororver.size() - 1] % 3 == 0) { //horizontal movement
						headhor = 18;
						headvert = 20;
					} // ===============================
					for (int i = 1; i < 30; i++) {
						SDL_Rect headtail = { snakexx[snakexx.size() - i] + 1, snakeyy[snakeyy.size() - i] + 1, 18, 18 };
						SDL_SetRenderDrawColor(gRenderer, 255, 255, 0xFF, 0xFF);
						SDL_RenderFillRect(gRenderer, &headtail);
					}
					// drawing head smoove movement
					SDL_Rect fillRect = { posx + 1, posy + 1, 18, 18 };
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderFillRect(gRenderer, &fillRect);
					//last tail 
					if (snakelength > 1) {
						for (int i = 0; i < 30; i++) {
							SDL_Rect tail = { snakexx[snakexx.size() - snakelength * 20 + i] + 1, snakeyy[snakeyy.size() - snakelength * 20 + i] + 1, 18, 18 };
							SDL_SetRenderDrawColor(gRenderer, 0xFF, 255, 0xFF, 0xFF);
							SDL_RenderFillRect(gRenderer, &tail);
						}
					}
					std::memset(freeSpace, 0, sizeof freeSpace);
					freeSpace[(bodysnakexx[bodysnakexx.size() - 1]) / 20][(bodysnakeyy[bodysnakeyy.size() - 1]) / 20] = 1;
					for (int i = 2; i < snakelength; i++) {
						if (hororver[hororver.size() - i] % 4 == 0) { //vertical movement
							bodyhor = 22;
							bodyvert = 18;
							offcentx = -1; // normal
							offcenty = 1;
						}
						if (hororver[hororver.size() - i] % 3 == 0) { //horizontal movement
							bodyhor = 18;
							bodyvert = 22;
							offcentx = 1;
							offcenty = -1; // normal
						}
						if (hororver[hororver.size() - i] == 21) { //corner nodes 
							//if (hororver[hororver.size() - i - 1] == 4 & hororver[hororver.size() - i+1] == 6) { // right up corner 
							bodyhor = 18;
							bodyvert = 18;
							offcentx = 1;
							offcenty = 1;
							// VERTICAL =============================================================================================================================
							if (hororver2[hororver2.size() - i] == 8 & (hororver2[hororver2.size() - i - 1] % 3 == 0)) {
								bodyhor = 20;
								offcentx = 1;
							}
							if (hororver2[hororver2.size() - i] == 4 & (hororver2[hororver2.size() - i - 1] % 3 == 0)) {
								bodyhor = 20;
								offcentx = -1;
							}
							// HORIZONTAL =============================================================================================================================
							if (hororver2[hororver2.size() - i] == 6 & (hororver2[hororver2.size() - i - 1] % 4 == 0)) {
								bodyvert = 20;
								offcenty = 1;
							}
							if (hororver2[hororver2.size() - i] == 3 & (hororver2[hororver2.size() - i - 1] % 4 == 0)) {
								bodyvert = 20;
								offcenty = -1;
							}
						}
						SDL_Rect fillRect = { bodysnakexx[bodysnakexx.size() - i] + (offcentx), bodysnakeyy[bodysnakeyy.size() - i] + (offcenty), bodyhor, bodyvert }; //drawing whitesquare
						SDL_SetRenderDrawColor(gRenderer, 255, 255, 0xFF, 0xFF);
						SDL_RenderFillRect(gRenderer, &fillRect);
						if (posx == (bodysnakexx[bodysnakexx.size() - i - 1]) & posy == (bodysnakeyy[bodysnakexx.size() - i - 1])) {
							previousSnakeLength = snakelength;
							snakelength = 1;
							posx = 500;
							posy = 300;
						}
						freeSpace[(bodysnakexx[bodysnakexx.size() - i]) / 20][(bodysnakeyy[bodysnakeyy.size() - i]) / 20] = 1;
					}
					if (posx < 0 || posx > 990 || posy < 0 || posy > 590) {
						previousSnakeLength = snakelength;
						snakelength = 1;
						posx = 500;
						posy = 300;
					}
					//candy
					SDL_Rect candy = { candyx + 1, candyy + 1, 18, 18 };
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
					SDL_RenderFillRect(gRenderer, &candy);
					//SDL_Delay(gameSpeed);
					//Update screen
					SDL_RenderPresent(gRenderer);
					frameTime = SDL_GetTicks() - frameStart;
					if (frameDelay > frameTime) {
						SDL_Delay(frameDelay - frameTime);
					}
				}
			}
		}
		//Free resources and close SDL
		close();
		return 0;
	}
}