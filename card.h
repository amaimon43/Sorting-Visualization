#pragma once
#include "screenSize.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

class Card {
  private:
    Vector2f m_Position;
    Sprite m_Sprite;
    Texture m_Texture;
    Text m_number;
    std::stringstream m_protoNumber;
    Font font;
    float m_Speed = 50;
    bool m_moving = 0;
    bool m_movingL = 0;
    int m_movePostn;
    Vector2f m_moveCoordinates;

  public:
    Card(int num = 0, float startX = 50, float startY = 50);
    void update(Time dt);
    FloatRect getPosition();
    Sprite getSprite();
    float getHeight();
    void setValue(int num, float startX, float startY);
    Text getNumber();
    void moveTo(int arrayIndex, Card &moveToThisCard);
    void moveToL(int arrayIndex, Card &moveToThisCard);
};
