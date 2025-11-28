/*
    GecProject - For GEC students to use as a start point for their projects.
    Already has SFML linked and ImGui set up.
*/

#include "ExternalHeaders.h"
#include "RedirectCout.h"
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "World.h"
#include "Rectangle.h"
#include "Direction.h"
#include <vector>

float x = 50;
float y = 50;
int scale = 0;
int state = 0;
float height = 65.125f;
int fps = 0;
int frames = 0;

int main()
{
    // Redirect cout to the Visual Studio output pane
    outbuf ob;
    std::streambuf* sb{ std::cout.rdbuf(&ob) };

    // Redirect cerr
    outbuferr oberr;
    std::streambuf* sberr{ std::cerr.rdbuf(&oberr) };

    // Turn on memory leak checking
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    World* world = new World;
    world->Run();

    return 0;
}

/* 
    Use IMGUI for a simple on screen GUI
    See: https://github.com/ocornut/imgui/wiki/
*/