#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

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


void moveOverlayBox( RectangleShape& overlayBox, float moveAmount, float maxX, float maxY) {
    if (Keyboard::isKeyPressed( Keyboard::Left) && overlayBox.getPosition().x > 0) {
        overlayBox.move(-moveAmount, 0);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right) && overlayBox.getPosition().x < maxX) {
        overlayBox.move(moveAmount, 0);
    }
    else if ( Keyboard::isKeyPressed( Keyboard::Up) && overlayBox.getPosition().y > 0) {
        overlayBox.move(0, -moveAmount);
    }
    else if ( Keyboard::isKeyPressed( Keyboard::Down) && overlayBox.getPosition().y < maxY) {
        overlayBox.move(0, moveAmount);
    }

}
void swapElementsAndUpdate( RectangleShape& overlayBox, int arr[8][8], bool samefound) {
    int i = overlayBox.getPosition().x / 70;
    int j = overlayBox.getPosition().y / 70;

    if ( Keyboard::isKeyPressed( Keyboard::A) && overlayBox.getPosition().y > 0 && j > 0) {
        swap(arr[i][j], arr[i - 1][j]);
        if (!samefound) {
            swap(arr[i ][j], arr[i-1][j]);
        }
    }
    else if ( Keyboard::isKeyPressed( Keyboard::S) && overlayBox.getPosition().x < (70 * 7) && i < 7) {
        swap(arr[i][j], arr[i][j + 1]);
        if (!samefound) {
            swap(arr[i][j], arr[i][j+1]);
        }
    }
    else if ( Keyboard::isKeyPressed( Keyboard::W) && overlayBox.getPosition().x > 0 && i > 0) {
        swap(arr[i][j], arr[i][j - 1]);
        if (!samefound) {
            swap(arr[i][j], arr[i][j-1]);
        }
    }
    else if ( Keyboard::isKeyPressed( Keyboard::D) && overlayBox.getPosition().y < (70 * 7) && j < 7) {
        swap(arr[i][j], arr[i + 1][j]);
        if (!samefound) {
            swap(arr[i][j], arr[i+1][j]);
        }
    }
}


void displayScore( RenderWindow& window, int& score) {
     Font font;

    if (!font.loadFromFile("Esportiva-8M0OM.ttf")) {
        std::cerr << "Error loading font for score" << std::endl;
        return;
    }

     Text scoreText("Score: " + std::to_string(score), font, 30);
    scoreText.setFillColor( Color::Black);
    scoreText.setPosition(10, windowHeight - 40);

    window.draw(scoreText);
}


void removeConsecutiveEntries(int arr[][8],int &score) {
    bool flag = false;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2] && arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j]) {
                arr[i][j] = 0;
                arr[i][j + 1] = 0;
                arr[i][j + 2] = 0;
                arr[i + 1][j] = 0;
                arr[i + 2][j] = 0;
                if (!flag) {
                    score += 10;
                    flag = true;
                }
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2] && arr[i][j] == arr[i - 1][j] && arr[i][j] == arr[i - 2][j]) {
                arr[i][j] = 0;
                arr[i][j + 1] = 0;
                arr[i][j + 2] = 0;
                arr[i - 1][j] = 0;
                arr[i - 2][j] = 0;
                if (!flag) {
                    score += 10;
                    flag = true;
                }
            }
        }
    }

    
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (i + 2 < 8 && j + 2 < 8 &&
                arr[i][j] == arr[i][j + 1] &&
                arr[i][j] == arr[i][j + 2] &&
                arr[i][j] == arr[i + 1][j + 2] &&
                arr[i][j] == arr[i + 2][j + 2]) {
                arr[i][j] = 0;
                arr[i][j + 1] = 0;
                arr[i][j + 2] = 0;
                arr[i + 1][j + 2] = 0;
                arr[i + 2][j + 2] = 0;
                if (!flag) {
                    score += 10;
                    flag = true;
                }
            }
        }
    }

   
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (i + 2 < 8 && j - 2 >= 0 &&
                arr[i][j] == arr[i][j - 1] &&
                arr[i][j] == arr[i][j - 2] &&
                arr[i][j] == arr[i + 1][j - 2] &&
                arr[i][j] == arr[i + 2][j - 2]) {
                arr[i][j] = 0;
                arr[i][j - 1] = 0;
                arr[i][j - 2] = 0;
                arr[i + 1][j - 2] = 0;
                arr[i + 2][j - 2] = 0;
                if (!flag) {
                    score += 10;
                    flag = true;
                }
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8 ; j++) {
            if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2] && arr[i][j] == arr[i][j + 3]) {
                arr[i][j] = 0;
                arr[i][j + 1] = 0;
                arr[i][j + 2] = 0;
                arr[i][j + 3] = 0;
                if (!flag) {
                    score += 7;
                    flag = true;
                }
            }
        }
    }
 
    for (int i = 1; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j]  && arr[i][j]==arr[i+3][j]) {
                arr[i][j] = 0;
                arr[i + 1][j] = 0;
                arr[i + 2][j] = 0;
                arr[i + 3][j] = 0;
                if (!flag) {
                    score += 7;
                    flag = true;
                }
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2]) {
                arr[i][j] = 0;
                arr[i][j + 1] = 0;
                arr[i][j + 2] = 0;
                if (!flag) {
                    score += 10;
                    flag = true;
                }
            }
        }
    }
    for (int i = 1; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i - 1][j]) {
                arr[i][j] = 0;
                arr[i + 1][j] = 0;
                arr[i + 2][j] = 0;
                if (!flag) {
                    score += 10;
                    flag = true;
                }
            }
        }
    }

}

