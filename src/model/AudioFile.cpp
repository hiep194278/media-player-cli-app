#include "AudioFile.hpp"
#include <iostream>

// Constructor for AudioFile class
AudioFile::AudioFile(const std::filesystem::path& path) : File(path) {}

// Displays the audio file's information
void AudioFile::displayInfo() const {
    std::cout << "[Audio] " << getFileName() 
            //   << " at " << getCanonicalPath() 
              << std::endl;
}

// Returns the type of the file
FileType AudioFile::getFileType() const {
    return FileType::Audio;
}
