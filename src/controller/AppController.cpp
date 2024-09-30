#include "AppController.hpp"
#include "PaginationView.hpp"
#include "AudioFile.hpp"
#include "VideoFile.hpp"
#include "Folder.hpp"
#include <iostream>
#include <limits>
#include <algorithm>

AppController::AppController(const std::filesystem::path& currentPath) 
    : currentWorkingDir(currentPath) {};

void AppController::runApp() {
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Welcome to Media Player CLI Application !" << std::endl;

    int choice;
    bool appIsRunning = true;

    while (appIsRunning) {
        displayMenu();
        std::cin >> choice;

        // Check if input failed (not an integer)
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), 
                '\n'); // Ignore the rest of the invalid input
            std::cout << "Invalid input, please enter a number.\n\n";
            continue;
        }

        switch (choice) {
            case VIEW_MEDIA_FILES_AND_SUB_FOLDERS:
                viewFilesAndSubFolders();
                break;
            case CHANGE_WORKING_DIRECTORY:
                changeWorkingDir();
                break;
            case ALL_PLAYLISTS:
                listPlaylists();
                break;
            case CREATE_PLAYLIST:
                createPlaylist();
                break;
            case DELETE_PLAYLIST:
                deletePlaylist();
                break;
            case START_PLAYLIST:
                std::cout << "Starting a playlist...\n";
                break;
            case EDIT_PLAYLIST_VIEW:
                std::cout << "Entering playlist edit view...\n";
                break;
            case ENTER_CONTROL_MODE:
                std::cout << "Entering control mode...\n";
                break;
            case ADJUST_VOLUME:
                std::cout << "Adjusting volume...\n";
                break;
            case SHOW_METADATA:
                std::cout << "Showing metadata of a file...\n";
                break;
            case EDIT_METADATA:
                std::cout << "Editing metadata...\n";
                break;   
            case EXIT_APP:
                std::cout << "Exiting...\n";
                appIsRunning = false;
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
        
        std::cout << std::endl;
    }
}

void AppController::displayMenu() const {
    std::cout << "Current working directory: " << currentWorkingDir 
        << std::endl;
    std::cout << "Option list:" << std::endl;
    std::cout << VIEW_MEDIA_FILES_AND_SUB_FOLDERS 
        << ". View media files and sub-folders\n";
    std::cout << CHANGE_WORKING_DIRECTORY 
        << ". Change working directory\n";
    std::cout << ALL_PLAYLISTS << ". All playlists\n";
    std::cout << CREATE_PLAYLIST << ". Create a playlist\n";
    std::cout << DELETE_PLAYLIST << ". Delete a playlist\n";
    std::cout << START_PLAYLIST << ". Start a playlist\n";
    std::cout << EDIT_PLAYLIST_VIEW << ". Enter playlist edit view\n";
    std::cout << ENTER_CONTROL_MODE << ". Enter music control view\n";
    std::cout << ADJUST_VOLUME << ". Adjust volume\n";
    std::cout << SHOW_METADATA << ". Show metadata of a file\n";
    std::cout << EDIT_METADATA << ". Edit metadata of a file\n";
    std::cout << EXIT_APP << ". Exit application\n";
    std::cout << "\nEnter your choice: ";
}

void AppController::viewFilesAndSubFolders() const {
    std::filesystem::path fullPath = enterRelativePath();

    if (std::filesystem::exists(fullPath) && 
        std::filesystem::is_directory(fullPath)
    ) {
        std::vector<std::shared_ptr<File>> files;

        for (const auto& entry : 
        std::filesystem::directory_iterator(fullPath)) {
            FileType fileType = File::determineFileType(entry.path());

            if (fileType == FileType::Audio) {
                files.push_back(std::make_shared<AudioFile>(
                    entry.path().string()));
            } else if (fileType == FileType::Video) {
                files.push_back(std::make_shared<VideoFile>(
                    entry.path().string()));
            } else if (fileType == FileType::Folder) {
                files.push_back(std::make_shared<Folder>(
                    entry.path().string()));
            }
        }

        PaginationView paginationView(files, 5);
        paginationView.handlePagination();
    } else {
        std::cout << "Invalid folder path!\n";
    }
};

void AppController::changeWorkingDir() {
    std::filesystem::path fullPath = enterRelativePath();

    // Ensure the relative path is valid
    if (std::filesystem::exists(fullPath) && 
        std::filesystem::is_directory(fullPath)
    ) {
        currentWorkingDir = std::filesystem::canonical(fullPath);
        std::cout << "New working directory set: " << currentWorkingDir;
        std::cout << std::endl;
    } else {
        std::cout << "Invalid folder path!\n";
    }
}

std::filesystem::path AppController::enterRelativePath() const {
    std::string relativePath;
    std::cout 
        << "Enter the relative path to the current working directory: ";
    std::cin >> relativePath;

    // Create a full path by appending the relative path to the current 
    // working directory
    std::filesystem::path fullPath = currentWorkingDir / relativePath;

    return fullPath;
}

// Create a new playlist
void AppController::createPlaylist() {
    std::string playlistName;
    std::cout 
        << "Enter the playlist name: ";
    std::cin >> playlistName;
    
    // Check if a playlist with the same name already exists
    auto it = std::find_if(playlists.begin(), playlists.end(),
        [&playlistName](const std::shared_ptr<Playlist>& playlist) {
            return playlist->getName() == playlistName;
        });

    if (it != playlists.end()) {
        // Playlist with the same name exists
        std::cerr << "Playlist with the name '" << playlistName 
                  << "' already exists." << std::endl;
        return;
    }

    // If no duplicate found, create a new playlist
    playlists.push_back(std::make_shared<Playlist>(playlistName));
    std::cout << "Created playlist: " << playlistName << std::endl;
}

// Delete a playlist by name
void AppController::deletePlaylist() {
    std::string playlistName;
    std::cout 
        << "Enter the playlist name: ";
    std::cin >> playlistName;

    auto it = std::find_if(playlists.begin(), playlists.end(),
        [&playlistName](const std::shared_ptr<Playlist>& playlist) {
            return playlist->getName() == playlistName;
        });

    if (it != playlists.end()) {
        playlists.erase(it);
        std::cout << "Deleted playlist: " << playlistName << std::endl;
    } else {
        std::cerr << "Playlist not found: " << playlistName << std::endl;
    }
}

// List all playlists
void AppController::listPlaylists() const {
    std::cout << "Available playlists:" << std::endl;
    for (const auto& playlist : playlists) {
        std::cout << " - " << playlist->getName() << std::endl;
    }
}

// Get a playlist by name
std::shared_ptr<Playlist> AppController::getPlaylist(
const std::string& playlistName) {
    for (const auto& playlist : playlists) {
        if (playlist->getName() == playlistName) {
            return playlist;
        }
    }
    std::cerr << "Playlist not found: " << playlistName << std::endl;
    return nullptr;
}

// Show the audio files in a specific playlist
void AppController::showCurrentPlaylist(const std::string& playlistName) 
const {
    auto playlist = std::find_if(playlists.begin(), playlists.end(),
        [&playlistName](const std::shared_ptr<Playlist>& p) {
            return p->getName() == playlistName;
        });

    if (playlist != playlists.end()) {
        (*playlist)->displayAudioFiles();
    } else {
        std::cerr << "Playlist not found: " << playlistName << std::endl;
    }
}