void fillEmptyCells(int arr[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (arr[i][j] == 0 || arr[i][j] < 0) {
                arr[i][j] = rand() % 6 + 1;
            }
        }
    }
}
void drawShapes(RenderWindow& window, int arr[][boardSize], int n) {
    Texture textures[7];
    for (int i = 0; i < 7; i++) {
        textures[i].loadFromFile("shape" + to_string(i + 1) + ".png");
    }
    Texture specialtexture;
    specialtexture.loadFromFile("shape7.png");
    Sprite shape;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] != 0) {
                shape.setTexture(textures[arr[i][j] - 1]);
                shape.setPosition(i * gridSize, j * gridSize);
                shape.setScale(0.25, 0.25);
                window.draw(shape);
            }
            else if (arr[i][j] == 99) {
                shape.setTexture(specialtexture);
                shape.setPosition(i * gridSize, j * gridSize);
                shape.setScale(0.25, 0.25);
                window.draw(shape);
            }
        }
    }
}

void newWindow() {

srand(static_cast<unsigned>(time(nullptr)));
int highscore = 0;
int score = 0;
int temphighscore = 0;
ifstream gethighscore("highscore.txt");
gethighscore >> highscore;

 RenderWindow newWindow;
newWindow.create( VideoMode(windowWidth, windowHeight), "New Window");

// Load background image
 Texture backgroundTexture;

if (!backgroundTexture.loadFromFile("new window back.jpg")) {
    std::cerr << "Error loading background image" << std::endl;
    return;
}
 Sprite backgroundSprite(backgroundTexture);

// Overlay box
 RectangleShape overlayBox( Vector2f(70, 70));
overlayBox.setFillColor( Color::Transparent);
overlayBox.setOutlineColor( Color::Blue);
overlayBox.setOutlineThickness(4.0f);

int arr[boardSize][boardSize];
randomizeArray(arr, boardSize);

removeConsecutiveEntries(arr,score);
fillEmptyCells(arr);

 Clock timer;
 Time elapsedTime;
 Text timerText;
 Font timerFont;

if (!timerFont.loadFromFile("Esportiva-8M0OM.ttf")) {
    std::cerr << "Error loading font for timer" << std::endl;
    return;
}

timerText.setFont(timerFont);
timerText.setCharacterSize(90);
timerText.setFillColor( Color::White);
timerText.setPosition(800, 10);

 RectangleShape timerBox( Vector2f(400, 115));
timerBox.setFillColor( Color::Red);
timerBox.setPosition(800, 5);
//score box
 RectangleShape scoreBox( Vector2f(400, 115));
scoreBox.setFillColor( Color::Red);
scoreBox.setPosition(800, 200);

 RectangleShape highscoreBox( Vector2f(400, 115));
highscoreBox.setFillColor( Color::Red);
highscoreBox.setPosition(800, 400);

// Create a score display text
 Text scoreText;
scoreText.setFont(timerFont);
scoreText.setCharacterSize(90);
scoreText.setFillColor( Color::White);
scoreText.setPosition(800,200);

 Text highscoreText;
highscoreText.setFont(timerFont);
highscoreText.setCharacterSize(90);
highscoreText.setFillColor( Color::White);
highscoreText.setPosition(800, 400);

while (newWindow.isOpen()) {
     Event event;
    while (newWindow.pollEvent(event)) {
        if (event.type ==  Event::Closed) {
            newWindow.close();
        }
        moveOverlayBox(overlayBox, 70.0f, 70.0f * 7, 70.0f * 7);

        if (event.type ==  Event::KeyPressed) {
            swapElementsAndUpdate(overlayBox, arr, sameFound);
        }
    }

    elapsedTime = timer.getElapsedTime();
     Time oneMinute =  seconds(60.0f);

    int remainingSeconds = static_cast<int>(oneMinute.asSeconds() - elapsedTime.asSeconds());
    timerText.setString("time: " + std::to_string(remainingSeconds) + "s");

    if (remainingSeconds <= 0) {
        std::cout << "Time's up!" << std::endl;
        newWindow.close();
    }
  
    removeConsecutiveEntries(arr,score);
   
    fillEmptyCells(arr);

    while (sameFound(arr, boardSize)) {
       
        removeConsecutiveEntries(arr,score);
        
        fillEmptyCells(arr);
    }
    if (score > highscore)
    {
        temphighscore = score;
        ofstream writehighscore("highscore.txt");
        writehighscore << temphighscore;
    }
    
   
    newWindow.clear();
    newWindow.draw(backgroundSprite);
    drawShapes(newWindow, arr, boardSize);
    newWindow.draw(overlayBox);
    newWindow.draw(timerBox);
    newWindow.draw(timerText);
    displayScore(newWindow, score);
    newWindow.draw(scoreBox);
    newWindow.draw(highscoreBox);
    // Display the score
    scoreText.setString("Score: " + std::to_string(score));
    newWindow.draw(scoreText);
    highscoreText.setString("High Score: " + std::to_string(highscore));
    newWindow.draw(highscoreText);

    newWindow.display();
}
}
int main() {
     RenderWindow window;
    window.create( VideoMode(1500, 1000), "my window");
    // loading background image
     Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("newback.jpg")) {
        // handle error if the image fails to load
        std::cerr << "Error loading background image" << std::endl;
        return -1;
    }

    // create sprite for the background
     Sprite backgroundSprite(backgroundTexture);

    // create font for text
     Font font;
     Font fontButton;

    if (!font.loadFromFile("campus personal use.ttf")) {
        // handle error if the font fails to load
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    if (!fontButton.loadFromFile("campus personal use.ttf")) {
        // handle error if the font fails to load
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    // create text object
     Text text("aznawar's pf", font, 100);
    text.setFillColor( Color::Yellow);
    text.setPosition(250, 10);

    // create first block
     RectangleShape block1( Vector2f(300, 100));
    block1.setFillColor( Color::Red);
    block1.setPosition(250, 780);

    // create text for the first block
     Text textBlock1(" Exit", fontButton, 90);
    textBlock1.setFillColor( Color::Black);
    textBlock1.setPosition(250, 780);

    // create second block
     RectangleShape block2( Vector2f(300, 100));
    block2.setFillColor( Color::Green);
    block2.setPosition(250, 670);

    // create text for the second block
     Text textBlock2(" Play", fontButton, 90);
    textBlock2.setFillColor( Color::Black);
    textBlock2.setPosition(250, 670);

    // create arrow

     Texture arrowTexture;

    if (!arrowTexture.loadFromFile("arrow.png")) {
        // handle error if the image fails to load
        std::cerr << "Error loading arrow image" << std::endl;
        return -1;
    }
     Sprite arrowSprite(arrowTexture);
    arrowSprite.setScale(0.01f, 0.01f);
    arrowSprite.setPosition(180, 790);


    while (window.isOpen()) {
         Event event;
        while (window.pollEvent(event)) {
            if (event.type ==  Event::Closed) {
                window.close();
            }
            if (event.type ==  Event::KeyPressed && event.key.code ==  Keyboard::Escape) {
                window.close();
            }

            // handle arrow movement
            if (event.type ==  Event::KeyPressed) {
                // move the arrow up
                if (event.key.code ==  Keyboard::Up && arrowSprite.getPosition().y > block2.getPosition().y) {
                    arrowSprite.move(0, -110);
                }
                // move the arrow down
                else if (event.key.code ==  Keyboard::Down && arrowSprite.getPosition().y < block1.getPosition().y) {
                    arrowSprite.move(0, 110);
                }
                // check if enter key is pressed and the arrow is at the first block
                else if (event.key.code ==  Keyboard::Return &&
                    arrowSprite.getPosition().y >= block1.getPosition().y &&
                    arrowSprite.getPosition().y <= (block1.getPosition().y + block1.getSize().y)) {
                    window.close();
                }
                // check if enter key is pressed and the arrow is at the second block
                else if (event.key.code ==  Keyboard::Return &&
                    arrowSprite.getPosition().y >= block2.getPosition().y &&
                    arrowSprite.getPosition().y <= (block2.getPosition().y + block2.getSize().y)) {
                    newWindow();
                }
            }
        }

        // clear the window
        window.clear();

        // draw the background
        window.draw(backgroundSprite);

        // draw the text
        window.draw(text);
        window.draw(block1);
        window.draw(textBlock1);
        window.draw(block2);
        window.draw(textBlock2);
        window.draw(arrowSprite);


        // display what was drawn
        window.display();
    }


    return 0;
}