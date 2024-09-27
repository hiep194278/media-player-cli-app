#include <iostream>
#include "File.hpp"
#include "AppController.hpp"

int main() {
    std::cout << "------------------------------" << std::endl;
    std::cout << "Welcome to Media Player CLI Application !" << std::endl;
    File file1;
    file1.getFile();
    AppController appController;
    appController.getAppController();

    return 0;
}