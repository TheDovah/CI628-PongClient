#include "MyGame.h"

#include "SDL_mixer.h"

Ball_texture_data ball;
Particle_engine particles;

/*

    Returns true iff s1 contains s2

*/
bool contains(std::string s1, std::string s2) {

    return s1.find(s2) != std::string::npos;

}

void MyGame::init_audio() {
    // open 44.1KHz, 
    // signed 16bit
    // system byte order, 
    // stereo audio,
    // using 1024 byte chunks
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        return;
    }

    // all good to go
    sound = Mix_LoadWAV("assets/drop.wav");
    if (sound == nullptr) {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }
    else {
        std::cout << "Sound effect loaded" << std::endl;
    }
}

int* i = new int(1);
void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        // we should have exactly 6 arguments
        if (args.size() == 6) 
        {
            std::cout << "6 Arguments" << std::endl;
            game_data.player1Y = stoi(args.at(0));
            game_data.player1X = stoi(args.at(1));
            game_data.player2Y = stoi(args.at(2));
            game_data.player2X = stoi(args.at(3));
            game_data.ballX = stoi(args.at(4));
            game_data.ballY = stoi(args.at(5));

        }
        if (args.size() == 4)
        // we should have exactly 4 arguments
        {
            if (*i == 1) { 
                std::cout << "4 Arguments" << std::endl;
                delete i;
            }
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.ballX = stoi(args.at(2));
            game_data.ballY = stoi(args.at(3));
        }
    }
    else {
        std::cout << "Received: " << cmd << std::endl;
    }

    if (contains(cmd, "HIT"))
    {
        play_sound();
    }
    if (contains(cmd, "exit"))
    {
        
    }
}


void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_w:
        send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
        break;
    case SDLK_s:
        send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
        break;
    case SDLK_i:
        send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
        break;
    case SDLK_k:
        send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
        break;
    }
}

void MyGame::play_sound() {
    if (Mix_PlayChannel(-1, sound, 0) == -1) {
        printf("Error playing sound. Mix_PlayChannel: %s\n", Mix_GetError());
    }
}

void MyGame::update() {
    player1_data.y = game_data.player1Y;
    player1_data.x = game_data.player1X;
    player2_data.y = game_data.player2Y;
    player2_data.x = game_data.player2X;

    ball_data.y = game_data.ballY;
    ball_data.x = game_data.ballX;
}


void MyGame::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if (ball.texture == nullptr)
    {
        ball.make_texture(renderer);
    }
    
    particles.update_particles(renderer);
    
    /*
    for (int i = 0; i < particles.get_size(); i++)
    {
        SDL_RenderFillRect(renderer, &particles.get_at(i));
    }
    */

    SDL_RenderCopy(renderer, ball.texture, NULL, &ball_data);

    SDL_RenderFillRect(renderer, &player1_data);
    SDL_RenderFillRect(renderer, &player2_data);
}

void MyGame::destroy() {
    sound = nullptr;
    Mix_FreeChunk(sound);

    Mix_CloseAudio();
}