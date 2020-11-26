#include "card.h"
#include "screenSize.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <type_traits>
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
    return m_number;
}
float Card::getPositionx() {
    return m_Position.x;
}
float Card::getPositiony() {
    return m_Position.y;
}
void Card::setValue(int num, int positionNumber, float startX, float startY) {
    m_positionNumber = positionNumber;
    FloatRect numberRect = m_number.getLocalBounds();
    FloatRect spriteRect = m_Sprite.getLocalBounds();

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
    /* m_number.setPosition(m_Sprite.getPosition().x + 43, m_Sprite.getPosition().y + 40); */
}
void Card::clearStream() {

    m_protoNumber.clear(); //clear any bits set
    m_protoNumber.str(std::string());
}
int Card::isItMoving() {
    return m_moving;
}
void Card::moveTo(Card &moveToThisCard) {
    m_moveCoordinates.x = moveToThisCard.m_Position.x;
    m_moveCoordinates.y = moveToThisCard.m_Position.y;
    moveToThisCard.m_moveCoordinates.x = m_Position.x;
    moveToThisCard.m_moveCoordinates.y = m_Position.y;
    m_R = (pow(pow((m_Position.x - m_moveCoordinates.x), 2) + pow((m_Position.y - m_moveCoordinates.y), 2), 1.0 / 2)) / 2;
    m_Cx = (m_Position.x + m_moveCoordinates.x) / 2;
    m_Cy = (m_Position.y + m_moveCoordinates.y) / 2;
    Card tempCard = std::move(*this);
    m_array[m_positionNumber] = std::move(moveToThisCard);
    m_array[moveToThisCard.m_positionNumber] = std::move(tempCard);
    int temp = m_positionNumber;
    m_positionNumber = moveToThisCard.m_positionNumber;
    moveToThisCard.m_positionNumber = temp;
}
void Card::update(Time dt) {
    if (m_moving == 1) {
        if (m_moveCoordinates.x > m_Position.x) {
            m_Position.x += m_Speed * dt.asSeconds();
            m_Position.y = pow(m_R * m_R - pow(m_Position.x - m_Cx, 2), .5) + m_Cy;
            if (m_Position.x > m_moveCoordinates.x) {
                m_Position.x = m_moveCoordinates.x;
                m_Position.y = m_moveCoordinates.y;
                m_moving = 0;
                m_animating = 0;
            }
        }
        if (m_moveCoordinates.x < m_Position.x) {
            m_Position.x -= m_Speed * dt.asSeconds();
            if (m_Position.x < m_moveCoordinates.x) {
                m_Position.x = m_moveCoordinates.x;
                m_moving = 0;
                m_animating = 0;
            }
        }
    }
    m_Sprite.setPosition(m_Position);
    m_number.setPosition(m_Sprite.getPosition().x + 43, m_Sprite.getPosition().y + 40);
}
void Card::moveNow() {
    m_moving = 1;
}
void Card::stopNow() {
    m_moving = 0;
}
bool Card::isItAnimating() {
    return m_animating;
}
void Card::animateNow() {
    m_animating = 1;
}
void Card::stopAnimation() {
    m_animating = 0;
}
float Card::getMoveCoordinatex() {
    return m_moveCoordinates.x;
}
float Card::getMoveCoordinatey() {
    return m_moveCoordinates.y;
}
