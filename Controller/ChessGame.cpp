#include "ChessGame.h"

ChessPiece::ChessPiece(const Texture& texture, int pieceType, float x, float y, int size) {
    sprite.setTexture(texture);
    int xTex = abs(pieceType) - 1;
    int yTex = (pieceType > 0) ? 0 : 1;
    sprite.setTextureRect(IntRect(size * xTex, size * yTex, size, size));
    sprite.setPosition(x, y);
}

Sprite& ChessPiece::getSprite() {
    return sprite;
}

ChessGame::ChessGame()
    : window(VideoMode(454, 455), "Chess-Game"), currentMoveIndex(-1) {
    loadTextures();
    initializeBoard();
}

void ChessGame::loadTextures() {
    textureFigures = std::make_unique<Texture>();
    textureFigures->loadFromFile("C:/Skole/C++/Chess_cmake/ChessGame/Images/figures.png");

    textureBoard = std::make_unique<Texture>();
    textureBoard->loadFromFile("C:/Skole/C++/Chess_cmake/ChessGame/Images/board0.png");
}

void ChessGame::initializeBoard() {
    int board[8][8] = {
        -1, -2, -3, -4, -5, -3, -2, -1,
        -6, -6, -6, -6, -6, -6, -6, -6,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
         6,  6,  6,  6,  6,  6,  6,  6,
         1,  2,  3,  4,  5,  3,  2,  1
    };

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int n = board[i][j];
            if (n != 0) {
                pieces.push_back(std::make_unique<ChessPiece>(*textureFigures, n, size * j, size * i, size));
            }
        }
    }
}

std::string ChessGame::toChessNote(const Vector2f& p) {
    std::string s;
    s += char(p.x / size + 97);
    s += char(7 - p.y / size + 49);
    return s;
}

Vector2f ChessGame::toCoord(char a, char b) {
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    return Vector2f(x * size, y * size);
}

void ChessGame::move(const std::string& str) {
    Vector2f oldPos = toCoord(str[0], str[1]);
    Vector2f newPos = toCoord(str[2], str[3]);

    for (auto& piece : pieces) {
        if (piece->getSprite().getPosition() == newPos) {
            piece->getSprite().setPosition(-100, -100);
        }
    }

    for (auto& piece : pieces) {
        if (piece->getSprite().getPosition() == oldPos) {
            piece->getSprite().setPosition(newPos);
        }
    }
}

void ChessGame::selectPiece(const Vector2i& mousePos) {
    for (size_t i = 0; i < pieces.size(); ++i) {
        if (pieces[i]->getSprite().getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            currentMoveIndex = i;
            return;
        }
    }
}

void ChessGame::movePiece(const Vector2i& mousePos) {
    if (currentMoveIndex >= 0 && currentMoveIndex < pieces.size()) {
        Vector2f oldPos = pieces[currentMoveIndex]->getSprite().getPosition();
        Vector2f newPos = Vector2f(size * int(mousePos.x / size), size * int(mousePos.y / size));
        std::string moveStr = toChessNote(oldPos) + toChessNote(newPos);
        move(moveStr);
        boardPosition += moveStr + "";
        pieces[currentMoveIndex]->getSprite().setPosition(newPos);
        currentMoveIndex = -1;
    }
}

void ChessGame::handleEvents() {
    Vector2i mousePos = Mouse::getPosition(window);
    Event e;
    while (window.pollEvent(e)) {
        if (e.type == Event::Closed) {
            window.close();
        }
        if (e.type == Event::KeyPressed && e.key.code == Keyboard::BackSpace) {
            if (boardPosition.length() >= 5) {
                boardPosition.erase(boardPosition.length() - 5);
                // Load position logic here if needed
            }
        }
        if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
            selectPiece(mousePos);
        }
        if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left) {
            movePiece(mousePos);
        }
    }
}

void ChessGame::render() {
    window.clear();
    Sprite boardSprite(*textureBoard);
    window.draw(boardSprite);
    for (const auto& piece : pieces) {
        window.draw(piece->getSprite());
    }
    window.display();
}

void ChessGame::update() {
    // Update logic can be added here if needed
}

void ChessGame::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}
