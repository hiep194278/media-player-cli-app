#include <iostream>
#include "File.hpp"
#include "AppController.hpp"

int main() {
    AppController app(std::filesystem::current_path());
    app.runApp();

    return 0;
}