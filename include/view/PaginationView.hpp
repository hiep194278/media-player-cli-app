#pragma once

#include <vector>
#include <memory>
#include "File.hpp"

class PaginationView {
public:
    PaginationView(const std::vector<std::shared_ptr<File>>& files, int itemsPerPage);

    // Method to display a specific page of files
    void displayPage();

    // Main method to handle pagination and file viewing
    void handlePagination();

private:
    std::vector<std::shared_ptr<File>> files;  // Vector containing the files
    int currentPage;                           // Current page index
    int itemsPerPage;                          // Number of items to display per page

    int calculateTotalPages() const;
};