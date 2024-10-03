#include "Folder.hpp"

// Constructor for Folder class
Folder::Folder(const std::filesystem::path& path) : File(path) {}

// Displays the folder's information
void Folder::displayInfo() const {
    std::cout << "[Folder] " << getFileName() 
            //   << " at " << getCanonicalPath() 
              << std::endl;
}

// Returns the type of the file
FileType Folder::getFileType() const {
    return FileType::Folder;
}
