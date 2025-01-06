#include <wchar.h>

#include "raylib.h"

struct AnimationData {
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main() {
    const int windowWidth{1024};
    const int windowHeight{768};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");
    SetTargetFPS(60);

    // acceleration due to gravity (pixels/frame)/frame
    const int gravity{1000};

    // player character "Scarfy"
    const Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimationData scarfyAnimationData{};
    scarfyAnimationData.rec.width = scarfy.width/6;
    scarfyAnimationData.rec.height = scarfy.height;
    scarfyAnimationData.rec.x = 0;
    scarfyAnimationData.rec.y = 0;
    scarfyAnimationData.pos.x = windowWidth/2 - scarfyAnimationData.rec.width/2;
    scarfyAnimationData.pos.y = windowHeight - scarfyAnimationData.rec.height;
    scarfyAnimationData.frame = 0;
    scarfyAnimationData.updateTime = 1.0 / 12.0;
    scarfyAnimationData.runningTime = 0.0;
    int scarfyVelocity{0};
    const int scarfyJumpVelocity{600};

    // enemy character "Nebula"
    const Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimationData nebulaAnimationData{};
    nebulaAnimationData.rec.width = nebula.width/8;
    nebulaAnimationData.rec.height = nebula.height;
    nebulaAnimationData.rec.x = 0;
    nebulaAnimationData.rec.y = 0;
    nebulaAnimationData.pos.x = windowWidth;
    nebulaAnimationData.pos.y = windowHeight - nebula.height/8;
    nebulaAnimationData.frame = 0;
    nebulaAnimationData.updateTime = 1.0 / 12.0;
    nebulaAnimationData.runningTime = 0.0;

    AnimationData nebula2AnimationData{};
    nebula2AnimationData.rec.width = nebula.width/8;
    nebula2AnimationData.rec.height = nebula.height;
    nebula2AnimationData.rec.x = 0;
    nebula2AnimationData.rec.y = 0;
    nebula2AnimationData.pos.x = windowWidth + 300;
    nebula2AnimationData.pos.y = windowHeight - nebula.height/8;
    nebula2AnimationData.frame = 0;
    nebula2AnimationData.updateTime = 1.0 / 16.0;
    nebula2AnimationData.runningTime = 0.0;

    int nebulaVelocity {-300};

    // Game Loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        float deltaTime(GetFrameTime());

        bool isOnGround{scarfyAnimationData.pos.y >= windowHeight - scarfyAnimationData.rec.height};
        // ground check
        if (isOnGround) {
            // rectangle is on the ground
            scarfyVelocity = 0;
        } else {
            // rectangle is in the air
            scarfyVelocity += gravity * deltaTime;
        }

        // jumping
        if (IsKeyPressed(KEY_SPACE) && isOnGround) {
            scarfyVelocity -= scarfyJumpVelocity;
        }

        // update the position of characters
        nebulaAnimationData.pos.x += nebulaVelocity * deltaTime;
        nebula2AnimationData.pos.x += nebulaVelocity * deltaTime;
        scarfyAnimationData.pos.y += scarfyVelocity * deltaTime;

        if (isOnGround) {
            // update running time
            scarfyAnimationData.runningTime += deltaTime;
            if (scarfyAnimationData.runningTime >= scarfyAnimationData.updateTime) {
                scarfyAnimationData.runningTime = 0;
                // update animation frame
                scarfyAnimationData.rec.x = scarfyAnimationData.frame * scarfyAnimationData.rec.width;
                scarfyAnimationData.frame++;
                if (scarfyAnimationData.frame > 5) {scarfyAnimationData.frame = 0;}
            }
        }

        nebulaAnimationData.runningTime += deltaTime;
        if (nebulaAnimationData.runningTime >= nebulaAnimationData.updateTime) {
            nebulaAnimationData.runningTime = 0;
            // update animation frame
            nebulaAnimationData.rec.x = nebulaAnimationData.frame * nebulaAnimationData.rec.width;
            nebulaAnimationData.frame++;
            if (nebulaAnimationData.frame > 7) {
                nebulaAnimationData.frame = 0;
            }
        }

        nebula2AnimationData.runningTime += deltaTime;
        if (nebula2AnimationData.runningTime >= nebula2AnimationData.updateTime) {
            nebula2AnimationData.runningTime = 0;
            // update animation frame
            nebula2AnimationData.rec.x = nebula2AnimationData.frame * nebula2AnimationData.rec.width;
            nebula2AnimationData.frame++;
            if (nebula2AnimationData.frame > 7) {
                nebula2AnimationData.frame = 0;
            }
        }

        // draw Nebula
        DrawTextureRec(nebula, nebulaAnimationData.rec, nebulaAnimationData.pos, GREEN);
        DrawTextureRec(nebula, nebula2AnimationData.rec, nebula2AnimationData.pos, RED);
        // draw Scarfy
        DrawTextureRec(scarfy, scarfyAnimationData.rec, scarfyAnimationData.pos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
