#include "card.h"
#include "screenSize.h"
#include <iostream>
#include <sstream>

Card::Card(int num, float startX, float startY) {
    m_Position.x = startX;
    m_Position.y = startY;

    m_Texture.loadFromFile("./deck_4.png");
    m_Sprite.setTexture(m_Texture);

    m_Sprite.setPosition(m_Position);
}
Sprite Card::getSprite() {
    return m_Sprite;
}
Text Card::getNumber() {
    /* std::cout << std::endl */
    /* << m_Sprite.getOrigin().x << " " << m_Sprite.getOrigin().y << std::endl; */
    return m_number;
}
float Card::getHeight() {
    return m_Position.x;
}
void Card::setValue(int num, float startX, float startY) {
    FloatRect numberRect = m_number.getLocalBounds();
    FloatRect spriteRect = m_Sprite.getLocalBounds();

    /* m_Sprite.setOrigin(spriteRect.left + spriteRect.width / 2.0f, spriteRect.top + spriteRect.height / 2.0f); */
    m_number.setOrigin(numberRect.left + numberRect.width / 2.0f, numberRect.top + numberRect.height / 2.0f);

    m_Position.x = startX;
    m_Position.y = startY;
    m_Texture.loadFromFile("./deck_4.png");
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setPosition(m_Position);

    m_protoNumber << num;
    font.loadFromFile("./DS-DIGI.TTF");
    m_number.setFont(font);
    m_number.setCharacterSize(75);
    m_number.setFillColor(Color::White);
    m_number.setString(m_protoNumber.str());
    m_number.setPosition(m_Sprite.getPosition().x + 43, m_Sprite.getPosition().y + 40);
    /* m_number.setPosition(100, 100); */
}
/* void Card::moveX() { */
/*     m_movingX = 1; */
/* } */
/* void Card::moveY() { */
/*     m_movingY = 1; */
/* } */
/* void Card::stopX() { */
/*     m_movingX = 0; */
/* } */
/* void Card::stopY() { */
/*     m_movingY = 0; */
/* } */
void Card::update(Time dt) {
    if (m_moving) {
        m_Position.x += m_Speed * dt.asSeconds();
        if (m_Position.x > m_moveCoordinates.x) {
            m_Position.x = m_moveCoordinates.x;
            m_moving = 0;
        }
    }
    if (m_movingL) {
        m_Position.x -= m_Speed * dt.asSeconds();
        if (m_Position.x < m_moveCoordinates.x) {
            m_Position.x = m_moveCoordinates.x;
            m_movingL = 0;
        }
    }
    m_Sprite.setPosition(m_Position);
    m_number.setPosition(m_Sprite.getPosition().x + 43, m_Sprite.getPosition().y + 40);
}
void Card::moveTo(int arrayIndex, Card &moveToThisCard) {
    if (!m_moving) {
        m_moving = 1;
        m_movePostn = arrayIndex;
        m_moveCoordinates.x = moveToThisCard.m_Position.x - 10;
        m_moveCoordinates.y = moveToThisCard.m_Position.y - 10;
    }
}
void Card::moveToL(int arrayIndex, Card &moveToThisCard) {
    if (!m_movingL) {
        m_movingL = 1;
        m_movePostn = arrayIndex;
        m_moveCoordinates.x = moveToThisCard.m_Position.x - 10;
        m_moveCoordinates.y = moveToThisCard.m_Position.y - 10;
    }
}
