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

    int oldScore1 = 0;
    int newScore1 = 0;

    int oldScore2 = 0;
    int newScore2 = 0;
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
    float max_lifetime = 5;
    int lifetime;
    int max_amount = 1000;

    float oldX;
    float newX;
    

    float number = 0.5; //(int)rand() % 5;

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

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);

        newX = game_data.ballX;
        srand(time(0));

        while (o.size() < max_amount)
        {
            small_rect = { game_data.ballX, game_data.ballY, 1, 1 };
            o.push_back(small_rect);
        }


        lifetime -= 5.0f;

        for (int i = 0; i < o.size(); i++)
        {
            if ( lifetime <= 0 || (o.at(i).x - game_data.ballX) >= 100 || (o.at(i).x - game_data.ballX) <= -100)
            {
                o.erase(o.begin());
                lifetime = max_lifetime;
            }

            if ( newX < oldX )
            {
                o.at(i).x += number;
            }
            else
            {
                o.at(i).x -= number;
            }
            //o.at(i).y += number%10;

        }
        oldX = game_data.ballX;
    }
};


class Score {
private:
    int fontsize = 24;
    const char* text;
    SDL_Color text_color = { 215, 138, 75 };
    std::string fontpath = "assets/Oswald-Bold.ttf";
    TTF_Font* font;
    SDL_Surface* text_surface;

public:
    int x;
    int y;
    int t_width = 100;
    int t_height = 100;

    SDL_Texture* ftexture = NULL; // our font-texture
    
    SDL_Rect makeRect(int x, int y) {

        SDL_Rect dst = { x, y, t_width, t_height };

        return dst;
    }


    void updateText(SDL_Renderer* renderer, std::string input) {
        TTF_Init();

        font = TTF_OpenFont(fontpath.c_str(), fontsize);
        text = input.c_str();

        // check to see that the font was loaded correctly
        if (font == NULL) {
            std::cout << "Failed the load the font!\n";
            std::cout << "SDL_TTF Error: " << TTF_GetError() << "\n";
        }
        else {
            // now create a surface from the font
            text_surface = TTF_RenderText_Solid(font, text, text_color);
            renderText(renderer);
        }
    }

    void renderText(SDL_Renderer* renderer) {
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

                SDL_RenderCopy(renderer, ftexture, NULL, &makeRect(x, y));
                
                //SDL_FreeSurface(text_surface);
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
    void init_text();
    void init_audio();
    void play_sound();
    void destroy();
};


#endif