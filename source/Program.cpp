// Program.cpp
/*#define PLATFORM_WII*/
#ifdef PLATFORM_WII
// Wii-specific includes
#include <wiiuse/wpad.h>
#include <grrlib.h>
#else
#include "raylib.h"
#endif
#include "Constants.h"
/*#include <vector>*/
#include "Ball.cpp"
#include "Paddle.cpp"

void initilize() {
  #ifdef PLATFORM_WII

  GRRLIB_Init();
  WPAD_Init();
  #else
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Super Cool Pong Game");
  SetTargetFPS(TARGET_FPS); // Set the frame rate
  #endif
}

int main() {

  initilize();

  Ball balls[2] = {
    Ball(4),
    Ball(-4),
  };

  Paddle player1 = Paddle(20, 1);
  Paddle player2 = Paddle(SCREEN_WIDTH - 20, 2);

  // Main game loop
  while (
    #ifdef PLATFORM_WII
      1 // Wii handles exit state differently
    #else
      !WindowShouldClose()
    #endif
  ) {

    /*   GAME LOGIC   */
    player1.Move();
    player2.Move();
    for (int i = 0; i < 2; i++) {
      balls[i].Move();
      balls[i].CollideWithPaddle(&player1);
      balls[i].CollideWithPaddle(&player2);
      balls[i].CheckOutOfBounds(&player1, &player2); // Also checks player score situation
    }


    /*   START DRAWING   */
    #ifdef PLATFORM_WII
    WPAD_ScanPads();
    u32 pressed = WPAD_ButtonsDown(0);
    if (pressed & WPAD_BUTTON_HOME) break; // Exit on HOME button
    GRRLIB_FillScreen(RGBA(0, 0, 0, 255));
    #else
    BeginDrawing();
    ClearBackground(RAYWHITE);
    #endif

    for (int i = 0; i < 2; i++) {
      balls[i].Render();
    }
    player1.Render();
    player2.Render();


    /*   END DRAWING   */
    #ifdef PLATFORM_WII
    GRRLIB_Render();
    VIDEO_WaitVSync();
    #else
    EndDrawing();
    #endif
  }

  #ifdef PLATFORM_WII
  GRRLIB_Exit();
  #else
  // De-Initialization
  CloseWindow(); // Close window and OpenGL context
  #endif

  return 0;
}


