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
    SDL_Surface* tmp = IMG_Load("ball.png");

    void make_texture(SDL_Renderer* renderer) {
        texture = SDL_CreateTextureFromSurface(renderer, tmp);
        SDL_FreeSurface(tmp);
    }
};

class MyGame {

private:
    SDL_Rect player1_data = { 60, 0, 20, 60 };
    SDL_Rect player2_data = { 700, 0, 20, 60 };
    SDL_Rect ball_data = {0, 0, 10, 10 };

public:
    std::vector<std::string> messages;

    void on_receive(std::string message, std::vector<std::string>& args);
    void send(std::string message);
    void input(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
};


#endif