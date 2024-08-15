#include "raylib.h"
#include <math.h>

#define GAME_SPEED 10

struct PlayerStruct
{
    Vector2 position;
    Vector2 velocity;
    float angle_rad;
    float radius;
    Color color;
};

static void UpdateDrawFrame(struct PlayerStruct *player);
void DrawPlayer(Vector2 position, float angle, float radius, Color color);


int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    struct PlayerStruct player = {
        .position = (Vector2){screenWidth / 2, screenHeight / 2},
        .velocity = (Vector2){0, 0},
        .angle_rad = 0,
        .radius = 10,
        .color = RED
    };

    InitWindow(screenWidth, screenHeight, "raylib");

    SetTargetFPS(288);

    while (!WindowShouldClose())
    {
        UpdateDrawFrame(&player);
    }

    CloseWindow();
    return 0;
}



static void UpdateDrawFrame(struct PlayerStruct *player)
{
    float delta_time = GetFrameTime();
    if (IsKeyDown(KEY_RIGHT)) player->angle_rad += 0.1 * GAME_SPEED * delta_time;
    if (IsKeyDown(KEY_LEFT)) player->angle_rad -= 0.1 * GAME_SPEED * delta_time;
    if (IsKeyDown(KEY_UP)) player->velocity.x += 0.1;

    player->position.x += player->velocity.x * cos(player->angle_rad) * GAME_SPEED * delta_time;
    player->position.y += player->velocity.x * sin(player->angle_rad) * GAME_SPEED * delta_time;

    if (player->position.x > GetScreenWidth()) player->position.x = 0;
    if (player->position.x < 0) player->position.x = GetScreenWidth();
    if (player->position.y > GetScreenHeight()) player->position.y = 0;
    if (player->position.y < 0) player->position.y = GetScreenHeight();

    
    BeginDrawing();

        ClearBackground(BLACK);
        DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);
        DrawPlayer(player->position, player->angle_rad, player->radius, player->color); 
        DrawFPS(10, 10);

    EndDrawing();
}

//finished
void DrawPlayer(Vector2 position, float angle, float radius, Color color)
{
    Vector2 p1, p2, p3;
    p1 = (Vector2){position.x + cos(angle) * radius, position.y + sin(angle) * radius};
    p2 = (Vector2){position.x + cos(angle + 2.356) * radius, position.y + sin(angle + 2.356) * radius};
    p3 = (Vector2){position.x + cos(angle - 2.356) * radius, position.y + sin(angle - 2.356) * radius};
    DrawLineV(p1, p2, color);
    DrawLineV(p1, p3, color);
    DrawLineV(p2, position, color);
    DrawLineV(p3, position, color);
}


