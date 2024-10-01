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
void AudioFile::updateMetadata() {
    // Load the file using TagLib
    TagLib::FileRef file(filePath.c_str());

    if (!file.isNull() && file.tag()) {
        TagLib::Tag *tag = file.tag();
        
        // Input new metadata from the user
        std::string input;
        int intInput;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), 
            '\n');

        std::cout << "Enter new Title: ";
        std::getline(std::cin, input);
        tag->setTitle(input);

        std::cout << "Enter new Artist: ";
        std::getline(std::cin, input);
        tag->setArtist(input);

        std::cout << "Enter new Album: ";
        std::getline(std::cin, input);
        tag->setAlbum(input);

        std::cout << "Enter new Year: ";
        std::cin >> intInput;
        tag->setYear(intInput);
        std::cin.ignore();  // Ignore newline left in the buffer

        std::cout << "Enter new Track: ";
        std::cin >> intInput;
        tag->setTrack(intInput);
        std::cin.ignore();  // Ignore newline left in the buffer

        std::cout << "Enter new Genre: ";
        std::getline(std::cin, input);
        tag->setGenre(input);

        // Save the updated metadata back to the file
        if (file.save()) {
            std::cout << "Metadata updated successfully.\n";
        } else {
            std::cout << "Failed to update metadata.\n";
        }
    } else {
        std::cerr << "Error: Could not open file or read metadata.\n";
    }
}