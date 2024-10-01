#pragma once

#include <vector>
#include <memory>
#include <string>
#include "AudioFile.hpp"
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_mixer.h>

// #define ADD_FILE 1
// #define REMOVE_FILE 2
// #define SHOW_ALL_FILES 3
// #define EXIT_VIEW 4

class Playlist {
private:
    std::string name;  // Name of the playlist
    std::vector<std::shared_ptr<File>> audioFiles;  // Collection of
                                                         // audio files

    // bool loadAudioFile(const std::string& filePath);

public:
    Playlist(const std::string& name);

    // Get the playlist name
    std::string getName() const;

    // Add, remove, modify audio files
    void addAudioFile(const std::shared_ptr<File>& audioFile);
    void removeAudioFile(const std::string& fileName);
    std::vector<std::shared_ptr<File>> getAudioFiles() const;

    // Play the playlist
    void play();

    // Display all audio files in the playlist
    void displayAudioFiles() const;
};

