#pragma once

#define VIEW_MEDIA_FILES_AND_SUB_FOLDERS 1
#define ALL_PLAYLISTS 2
#define CREATE_PLAYLIST 3
#define DELETE_PLAYLIST 4
#define START_PLAYLIST 5
#define EDIT_PLAYLIST_VIEW 6
#define SHOW_METADATA 7
#define EDIT_METADATA 8
#define ENTER_CONTROL_MODE 9
#define ADJUST_VOLUME 10
#define EXIT_APP 11

class AppController {
public:
    void runApp();
    void displayMenu() const;
};