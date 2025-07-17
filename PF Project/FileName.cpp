#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

const int gridSize = 70;
const int windowWidth = 1500;
const int windowHeight = 1000;
const int boardSize = 8;

bool sameFound(int arr[][boardSize], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] != 0 &&
                ((j < n - 2 && arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2]) ||
                    (i < n - 2 && arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j]))) {
                arr[i][j] = 0;
                arr[i][j + 1] = 0;
                arr[i][j + 2] = 0;
                return true;
            }
        }
    }
    return false;
}

void randomizeArray(int arr[][boardSize], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = rand() % 6 + 1;
        }
    }
}

void drawShapes(RenderWindow& window, int arr[][boardSize], int n) {
    Texture textures[6];
    for (int i = 0; i < 6; i++) {
        textures[i].loadFromFile("shape" + to_string(i + 1) + ".png");
    }

    Sprite shape;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] != 0) {
                shape.setTexture(textures[arr[i][j] - 1]);
                shape.setPosition(i * gridSize, j * gridSize);
                shape.setScale(0.25, 0.25);
                window.draw(shape);
            }
        }
    }
}
void moveOverlayBox(sf::RectangleShape& overlayBox, float moveAmount, float maxX, float maxY) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && overlayBox.getPosition().x > 0) {
        overlayBox.move(-moveAmount, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && overlayBox.getPosition().x < maxX) {
        overlayBox.move(moveAmount, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && overlayBox.getPosition().y > 0) {
        overlayBox.move(0, -moveAmount);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && overlayBox.getPosition().y < maxY) {
        overlayBox.move(0, moveAmount);
    }

}
void swapElementsAndUpdate(sf::RectangleShape& overlayBox, int arr[8][8], bool samefound) {
    int i = overlayBox.getPosition().x / 70;
    int j = overlayBox.getPosition().y / 70;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && overlayBox.getPosition().y > 0 && j > 0) {
        overlayBox.move(0, -70);
        std::swap(arr[i][j], arr[i - 1][j]);
        if (!samefound) {
            std::swap(arr[i - 1][j], arr[i][j]);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && overlayBox.getPosition().x < (70 * 7) && i < 7) {
        overlayBox.move(70, 0);
        std::swap(arr[i][j], arr[i][j + 1]);
        if (!samefound) {
            std::swap(arr[i][j + 1], arr[i][j]);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && overlayBox.getPosition().x > 0 && i > 0) {
        overlayBox.move(-70, 0);
        std::swap(arr[i][j], arr[i][j - 1]);
        if (!samefound) {
            std::swap(arr[i][j - 1], arr[i][j]);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && overlayBox.getPosition().y < (70 * 7) && j < 7) {
        overlayBox.move(0, 70);
        std::swap(arr[i][j], arr[i + 1][j]);
        if (!samefound) {
            std::swap(arr[i + 1][j], arr[i][j]);
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow newWindow;
    newWindow.create(VideoMode(windowWidth, windowHeight), "New Window");
    ////array
    //int arr[8][8];
    //for (int i = 0;i < 8;i++) {
    //    for (int j = 0;j < 8;j++) {
    //        arr[i][j] = rand() % 6 + 1;
    //    }
    //}
    // Load background image
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("newback.jpg");
    Sprite backgroundSprite(backgroundTexture);
    //overlay box
    sf::RectangleShape overlayBox(sf::Vector2f(70, 70));
    overlayBox.setFillColor(sf::Color::Transparent);
    overlayBox.setOutlineColor(sf::Color::Blue);
    overlayBox.setOutlineThickness(4.0f);

    int arr[boardSize][boardSize];
    randomizeArray(arr, boardSize);
    swapElementsAndUpdate(overlayBox, arr, sameFound);

    while (newWindow.isOpen()) {
        Event event;
        while (newWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                newWindow.close();
            }
            moveOverlayBox(overlayBox, 70.0f, 70.0f * 7, 70.0f * 7);

        }
        //Check for matches and update the array
       //if (sameFound(arr, boardSize)) {
          //  Handle matches (e.g., scoring or game logic)
       //}

       // Draw the background and shapes
        newWindow.clear();
        newWindow.draw(backgroundSprite);
        drawShapes(newWindow, arr, boardSize);
        newWindow.draw(overlayBox);
        newWindow.display();
    }
    //kphpigpoaergfgbhh

    return 0;
}
