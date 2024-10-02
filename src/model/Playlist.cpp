#include "Playlist.hpp"
#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// Initialize the static instance pointer
std::shared_ptr<Playlist> Playlist::currentPlaylist = nullptr;
bool Playlist::isPlaying = false;
// bool Playlist::isExiting = false;

// Constructor
Playlist::Playlist(const std::string& name) : name(name), currentTrack(0) {}

// Get the playlist name
std::string Playlist::getName() const {
    return name;
}

// Check if playlist is empty
bool Playlist::isEmpty() const {
    return audioFiles.empty();
};

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

void Playlist::play() {
    Mix_Music* music = Mix_LoadMUS(audioFiles[currentTrack]->getFilePath().c_str());
    if (!music) {
        std::cout << "Can't load music: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }
    
    // std::cout << "Current track: " << name << std::endl;
    // std::cout << "Playing: " << audioFiles[currentTrack]->getFileName() << std::endl;

    if (Mix_PlayMusic(music, 0) == -1) {  // Play the music once
        std::cout << "Can't play music: " << Mix_GetError() << std::endl;
    } 

    // Set the callback for when the music finishes
    Mix_HookMusicFinished(onMusicFinished);
}

// Move the next song
void Playlist::next() {
    currentTrack = (currentTrack + 1) % audioFiles.size();
    std::cout << "Playing: " << audioFiles[currentTrack]->getFileName() << std::endl;
    play();
}

// Move the previous song
void Playlist::prev() {
    currentTrack = (currentTrack - 1 + audioFiles.size()) % audioFiles.size();
    std::cout << "Playing: " << audioFiles[currentTrack]->getFileName() << std::endl;
    play();
}


// Static callback function when music finishes
void Playlist::onMusicFinished() {
    if (currentPlaylist) {
        currentPlaylist->currentTrack = (currentPlaylist->currentTrack + 1) % currentPlaylist->audioFiles.size();
        // std::cout << "\nNext track: " << currentPlaylist->audioFiles[currentPlaylist->currentTrack]->getFileName() << std::endl;
        currentPlaylist->play();
    } else {
        std::cout << "Null pointer" << std::endl;
    }
}

void Playlist::getTimeAndDuration() {
    Mix_Music* music = Mix_LoadMUS(audioFiles[currentTrack]->getFilePath().c_str());
    std::cout << "Current song: " << audioFiles[currentTrack]->getFileName() << std::endl;
    std::cout << "Time/Duration: " << static_cast<int>(Mix_GetMusicPosition(music)) << "/" << static_cast<int>(Mix_MusicDuration(music)) << std::endl;
};