#include "AppController.hpp"

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
            case EDIT_PLAYLIST_VIEW:
                enterEditPlaylistView(currentWorkingDir, playlists);
                break;
            case START_PLAYLIST:
                startPlaylist();
                break;
            case ENTER_MUSIC_CONTROL_MODE:
                enterMusicControlView();     // 2
                break;
            case ADJUST_VOLUME:
                enterAdjustVolumeView();     // 3
                break;
            case SHOW_METADATA:
                showFileMetadata();
                break;
            case EDIT_METADATA:
                updateFileMetadata();
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
    std::cout << EDIT_PLAYLIST_VIEW << ". Enter playlist edit view\n";
    std::cout << START_PLAYLIST << ". Start a playlist\n";
    std::cout << ENTER_MUSIC_CONTROL_MODE << ". Enter music control view\n";
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

        PaginationView<File> paginationView(files);
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

std::string AppController::enterPlaylistName() {
    std::string playlistName;
    std::cout 
        << "Enter the playlist name: ";
    std::cin >> playlistName;

    return playlistName;
}

// Create a new playlist
void AppController::createPlaylist() {
    std::string playlistName = enterPlaylistName();
    
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
    std::string playlistName = enterPlaylistName();

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
    if (playlists.empty()) {
        std::cout << "No playlists available." << std::endl;
        return;
    }

    // Create a PaginationView for the playlists
    PaginationView<Playlist> playlistPagination(playlists);  // 5 items per page
    playlistPagination.handlePagination();  // Start the pagination view
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

void AppController::showFileMetadata() const {
    std::filesystem::path filePath = enterRelativePath(); 
    
    // Ensure the relative path is valid
    if (std::filesystem::exists(filePath) && 
        File::determineFileType(filePath) == FileType::Audio
    ) {
        AudioFile audioFile(filePath);
        audioFile.showMetadata();
    } else {
        std::cout << "Invalid audio file path!\n";
    }
}

void AppController::updateFileMetadata() const {
    std::filesystem::path filePath = enterRelativePath(); 
    
    // Ensure the relative path is valid
    if (std::filesystem::exists(filePath) && 
        File::determineFileType(filePath) == FileType::Audio
    ) {
        AudioFile audioFile(filePath);
        audioFile.updateMetadata();
    } else {
        std::cout << "Invalid audio file path!\n";
    }    
};

void AppController::startPlaylist() {
    std::string playlistName = enterPlaylistName();

    for (const auto& playlist : playlists) {
        if (playlist->getName() == playlistName) {
            if (playlist->isEmpty()) {
                std::cerr << "Playlist is empty" << std::endl;
                return;
            }

            Playlist::currentPlaylist = playlist;
            Playlist::isPlaying = true;
            Playlist::stopRequested = false;
            Playlist::currentPlaylist->play(); 
            std::cout << "Playing playlist: " << playlistName << std::endl;
            return;
        }
    }
    std::cerr << "Playlist not found!" << std::endl;
}