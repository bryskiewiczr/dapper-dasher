#include <wchar.h>

#include "raylib.h"

int main() {
    const int windowWidth{1024};
    const int windowHeight{768};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");
    SetTargetFPS(60);

    // acceleration due to gravity (pixels/frame)/frame
    const int gravity{1000};

    // player character "Scarfy"
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec{0.0, 0.0, scarfy.width/6, scarfy.height};
    Vector2 scarfyPos{windowWidth/2 - scarfyRec.width/2, windowHeight - scarfyRec.height};
    int velocity{0};
    const int jumpVelocity{600};

    // enemy character "Nebula"
    const Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebulaPos{windowWidth, windowHeight - nebulaRec.height - 25};
    int nebulaVelocity{-300};

    Rectangle nebula2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebula2Pos{windowWidth + 300, windowHeight - nebulaRec.height - 25};

    int frame{};\
    const float updateTime{1.0 / 12.0};
    float runningTime{0.0};

    int nebulaFrame{};
    const float nebulaUpdateTime{1.0/12.0};
    float nebulaRunningTime{0.0};

    int nebula2Frame{};
    const float nebula2UpdateTime{1.0/12.0};
    float nebula2RunningTime{0.0};

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

        // update the position of characters
        nebulaPos.x += nebulaVelocity * deltaTime;
        nebula2Pos.x += nebulaVelocity * deltaTime;
        scarfyPos.y += velocity * deltaTime;

        if (isOnGround) {
            // update running time
            runningTime += deltaTime;
            if (runningTime >= updateTime) {
                runningTime = 0;
                // update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5) {frame = 0;}
            }
        }

        nebulaRunningTime += deltaTime;
        if (nebulaRunningTime >= nebulaUpdateTime) {
            nebulaRunningTime = 0;
            // update animation frame
            nebulaRec.x = nebulaFrame * nebulaRec.width;
            nebulaFrame++;
            if (nebulaFrame > 7) {nebulaFrame = 0;}
        }

        nebula2RunningTime += deltaTime;
        if (nebula2RunningTime >= nebula2UpdateTime) {
            nebula2RunningTime = 0;
            // update animation frame
            nebula2Rec.x = nebula2Frame * nebula2Rec.width;
            nebula2Frame++;
            if (nebula2Frame > 7) {nebula2Frame = 0;}
        }

        // draw Nebula
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
        DrawTextureRec(nebula, nebula2Rec, nebula2Pos, RED);
        // draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
