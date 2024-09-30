#include "AudioFile.hpp"
#include <iostream>

// Constructor for AudioFile class
AudioFile::AudioFile(const std::filesystem::path& path) : File(path) {}

// Displays the audio file's information
void AudioFile::displayInfo() const {
    std::cout << "[Audio] " << getFileName() 
            //   << " at " << getCanonicalPath() 
              << std::endl;
}

// Returns the type of the file
FileType AudioFile::getFileType() const {
    return FileType::Audio;
}


// Show Metadata using TagLib
void AudioFile::showMetadata() const {
    TagLib::FileRef f(filePath.c_str());
    
    if(!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();
        
        std::cout << "Title  : " << tag->title().toCString(true) << std::endl;
        std::cout << "Artist : " << tag->artist().toCString(true) << std::endl;
        std::cout << "Album  : " << tag->album().toCString(true) << std::endl;
        std::cout << "Year   : " << tag->year() << std::endl;
        std::cout << "Track  : " << tag->track() << std::endl;
        std::cout << "Genre  : " << tag->genre().toCString(true) << std::endl;
    } else {
        std::cout << "Unable to read metadata for: " << filePath << std::endl;
    }
}

// Update Metadata using TagLib
void AudioFile::updateMetadata(const std::string& title, const std::string& artist, const std::string& album) {
    TagLib::FileRef f(filePath.c_str());

    if(!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();
        
        tag->setTitle(title);
        tag->setArtist(artist);
        tag->setAlbum(album);
        
        // Save the updated metadata back to the file
        f.save();
        std::cout << "Metadata updated successfully!" << std::endl;
    } else {
        std::cout << "Unable to update metadata for: " << filePath << std::endl;
    }
}