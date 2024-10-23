
# WiiPong

Cross-platform C++ codebase

This is a simple Pong game made to run on both the Wii and the desktop. It uses compile-time logic to determine which code to include in the compilation. Uses [Raylib](https://www.raylib.com/) on Desktop and [GRRLIB](https://github.com/GRRLIB/GRRLIB) on Wii.

## How does it work?

The vast majority of game logic is exactly the same, regardless of the platform. If the computer can run C++ code, it can run all of the game logic! The hard part of this is when we want to handle user input and render to a display. If the game had audio or interacted with some other kind of peripheral, they would also require specialized code for each platform.

In this codebase, you will notice conditional branching using `#ifdef PLATFORM_WII`. This is leveraging C++'s macro system to include or exclude certain parts of the source code at compile time. For example, take a look at this function from `source/Program.cpp`:

```C++
void initilize() {
  #ifdef PLATFORM_WII
  GRRLIB_Init();
  WPAD_Init();
  #else
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Super Cool Pong Game");
  SetTargetFPS(TARGET_FPS); // Set the frame rate
  #endif
}
```

In this example, `InitWindow` is a Raylib (desktop) function that communicates using Wayland, Linux's display protocol, to create a floating window. That does not apply to the Wii, so when the compile target is a Wii, `GRRLIB_Init` is used, which initializes a graphics context for the Wii. I also had to include code that initializes gamepad reading on the Wii, while on the desktop I can specify the desired FPS.

## Building

### Wii (Homebrew Channel)

1. Prerequisites: DevKitPro with the `wii` package group installed, `GRRLIB` 
  - NOTE to Arch Linux users: both can be found in the AUR ([`wii`](https://aur.archlinux.org/packages/dkp-devkitppc), [`GRRLIB`](https://aur.archlinux.org/packages/grrlib))
2. Clone the repo (`git clone https://github.com/pgattic/wiipong`)
3. `make`
4. Place `wiipong.dol` at `/apps/wiipong/wiipong.dol` in the Wii's SD card
5. Launch "wiipong" from the Homebrew Channel

### Desktop (Linux)

1. Prerequisites: `g++`, `make`, `raylib`
2. Clone the repo (`git clone https://github.com/pgattic/wiipong`)
3. `make -f Makefile-desktop`
4. `make -f Makefile-desktop run`

