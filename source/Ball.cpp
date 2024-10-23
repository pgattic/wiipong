// Ball.cpp
/*#define PLATFORM_WII*/
#include "Constants.h"
#include "Paddle.cpp"
#ifdef PLATFORM_WII
// Wii-specific includes
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h> // For sleep
#include "WiiDrawFunctions.h"
#else
#include "raylib.h"
#endif

#ifndef BALL
#define BALL

class Ball {

  float x;
  float y;
  float dx;
  float dy;
  int radius;

  void Reset(float new_dx) {
    x = SCREEN_WIDTH / 2;
    y = SCREEN_HEIGHT / 2;
    dx = new_dx;
    dy = 0;
    radius = 10;
  }

  public:

  Ball(float dx) {
    Reset(dx);
  }

  void Move() {
    int newX = x - dx;
    int newY = y + dy;

    // Up/Down collision
    if (newY - radius < 0 || newY + radius > SCREEN_HEIGHT) {
      dy = -dy;
      newY = y + dy;
    }

    x = newX;
    y = newY;
  }

  void Render() const {
    #ifdef PLATFORM_WII
    WiiDrawCircle(x, y, 10, (GXColor){0, 255, 0, 255}, 32);
    #else
    DrawCircle(x, y, 10, GREEN);
    #endif
  }

  void CollideWithPaddle(Paddle* paddle) {
    if (
      x > paddle->GetX() - paddle->GetThickness() &&
      x < paddle->GetX() + paddle->GetThickness() &&
      y + radius > paddle->GetY() - paddle->GetSize()/2 &&
      y - radius < paddle->GetY() + paddle->GetSize()/2
    ) {
      float diff = y - paddle->GetY();
      if (dx < 0) {
        dx = -dx + 0.5;
      } else {
        dx = -dx - 0.5;
      }
      /*dx = dx * -1.0625;*/
      dy += diff / 20;
      Move();
    }
  }

  void CheckOutOfBounds(Paddle* player1, Paddle* player2) {
    if (x < 0) {
      player2->Score();
      /*player1->Reset();*/
      /*player2->Reset();*/
      Reset(-4);
    }

    if (x > SCREEN_WIDTH) {
      player1->Score();
      /*player1->Reset();*/
      /*player2->Reset();*/
      Reset(4);
    }
  }
};

#endif

