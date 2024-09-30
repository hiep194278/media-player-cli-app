#pragma once

#include "File.hpp"
#include <filesystem>
#include <taglib/fileref.h>
#include <taglib/tag.h>

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

    // Method to display metadata
    void showMetadata() const;

    // Method to update metadata
    void updateMetadata(const std::string& title, const std::string& artist, const std::string& album);

};

