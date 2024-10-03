#include "MusicControlView.hpp"
#include "Playlist.hpp"

#include <iostream>

void enterMusicControlView() {
    if (Playlist::currentPlaylist == nullptr) {
        std::cout << "No playlist is currently playing" << std::endl;
        return;
    }

    char choice;
    while (true)
    {
        displayMusicControlViewMenu();
        std::cin >> choice;

        // Handle user input
        if (choice == 'n' || choice == 'N') {
            Playlist::currentPlaylist->next();
        } else if (choice == 'p' || choice == 'P') {
            Playlist::currentPlaylist->prev();
        } else if (choice == 'r' || choice == 'R') {
            if (Playlist::isPlaying == true) {
                Mix_PauseMusic(); 
                Playlist::isPlaying = false;
            } else {
                Mix_ResumeMusic();
                Playlist::isPlaying = true;
            }
        } else if (choice == 'v' || choice == 'V') {
            Playlist::currentPlaylist->getTimeAndDuration();
        } else if (choice == 'c' || choice == 'C') {
            Mix_HaltMusic();
            Mix_FreeMusic(Playlist::currentPlaylist->getMusic());
            Playlist::stopRequested = true;
            Playlist::currentPlaylist = nullptr;
            Playlist::isPlaying = false;
            break;
        } else if (choice == 'e' || choice == 'E') {
            break;
        } else {
            std::cout << "Invalid option! Please try again." << std::endl;
        }
    }
}

void displayMusicControlViewMenu() {
    std::cout << "\nCurrent playlist: " 
                << Playlist::currentPlaylist->getName();

    // Display navigation options
    std::cout << "\nOptions: \n";
    std::cout << "[n] Play next song\n";
    std::cout << "[p] Play previous song\n";
    std::cout << "[r] Resume/Pause playlist\n";
    std::cout << "[v] View time/duration\n";
    std::cout << "[c] Close the playlist playback\n";
    std::cout << "[e] Exit music control view\n";
    std::cout << "Enter choice: ";
}