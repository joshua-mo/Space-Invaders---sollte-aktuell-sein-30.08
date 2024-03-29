﻿#include <cstdlib>

#include "raylib.h"

#include "config.h"
#include "helper.h"
#include "game.h"
#include "Entity.h"

#include <iostream> 




Game::Screen* currentScreen;
int highscore = 0;
Player player;

#define NUM_MAX_ENEMIES 50
 Enemy enemy[NUM_MAX_ENEMIES];
  int activeEnemies;

  Enemy enemy2[NUM_MAX_ENEMIES];
  int activeEnemies2;

  Planet planet;

  bool ScreenChangeto1;

  bool ScreenChangeto2;

   Bullet bullet[NUM_SHOOTS];

   Bullet bullet2[NUM_SHOOTS];

    Asteroid asteroid[NUM_MAX_ASTEROIDS];
    int activeAsteroids;

//Boss 
Boss boss[NUM_MAX_ENEMIES];

int hits;

int activeEnemies3;

bool BossMoving;

Rectangle StopBoss;

int framescounter;

int framescounter2;

int framescounter3;

int seconds = 5;

int minutes = 3;

Flotte flotte[NUM_SHOOTS];

using namespace std;

bool changeto2 = false;

bool changeto1 = false;

int main() {
    // Enable config flags for resizable window and vertical synchro
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetWindowMinSize(Game::ScreenWidth / 2, Game::ScreenHeight / 2);
    // Set game to run at 60 frames-per-second
    SetTargetFPS(60);

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(Game::ScreenWidth, Game::ScreenHeight);
    // Texture scale filter to use
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Set start screen
    currentScreen = Game::MenuScreen::getInstance();

    InitAudioDevice();      // Initialize audio device
  
    //Sound fxshoot = LoadSound("assets/audio/sfx/laser4.wav");
  
    Music music = LoadMusicStream("assets/audio/tracks/Mix.mp3");
    PlayMusicStream(music);
    music.looping = true;
     SetMasterVolume(0.1);
    
    

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
       // if (IsKeyPressed(KEY_SPACE)) PlaySound(fxshoot);
    
        UpdateMusicStream(music);
      



      
      
        






        // Compute required framebuffer scaling
        float scale = MIN((float) GetScreenWidth() / Game::ScreenWidth, (float) GetScreenHeight() / Game::ScreenHeight);

        // Update virtual mouse (clamped mouse value behind game screen)
        Vector2 mouse = GetMousePosition();
        Vector2 virtualMouse = {0};
        virtualMouse.x =
                (mouse.x - (static_cast<float>(GetScreenWidth()) - (Game::ScreenWidth * scale)) * 0.5f) / scale;
        virtualMouse.y =
                (mouse.y - (static_cast<float>(GetScreenHeight()) - (Game::ScreenHeight * scale)) * 0.5f) / scale;
        virtualMouse = ClampValue(virtualMouse, {0, 0}, {static_cast<float>(Game::ScreenWidth),
                                                         static_cast<float>(Game::ScreenHeight)});

        currentScreen->ProcessInput();
        currentScreen->Update();

        BeginDrawing();
        ClearBackground(BLACK); // Letterbox color

        // Draw everything in the render texture, note this will not be rendered on screen, yet
        BeginTextureMode(target);
        currentScreen->Draw();
        EndTextureMode();

        // Draw RenderTexture2D to window, properly scaled
        DrawTexturePro(target.texture,
                       {0.0f, 0.0f, (float) target.texture.width, (float) -target.texture.height},
                       {(static_cast<float>(GetScreenWidth()) - ((float) Game::ScreenWidth * scale)) * 0.5f,
                        (static_cast<float>(GetScreenHeight()) - ((float) Game::ScreenHeight * scale)) * 0.5f,
                        (float) Game::ScreenWidth * scale, (float) Game::ScreenHeight * scale},
                       {0, 0}, 0.0f, WHITE);

        EndDrawing();
    } // Main game loop end

    // De-Initialization here...
    

    // Unload render texture
    UnloadRenderTexture(target);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
