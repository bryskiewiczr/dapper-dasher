#include "raylib.h"

struct AnimationData {
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

AnimationData updateAnimationData(AnimationData animationData, float deltaTime, int maxFrameValue) {
    animationData.runningTime += deltaTime;
    if (animationData.runningTime >= animationData.updateTime) {
        animationData.runningTime = 0;
        animationData.rec.x = animationData.frame * animationData.rec.width;
        animationData.frame++;
        if (animationData.frame > maxFrameValue) {animationData.frame = 0;}
    }
    return animationData;
}

int main() {
    const int windowDimensions[]{480, 320};

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

    // background
    const Texture2D farBuildingsBackground = LoadTexture("textures/far-buildings.png");
    const Texture2D backBuildingsBackground = LoadTexture("textures/back-buildings.png");
    const Texture2D foregroundBuildingsBackground = LoadTexture("textures/foreground.png");
    float farBuildingsBackgroundX{};
    float backBuildingsBackgroundX{};
    float foregroundBuildingsBackgroundX{};

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

        // draw the background
        farBuildingsBackgroundX -= 20 * deltaTime;
        backBuildingsBackgroundX -= 40 * deltaTime;
        foregroundBuildingsBackgroundX -= 80 * deltaTime;

        if (farBuildingsBackgroundX <= -farBuildingsBackground.width * 2) {
            farBuildingsBackgroundX = 0;
        }

        if (backBuildingsBackgroundX <= -backBuildingsBackground.width * 2) {
            backBuildingsBackgroundX = 0;
        }

        if (foregroundBuildingsBackgroundX <= -foregroundBuildingsBackground.width * 2) {
            foregroundBuildingsBackgroundX = 0;
        }
        Vector2 farBuildingsBackgroundPos{farBuildingsBackgroundX, 0.0};
        Vector2 farBuildingsBackground2Pos{farBuildingsBackgroundX + farBuildingsBackground.width * 2, 0.0};
        DrawTextureEx(farBuildingsBackground, farBuildingsBackgroundPos, 0.0, 2.0, WHITE);
        DrawTextureEx(farBuildingsBackground, farBuildingsBackground2Pos, 0.0, 2.0, WHITE);

        Vector2 backBuildingsBackgroundPos{backBuildingsBackgroundX, 0.0};
        Vector2 backBuildingsBackground2Pos{backBuildingsBackgroundX + backBuildingsBackground.width * 2, 0.0};
        DrawTextureEx(backBuildingsBackground, backBuildingsBackgroundPos, 0.0, 2.0, WHITE);
        DrawTextureEx(backBuildingsBackground, backBuildingsBackground2Pos, 0.0, 2.0, WHITE);

        Vector2 foregroundBuildingsBackgroundPos{foregroundBuildingsBackgroundX, 0.0};
        Vector2 foregroundBuildingsBackground2Pos{foregroundBuildingsBackgroundX + foregroundBuildingsBackground.width * 2, 0.0};
        DrawTextureEx(foregroundBuildingsBackground, foregroundBuildingsBackgroundPos, 0.0, 2.0, WHITE);
        DrawTextureEx(foregroundBuildingsBackground, foregroundBuildingsBackground2Pos, 0.0, 2.0, WHITE);

        // ground check
        bool isOnGround{scarfyAnimationData.pos.y >= windowDimensions[1] - scarfyAnimationData.rec.height};
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

        // update the position
        for (int i = 0; i < sizeOfNebulae; i++) {
            nebulae[i].pos.x += nebulaVelocity * deltaTime;
        }
        scarfyAnimationData.pos.y += scarfyVelocity * deltaTime;

        // update animation data
        if (isOnGround) {
            scarfyAnimationData = updateAnimationData(scarfyAnimationData, deltaTime, 5);
        }
        for (int i = 0; i < sizeOfNebulae; i++) {
            nebulae[i] = updateAnimationData(nebulae[i], deltaTime, 7);
        }

        // draw characters
        for (int i = 0; i < sizeOfNebulae; i++) {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
        DrawTextureRec(scarfy, scarfyAnimationData.rec, scarfyAnimationData.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(farBuildingsBackground);
    UnloadTexture(foregroundBuildingsBackground);
    UnloadTexture(backBuildingsBackground);
    CloseWindow();
}
