#pragma once

#include "Playlist.hpp"
#include "PaginationView.hpp"

#include <filesystem>
#include <vector>
#include <algorithm>
#include <iostream>

void enterEditPlaylistView(std::filesystem::path& currentworkingDir,
std::vector<std::shared_ptr<Playlist>>& playlists);

std::shared_ptr<Playlist> getPlaylist(const std::string& playlistName, 
std::vector<std::shared_ptr<Playlist>>& playlists);

void editPlaylistViewMenu();