#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

Game::Game() {
    isRunning = false;
    Logger::Log("Game Constructor Called");
}

Game::~Game() {
    Logger::Log("Game Destructor Called");
}

void Game::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) !=0){
        Logger::Err("Error initializing SDL.");
        return;
    }
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = 800; //displayMode.w;
    windowHeight = 600; //displayMode.h;
    window = SDL_CreateWindow(
        NULL, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS);
        if (!window) {
            Logger::Err("Error creating SDL window.");
            return;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(!renderer){
            Logger::Err("Error creating SDL Renderer.");
            return;
        }
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        isRunning = true;
}


void Game::Setup() {
    //TODO:
    //Entity tank = registry.CreateEntity();
    //tank.AddComponent<TransformComponent>();
    //tank.AddComponent<BoxColliderComponent>();
    //tank.AddComponent<SpriteComponent>("./assets/images/tank.png");
}

void Game::Update() {
    //If running to fast lock until it reaches the correct milliseconds
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME){
        SDL_Delay(timeToWait);
    }
    
    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
    // Store current game time
    millisecsPreviousFrame = SDL_GetTicks();
    // Object Velocity 
    //TODO:
    //MovementSystem.Update();
    //CollisionSystem.Update();
    //DamageSystem.Update();
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

//TODO: Render game objects

void Game::ProccessInput() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type){
            case SDL_QUIT:
            isRunning = false;
            break;
            case SDL_KEYDOWN:
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
                break;
            }

        }
    }
}

void Game::Run(){
    Setup();
    while (isRunning){
        ProccessInput();
        Update();
        Render();
    }
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); 
}
