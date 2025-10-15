#include "raylib.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// to define dimensions of board
#define BOARD_SIZE 8
// to define the size of each tile
#define TILE_SIZE 42
// how many types of tiles we'll include
#define TILE_TYPES 7

const char tile_chars[TILE_TYPES] = {'#', '@', '$%', '%', '&', '*', '+'};

char board[BOARD_SIZE][BOARD_SIZE];

Vector2 grid_origin;
Texture2D background;

char random_tile() {
  return tile_chars[rand() % TILE_TYPES];
}

// generate board from here BOARD_SIZE and TILE_SIZE
void init_board() {
  for (int y = 0; y < BOARD_SIZE; y++) {
      for (int x = 0; x < BOARD_SIZE; x++) {
      board[y][x] = random_tile();
    }
  }

  int grid_width = BOARD_SIZE * TILE_SIZE;
  int grid_height = BOARD_SIZE * TILE_SIZE;

  grid_origin = (Vector2) {
    (GetScreenWidth() - grid_width) / 2,
    (GetScreenHeight() - grid_height) / 2
  };
}

int main(void) {
  // create window
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Beju Board");
  SetTargetFPS(60);
  srand(time(NULL));
  
  background = LoadTexture("C:/Users/jay-5/source/repos/Beju/assets/background.jpg");
  
  init_board();

  while (!WindowShouldClose()) {
    // game logic goes here

    BeginDrawing();
    ClearBackground(BLACK);
    
    DrawTexturePro(
        background,
        (Rectangle) {
        0, 0, background.width, background.height
    },
        (Rectangle) {
        0, 0, GetScreenWidth(), GetScreenHeight()
    },
        (Vector2) {
        0, 0
    },
        0.0f,
        WHITE
    );

    for (int y = 0; y < BOARD_SIZE; y++){
      for (int x = 0; x < BOARD_SIZE; x++){
        Rectangle rect = {
          grid_origin.x + (x * TILE_SIZE),
          grid_origin.y + (y * TILE_SIZE),
          TILE_SIZE,
          TILE_SIZE
        };

        DrawRectangleLinesEx(rect, 1, DARKGRAY);
        
        DrawTextEx(
          GetFontDefault(),
          TextFormat("%c", board[y][x]),
          (Vector2) {rect.x + 12, rect.y + 8},
          20, 1, WHITE
        );
      }
    }

    EndDrawing();
  }
  
  UnloadTexture(background);
  return 0;
}
