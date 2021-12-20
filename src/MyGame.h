#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <dos.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>
#include <iostream>
#include <iostream>
#include <string>

static struct GameData {
    int player1Y = 0;
    int player2Y = 0;
    int player1X = 0;
    int player2X = 0;
    int ballX = 0;
    int ballY = 0;
    int score1 = 0;
    int score2 = 0;
    int oldScore = 0;
    int newScore = 0;
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

        if (lifetime <= 0)
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

class dst {
public:
    int x, y;
    int t_width = 200;
    int t_height = 200;

    const SDL_Rect& GetRect() const { SDL_Rect cube = { x, y, t_width, t_height }; return cube; }
};

class Score {
private:
    int fontsize = 24;
    SDL_Color text_color = { 255,0,0 };
    std::string fontpath = "assets/Oswald-Bold.ttf";
    int text = game_data.score1;
    TTF_Font* font = TTF_OpenFont(fontpath.c_str(), fontsize);

public:

    SDL_Texture* ftexture = NULL; // our font-texture
    int t_width = 0; // width of the loaded font-texture
    int t_height = 0; // height of the loaded font-texture

    void renderScore(SDL_Renderer* renderer) {
        // check to see that the font was loaded correctly
        if (font == NULL) {
            std::cout << "Failed the load the font!\n";
            std::cout << "SDL_TTF Error: " << TTF_GetError() << "\n";
        }
        else {
            // now create a surface from the font
            SDL_Surface* text_surface = TTF_RenderText_Solid(font, std::to_string(text).c_str(), text_color);

            // render the text surface
            if (text_surface == NULL) {
                std::cout << "Failed to render text surface!\n";
                std::cout << "SDL_TTF Error: " << TTF_GetError() << "\n";
            }
            else {
                // create a texture from the surface
                ftexture = SDL_CreateTextureFromSurface(renderer, text_surface);

                if (ftexture == NULL) {
                    std::cout  << "Unable to create texture from rendered text!\n";
                }
                else {
                    t_width = text_surface->w; // assign the width of the texture
                    t_height = text_surface->h; // assign the height of the texture

                    // clean up after ourselves (destroy the surface)
                    SDL_FreeSurface(text_surface);
                }
            }
        }
    }
};

class MyGame {

private:
    SDL_Rect player1_data = { 60, 0, 20, 60 };
    SDL_Rect player2_data = { 70, 0, 20, 60 };
    SDL_Rect ball_data = {0, 0, 10, 10 };

    Mix_Chunk* sound;

public:
    std::vector<std::string> messages;

    void on_receive(std::string message, std::vector<std::string>& args);
    void send(std::string message);
    void input(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);

    void init_audio();
    void play_sound();
    void destroy();
};


#endif