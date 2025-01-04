#include <wchar.h>

#include "raylib.h"

int main() {
    const int windowWidth{1024};
    const int windowHeight{768};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");
    SetTargetFPS(60);

    // rectangle dimensions
    int velocity{0};
    const int jumpVelocity{600};

    // acceleration due to gravity (pixels/frame)/frame
    const int gravity{1'000};

    // animation frame
    int frame{};

    _wgetcwd(NULL, 0);

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    const float updateTime{1.0 / 12.0};
    float runningTime{0.0};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        float deltaTime(GetFrameTime());

        bool isOnGround{scarfyPos.y >= windowHeight - scarfyRec.height};
        // ground check
        if (isOnGround) {
            // rectangle is on the ground
            velocity = 0;
        } else {
            // rectangle is in the air
            velocity += gravity * deltaTime;
        }

        // jumping
        if (IsKeyPressed(KEY_SPACE) && isOnGround) {
            velocity -= jumpVelocity;
        }

        // update the position
        scarfyPos.y += velocity * deltaTime;

        // update running time
        runningTime += deltaTime;
        if (runningTime >= updateTime) {
            runningTime = 0;
            // update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5) {frame = 0;}
        }

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}
