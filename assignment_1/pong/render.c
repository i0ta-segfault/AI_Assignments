#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 100
#define BALL_SIZE 10
#define PADDLE_SPEED 8
#define BALL_SPEED 5

typedef struct {
    float x, y;
    float speed;
} Paddle;

typedef struct {
    float x, y;
    float dx, dy;
} Ball;

typedef struct {
    Paddle player;
    Paddle ai;
    Ball ball;
    int playerScore;
    int aiScore;
} GameState;

void init_game(GameState *game) {
    game->player.x = 20;
    game->player.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    game->player.speed = PADDLE_SPEED;

    game->ai.x = SCREEN_WIDTH - 30;
    game->ai.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    game->ai.speed = PADDLE_SPEED;

    game->ball.x = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
    game->ball.y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;
    game->ball.dx = BALL_SPEED;
    game->ball.dy = BALL_SPEED;

    game->playerScore = 0;
    game->aiScore = 0;
}

void reset_round(GameState *game) {
    game->player.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    game->ai.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;

    game->ball.x = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
    game->ball.y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;

    game->ball.dx *= -1;
    game->ball.dy = (GetRandomValue(0, 1) == 0 ? 1 : -1) * BALL_SPEED;
}

void update_player(GameState *game) {
    if (IsKeyDown(KEY_W)) game->player.y -= game->player.speed;
    if (IsKeyDown(KEY_S)) game->player.y += game->player.speed;

    if (game->player.y < 0) game->player.y = 0;
    if (game->player.y > SCREEN_HEIGHT - PADDLE_HEIGHT) {
        game->player.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
    }
}

void update_ai(GameState *game) {
    float ballCenterY = game->ball.y + BALL_SIZE / 2;
    float aiCenterY = game->ai.y + PADDLE_HEIGHT / 2;

    if (ballCenterY < aiCenterY) {
        game->ai.y -= game->ai.speed;
    } 
    else if (ballCenterY > aiCenterY) {
        game->ai.y += game->ai.speed;
    }

    if (game->ai.y < 0) game->ai.y = 0;
    if (game->ai.y > SCREEN_HEIGHT - PADDLE_HEIGHT) {
        game->ai.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
    }
}

void update_ball(GameState *game) {
    game->ball.x += game->ball.dx;
    game->ball.y += game->ball.dy;
    if (game->ball.y <= 0 || game->ball.y >= SCREEN_HEIGHT - BALL_SIZE) {
        game->ball.dy *= -1;
    }
    if (game->ball.x < 0) {
        game->aiScore++;
        reset_round(game);
    }
    if (game->ball.x > SCREEN_WIDTH) {
        game->playerScore++;
        reset_round(game);
    }

    Rectangle ballRect = { game->ball.x, game->ball.y, BALL_SIZE, BALL_SIZE };
    Rectangle playerRect = { game->player.x, game->player.y, PADDLE_WIDTH, PADDLE_HEIGHT };
    Rectangle aiRect = { game->ai.x, game->ai.y, PADDLE_WIDTH, PADDLE_HEIGHT };

    if (CheckCollisionRecs(ballRect, playerRect)) {
        game->ball.dx *= -1;
        game->ball.x = game->player.x + PADDLE_WIDTH + 1;
    }
    if (CheckCollisionRecs(ballRect, aiRect)) {
        game->ball.dx *= -1;
        game->ball.x = game->ai.x - BALL_SIZE - 1;
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong | Use W & S to move paddle");
    SetTargetFPS(60);
    GameState game;
    init_game(&game);
    while (!WindowShouldClose()) {
        update_player(&game);
        update_ai(&game);
        update_ball(&game);

        BeginDrawing();
            ClearBackground(BLACK);

            DrawLine(SCREEN_WIDTH / 2 - 1, 0, SCREEN_WIDTH / 2 - 1, SCREEN_HEIGHT, PINK);
            DrawRectangle(game.player.x, game.player.y, PADDLE_WIDTH, PADDLE_HEIGHT, BROWN);
            DrawRectangle(game.ai.x, game.ai.y, PADDLE_WIDTH, PADDLE_HEIGHT, LIME);
            DrawCircle(game.ball.x, game.ball.y, BALL_SIZE, RAYWHITE);
            DrawText(TextFormat("%d", game.playerScore), SCREEN_WIDTH / 2 - 40, 20, 40, GOLD);
            DrawText(TextFormat("%d", game.aiScore), SCREEN_WIDTH / 2 + 20, 20, 40, GOLD);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
