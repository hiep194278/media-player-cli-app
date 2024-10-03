#include "VolumeView.hpp"
#include "Playlist.hpp"

#include <iostream>

void enterAdjustVolumeView() {
    char choice;

    while (true)
    {
        std::cout << "\nOptions: \n";
        std::cout << "[i] Increase volume\n";
        std::cout << "[d] Decrease volume\n";
        std::cout << "[m] Mute/Unmute\n";
        std::cout << "[e] Exit adjust volume view\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        // Handle user input
        if (choice == 'i' || choice == 'I') {
            Playlist::currentPlaylist->increaseVolume();
        } else if (choice == 'd' || choice == 'D') {
            Playlist::currentPlaylist->decreaseVolume();
        } else if (choice == 'm' || choice == 'M') {
            Playlist::currentPlaylist->muteOrUnmute();
        } else if (choice == 'e' || choice == 'E') {
            break;
        } else {
            std::cout << "Invalid option! Please try again." << std::endl;
        }
    }
    
};