// Program.cpp
/*#define PLATFORM_WII*/
#ifdef PLATFORM_WII
// Wii-specific includes
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h> // For sleep
#include <ogc/video.h>
#else
#include "raylib.h"
#endif
#include "Constants.h"
/*#include <vector>*/
#include "Ball.cpp"
#include "Paddle.cpp"

#ifdef PLATFORM_WII
GXRModeObj	*rmode;
static void	*framebuffer;
static vu8	readyForCopy;
#endif

void initilize() {
  #ifdef PLATFORM_WII
  VIDEO_Init();
  rmode = VIDEO_GetPreferredMode(NULL);
  framebuffer = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
  console_init(framebuffer, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * 2);
  VIDEO_Configure(rmode);
  VIDEO_SetNextFramebuffer(framebuffer);
  VIDEO_SetBlack(FALSE);
  VIDEO_Flush();
  VIDEO_WaitVSync();
  if (rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();

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
    VIDEO_ClearFrameBuffer(rmode, framebuffer, COLOR_BLACK); // Clear the screen
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
    VIDEO_Flush();
    VIDEO_WaitVSync();
    #else
    EndDrawing();
    #endif
  }

  #ifndef PLATFORM_WII
  // De-Initialization
  CloseWindow(); // Close window and OpenGL context
  #endif

  return 0;
}


