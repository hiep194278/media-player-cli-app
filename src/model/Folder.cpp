#include "Folder.hpp"
#include <iostream>

// Constructor for Folder class
Folder::Folder(const std::filesystem::path& path) : File(path) {}

// Displays the folder's information
void Folder::displayInfo() const {
    std::cout << "Folder: " << getFileName() 
              << " at " << getCanonicalPath() << std::endl;
}

// Returns the type of the file
File::FileType Folder::getFileType() const {
    return FOLDER;
}
