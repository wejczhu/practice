#include <iostream>
#include <string>
#include <cstring>
#include "scene.h"
#include "input.h"
#include "test.h"

#define _TEST_ 0

static void printHelp()
{
    std::cout << std::endl;
    std::cout << "sudoku - a little game in commandline" << std::endl
              << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "\t sudoku [-l <progressFile>]" << std::endl << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "\t -l <path> \t specify path of progress file to load, optional" << std::endl;
              << std::endl;
}

int main(int argc, char* argv[])
{
#if _TEST_
    test_case1();
    getchar();
#else
    SceneC scene;

    if(argc == 1)
    {
        int eraseGridNumber = inputDifficulty();
        scene.Generate();
        scene.EraseRandomGrids(eraseGridNumber);
    }
    else if(argc == 3 && !strcmp(argv[1], "-l"))
    {
        scene.Load(argv[2]);
    }
    else
    {
        printHelp();
        return 0;
    }

    scene.Play();
#endif

    return 0;
}