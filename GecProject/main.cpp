/*
    GecProject - For GEC students to use as a start point for their projects.
    Already has SFML linked and ImGui set up.
*/

#include "ExternalHeaders.h"
#include "RedirectCout.h"

#include <iostream>
#include <SFML/Graphics.hpp>

void DefineGUI();

float x = 50;
float y = 50;
int scale = 1;
float height = 65.125f;


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

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "GEC Start Project");

    // Set up ImGui (the UI library)
    if (!ImGui::SFML::Init(window))
        return -1;

    // Create a simple shape to draw
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
   

    sf::Texture texture1("Data/Textures/MaleZombie/attack_combined.png");
    if (!texture1.loadFromFile("Data/Textures/MaleZombie/attack_combined.png"))
    {
        std::cout << "could not load texture" << std::endl;
        return-1;
    }


    sf::Sprite sprite(texture1);
    
    // Clock required by ImGui
    sf::Clock uiDeltaClock;
  
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Feed ImGui
            ImGui::SFML::ProcessEvent(window, event.value());

            // User clicked on window close X
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // ImGui must be updated each frame
        ImGui::SFML::Update(window, uiDeltaClock.restart());

        // The UI gets defined each time
        DefineGUI();

        sprite.setPosition({ x,y });
        //sprite.setScale({ scale, scale });
        sprite.setTextureRect(sf::IntRect({ 0,int(scale*521) }, { 432,521 }));

        // Clear the window
        window.clear();
       
        // Draw the shape
        window.draw(sprite);

        // UI needs drawing last
        ImGui::SFML::Render(window);

        window.display();
        scale = (scale + 1) % 8;
    }

    std::cout << "Finished!" << std::endl;

	ImGui::SFML::Shutdown();

    return 0;
}

/* 
    Use IMGUI for a simple on screen GUI
    See: https://github.com/ocornut/imgui/wiki/
*/
void DefineGUI()
{
    // Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::Begin("GEC");				// Create a window called "3GP" and append into it.

    ImGui::Text("Some Text.");	      	// Display some text (you can use a format strings too)	

    ImGui::Button("Button");			// Buttons return true when clicked (most widgets return true when edited/activated)
    
 //   ImGui::Checkbox("Wireframe", &m_wireframe);	// A checkbox linked to a member variable

  //  ImGui::Checkbox("Cull Face", &m_cullFace);

    ImGui::SliderFloat("X", &x, 1, 800);
    ImGui::SliderFloat("Y", &y, 1, 600);
    ImGui::SliderInt("SCALE", &scale, 0, 7);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();
}
