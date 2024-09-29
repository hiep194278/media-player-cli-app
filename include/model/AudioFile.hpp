#pragma once

#include "File.hpp"
#include <filesystem>

/**
 * @brief Represents an audio file in the media player application.
 */
class AudioFile : public File {
public:
    // Constructor
    AudioFile(const std::filesystem::path& path);

    // Override displayInfo
    void displayInfo() const override;

    // Override getFileType
    FileType getFileType() const override;
};

