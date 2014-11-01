#include <iostream>
#include "Application.h"

//#define _GLIBCXX_USE_WCHAR_T 0

int main() {
    try {
        Application application;
        application.run();
    }
    catch (std::exception& e) {
        std::cout << "\nEXCEPTION " << e.what() << std::endl;
    }

    return 0;
}

