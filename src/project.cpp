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

int calcInit(int n);
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
void selectionSort(int arr[], int n) {
    save.push_back({0, 0});
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        save.push_back({min_idx, i});
        swap(&arr[min_idx], &arr[i]);
    }
}
void insertionSort(int arr[], int n) {
    save.push_back({0, 0});
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            save.push_back({j, j + 1});
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
Card *Card::m_array{};
bool Card::drawNumber;
int main() {
    int whichSort = 1;
    int numOfCards;
    std::cout << "Enter number of cards(eg. 5): ";
    std::cin >> numOfCards;
    int numInsideCard[numOfCards];
    int numInsideCardSorted[numOfCards];
    int numInsideCardForReset[numOfCards];
    for (int i = 0; i < numOfCards; i++) {
        int x;
        std::cout << "Enter card no. " << i + 1 << ": ";
        std::cin >> x;
        numInsideCard[i] = x;
    }
    std::cout << "Select sort: " << std::endl;
    std::cout << "\t"
              << "1 for Bubble Sort";
    std::cout << "\t"
              << "2 for Insertion Sort" << std::endl;
    std::cin >> whichSort;
    std::copy(numInsideCard, numInsideCard + numOfCards, numInsideCardSorted);
    /* std::copy(numInsideCard, numInsideCard + numOfCards, numInsideCardForReset); */
    Card card[numOfCards];
    card[0].m_array = card;
    if (whichSort == 1)
        Sort(numInsideCardSorted, numOfCards);
    else if (whichSort == 2)
        insertionSort(numInsideCardSorted, numOfCards);
    /* else if (whichSort == 3) */
    /*     selectionSort(numInsideCardSorted, numOfCards); */
    std::vector<int> movers;
    int savePtr = 0;
    bool leftEnabled = 0, rightEnabled = 1;

    /* for (int i = 0; i < save.size(); i++) { */
    /*     for (int j = 0; j < save[i].size(); j++) { */
    /*         std::cout << save[i][j] << " "; */
    /*     } */
    /*     std::cout << std::endl; */
    /* } */

    int size = save.size();

    Text header[2];
    Text footer;
    Font font;
    font.loadFromFile("../sprites/DS-DIGI.TTF");
    FloatRect headerRect[2];
    for (int i = 0; i < 2; i++) {
        header[i].setFont(font);
        header[i].setCharacterSize(70);

        headerRect[i] = header[i].getLocalBounds();
        header[i].setOrigin(headerRect[i].left +
                                headerRect[i].width / 2.0f,
                            headerRect[i].top +
                                headerRect[i].height / 2.0f);
    }
    if (whichSort == 1)
        header[0].setFillColor(Color(255, 255, 255));
    else
        header[0].setFillColor(Color(255, 255, 255, 100));
    if (whichSort == 2)
        header[1].setFillColor(Color(255, 255, 255));
    else
        header[1].setFillColor(Color(255, 255, 255, 100));
    /* if (whichSort == 3) */
    /*     header[2].setFillColor(Color(255, 255, 255)); */
    /* else */
    /*     header[2].setFillColor(Color(255, 255, 255, 100)); */

    header[0].setString("Bubble Sort");
    header[0].setPosition(25.0 / 100 * 1920 - 235, 100);
    header[1].setString("Insertion Sort");
    header[1].setPosition(75.0 / 100 * 1920 - 200, 100);
    footer.setFont(font);
    footer.setString("Press arrow keys to continue!");
    footer.setFillColor(Color::White);

    FloatRect footerRect = footer.getLocalBounds();
    footer.setOrigin(footerRect.left +
                         footerRect.width / 2.0f,
                     footerRect.top +
                         footerRect.height / 2.0f);
    footer.setPosition(1920 / 2.0f, 900);

    Button buttonLeft;
    Button buttonRight;
    buttonRight.putUnclickedTexture("../sprites/button_sprites/right.png");
    buttonRight.putClickedTexture("../sprites/button_sprites/GreenRight.png");
    buttonLeft.putUnclickedTexture("../sprites/button_sprites/Left.png");
    buttonLeft.putClickedTexture("../sprites/button_sprites/GreenLeft.png");
    buttonLeft.setPosition(610, 600);
    buttonRight.setPosition(1110, 600);

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(screenWidth - 500, screenHeight - 500));
    rectangle.setFillColor(Color::Black);
    rectangle.setOrigin(rectangle.getLocalBounds().left +
                            rectangle.getLocalBounds().width / 2.0f,
                        rectangle.getLocalBounds().top +
                            rectangle.getLocalBounds().height / 2.0f);
    rectangle.setPosition(screenWidth / 2.0, screenHeight / 2.0);

    VideoMode vm(screenWidth, screenHeight);
    RenderWindow window(vm, "Animate", Style::Close);

    int init = calcInit(numOfCards);
    for (int i = 0; i < numOfCards; i++) {
        card[i].setValue(numInsideCard[i], i, init + 180 * i, 300);
    }

    Clock clock;
    movers = save[savePtr];
    Card::drawNumber = 1;
    /* 1 = bubblesort */
    /* 2 = insertionSort */
    while (window.isOpen()) {
        /* window.setKeyRepeatEnabled(false); */
        /* sf::Event event; */
        /* while (window.pollEvent(event)) { */
        /*     if (event.type == sf::Event::MouseButtonPressed) { */
        /*         if (event.mouseButton.button == sf::Mouse::Left) { */
        /*             auto mouse_pos = sf::Mouse::getPosition(window); */
        /*             auto translated_pos = window.mapPixelToCoords(mouse_pos); */
        /*             if (header[1].getGlobalBounds().contains(translated_pos)) { */
        /*                 /1* Card::drawNumber = 0; *1/ */
        /*                 header[1].setFillColor(Color(255, 255, 255)); */
        /*                 header[0].setFillColor(Color(255, 255, 255, 150)); */
        /*                 whichSort = 2; */
        /*                 savePtr = 0; */
        /*                 movers = save[savePtr]; */
        /*                 int init = calcInit(numOfCards); */
        /*                 for (int i = 0; i < numOfCards; i++) { */
        /*                     card[i].setValue(numInsideCardForReset[i], i, init + 180 * i, 300); */
        /*                 } */
        /*                 std::copy(numInsideCardForReset, numInsideCardForReset + numOfCards, numInsideCardSorted); */
        /*                 insertionSort(numInsideCardSorted, numOfCards); */
        /*             } else { */
        /*                 /1* Card::drawNumber = 1; *1/ */
        /*             } */
        /*         } */
        /*     } */
        /* } */
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (card[movers[0]].isItAnimating() == 0 && card[movers[1]].isItAnimating() == 0 && rightEnabled) {
                buttonRight.clickRight();
                if (savePtr < int(size - 1)) {
                    savePtr++;
                    movers = save[savePtr];
                    if (savePtr == int(size - 1)) {
                        rightEnabled = 0;
                    }
                } else {
                    rightEnabled = 0;
                    goto outRight;
                }
                leftEnabled = 1;
                /* std::cout << std::endl */
                /*           << "clickRight:" */
                /*           << "  " */
                /*           << "pointer:   " << savePtr << "     " */
                /*           << movers[0] << "  " << movers[1] << std::endl; */
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
                /* std::cout << std::endl */
                /*           << "clickLeft:" */
                /*           << "  " */
                /*           << movers[0] << "  " << movers[1]; */
                if (savePtr >= 1) {
                    savePtr--;
                    movers = save[savePtr];
                    if (savePtr == 0) leftEnabled = 0;
                } else
                    leftEnabled = 0;
                /* std::cout << "pointer:   " << savePtr << "  " << std::endl; */
            }
        } else
            buttonLeft.unclickLeft();

        Time dt = clock.restart();
        for (int i = 0; i < numOfCards; i++) {
            card[i].update(dt);
        }
        buttonLeft.update(dt);
        buttonRight.update(dt);

        window.clear(Color(26, 26, 26));
        window.draw(rectangle);
        for (int i = 0; i < numOfCards; i++) {
            window.draw(card[i].getSprite());
            /* if (Card::drawNumber != 0) */
            window.draw(card[i].getNumber());
        }
        /* std::cout << Card::drawNumber; */

        window.draw(buttonLeft.getSprite());
        window.draw(buttonRight.getSprite());
        for (int i = 0; i < 2; i++)
            window.draw(header[i]);
        window.draw(footer);
        window.display();
    }
}
int calcInit(int num) {
    if (num % 2 == 1) {
        if (num == 1) return 960;
        else {
            return 960 - 65 + (-180) * (num - 1) * .5;
        }
    } else {
        if (num == 2) return 960 - 25 - 130;
        else {
            return 960 - 25 - 130 + (-180) * (num - 2) * .5;
        }
    }
}
