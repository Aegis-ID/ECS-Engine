/*
** EPITECH PROJECT, 2025
** main.cpp
** File description:
** main
*/

#include "Engine/Core.hpp"

int main(int argc, char **argv)
{
    Engine::Core gameEngine;
    std::vector<std::string> args;

    argc -= 1;
    argv += 1;
    for (int i = 0; i < argc; ++i)
        args.push_back(argv[i]);
    gameEngine.run(args);
    return 0;
}
