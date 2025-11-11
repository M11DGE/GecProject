#include "World.h"
#include "Player.h"
#include "Enemy.h"

bool World::LoadTextures()
{
    if (!m_graphics->LoadTexture("Attack Ani", "Data/Textures/MaleZombie/attack_combined.png"))
        return false;
    if (!m_graphics->LoadTexture("Idle Ani", "Data/Textures/MaleZombie/idle_combined.png"))
        return false;
    if (!m_graphics->LoadTexture("Dead Ani", "Data/Textures/MaleZombie/dead_combined.png"))
        return false;
    if (!m_graphics->LoadTexture("Walk Ani", "Data/Textures/MaleZombie/walk_combined.png"))
        return false;
    return true;
}

void World::CreateSprites()
{
    Player* newPlayer = new Player("Player", m_graphics);
    m_entityVec.push_back(newPlayer);
	Enemy* newEnemy = new Enemy("Enemy", m_graphics);
	m_entityVec.push_back(newEnemy);
}

int World::Run()
{
    sf::Clock fpsTimer;
    fpsTimer.start();
	m_clock.start();
    int frame = 0;

    LoadTextures();
	CreateSprites();

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "GEC Start Project");
    if (!ImGui::SFML::Init(window))
        return -1;

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

        if (fpsTimer.getElapsedTime().asSeconds() >= 1)
        {
            m_fps = frame;
            frame = 0;
            fpsTimer.restart();
        }
            frame ++;

        //Clear the window
        window.clear();
        for (auto entity : m_entityVec)
            entity->Update(window, m_graphics);


        for (auto entity : m_entityVec)
        {
            for (auto entity2 : m_entityVec)
				entity->CheckCollision(m_graphics, entity2->GetName(), entity2->GetRectangle(m_graphics));
        }


        // UI needs drawing last
        ImGui::SFML::Render(window);


        window.display();
    }

    std::cout << "Finished!" << std::endl;


    ImGui::SFML::Shutdown();

    return 0;
}

void World::update()
{

}

void World::DefineGUI()
{
    // Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::Begin("GEC");				// Create a window called "3GP" and append into it.

    ImGui::Text("Some Text.");	      	// Display some text (you can use a format strings too)	

    //   ImGui::Checkbox("Wireframe", &m_wireframe);	// A checkbox linked to a member variable

     //  ImGui::Checkbox("Cull Face", &m_cullFace);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    std::string fpsText = "fps is " + std::to_string(m_fps);
    ImGui::Text(fpsText.c_str());

    ImGui::End();
}
