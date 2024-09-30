#pragma once

#include <vector>
#include <memory>
#include <string>
#include "AudioFile.hpp"
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_mixer.h>

class Playlist {
private:
    std::string name;  // Name of the playlist
    std::vector<std::shared_ptr<AudioFile>> audioFiles;  // Collection of
                                                         // audio files

    // bool loadAudioFile(const std::string& filePath);

public:
    Playlist(const std::string& name);

    // Get the playlist name
    std::string getName() const;

    // Add, remove, modify audio files
    void addAudioFile(const std::shared_ptr<AudioFile>& audioFile);
    void removeAudioFile(const std::string& fileName);
    void modifyAudioFile(const std::string& fileName, 
                         const std::shared_ptr<AudioFile>& newAudioFile);

    // Play the playlist
    // void play();

    // Display all audio files in the playlist
    void displayAudioFiles() const;
};

