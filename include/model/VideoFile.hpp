#pragma once

#include "File.hpp"
#include <iostream>

/**
 * @brief Represents a video file in the media player application.
 */
class VideoFile : public File {
public:
    // Constructor
    VideoFile(const std::filesystem::path& path);

    // Override displayInfo
    void displayInfo() const override;

    // Override getFileType
    FileType getFileType() const override;
};

