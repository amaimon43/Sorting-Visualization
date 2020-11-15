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
    float m_Speed = 1000;
    bool m_moving = 0, m_animating = 0;
    Vector2f m_moveCoordinates;
    int m_positionNumber;

  public:
    static Card *m_array;
    Card(int num = 0, float startX = 50, float startY = 50);
    void setValue(int num, int positionNumber, float startX, float startY);
    int isItMoving();
    bool isItAnimating();
    void moveNow();
    void stopNow();
    void update(Time dt);
    FloatRect getPosition();
    Sprite getSprite();
    float getHeight();
    Text getNumber();
    void moveTo(Card &moveToThisCard);
    void moveToL(Card &moveToThisCard);
    void animateNow();
    void stopAnimation();
};
