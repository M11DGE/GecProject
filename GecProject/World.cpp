#include "World.h"
#include "Player.h"
#include "Enemy.h"
#include "Floor.h"
#include "Background.h"
#include "Wall.h"
#include "Projectile.h"
#include <SFML/Audio.hpp>

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
    if(!m_graphics->LoadTexture("PAttack Ani", "Data/Textures/CyberSprites/2 Punk/PunkAttack.png"))
		return false;
    if (!m_graphics->LoadTexture("PWalk Ani", "Data/Textures/CyberSprites/2 Punk/PunkRun.png"))
        return false;
    if (!m_graphics->LoadTexture("PHurt Ani", "Data/Textures/CyberSprites/2 Punk/PunkHurt.png"))
        return false;
    if (!m_graphics->LoadTexture("PAttackRange Ani", "Data/Textures/CyberSprites/2 Punk/PunkAttack3.png"))
        return false;
    if (!m_graphics->LoadTexture("PIdle Ani", "Data/Textures/CyberSprites/2 Punk/PunkIdle.png"))
        return false;
    if (!m_graphics->LoadTexture("PDead Ani", "Data/Textures/CyberSprites/2 Punk/PunkDead.png"))
        return false;
    if (!m_graphics->LoadTexture("Background4", "Data/Textures/CyberpunkWorld/Backgrounds/2/Day/1.png"))
        return false;
    if (!m_graphics->LoadTexture("Background3", "Data/Textures/CyberpunkWorld/Backgrounds/2/Day/2.png"))
        return false;
    if (!m_graphics->LoadTexture("Background2", "Data/Textures/CyberpunkWorld/Backgrounds/2/Day/3.png"))
        return false;
    if (!m_graphics->LoadTexture("Background1", "Data/Textures/CyberpunkWorld/Backgrounds/2/Day/5.png"))
        return false;
    if (!m_graphics->LoadTexture("Road", "Data/Textures/Road.png"))
        return false;
    if (!m_graphics->LoadTexture("Barb", "Data/Textures/Wall.png"))
        return false;
    if (!m_graphics->LoadTexture("DamagedWall", "Data/Textures/DamagedWall.png"))
        return false;
    if (!m_graphics->LoadTexture("Projectile Ani", "Data/Textures/Projectile.png"))
        return false;
    return true;
}

void World::CreateSprites()
{
    Player* newPlayer = new Player("Player", m_graphics);
    m_entityVec.push_back(newPlayer);
    for (int i = 0; i < 30; i++)
    {
        std::string enemyName = "Enemy" + std::to_string(i);
        Enemy* newEnemy = new Enemy(enemyName, m_graphics, i);
        m_entityVec.push_back(newEnemy);
    }
	Wall* newWall = new Wall("Wall", { 50, 340 }, m_graphics, "Barb");
	m_entityVec.push_back(newWall);

	Background* newBackground = new Background("Background", { 0,0 }, m_graphics, "Background4", 0.001f, 1);
	m_backgroundVec.push_back(newBackground);
    Background* newBackgrounds = new Background("Background.5", { 1152,0 }, m_graphics, "Background4", 0.001f, 1);
    m_backgroundVec.push_back(newBackgrounds);
	Background* newBackground2 = new Background("Background2", { 0,0 }, m_graphics, "Background3", 0.375f, 1);
	m_backgroundVec.push_back(newBackground2);
    Background* newBackground2s = new Background("Background2.5", { 1152,0 }, m_graphics, "Background4", 0.375f, 1);
    m_backgroundVec.push_back(newBackground2s);
	Background* newBackground3 = new Background("Background3", { 0,0 }, m_graphics, "Background2", 0.75f, 1);
	m_backgroundVec.push_back(newBackground3);
    Background* newBackground3s = new Background("Background3.5", { 1152,0 }, m_graphics, "Background2", 0.75f, 1);
    m_backgroundVec.push_back(newBackground3s);
	Background* newBackground4 = new Background("Background4", { 0,0 }, m_graphics, "Background1", 1.5, 1);
	m_backgroundVec.push_back(newBackground4);
    Background* newBackground4s = new Background("Background4.5", { 1152,0 }, m_graphics, "Background1", 1.5, 1);
    m_backgroundVec.push_back(newBackground4s);
    Background* roadFloor = new Background("road", { 0, 324 }, m_graphics, "Road", 0, 2);
    m_backgroundVec.push_back(roadFloor);


}

