#include <iostream>
#include "File.hpp"
#include "AppController.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main() {
        // SDL init
    if(SDL_Init(SDL_INIT_AUDIO) < 0){
        std::cout << "SDL can't init: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Mixer init
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2,2048) < 0){
        std::cout << "Mixer can't init: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    AppController app(std::filesystem::current_path());
    app.runApp();

    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}