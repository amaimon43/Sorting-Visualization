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
    bool m_movingX = 0, m_movingY = 0;
    float m_Speed, m_movedX = 0, m_movedY = 0;

  public:
    bool m_move;
    Card(int num = 0, float startX = 50, float startY = 50);
    void update(Time dt);
    FloatRect getPosition();
    Sprite getSprite();
    float getHeight();
    void setValue(int num, float startX, float startY);
    Text getNumber();
    void moveX();
    void moveY();
    void stopX();
    void stopY();
};
