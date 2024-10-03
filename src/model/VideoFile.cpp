#include "VideoFile.hpp"

// Constructor for VideoFile class
VideoFile::VideoFile(const std::filesystem::path& path) : File(path) {}

// Displays the video file's information
void VideoFile::displayInfo() const {
    std::cout << "[Video] " << getFileName() 
            //   << " at " << getCanonicalPath() 
              << std::endl;
}

// Returns the type of the file
FileType VideoFile::getFileType() const {
    return FileType::Video;
}
