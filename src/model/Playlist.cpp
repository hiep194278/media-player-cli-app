#include "Playlist.hpp"
#include <iostream>
#include <algorithm>

// Constructor
Playlist::Playlist(const std::string& name) : name(name) {}

// Get the playlist name
std::string Playlist::getName() const {
    return name;
}

// void Playlist::play() {
//     if (audioFiles.empty()) {
//         std::cerr << "The playlist is empty!" << std::endl;
//         return;
//     }

//     if (SDL_Init(SDL_INIT_AUDIO) < 0) {
//         std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
//         return;
//     }

//     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//         std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
//         SDL_Quit();
//         return;
//     }

//     for (const auto& audioFile : audioFiles) {
//         std::cout << "Playing: " << audioFile->getFileName() << std::endl;
//         if (loadAudioFile(audioFile->getFilePath())) {
//             Mix_Music* music = Mix_LoadMUS(audioFile->getFilePath().c_str());
//             if (Mix_PlayMusic(music, 1) == -1) {
//                 std::cerr << "Error playing music: " << Mix_GetError() << std::endl;
//             }
//             while (Mix_PlayingMusic()) {
//                 SDL_Delay(100);  // Wait until the current music finishes
//             }
//             Mix_FreeMusic(music);  // Free the music resource
//         }
//     }

//     Mix_CloseAudio();
//     SDL_Quit();
// }

// Add an audio file to the playlist
void Playlist::addAudioFile(const std::shared_ptr<File>& audioFile) {
    audioFiles.push_back(audioFile);
    std::cout << "Added audio file: " << audioFile->getFileName() 
              << " to the playlist: " << name << std::endl;
}

// Remove an audio file from the playlist by filename
void Playlist::removeAudioFile(const std::string& fileName) {
    audioFiles.erase(std::remove_if(audioFiles.begin(), audioFiles.end(),
        [&fileName](const std::shared_ptr<File>& audioFile) {
            return audioFile->getFileName() == fileName;
        }), audioFiles.end());
    std::cout << "Removed audio file: " << fileName 
              << " from the playlist: " << name << std::endl;
}

// // Load audio file using SDL2 Mixer (helper method)
// bool Playlist::loadAudioFile(const std::string& filePath) {
//     Mix_Music* music = Mix_LoadMUS(filePath.c_str());
//     if (!music) {
//         std::cerr << "Failed to load music: " << filePath << " SDL Error: " << Mix_GetError() << std::endl;
//         return false;
//     }
//     return true;
// }

std::vector<std::shared_ptr<File>> Playlist::getAudioFiles() const {
    return audioFiles;
};

// Display all audio files in the playlist
void Playlist::displayAudioFiles() const {
    std::cout << "Playlist: " << name << std::endl;
    for (const auto& audioFile : audioFiles) {
        std::cout << " - " << audioFile->getFileName() << std::endl;
    }
}

// Play the playlist using SDL2
// void Playlist::play() {
//     if (audioFiles.empty()) {
//         std::cerr << "The playlist is empty!" << std::endl;
//         return;
//     }

//     if (SDL_Init(SDL_INIT_AUDIO) < 0) {
//         std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
//         return;
//     }

//     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//         std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
//         SDL_Quit();
//         return;
//     }

//     for (const auto& audioFile : audioFiles) {
//         std::cout << "Playing: " << audioFile->getFileName() << std::endl;
//         if (loadAudioFile(audioFile->getFilePath())) {
//             Mix_Music* music = Mix_LoadMUS(audioFile->getFilePath().c_str());
//             if (Mix_PlayMusic(music, 1) == -1) {
//                 std::cerr << "Error playing music: " << Mix_GetError() << std::endl;
//             }
//             while (Mix_PlayingMusic()) {
//                 SDL_Delay(100);  // Wait until the current music finishes
//             }
//             Mix_FreeMusic(music);  // Free the music resource
//         }
//     }

//     Mix_CloseAudio();
//     SDL_Quit();
// }
