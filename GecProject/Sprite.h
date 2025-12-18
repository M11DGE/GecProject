#pragma once
#include "AnimationSetData.h"
#include <unordered_map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "Direction.h"

struct AnimationSet
{
	AnimationSetData setData;
	sf::Texture* sfmlTexture{ nullptr };
	AnimationSet(const AnimationSetData& setDataData, sf::Texture* texture);
	AnimationSet(){}
};

class Sprite
{
private:
	std::unordered_map<std::string, AnimationSet> m_AnimationSet;
	int m_frameNum = 0;
	int m_flip = 1;
	bool m_midAnimation = false;
	std::string m_name;
	Direction m_currentDir = Direction::Right;
	Direction m_collisionDir = Direction::None;
	MyRectangle* m_rectangle;
	std::string m_currentTex;
	sf::Sprite* m_sprite;
	sf::Vector2i m_intRectSize = sf::Vector2i(432, 521);
public:
	Sprite(sf::Texture* texture, std::string name) { m_sprite = new sf::Sprite(*texture), m_name = name, m_sprite, m_rectangle = new MyRectangle; }
	~Sprite() { delete m_sprite; delete m_rectangle; }
	void AddAnimationSet(const std::string& name,const AnimationSetData& setData, sf::Texture* texture);
	void DrawSprite(sf::RenderWindow& window);
	void Update(sf::Clock& clock);
	void Update();
	std::string GetSpriteName();
	void ChangeTexture(const std::string& textureName, const bool& midAnimation);
	sf::Vector2f GetPos();
	void SetPos(const sf::Vector2f& amount);
	void SetScale(const sf::Vector2f& scale);
	sf::Vector2f GetScale();;
	std::string GetCurrentTex() { return m_currentTex; }
	int GetFramNum() { return m_frameNum; }
};

