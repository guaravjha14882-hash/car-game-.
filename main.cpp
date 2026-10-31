```cpp
#include "raylib.h"
#include <vector>
#include <cstdlib>

struct Enemy {
    float x, z;
};

int main() {
    const int W = 1000;
    const int H = 700;

    InitWindow(W, H, "3D CAR RACING");
    SetTargetFPS(60);

    float player = 0;
    float speed = 0.5f;
    int score = 0;
    bool gameOver = false;

    std::vector<Enemy> enemies;

    Camera3D camera = {0};
    camera.position = {0, 7, 12};
    camera.target = {0, 0, -10};
    camera.up = {0, 1, 0};
    camera.fovy = 60;
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {

        if (!gameOver) {

            if (IsKeyDown(KEY_LEFT)) player -= 0.08f;
            if (IsKeyDown(KEY_RIGHT)) player += 0.08f;

            if (IsKeyDown(KEY_UP)) speed += 0.01f;
            if (IsKeyDown(KEY_DOWN)) speed -= 0.01f;

            if (speed < 0.2f) speed = 0.2f;
            if (speed > 1.5f) speed = 1.5f;

            for (auto &e : enemies) {
                e.z += speed * 0.15f;

                if (e.z > 12) {
                    e.z = -60;
                    e.x = (rand() % 7 - 3) * 2.0f;
                    score += 10;
                }

                if (e.z > 5 && e.z < 9 &&
                    e.x > player - 1.5f &&
                    e.x < player + 1.5f) {
                    gameOver = true;
                }
            }

            if (enemies.empty()) {
                for (int i = 0; i < 5; i++) {
                    enemies.push_back({
                        float((rand() % 7 - 3) * 2),
                        float(-15 - i * 15)
                    });
                }
            }
        }

        if (gameOver && IsKeyPressed(KEY_ENTER)) {
            gameOver = false;
            player = 0;
            score = 0;
            speed = 0.5f;
            enemies.clear();
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(camera);

        DrawPlane({0, -0.1f, 0}, {200, 200}, DARKGREEN);

        // Road
        DrawCube({0, 0, -20}, 12, 0.2f, 100, DARKGRAY);

        // Road boundaries
        DrawCube({-6, 0.2f, -20}, 0.3f, 0.3f, 100, WHITE);
        DrawCube({6, 0.2f, -20}, 0.3f, 0.3f, 100, WHITE);

        // Road divider
        for (int i = 0; i < 20; i++) {
            float z = -60 + i * 5;
            DrawCube({0, 0.15f, z}, 0.15f, 0.1f, 2, YELLOW);
        }

        // Player car
        DrawCube({player, 0.8f, 7}, 1.8f, 1, 3.5f, BLUE);
        DrawCube({player, 1.5f, 7}, 1.2f, 0.7f, 1.5f, SKYBLUE);

        // Enemy cars
        for (auto e : enemies) {
            DrawCube({e.x, 0.8f, e.z}, 1.8f, 1, 3.5f, RED);
            DrawCube({e.x, 1.5f, e.z}, 1.2f, 0.7f, 1.5f, WHITE);
        }

        EndMode3D();

        DrawText("3D CAR RACING", 20, 20, 30, WHITE);
        DrawText(TextFormat("SCORE: %d", score), 20, 65, 25, YELLOW);
        DrawText(TextFormat("SPEED: %d", int(speed * 150)), 20, 100, 25, GREEN);

        DrawText("LEFT / RIGHT = STEERING", 20, 620, 20, WHITE);
        DrawText("UP / DOWN = SPEED", 20, 650, 20, WHITE);

        if (gameOver) {
            DrawRectangle(250, 250, 500, 180, BLACK);
            DrawText("GAME OVER!", 370, 280, 45, RED);
            DrawText("PRESS ENTER TO RESTART", 320, 350, 25, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
```
