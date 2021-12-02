#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <dos.h>

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

class Ball_texture_data {
private:

public:
    SDL_Texture* texture = nullptr;
    SDL_Surface* ball_sf_tmp = IMG_Load("assets/ball.png");

    void make_texture(SDL_Renderer* renderer) {
        texture = SDL_CreateTextureFromSurface(renderer, ball_sf_tmp);
        SDL_FreeSurface(ball_sf_tmp);
    }
};


class Particle_engine {

private:
    SDL_Rect small_rect;
    float max_lifetime = 0.2;
    int lifetime;
    int max_amount = 100;

    float oldX;
    float newX;

    std::vector<SDL_Rect> o;

public:

    int get_maxamount() {
        return max_amount;
    }

    int get_size() {
        return o.size();
    }

    SDL_Rect get_at(int i) {
        return o.at(i);
    }

    void update_particles(SDL_Renderer* renderer) {

        oldX = game_data.ballX;

        while (o.size() < max_amount)
        {
            small_rect = { game_data.ballX, game_data.ballY, 5, 5 };
            o.push_back(small_rect);
        }

        if (lifetime == 0)
        {
            o.erase(o.begin());
            lifetime = max_lifetime;
        }

        srand(time(0));
        int number = (int)rand() % 30;

        for (int i = 0; i < o.size(); i++)
        {
            if (oldX < newX)
            {
                o.at(i).x += number;
            }
            else
            {
                o.at(i).x -= number;
            }
            o.at(i).y += number%10;
        }
        newX = game_data.ballX;
        lifetime -= 0.2f;
    }
};


class MyGame {

private:
    SDL_Rect player1_data = { 60, 0, 20, 60 };
    SDL_Rect player2_data = { 70, 0, 20, 60 };
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