#include "File.hpp"
#include <iostream>

// Constructor for File class
File::File(const std::filesystem::path& path) : filePath(path) {}

// Destructor for File class (empty since it's a base class)
File::~File() {}

// Getter for the full path
std::filesystem::path File::getFilePath() const {
    return filePath;
}

// Getter for the file name
std::string File::getFileName() const {
    return filePath.filename().string();
}

// Clean, absolute display of the path (canonical)
std::string File::getCanonicalPath() const {
    try {
        return std::filesystem::canonical(filePath).string();
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return filePath.string();  // If canonical fails, fallback 
                                    // to original path
    }
}

// Static method to determine the file type
FileType File::determineFileType(const std::filesystem::path& filePath) {
    if (std::filesystem::is_directory(filePath)) {
        return FileType::Folder;
    }
    
    std::string extension = filePath.extension().string();
    
    if (extension == ".mp3" || extension == ".wav" || extension == ".ogg" ||
        extension == ".voc" || extension == ".flac"
    ) {
        return FileType::Audio;
    } else if (extension == ".mp4" || extension == ".avi") {
        return FileType::Video;
    }
    
    return FileType::Unknown;
}
