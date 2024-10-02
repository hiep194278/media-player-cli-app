#pragma once

#include <vector>
#include <memory>
#include <string>
#include "AudioFile.hpp"
#include <thread>
#include <memory>

class Playlist {
private:
    std::string name;  // Name of the playlist
    std::vector<std::shared_ptr<File>> audioFiles;  // Collection of
                                                         // audio files
    unsigned int currentTrack;

public:
    // Static pointer to the currently playing playlist for the callback
    static std::shared_ptr<Playlist> currentPlaylist;
    static bool isPlaying;

    Playlist(const std::string& name);

    // Get the playlist name
    std::string getName() const;

    // Check if playlist is empty
    bool isEmpty() const;

    // Add, remove, modify audio files
    void addAudioFile(const std::shared_ptr<File>& audioFile);
    void removeAudioFile(const std::string& fileName);
    std::vector<std::shared_ptr<File>> getAudioFiles() const;

    // Display all audio files in the playlist
    void displayAudioFiles() const;

    // Play the playlist
    void play();
    void next();
    void prev();
    void getTimeAndDuration();

    // Static callback function when music finishes
    static void onMusicFinished();
};