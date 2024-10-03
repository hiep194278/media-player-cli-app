#pragma once

#include "File.hpp"

#include <iostream>

/**
 * @brief Represents a folder in the media player application.
 */
class Folder : public File {
public:
    // Constructor
    Folder(const std::filesystem::path& path);

    // Override displayInfo
    void displayInfo() const override;

    // Override getFileType
    FileType getFileType() const override;
};
