#pragma once

#include <string>
#include <filesystem>

enum class FileType {
    Audio,
    Video,
    Folder,
    Unknown
};

class File {
protected:
    std::filesystem::path filePath;

public:
    // Constructor
    File(const std::filesystem::path& path);
    
    // Virtual Destructor
    virtual ~File();

    // Pure virtual methods
    virtual void displayInfo() const = 0;
    virtual FileType getFileType() const = 0;

    // Getter for the full path
    std::filesystem::path getFilePath() const;

    // Getter for the file name
    std::string getFileName() const;

    // Clean, absolute display of the path (canonical)
    std::string getCanonicalPath() const;

    // Static method to check file type
    static FileType determineFileType(const std::filesystem::path& filePath);
};