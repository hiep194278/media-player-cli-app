#pragma once

#include <vector>
#include <memory>
#include <string>
#include "AudioFile.hpp"
#include <thread>

class Playlist {
private:
    std::string name;  // Name of the playlist
    std::vector<std::shared_ptr<File>> audioFiles;  // Collection of
                                                         // audio files
    std::thread playbackThread;
    bool stopRequested;

    void playOnThread();  // This will be the actual function run by the thread

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
    void stop();
    void requestStop();  // Call this to stop the playlist playback

    // Display all audio files in the playlist
    void displayAudioFiles() const;

    // Deconstructor
    ~Playlist();
};

