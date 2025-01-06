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
    const int windowDimensions[]{1024, 768};

    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");
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
    scarfyAnimationData.pos.x = windowDimensions[0]/2 - scarfyAnimationData.rec.width/2;
    scarfyAnimationData.pos.y = windowDimensions[1] - scarfyAnimationData.rec.height;
    scarfyAnimationData.frame = 0;
    scarfyAnimationData.updateTime = 1.0 / 12.0;
    scarfyAnimationData.runningTime = 0.0;
    int scarfyVelocity{0};
    const int scarfyJumpVelocity{600};

    // enemy character "Nebula"
    const Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // enemy variables
    const int nebulaVelocity {-300};
    const int sizeOfNebulae{20};
    AnimationData nebulae[sizeOfNebulae]{};
    for (int i = 0; i < sizeOfNebulae; i++) {
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height;
        nebulae[i].rec.x = 0;
        nebulae[i].rec.y = 0;
        nebulae[i].pos.x = windowDimensions[0] + (450 * i);
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].updateTime = 1.0 / 12.0;
        nebulae[i].runningTime = 0.0;
    }

    // Game Loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        float deltaTime(GetFrameTime());

        bool isOnGround{scarfyAnimationData.pos.y >= windowDimensions[1] - scarfyAnimationData.rec.height};
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

        // update the position of
        for (int i = 0; i < sizeOfNebulae; i++) {
            nebulae[i].pos.x += nebulaVelocity * deltaTime;
        }
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

        for (int i = 0; i < sizeOfNebulae; i++) {
            nebulae[i].runningTime += deltaTime;
            if (nebulae[i].runningTime >= nebulae[i].updateTime) {
                nebulae[i].runningTime = 0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if (nebulae[i].frame > 7) {
                    nebulae[i].frame = 0;
                }
            }
        }

        // draw Nebula
        for (int i = 0; i < sizeOfNebulae; i++) {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
        // draw Scarfy
        DrawTextureRec(scarfy, scarfyAnimationData.rec, scarfyAnimationData.pos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
