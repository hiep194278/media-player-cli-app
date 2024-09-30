#include "PaginationView.hpp"
#include "File.hpp"
#include "AudioFile.hpp"
#include "VideoFile.hpp"
#include "Folder.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>

// Constructor
PaginationView::PaginationView(const std::vector<std::shared_ptr<File>>& files, int itemsPerPage)
    : files(files), currentPage(0), itemsPerPage(itemsPerPage) {}

// Method to calculate the total number of pages
int PaginationView::calculateTotalPages() const {
    return (files.size() + itemsPerPage - 1) / itemsPerPage;  // Ceiling division
}

// Method to display a specific page of files
void PaginationView::displayPage() {
    int start = currentPage * itemsPerPage;
    int numItems = static_cast<int>(files.size());
    int end = std::min(numItems, start + itemsPerPage);

    std::cout << "Page " << currentPage + 1 << " of " 
              << calculateTotalPages() << " (Showing items " 
              << start + 1 << " to " << end << " over " << numItems 
              << " items)" 
              << std::endl;
    std::cout << "-------------------------" << std::endl;

    for (int i = start; i < end; ++i) {
        std::cout << i + 1 << ". ";
        files[i]->displayInfo();
    }
}

// Main method to handle pagination and file viewing
void PaginationView::handlePagination() {
    char choice;

    while (true) {
        displayPage();

        // Display navigation options
        std::cout << "\nOptions: ";
        std::cout << "[n] Next Page";
        std::cout << "   [p] Previous Page";
        std::cout << "   [q] Quit Pagination View" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        // Handle user input
        if (choice == 'n' || choice == 'N') {
            if (currentPage < calculateTotalPages() - 1) {
                ++currentPage;
            } else {
                std::cout << "You are on the last page!" << std::endl;
            }
        } else if (choice == 'p' || choice == 'P') {
            if (currentPage > 0) {
                --currentPage;
            } else {
                std::cout << "You are on the first page!" << std::endl;
            }
        } else if (choice == 'q' || choice == 'Q') {
            break;  // Exit the loop
        } else {
            std::cout << "Invalid option! Please try again." << std::endl;
        }
    }
}