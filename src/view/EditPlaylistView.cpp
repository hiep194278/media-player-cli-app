#include "EditPlaylistView.hpp"

void enterEditPlaylistView(std::filesystem::path& currentWorkingDir, 
std::vector<std::shared_ptr<Playlist>>& playlists) {
    std::string playlistName;
    std::cout << "Enter the playlist name: ";
    std::cin >> playlistName;
    
    std::shared_ptr<Playlist> playlist = getPlaylist(playlistName, 
                                                     playlists);

    if (playlist != nullptr) {
        char choice;
        while (true)
        {
            std::cout << "\nCurrent working directory: " 
                      << currentWorkingDir;
            std::cout << "\nPlaylist name: " << playlistName;
            editPlaylistViewMenu();
            std::cout << "Enter choice: ";
            std::cin >> choice;

            // Handle user input
            if (choice == 'a' || choice == 'A') {
                std::string relativePath;
                std::cout << "Enter the relative path to the audio file: ";
                std::cin >> relativePath;

                // Resolve the relative path to the full path based on the 
                // current working directory
                std::filesystem::path fullPath = currentWorkingDir / relativePath;

                if (std::filesystem::exists(fullPath) && 
                    File::determineFileType(fullPath) == FileType::Audio
                ) {
                    auto audioFile = std::make_shared<AudioFile>(fullPath);
                    playlist->addAudioFile(audioFile);
                } else {
                    std::cout << "Invalid audio file at path: " << fullPath << '\n';
                }
            } else if (choice == 'r' || choice == 'R') {
                std::string fileName;
                std::cout << "Enter the name of the audio file to delete: ";
                std::cin >> fileName;
                playlist->removeAudioFile(fileName);
            } else if (choice == 's' || choice == 'S') {
                PaginationView<File> paginationView(playlist->getAudioFiles());
                paginationView.handlePagination();
            } else if (choice == 'e' || choice == 'E') {
                std::cout << "Exiting the Edit Playlist View.\n";
                return;
            } else {
                std::cout << "Invalid option! Please try again." << std::endl;
            }

        }
    }    
}

std::shared_ptr<Playlist> getPlaylist(const std::string& playlistName, 
std::vector<std::shared_ptr<Playlist>>& playlists) {
    for (const auto& playlist : playlists) {
        if (playlist->getName() == playlistName) {
            return playlist;
        }
    }
    std::cerr << "Playlist not found: " << playlistName << std::endl;
    return nullptr;
}

void editPlaylistViewMenu() {
    // Display navigation options
    std::cout << "\nOptions: \n";
    std::cout << "[a] Add an audio file to the playlist\n";
    std::cout << "[r] Remove a file from the playlist\n";
    std::cout << "[s] Show all files in the playlist\n";
    std::cout << "[e] Exit edit playlist view\n";
}