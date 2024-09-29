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