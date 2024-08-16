#ifndef CHESSGAME_H
#define CHESSGAME_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

using namespace sf;

class ChessPiece {
public:
    ChessPiece(const Texture& texture, int pieceType, float x, float y, int size);
    Sprite& getSprite();

private:
    Sprite sprite;
};

class ChessGame {
public:
    ChessGame();
    void run();

private:
    void initializeBoard();
    void loadTextures();
    void handleEvents();
    void selectPiece(const Vector2i& mousePos);
    void movePiece(const Vector2i& mousePos);
    void move(const std::string& str);
    std::string toChessNote(const Vector2f& p);
    Vector2f toCoord(char a, char b);
    void render();
    void update();

    RenderWindow window;
    std::unique_ptr<Texture> textureFigures;
    std::unique_ptr<Texture> textureBoard;
    std::vector<std::unique_ptr<ChessPiece>> pieces;
    std::string boardPosition;
    int currentMoveIndex;
    static const int size = 56; // Size of each square on the chessboard
};

#endif // CHESSGAME_H