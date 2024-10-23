#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h> // For sleep
#include <stdio.h>
#include <math.h>


#ifndef WII_DRAW_FUNCS
#define WII_DRAW_FUNCS

#define PI 3.14159265358979323846

inline void WiiDrawRectangle(f32 x, f32 y, f32 width, f32 height, GXColor color) {
  GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
  GX_Position3f32(x, y, 0);
  GX_Color4u8(color.r, color.g, color.b, color.a);
  GX_Position3f32(x + width, y, 0);
  GX_Color4u8(color.r, color.g, color.b, color.a);
  GX_Position3f32(x + width, y + height, 0);
  GX_Color4u8(color.r, color.g, color.b, color.a);
  GX_Position3f32(x, y + height, 0);
  GX_Color4u8(color.r, color.g, color.b, color.a);
  GX_End();
}

// Function to draw text using console functions
/*inline void WiiDrawText(f32 x, f32 y, const char* text) {*/
/*  printf("\x1b[%d;%dH%s", (int)(y / 8), (int)(x / 8), text);*/
/*}*/

inline void WiiDrawCircle(f32 centerX, f32 centerY, f32 radius, GXColor color, int numSegments) {
  GX_Begin(GX_TRIANGLEFAN, GX_VTXFMT0, numSegments + 2);
  // Center vertex
  GX_Position3f32(centerX, centerY, 0);
  GX_Color4u8(color.r, color.g, color.b, color.a);

  // Generate vertices around the circumference
  for (int i = 0; i <= numSegments; i++) {
    float angle = (2.0f * PI * i) / numSegments;
    float x = centerX + cosf(angle) * radius;
    float y = centerY + sinf(angle) * radius;
    GX_Position3f32(x, y, 0);
    GX_Color4u8(color.r, color.g, color.b, color.a);
  }

  GX_End();
}

#endif
