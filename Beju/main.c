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
#define TILE_TYPES 5

const char tile_chars[TILE_TYPES] = {'#', '@', '$%', '%', '&'};

char board[BOARD_SIZE][BOARD_SIZE];

char random_tile() {
  return tile_chars[rand() % TILE_TYPES];
}

void init_board() {
  for (int y = 0; y < BOARD_SIZE; y++) {
      for (int x = 0; x < BOARD_SIZE; x++) {
      board[y][x] = random_tile();
    }
  }
}

int main(void) {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Beju Board");
  SetTargetFPS(60);
  srand(time(NULL));

  init_board();

  while (!WindowShouldClose()) {
    // game logic goes here
    //
    BeginDrawing();
    ClearBackground(BLACK);
    
    for (int y = 0; y < BOARD_SIZE; y++){
      for (int x = 0; x < BOARD_SIZE; x++){
        Rectangle rect = {
          x * TILE_SIZE,
          y * TILE_SIZE,
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
  return 0;
}
