#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "Rectangle.h"
#include "Direction.h"
#include "AnimationSetData.h"
#include <iostream>

struct CollisionFlags
{
	bool top = false;
	bool bottom = false;
	bool left = false;
	bool right = false;

	void Reset()
	{
		top = bottom = left = right = false;
	}
};

class Entity
{
private:

protected:
	int m_health = 0;
	int m_maxHealth = 0;
	int m_flip = 1;
	float m_scale = 1.0f;
	int m_points = 0;
	std::string m_name;
	std::string m_gameName;
	sf::Vector2f m_pos;
	sf::Vector2f m_wandh;
	std::string m_currentAni;
	Direction m_currentDir{ Direction::None };
	Direction m_collisionDir{ Direction::None };
	bool m_isColliding{ false };
	bool m_midAnimation{ false };
	bool m_canCollide{ false };
	bool m_destroy{ false };
	bool m_spawnProj{ false };
	bool m_winCondition{ false };
	MyRectangle m_rectangle;
	CollisionFlags m_collisionFlags;
	std::unordered_map<std::string, AnimationSetData > m_textures;

public:
	Entity() {}
	virtual void Update(sf::RenderWindow& window, Graphics* graphics);
	virtual void Draw(Graphics* graphics, sf::RenderWindow& window) = 0;

	virtual void LoadTextures(Graphics* graphics) = 0;
	void IsAniFinished(Graphics* graphics);
	
	void Gravity(Graphics* graphics);

	std::string GetName();
	sf::Vector2f GetPos();
	void SetPosX(const float& pos) { m_pos.x = pos; }
	bool GetSpawnProj() { return m_spawnProj; }
	sf::Vector2f GetProjSpawnPoint();
	void SetSpawnProj(const bool& spawn) { m_spawnProj = spawn; }
	Direction GetCurrentDir() { return m_currentDir; }
	Direction GetFacingDirection() const { return (m_flip == 1) ? Direction::Right : Direction::Left; }
	bool GetWinCondition() { return m_winCondition; }
	void SetPoints(const int& points) { m_points += points; }
	int GetPoints() { return m_points; }
	
	void ResetCollisionFlags();
	bool IsBlocked(Direction dir) const;

	void SetColliding(bool colliding) { m_isColliding = colliding; }
	bool IsColliding() const { return m_isColliding; }
	virtual bool CheckCollision(Entity* otherEntity, Graphics* graphics);
	sf::Vector2f PushEntity(const MyRectangle& otherRect);

	virtual void UpdateRectangle();
	MyRectangle GetRectangle();

	virtual void MoveEnt(Graphics* graphics);
	void MoveEnt(const sf::Vector2f& distance, Graphics* graphics);
	void Flip(const int& flip, Graphics* graphics);

	virtual void TakeDamage(const int& damage, Graphics* graphics);

	bool ShouldDestroy() { return m_destroy; }

	
};
