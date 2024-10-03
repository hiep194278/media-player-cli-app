#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <iomanip>

template <typename T>
class PaginationView {
public:
    PaginationView(const std::vector<std::shared_ptr<T>>& items, int itemsPerPage = 5);

    // Method to display a specific page of files
    void displayPage();

    // Main method to handle pagination and file viewing
    void handlePagination();

private:
    std::vector<std::shared_ptr<T>> items;  // Vector containing the files
    int currentPage;                           // Current page index
    int itemsPerPage;                          // Number of items to display per page

    int calculateTotalPages() const;
};

#include "PaginationView.tpp"