#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Button {
  private:
    Vector2f m_Position;
    Sprite m_SpriteClicked;
    Sprite m_SpriteUnclicked;
    Sprite *m_returnSprite;
    Texture m_TextureUnclicked;
    Texture m_TextureClicked;
    bool m_clickingLeft = 0;

  public:
    Sprite getSprite();
    void putUnclickedTexture(std::string location);
    void putClickedTexture(std::string location);
    void update(Time dt);
    void clickLeft();
    void unclickLeft();
    void setPosition(float, float);
};
