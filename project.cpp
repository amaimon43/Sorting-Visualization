#include "buttons.h"
#include "card.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ostream>
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
    save.push_back({0, 0});
    for (int i = 0; i < numOfCards - 1; i++) {
        for (int p = 0; p < numOfCards - i - 1; p++) {
            if (numInsideCard[p] > numInsideCard[p + 1]) {
                save.push_back({p, p + 1});
                swap(&numInsideCard[p], &numInsideCard[p + 1]);
            }
        }
    }
}
Card *Card::m_array{};
int main() {
    int numOfCards;
    std::cout << "Enter number of cards: ";
    std::cin >> numOfCards;
    int numInsideCard[numOfCards];
    int numInsideCardSorted[numOfCards];
    for (int i = 0; i < numOfCards; i++) {
        int x;
        std::cout << "Enter card no. " << i + 1 << ":";
        std::cin >> x;
        numInsideCard[i] = x;
    }
    std::copy(numInsideCard, numInsideCard + numOfCards, numInsideCardSorted);
    Card card[numOfCards];
    card[0].m_array = card;
    Sort(numInsideCardSorted, numOfCards);
    std::vector<int> movers;
    int savePtr = 0;
    bool leftEnabled = 0, rightEnabled = 1;

    for (int i = 0; i < save.size(); i++) {
        for (int j = 0; j < save[i].size(); j++) {
            std::cout << save[i][j] << " ";
        }
        std::cout << std::endl;
    }
    int size = save.size();

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
        card[i].setValue(numInsideCard[i], i, 50 + 180 * i, 300);
    }

    Clock clock;
    movers = save[savePtr];
    while (window.isOpen()) {

        /* movers[0] = save[0][0]; */
        /* movers[1] = save[0][1]; */
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (card[movers[0]].isItAnimating() == 0 && card[movers[1]].isItAnimating() == 0 && rightEnabled) {
                buttonRight.clickRight();
                if (savePtr < int(size - 1)) {
                    savePtr++;
                    movers = save[savePtr];
                } else {
                    rightEnabled = 0;
                    goto outRight;
                }
                leftEnabled = 1;
                std::cout << std::endl
                          << "clickRight:"
                          << "  "
                          << "pointer:   " << savePtr << "     "
                          << movers[0] << "  " << movers[1] << std::endl;
                card[movers[0]].moveNow();
                card[movers[0]].animateNow();
                card[movers[1]].moveNow();
                card[movers[1]].animateNow();
                card[movers[0]].moveTo(card[movers[1]]);
            outRight:;
            }
        } else {
            buttonRight.unclickRight();
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (card[movers[0]].isItAnimating() == 0 && card[movers[1]].isItAnimating() == 0 && leftEnabled) {
                buttonLeft.clickLeft();
                rightEnabled = 1;
                card[movers[0]].moveNow();
                card[movers[0]].animateNow();
                card[movers[1]].moveNow();
                card[movers[1]].animateNow();
                card[movers[0]].moveTo(card[movers[1]]);
                std::cout << std::endl
                          << "clickLeft:"
                          << "  "
                          << movers[0] << "  " << movers[1];
                if (savePtr > 0) {
                    savePtr--;
                    movers = save[savePtr];
                    if (savePtr == 0) leftEnabled = 0;
                } else
                    leftEnabled = 0;
                std::cout << "pointer:   " << savePtr << "  " << std::endl;
            }
        } else
            buttonLeft.unclickLeft();

        /* if (incrementFlag == 1 && savePtr < int(size)) { */
        /*     savePtr++; */
        /*     movers = save[savePtr]; */
        /*     incrementFlag = 0; */
        /* } */

        Time dt = clock.restart();
        for (int i = 0; i < numOfCards; i++) {
            card[i].update(dt);
            /* if (card[i].getPositionx() > card[i].getMoveCoordinatex()) { */
            /*     card[i].setPositionx(card[i].getMoveCoordinatex()); */
            /*     card[i].stopNow(); */
            /*     card[i].stopAnimation(); */
            /* } */
            /* else if(card[i].getPositionx()<card[i].getMoveCoordinatex()){ */
            /*     card[i].setPositionx(card[i].getMoveCoordinatex()); */
            /* } */
        }
        buttonLeft.update(dt);
        buttonRight.update(dt);

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

        /* if (decrementFlag == 1 && savePtr != 0) { */
        /*     savePtr--; */
        /*     movers = save[savePtr]; */
        /*     decrementFlag = 0; */
        /* } */
    }
}
