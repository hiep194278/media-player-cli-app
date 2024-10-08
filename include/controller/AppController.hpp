#pragma once

#define VIEW_MEDIA_FILES_AND_SUB_FOLDERS 1
#define CHANGE_WORKING_DIRECTORY 2
#define ALL_PLAYLISTS 3
#define CREATE_PLAYLIST 4
#define DELETE_PLAYLIST 5
#define EDIT_PLAYLIST_VIEW 6
#define START_PLAYLIST 7
#define ENTER_MUSIC_CONTROL_MODE 8
#define ADJUST_VOLUME 9
#define SHOW_METADATA 10
#define EDIT_METADATA 11
#define EXIT_APP 12

#include "Playlist.hpp"
#include "PaginationView.hpp"
#include "AudioFile.hpp"
#include "VideoFile.hpp"
#include "Folder.hpp"
#include "EditPlaylistView.hpp"
#include "MusicControlView.hpp"
#include "VolumeView.hpp"

#include <iostream>
#include <limits>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <filesystem>

class AppController {
private:
    std::filesystem::path currentWorkingDir;
    std::vector<std::shared_ptr<Playlist>> playlists;  // Collection of 
                                                       // playlists

public:
    AppController(const std::filesystem::path& currentPath);

    void runApp();

    // File Management
    void displayMenu() const;
    void viewFilesAndSubFolders() const;
    void changeWorkingDir();
    std::filesystem::path enterRelativePath() const;

    // Playlist management
    std::string enterPlaylistName();
    void createPlaylist();
    void deletePlaylist();
    void listPlaylists() const;
    std::shared_ptr<Playlist> getPlaylist(const std::string& playlistName);

    // Show all audio files in the current playlist
    void showCurrentPlaylist(const std::string& playlistName) const;

    // Metadata Management
    void showFileMetadata() const;
    void updateFileMetadata() const;

    // Playing music
    void startPlaylist();
};