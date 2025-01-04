#include "raylib.h"

int main() {
    const int windowWidth{1024};
    const int windowHeight{768};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}
