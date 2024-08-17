#include "raylib.h"
#include <math.h>

#define GAME_SPEED 10
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 650

struct Bullet
{
    struct Bullet* pre_bul;
    Vector2 position;
    Vector2 velocity;
    struct Bullet* next_bul;
};

struct PlayerStruct
{
    Vector2 position;
    Vector2 velocity;
    float angle_rad;
    float radius;
    Color color;
    struct Bullet first_bullet;
};



static void UpdateDrawFrame(struct PlayerStruct *player);
void DrawPlayer(Vector2 position, float angle, float radius, Color color);


int main()
{
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    struct PlayerStruct player = {
        .position = (Vector2){screenWidth / 2, screenHeight / 2},
        .velocity = (Vector2){0, 0},
        .angle_rad = 0,
        .radius = 10,
        .color = WHITE
    };

    InitWindow(screenWidth, screenHeight, "raylib");

    SetTargetFPS(144);
    BeginDrawing();

        ClearBackground(WHITE);

    EndDrawing();

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
    if (IsKeyDown(KEY_RIGHT)) player->angle_rad += 0.5 * GAME_SPEED * delta_time;
    if (IsKeyDown(KEY_LEFT)) player->angle_rad -= 0.5 * GAME_SPEED * delta_time;
    //TODO: Use vectors to move the player ore towards the direction they are facing
    player->velocity.x -= player->velocity.x * 0.9 * delta_time;
    player->velocity.y -= player->velocity.y * 0.9 * delta_time;
    if (IsKeyDown(KEY_UP))
    {
        player->velocity.x -= player->velocity.x * 0.2 * delta_time;
        player->velocity.y -= player->velocity.y * 0.2 * delta_time;
        player->velocity.x += GAME_SPEED * 50 * delta_time * cos(player->angle_rad);
        player->velocity.y += GAME_SPEED * 50 * delta_time * sin(player->angle_rad);
    }

    player->position.x += player->velocity.x * delta_time;
    player->position.y += player->velocity.y * delta_time;

    if (player->position.x > SCREEN_WIDTH) player->position.x = 0;
    if (player->position.x < 0) player->position.x = SCREEN_WIDTH;
    if (player->position.y > SCREEN_HEIGHT) player->position.y = 0;
    if (player->position.y < 0) player->position.y = SCREEN_HEIGHT;



    
    BeginDrawing();

        ClearBackground(BLANK);
        DrawPlayer(player->position, player->angle_rad, player->radius, player->color); 

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


