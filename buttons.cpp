#include "buttons.h"

void Button::putUnclickedTexture(std::string location) {
    m_TextureUnclicked.loadFromFile(location);
    m_SpriteUnclicked.setTexture(m_TextureUnclicked);
}
void Button::putClickedTexture(std::string location) {
    m_TextureClicked.loadFromFile(location);
    m_SpriteClicked.setTexture(m_TextureClicked);
}
void Button::update(Time dt) {

    if (m_clickingLeft || m_clickingRight) m_returnSprite = &m_SpriteClicked;
    else
        m_returnSprite = &m_SpriteUnclicked;
}
void Button::clickLeft() {
    m_clickingLeft = 1;
}
void Button::unclickLeft() {
    m_clickingLeft = 0;
}
void Button::clickRight() {
    m_clickingRight = 1;
}
void Button::unclickRight() {
    m_clickingRight = 0;
}
Sprite Button::getSprite() {
    return *m_returnSprite;
}
void Button::setPosition(float startX, float startY) {
    m_Position.x = startX;
    m_Position.y = startY;

    m_SpriteClicked.setPosition(m_Position);
    m_SpriteUnclicked.setPosition(m_Position);
}
