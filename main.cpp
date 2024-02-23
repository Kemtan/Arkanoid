#include <raylib.h>

// Ball
struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int)x, (int)y, radius, WHITE);
	}
};

// Paddle
struct Paddle
{
	float x, y;
	float speed;
	float width, height;

	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2, y - height / 2, 100, 10 };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
};

int main()
{
	// Window
	InitWindow(1600, 900, "Space");
	SetWindowState(FLAG_VSYNC_HINT);

	// Ball
	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300;
	ball.speedY = 300;

	// Paddle 
	Paddle paddle;
	paddle.x = GetScreenWidth() / 2;
	paddle.y = GetScreenHeight() - 50;
	paddle.width = 100;
	paddle.height = 10;
	paddle.speed = 500;

	// Collision
	if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, paddle.GetRect()))
	{
		if (ball.speedY < 0)
		{
			ball.speedX = (ball.x - paddle.x) / (paddle.width / 2) * -ball.speedX;
			ball.speedY *= -1.1f;
		}
	}

	while (!WindowShouldClose())
	{
		// Ball pos
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		// Control
		if (IsKeyDown(KEY_A))
		{
			paddle.x -= paddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_D))
		{
			paddle.x += paddle.speed * GetFrameTime();
		}


		// Draw
		BeginDrawing();
		ClearBackground(BLACK);

		ball.Draw();
		paddle.Draw();

		DrawFPS(10, 10);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}