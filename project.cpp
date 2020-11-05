#include "buttons.h"
#include "card.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
using namespace sf;

float screenWidth = 1920;
float screenHeight = 1080;

std::vector<std::vector<int>> save;
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void Sort(int numInsideCard[], int numOfCards) {
    for (int i = 0; i < numOfCards - 1; i++) {
        for (int p = 0; p < numOfCards - i - 1; p++) {
            if (numInsideCard[p] > numInsideCard[p + 1]) {
                save.push_back({p, p + 1});
                swap(&numInsideCard[p], &numInsideCard[p + 1]);
            }
        }
    }
}

int main() {
    const int numOfCards = 8;
    int numInsideCard[numOfCards] = {1, 20, 3, 4, 5, 6, 7, 2};
    Card card[numOfCards];
    Sort(numInsideCard, numOfCards);

    /* for (int i = 0; i < save.size(); i++) { */
    /*     for (int j = 0; j < save[i].size(); j++) { */
    /*         std::cout << save[i][j] << " "; */
    /*     } */
    /*     std::cout << std::endl; */
    /* } */

    Button buttonLeft;
    buttonLeft.putUnclickedTexture("./button_sprites/Left.png");
    buttonLeft.putClickedTexture("./button_sprites/GreenLeft.png");
    buttonLeft.setPosition(500, 500);

    VideoMode vm(screenWidth, screenHeight);
    RenderWindow window(vm, "Animate", Style::Close);

    for (int i = 0; i < numOfCards; i++) {
        card[i].setValue(numInsideCard[i], 50 + 180 * i, 500);
    }

    Clock clock;
    while (window.isOpen()) {
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) buttonLeft.clickLeft();
        else
            buttonLeft.unclickLeft();

        Time dt = clock.restart();
        /* for (int i = 0; i < numOfCards; i++) { */
        /*     card[i].update(); */
        /* } */
        buttonLeft.update(dt);
        window.clear();
        for (int i = 0; i < numOfCards; i++) {
            window.draw(card[i].getSprite());
            window.draw(card[i].getNumber());
        }
        window.draw(buttonLeft.getSprite());
        window.display();
    }
}
