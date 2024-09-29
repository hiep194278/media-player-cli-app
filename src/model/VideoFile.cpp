#include "VideoFile.hpp"
#include <iostream>

// Constructor for VideoFile class
VideoFile::VideoFile(const std::filesystem::path& path) : File(path) {}

// Displays the video file's information
void VideoFile::displayInfo() const {
    std::cout << "Video File: " << getFileName() 
              << " at " << getCanonicalPath() << std::endl;
}

// Returns the type of the file
File::FileType VideoFile::getFileType() const {
    return VIDEO;
}
