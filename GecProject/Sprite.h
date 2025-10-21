#pragma once
#include "AnimationSetData.h"
#include <unordered_map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rectangle.h"

 
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
	MyRectangle* m_rectangle;
	std::string m_currentTex;
	sf::Sprite* m_sprite;
	sf::Vector2i m_intRectSize = sf::Vector2i(432, 521);
public:
	Sprite(sf::Texture* texture) { m_sprite = new sf::Sprite(*texture), m_rectangle = new MyRectangle; }
	void AddAnimationSet(const std::string& name,const AnimationSetData& setData, sf::Texture* texture);
	void DrawSprite(sf::Vector2f, const std::string& spriteAnimationSet, sf::RenderWindow& window);
	void Update(sf::Clock& clock, const MyRectangle& rect);
	void ChangeTexture(const std::string& textureName);
	sf::Vector2f GetPos();
	void SetPos(const sf::Vector2f& amount);
	void Flip(const int& flip);
	MyRectangle GetRect();
};