int World::Run()
{
    sf::Clock fpsTimer;
    fpsTimer.start();
	m_clock.start();
    int frame = 0;
    int i = 0;
    std::srand(time(nullptr));

	sf::SoundBuffer m_shootBuffer;
	m_shootBuffer.loadFromFile("Data/Textures/Pew.wav");
	sf::Sound m_shootSound(m_shootBuffer);


    sf::Font font("Font.ttf");
    sf::Text m_deathMessage(font);
    m_deathMessage.setString("Game Over");
    m_deathMessage.setCharacterSize(100);
    m_deathMessage.setPosition({ 150,300 });
    m_deathMessage.setFillColor(sf::Color::Red);
    m_deathMessage.setFont(font);
    sf::Text m_pointsMsg(font);
	m_pointsMsg.setString("Points: " + std::to_string(m_playerPoints));
	m_pointsMsg.setCharacterSize(30);
	m_pointsMsg.setPosition({ 10, 10 });
	m_pointsMsg.setFillColor(sf::Color::Red);
    m_pointsMsg.setFont(font);

    LoadTextures();
	CreateSprites();

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "GEC Start Project");
    if (!ImGui::SFML::Init(window))
        return -1;

    sf::Clock uiDeltaClock;
    window.setFramerateLimit(60);

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
            if (m_gameOver == false)
            {
                m_pointsMsg.setString("Points: " + std::to_string(m_playerPoints));
                window.clear();
                if (m_clock.getElapsedTime().asMilliseconds() >= 20)
                {
                    UpdateBackgrounds();
                    m_clock.restart();
                }

                for (auto& entity : m_entityVec)
                {
                    bool collided = false;

                    for (auto& entity2 : m_entityVec)
                    {
                        if (entity == entity2) continue;  // skip self

                        if (entity->CheckCollision(entity2, m_graphics))
                            collided = true;
                    }

                    entity->SetColliding(collided);
                }

                for (auto background : m_backgroundVec)
                {
                    background->Update(window, m_graphics);
                }

                std::vector<Entity*> toAdd;
                std::vector<Entity*> toRemove;

                for (auto entity : m_entityVec)
                {
                    i++;;
                    entity->Update(window, m_graphics);
                    entity->ResetCollisionFlags();

                    if (entity->GetSpawnProj())
                    {
                        Projectile* newProj = new Projectile("Projectile"+i, m_graphics, entity->GetProjSpawnPoint(), entity->GetFacingDirection());
                        toAdd.push_back(newProj);
                        entity->SetSpawnProj(false);
                    }

                    if (entity->ShouldDestroy())
                    {
                        if (entity->GetName() == "Zombie")
                        {
                            m_playerPoints += 100;
                        }
                        toRemove.push_back(entity);
                    }
                }
				window.draw(m_pointsMsg);

                if (!toAdd.empty()) {
                    m_entityVec.insert(m_entityVec.end(), toAdd.begin(), toAdd.end());
                }

                for (auto rem : toRemove)
                {
                    if (rem->GetWinCondition() == true or m_playerPoints >= 3000)
                        m_gameOver = true;
                    auto it = std::find(m_entityVec.begin(), m_entityVec.end(), rem);
                    if (it != m_entityVec.end())
                    {
                        delete* it;
                        m_entityVec.erase(it);
                    }
                }
            }
            if (m_gameOver == true)
            {
                window.clear();
                window.draw(m_pointsMsg);
                window.draw(m_deathMessage);
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

void World::UpdateBackgrounds()
{
    for (auto background : m_backgroundVec)
    {
        background->Move(m_graphics);
	}
	if (m_backgroundVec[2]->GetPos().x <= -1152)
    {
        m_backgroundVec[2]->SetPosX(m_backgroundVec[3]->GetPos().x + 1152);
    }
    if (m_backgroundVec[3]->GetPos().x <= -1152)
    {
        m_backgroundVec[3]->SetPosX(m_backgroundVec[2]->GetPos().x + 1152);
    }
    if (m_backgroundVec[4]->GetPos().x <= -1152)
    {
        m_backgroundVec[4]->SetPosX(m_backgroundVec[5]->GetPos().x + 1152);
    }
    if (m_backgroundVec[5]->GetPos().x <= -1152)
    {
        m_backgroundVec[5]->SetPosX(m_backgroundVec[4]->GetPos().x + 1152);
    }
    if (m_backgroundVec[6]->GetPos().x <= -1152)
    {
        m_backgroundVec[6]->SetPosX(m_backgroundVec[7]->GetPos().x + 1152);
    }
    if (m_backgroundVec[7]->GetPos().x <= -1152)
    {
        m_backgroundVec[7]->SetPosX(m_backgroundVec[6]->GetPos().x + 1152);
    }
}
