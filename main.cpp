#include "lib.h"
using namespace sf;

const int size = 56; // Size of each square on the chessboard (e.g., 64x64 pixels)
Sprite f[32]; // Array to hold 32 sprites for chess pieces

int board[8][8] =
{ -1,-2,-3,-4,-5,-3,-2,-1,
 -6,-6,-6,-6,-6,-6,-6,-6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6,
  1, 2, 3, 4, 5, 3, 2, 1 };

std::string toChessNote(Vector2f p) {
    std::string s = "";
    s += char(p.x / size + 97);
    s += char(7 - p.y / size + 49);

    return s;
}

// Clear a square

Vector2f toCoord(char a, char b) {
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    
    return Vector2f(x * size, y * size);
}

void move(std::string str) {
    Vector2f oldPos = toCoord(str[0], str[1]);
    Vector2f newPos = toCoord(str[2], str[3]);

    for (size_t i{}; i < 32; i++) {
        if (f[i].getPosition() == newPos) f[i].setPosition(-100, -100);
    }

    for (size_t i{}; i < 32; i++) {
        if (f[i].getPosition() == oldPos) f[i].setPosition(newPos);
    }

}


/*
void loadPos() {
    int k = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int n = board[i][j];
            if (n != 0) {
                int x = abs(n) - 1; // Texture column based on piece type
                int y = (n > 0) ? 0 : 1; // Texture row (0 for white, 1 for black)
                f[k].setTextureRect(IntRect(size * x, size * y, size, size));
                f[k].setPosition(size * j, size * i);
                k++;
            }
        }
    }
}
*/


std::string position = "";
void loadPos(Texture& texture) {
    int k = 0;
    for (size_t i{}; i < 8; i++) {
        for (size_t j{}; j < 8; j++) {
            int n = board[i][j];
            if (n != 0) {
                int x = abs(n) - 1; // Texture column based on piece type
                int y = (n > 0) ? 0 : 1; // Texture row (0 for white, 1 for black)

                // Adjust texture coordinates for the resized pieces
                float scale_x = static_cast<float>(320) / texture.getSize().x;
                float scale_y = static_cast<float>(120) / texture.getSize().y;
                f[k].setTextureRect(IntRect(size * x, size * y, size, size));
                f[k].setScale(scale_x, scale_y);

                f[k].setPosition(size * j, size * i);
                k++;
            }
        }
    }

    for (size_t i{}; i < position.length(); i += 5) {
        move(position.substr(i, 4));
    }
}


int main() {
    RenderWindow window(VideoMode(454, 455), "Chess-Game");
    Texture t1, t2;

    // size Output: 272 X 96
   t1.loadFromFile("C:/Skole/C++/Chess_cmake/Chess_3/Chess_3/figures.png");
    

  // 768x768
     //t2.loadFromFile("C:/Skole/C++/Chess_cmake/Chess_3/Chess_3/board.png");

    t2.loadFromFile("C:/Skole/C++/Chess_cmake/Chess_3/Chess_3/board0.png");
    //t2.loadFromFile("C:/Skole/C++/Chess_cmake/Chess_3/Chess_3/133.png");

    Sprite s(t1);
    Sprite sBoard(t2);

    // Initialize all pieces with the chess pieces texture
    for (size_t i{}; i < 32; i++) f[i].setTexture(t1);


    loadPos(t1); // Set positions for each piece based on board array

    bool isMove = false;
    float dx = 0, dy = 0;
    Vector2f oldPos, newPos;
    std::string str;
    int n{0};
    /*
    sBoard.setPosition((window.getSize().x - sBoard.getGlobalBounds().width) / 2.f,
        (window.getSize().y - sBoard.getGlobalBounds().height) / 2.f);
        

*/
    while (window.isOpen()) {
        Vector2i pos = Mouse::getPosition(window);
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }

            // Move_back

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::BackSpace) {
                    position.erase(position.length() - 6, 5); loadPos(t1);
                }
            }

            // Drag and drop logic
            if (e.type == Event::MouseButtonPressed) {
                if (e.mouseButton.button == Mouse::Left) {
                    for (size_t i{}; i < 32; i++) {
                        // s.get
                        if (f[i] .getGlobalBounds().contains(static_cast<float>(pos.x), static_cast<float>(pos.y))) {
                            isMove = true; 
                            n = i;
                            dx = pos.x - f[i].getPosition().x;
                            dy = pos.y - f[i].getPosition().y;
                            oldPos = f[i].getPosition();
                            break;

                        }
                    }
                }
            }
            if (e.type == Event::MouseButtonReleased) {
                if (e.mouseButton.button == Mouse::Left) {
                    isMove = false;
                    std::cout << "Piece dropped" << std::endl;
                    Vector2f p = f[n].getPosition() + Vector2f(size / 2, size / 2);
                    Vector2f newPos = Vector2f(size * int(p.x / size), size * int(p.y / size));
                    str = toChessNote(oldPos) + toChessNote(newPos);
                    move(str);
                    position += str + "";

                    std::cout << str << std::endl;
                    f[n].setPosition(newPos);
                }
            }
        }


        // cMove

      

      //if (isMove) f[n].setPosition(pos.x - dx, pos.y - dy);

        if (isMove && n != -1) {
            f[n].setPosition(static_cast<float>(pos.x) - dx, static_cast<float>(pos.y) - dy);
            std::cout << "Moving piece: " << n << " to " << pos.x - dx << ", " << pos.y - dy << std::endl;

        }
        

        // Draw //
        window.clear();
        window.draw(sBoard);
        for (int i = 0; i < 32; i++) {
            window.draw(f[i]);
        }
        window.display();
    }

    return 0;
}
