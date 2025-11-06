#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow{ nullptr };
SDL_Surface* gScreenSurface{ nullptr };

int main(int argc, char* args[]) {

    int exitCode { 0 };

    float x = 0;
    int y = 0;

    if(init() == false) {
        SDL_Log("Unable to initialize program!\n");
        exitCode = 1;
    }
    else {
        bool quit { false };

        SDL_Event e;
        SDL_zero( e );

        while(quit == false) {
            
            while(SDL_PollEvent(&e) == true) {
                if(e.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
            }
            
            x += 0.01;
            if(x >= 1) {
                y += 1;
                x = 0;
            }
            SDL_Rect particle = { 100 + y, 100, 50, 50 };
            Uint32 color = SDL_MapRGB(SDL_GetPixelFormatDetails(gScreenSurface->format), nullptr, 255, 0, 0);


            SDL_FillSurfaceRect( gScreenSurface, nullptr, SDL_MapSurfaceRGB( gScreenSurface, 0xFF, 0xFF, 0xFF ) );
            SDL_FillSurfaceRect( gScreenSurface, &particle, color );
            
            SDL_UpdateWindowSurface( gWindow );
        }
    }

    close();

    return exitCode;
}

bool init() {
    bool success{ true };
    
    if(SDL_Init(SDL_INIT_VIDEO) == false) {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        success = false;
    }  
    else {
        if( gWindow = SDL_CreateWindow( "SDL3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0 ); gWindow == nullptr )
        {
            SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

void close() {
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gScreenSurface = nullptr;

    SDL_Quit();
}