#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

static struct GameData {
    int player1Y = 0;
    int player2Y = 0;
    int player1X = 0;
    int player2X = 0;
    int ballX = 0;
    int ballY = 0;
} game_data;

class MakeBall {
private:

public:
    SDL_Texture* texture = nullptr;
    SDL_Surface* tmp = IMG_Load("Ygg_token.png");

};

class MyGame {

private:
    SDL_Rect player1 = { 60, 0, 20, 60 };
    SDL_Rect player2 = { 700, 0, 20, 60 };
    SDL_Rect ball = {0, 0, 10, 10 };

public:
    std::vector<std::string> messages;

    void on_receive(std::string message, std::vector<std::string>& args);
    void send(std::string message);
    void input(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
};

class FX {

public:
    SDL_Surface* imgP1 = SDL_LoadBMP("Player1.bmp");
};

#endif