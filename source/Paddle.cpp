// Paddle.cpp
/*#define PLATFORM_WII*/
#include "Constants.h"
#ifdef PLATFORM_WII
// Wii-specific includes
#include <wiiuse/wpad.h>
#include <grrlib.h>
#include <stdio.h>
#include <stdlib.h>
#else
#include <algorithm>
#include <raylib.h>
#include <stdlib.h>
#endif

#ifndef PADDLE
#define PADDLE

inline float clamp(const float value, const float min, const float max) {
    return (value < min) ? min : (value > max) ? max : value;
}

class Paddle {

  float x;
  float y;
  float dy;
  int size;
  int thickness;
  int score;
  int playerNum;

  public:

  Paddle(float x, int playerNum): x(x), playerNum(playerNum) {
    size = 120;
    thickness = 20;
    score = 0;
    Reset();
  }

  void Reset() {
    y = SCREEN_HEIGHT / 2;
    dy = 0;
  }

  void Move() {

    #ifdef PLATFORM_WII
    WPAD_ScanPads();
    u32 held = WPAD_ButtonsHeld(playerNum-1);
    if (held & WPAD_BUTTON_UP) {
      dy -= 1.2;
    }
    if (held & WPAD_BUTTON_DOWN) {
      dy += 1.2;
    }
    #else
    if (playerNum == 1) {
      if (IsKeyDown(KEY_Q)) {
        dy -= 1.2;
      }
      if (IsKeyDown(KEY_A)) {
        dy += 1.2;
      }
    } else {
      if (IsKeyDown(KEY_O)) {
        dy -= 1.2;
      }
      if (IsKeyDown(KEY_L)) {
        dy += 1.2;
      }
    }
    #endif

    int newY = y + dy;
    if (newY - size/2 < 0 || newY + size/2 > SCREEN_HEIGHT) {
      dy = 0;
      newY = clamp(newY, size/2, SCREEN_HEIGHT - size/2);
    }
    y = newY;
    dy *= 0.9;
    if (std::abs(dy) < 0.3) dy = 0;
  }

  void Render() const {
    #ifdef PLATFORM_WII
    GRRLIB_Rectangle(x - thickness/2, y - size/2, thickness, size, RGBA(0, 0, 255, 255), 1);
    printf("\x1b[%d;%dH%d", (int)(20 / 8), (int)(x / 8), score);
    #else
    DrawRectangle(x - thickness/2, y - size/2, thickness, size, BLUE);
    DrawText(TextFormat("%d", score), x, 20, 20, BLACK);
    #endif
  }

  void Score() {
    score++;
  }

  float GetX() const { return x; }
  float GetY() const { return y; }
  int GetThickness() const { return thickness; }
  int GetSize() const { return size; }
};

#endif

