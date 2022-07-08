#include "first_app.hpp"
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

int main() {
    lve::first_app app{};

    try
    {
        app.Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
