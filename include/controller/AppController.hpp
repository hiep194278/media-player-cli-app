#pragma once

#define VIEW_MEDIA_FILES_AND_SUB_FOLDERS 1
#define CHANGE_WORKING_DIRECTORY 2
#define ALL_PLAYLISTS 3
#define CREATE_PLAYLIST 4
#define DELETE_PLAYLIST 5
#define START_PLAYLIST 6
#define EDIT_PLAYLIST_VIEW 7
#define SHOW_METADATA 8
#define EDIT_METADATA 9
#define ENTER_CONTROL_MODE 10
#define ADJUST_VOLUME 11
#define EXIT_APP 12

#include <filesystem>

class AppController {
private:
    std::filesystem::path currentWorkingDir;
public:
    AppController(const std::filesystem::path& currentPath);
    void runApp();
    void displayMenu() const;
    void viewFilesAndSubFolders() const;
    void changeWorkingDir();
};