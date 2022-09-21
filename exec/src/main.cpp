#include "game/State.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
    vkmc::State app{};

    try
    {
        app.Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}