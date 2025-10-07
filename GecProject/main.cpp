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

void DefineGUI();

float x = 50;
float y = 50;
int scale = 0;
int state = 0;
float height = 65.125f;
int fps = 0;
int frames = 0;

void Inputs(sf::Sprite &sprite) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        y -= 0.05f;
        state = 3;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        x -= 0.05f;
        state = 3;
        sprite.setScale({ -1, 1 });
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        y += 0.05f;
        state = 3;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        x += 0.05f;
        state = 3;
        sprite.setScale({ 1, 1 });
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        state = 0;

}

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

   sf::Texture attack("Data/Textures/MaleZombie/attack_combined.png");
    if (!attack.loadFromFile("Data/Textures/MaleZombie/attack_combined.png"))
    {
        std::cout << "could not load texture" << std::endl;
        return -1;
    }
    sf::Texture dead("Data/Textures/MaleZombie/dead_combined.png");
    if (!dead.loadFromFile("Data/Textures/MaleZombie/dead_combined.png"))
    {
        std::cout << "could not load texture" << std::endl;
        return -1;
    }
    sf::Texture idle("Data/Textures/MaleZombie/idle_combined.png");
    if (!idle.loadFromFile("Data/Textures/MaleZombie/idle_combined.png"))
    {
        std::cout << "could not load texture" << std::endl;
        return -1;
    }
    sf::Texture walk("Data/Textures/MaleZombie/walk_combined.png");
    if (!walk.loadFromFile("Data/Textures/MaleZombie/walk_combined.png"))
    {
        std::cout << "could not load texture" << std::endl;
        return -1;
    }
    std::unordered_map<int, sf::Texture> zombieTextures = { {1, attack},{2,dead},{3,idle},{4,walk} };

    sf::Clock clock;
    sf::Clock fpsTimer;
    fpsTimer.start();
    sf::Sprite sprite(attack);
    Graphics* graphics = new Graphics;
    
    if (!graphics->LoadTexture("Attack Ani", "Data/Textures/MaleZombie/attack_combined.png"))
        return -1;
    graphics->CreateSprite("Zombie");
    graphics->AddAnimationSet("Zombie", "Attack Ani", AnimationSetData("Attack Ani", 8, 432, 521));
    
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
     
        switch (state)
        {
        case 0:
            sprite.setTexture(zombieTextures[1]);
            sprite.setTextureRect(sf::IntRect({ 0,scale * 521 }, { 432,521 }));
            if (clock.getElapsedTime().asSeconds() >= 0.07f) {
                scale++;
                clock.restart();
                if (scale > 7)
                    scale = 0;
            }
            break;
        case 1:
            sprite.setTexture(zombieTextures[2]);
            sprite.setTextureRect(sf::IntRect({ 0,scale * 528 }, { 631,528 }));
            if (clock.getElapsedTime().asSeconds() >= 0.07f) {
                scale++;
                clock.restart();
                if (scale > 11)
                    scale = 0;
            }
            break;
        case 2:
            sprite.setTexture(zombieTextures[3]);
            sprite.setTextureRect(sf::IntRect({ 0,scale * 521 }, { 432,521 }));
            if (clock.getElapsedTime().asSeconds() >= 0.07f) {
                scale++;
                clock.restart();
                if (scale > 14)
                    scale = 0;
            }
            break;
        case 3:
            sprite.setTexture(zombieTextures[4]);
            sprite.setTextureRect(sf::IntRect({ 0,scale * 521 }, { 432,521 }));
            if (clock.getElapsedTime().asSeconds() >= 0.07f) {
                scale++;
                clock.restart();
                if (scale > 9)
                    scale = 0;
            }
            break;
        }
        frames ++;
        if (fpsTimer.getElapsedTime().asSeconds() >= 1) {
            fps = frames;
            std::cout << fps << std::endl;
            frames = 0;
            fpsTimer.restart();
        }
        
        Inputs(sprite);
        // Clear the window
        window.clear();
       
        // Draw the shape
        //window.draw(sprite);
        graphics->DrawSprite("Zombie", { 50,50 }, "Attack Ani", 0, window, clock);

        // UI needs drawing last
        ImGui::SFML::Render(window);
        

        window.display();
    }

    std::cout << "Finished!" << std::endl;

    delete graphics;

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

    bool result = ImGui::Button("Change animation");      // Buttons return true when clicked (most widgets return true when edited/activated)
    if (result == true) {
        state++;
        scale = 0;
        if (state > 3)
            state = 0;
    }

 //   ImGui::Checkbox("Wireframe", &m_wireframe);	// A checkbox linked to a member variable

  //  ImGui::Checkbox("Cull Face", &m_cullFace);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    std::string fpsText = "fps is " + std::to_string(fps);
    ImGui::Text(fpsText.c_str());

    ImGui::End();
}
