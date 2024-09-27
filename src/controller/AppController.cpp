#include "AppController.hpp"
#include <iostream>

void AppController::runApp() {
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Welcome to Media Player CLI Application !" << std::endl;

    int choice;
    bool appIsRunning = true;

    while (appIsRunning) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case VIEW_MEDIA_FILES_AND_SUB_FOLDERS:
                std::cout << "Viewing media files and sub-folders...\n";
                break;
            case ALL_PLAYLISTS:
                std::cout << "Viewing all playlists...\n";
                break;
            case CREATE_PLAYLIST:
                std::cout << "Creating a playlist...\n";
                break;
            case DELETE_PLAYLIST:
                std::cout << "Deleting a playlist...\n";
                break;
            case START_PLAYLIST:
                std::cout << "Starting a playlist...\n";
                break;
            case EDIT_PLAYLIST_VIEW:
                std::cout << "Entering playlist edit view...\n";
                break;
            case SHOW_METADATA:
                std::cout << "Showing metadata of a file...\n";
                break;
            case EDIT_METADATA:
                std::cout << "Editing metadata...\n";
                break;
            case ENTER_CONTROL_MODE:
                std::cout << "Entering control mode...\n";
                break;
            case ADJUST_VOLUME:
                std::cout << "Adjusting volume...\n";
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
    std::cout << "Option list:" << std::endl;
    std::cout << VIEW_MEDIA_FILES_AND_SUB_FOLDERS 
        << ". View media files and sub-folders" << std::endl;
    std::cout << ALL_PLAYLISTS << ". All playlists" << std::endl;
    std::cout << CREATE_PLAYLIST << ". Create a playlist" << std::endl;
    std::cout << DELETE_PLAYLIST << ". Delete a playlist" << std::endl;
    std::cout << START_PLAYLIST << ". Start a playlist" << std::endl;
    std::cout << EDIT_PLAYLIST_VIEW << ". Enter playlist edit view" 
        << std::endl;
    std::cout << SHOW_METADATA << ". Show metadata of a file" << std::endl;
    std::cout << EDIT_METADATA << ". Edit metadata of a file" << std::endl;
    std::cout << ENTER_CONTROL_MODE << ". Enter music control view" << 
        std::endl;
    std::cout << ADJUST_VOLUME << ". Adjust volume" << std::endl;
    std::cout << EXIT_APP << ". Exit application" << std::endl;
    std::cout << "Enter your choice: ";
}