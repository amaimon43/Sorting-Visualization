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
    int numInsideCard[numOfCards] = {8, 7, 6, 5, 4, 3, 2, 1};
    int numInsideCardSorted[numOfCards] = {8, 7, 6, 5, 4, 3, 2, 1};
    Card card[numOfCards];
    Sort(numInsideCardSorted, numOfCards);
    int movers[2];

    for (int i = 0; i < save.size(); i++) {
        for (int j = 0; j < save[i].size(); j++) {
            std::cout << save[i][j] << " ";
        }
        std::cout << std::endl;
    }

    Button buttonLeft;
    Button buttonRight;
    buttonRight.putUnclickedTexture("./button_sprites/right.png");
    buttonRight.putClickedTexture("./button_sprites/GreenRight.png");
    buttonLeft.putUnclickedTexture("./button_sprites/Left.png");
    buttonLeft.putClickedTexture("./button_sprites/GreenLeft.png");
    buttonLeft.setPosition(500, 600);
    buttonRight.setPosition(800, 600);

    VideoMode vm(screenWidth, screenHeight);
    RenderWindow window(vm, "Animate", Style::Close);

    for (int i = 0; i < numOfCards; i++) {
        card[i].setValue(numInsideCard[i], 50 + 180 * i, 300);
    }

    Clock clock;
    int p = 0;
    bool onLoop = 1;
    while (window.isOpen()) {

        /* if (onLoop == 1 && card[movers[0]].isItAnimating() == 0 && card[movers[1]].isItAnimating() == 0) { */

        /*     movers[0] = save[p][0]; */
        /*     movers[1] = save[p][1]; */
        /*     /1* if(p>) *1/ */
        /*     p++; */
        /*     if (p > save.size()) onLoop = 0; */
        /* } */
        movers[0] = save[0][0];
        movers[1] = save[0][1];

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        /* if (Keyboard::isKeyPressed(Keyboard::Left)) { */
        /* buttonLeft.clickLeft(); */
        /* card[movers[0]].moveNow(); */
        /* card[movers[1]].moveNow(); */
        /* } else { */
        /* buttonLeft.unclickLeft(); */
        /* card[movers[0]].stopNow(); */
        /* card[movers[1]].stopNow(); */
        /* } */
        if (Keyboard::isKeyPressed(Keyboard::Right) && card[movers[0]].isItAnimating() == 0) {
            buttonRight.clickRight();
            card[movers[0]].moveNow();
            card[movers[0]].animateNow();
            card[movers[1]].moveNow();
            card[movers[1]].animateNow();
        }

        else {
            buttonRight.unclickRight();
            if (card[movers[0]].isItAnimating() == 1) {
                card[movers[0]].moveNow();
                card[movers[1]].moveNow();
                /* card[movers[0]].stopNow(); */
                /* card[movers[1]].stopNow(); */
            } else {
                card[movers[0]].stopNow();
                card[movers[1]].stopNow();
            }
        }

        Time dt = clock.restart();
        for (int i = 0; i < numOfCards; i++) {
            card[i].update(dt);
        }
        buttonLeft.update(dt);
        buttonRight.update(dt);

        if (card[movers[0]].isItAnimating() == 0) {
            card[movers[0]].moveTo(card[movers[1]]);
            card[movers[1]].moveTo(card[movers[0]]);
        }

        window.clear();
        for (int i = 0; i < numOfCards; i++) {
            window.draw(card[i].getSprite());
            window.draw(card[i].getNumber());
        }

        /* window.draw(card[0].getSprite()); */
        /* window.draw(card[0].getNumber()); */
        /* window.draw(card[1].getSprite()); */
        /* window.draw(card[1].getNumber()); */

        window.draw(buttonLeft.getSprite());
        window.draw(buttonRight.getSprite());
        window.display();
    }
}
