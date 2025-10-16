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
// size of imported font
#define SCORE_FONT_SIZE 32

const char tile_chars[TILE_TYPES] = {'#', '@', '$%', '%', '&', 'O', 'X'};

char board[BOARD_SIZE][BOARD_SIZE];

int score = 200;
Vector2 grid_origin;
Texture2D background;
Font score_font;

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
  // create window and its demensions
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "Beju Board");
  SetTargetFPS(60);
  srand(time(NULL));
  
  background = LoadTexture("C:/Users/jay-5/source/repos/Beju/assets/background.jpg");
  score_font = LoadFontEx("C:/Users/jay-5/source/repos/Beju/assets/Trader-lxrWd.ttf", SCORE_FONT_SIZE, NULL, 0);
  
  init_board();

  while (!WindowShouldClose()) {
    // game logic

    BeginDrawing();
    ClearBackground(BLACK);
    
    // create boxes for board
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
    //generate the 2D Board
    for (int y = 0; y < BOARD_SIZE; y++){
      for (int x = 0; x < BOARD_SIZE; x++){
        Rectangle rect = {
          grid_origin.x + (x * TILE_SIZE),
          grid_origin.y + (y * TILE_SIZE),
          TILE_SIZE,
          TILE_SIZE
        };

        DrawRectangleLinesEx(rect, 1, BLACK);

        DrawTextEx(
          GetFontDefault(),
          TextFormat("%c", board[y][x]),
          (Vector2) {rect.x + 12, rect.y + 8},
          20, 1, BLUE
        );
      }
    }
    // Dimensions of font and uses font import
    DrawTextEx(
      score_font,
      TextFormat("SCORE: %d", score),
      (Vector2) {
        20, 20
      },
      SCORE_FONT_SIZE,
      1.0f,
      BLUE
    );
    EndDrawing();
  }
  
  UnloadTexture(background);
  UnloadFont(score_font);
  return 0;
}
