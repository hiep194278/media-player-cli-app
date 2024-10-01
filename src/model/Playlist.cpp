#include "Playlist.hpp"
#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// Constructor
Playlist::Playlist(const std::string& name) : name(name) {}

// Get the playlist name
std::string Playlist::getName() const {
    return name;
}

// Add an audio file to the playlist
void Playlist::addAudioFile(const std::shared_ptr<File>& audioFile) {
    std::string audioFileName = audioFile->getFileName();

    // Check if an audio file with the same name already exists
    auto it = std::find_if(audioFiles.begin(), audioFiles.end(),
        [&audioFileName](const std::shared_ptr<File>& audioFile) {
            return audioFile->getFileName() == audioFileName;
        });

    if (it != audioFiles.end()) {
        // Playlist with the same name exists
        std::cerr << "Audio file with the name '" << audioFileName 
                  << "' already exists." << std::endl;
        return;
    }

    audioFiles.push_back(audioFile);
    std::cout << "Added audio file: " << audioFile->getFileName() 
              << " to the playlist: " << name << std::endl;
}

// Remove an audio file from the playlist by filename
void Playlist::removeAudioFile(const std::string& fileName) {
    bool found = false;

    // Iterate through the audio files in the playlist
    for (auto it = audioFiles.begin(); it != audioFiles.end(); ++it) {
        std::string currentFileName = (*it)->getFileName();

        // Check if the file name matches the one to be removed
        if (currentFileName == fileName) {
            // Remove the audio file from the playlist
            audioFiles.erase(it);
            found = true;
            break;
        }
    }

    // If the audio file is not found
    if (!found) {
        std::cout << "Audio file not found in the playlist: " << fileName 
                  << std::endl;
    }
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

// The function that will be run on a separate thread to play the playlist
void Playlist::playOnThread() {
    if (audioFiles.empty()) {
        std::cerr << "The playlist is empty!" << std::endl;
        return;
    }

    for (const auto& audioFile : audioFiles) {
        if (stopRequested) break;  // Check if we should stop

        Mix_Music* music = Mix_LoadMUS(audioFile->getFilePath().c_str());
        if (Mix_PlayMusic(music, 1) == -1) {
            std::cerr << "Error playing music: " << Mix_GetError() << std::endl;
        }

        while (Mix_PlayingMusic()) {
            if (stopRequested) {
                Mix_HaltMusic();  // Stop the music if requested
                break;
            }
            SDL_Delay(100);  // Wait until the current music finishes
        }

        Mix_FreeMusic(music);  // Free the music resource

        if (stopRequested) break;  // Stop if requested
    }
}

// Public method to play the playlist (starts a separate thread)
void Playlist::play() {
    stopRequested = false;  // Reset stop request

    if (playbackThread.joinable()) {
        playbackThread.join();  // Ensure any previous thread is joined
    }

    playbackThread = std::thread(&Playlist::playOnThread, this);  // Launch playOnThread in a separate thread
}

// Method to stop the playlist playback
void Playlist::requestStop() {
    stopRequested = true;
}

// This method ensures that the thread is properly stopped and joined
void Playlist::stop() {
    requestStop();

    if (playbackThread.joinable()) {
        playbackThread.join();  // Wait for the playback thread to finish
    }
}

// Destructor to clean up resources
Playlist::~Playlist() {
    stop();  // Ensure any running thread is stopped and joined
}