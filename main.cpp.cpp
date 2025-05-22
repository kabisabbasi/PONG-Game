#include <raylib.h>
#include <iostream>
#include <string>
#include<fstream>
using namespace std;

/////// Game loop consists of ///////
// events
// update data based on events
// display data

////// Draw Circle takes x,y co-oridinates [center of circle], radius, and color constructor
Color Green = Color{ 38,185,154,255 };
Color Dark_Green = Color{ 20,160,133,255 };
Color Light_Green = Color{ 129,204,154,255 };
Color Yellow = Color{ 38,185,154,255 };




int Player_Score = 0;
int CPU_Score = 0;
string name;
char key;
bool IsTyping = false;
int namelength;
void NameEntering() {
    InitWindow(640, 400, "Name of Player");
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Green);
        DrawText("Enter your Name", 20, 20, 20, DARKGRAY);
        if (IsTyping) {
            while (IsKeyPressed(key)) {
                cin >> name;
            }
        }
        EndDrawing();
    }
}


float Ball_x = 640;
float Ball_y = 400;
int Ball_Speed_x = 7;
int Ball_Speed_y = 7;
float Ball_Radius = 20;

float PlayerP_x, PlayerP_y;
float PlayerP_Width = 15, PlayerP_Height = 125, PlayerP_Speed = 6;
float CPU_x, CPU_y;
float CPU_Width = 25, CPU_Height = 125, CPU_Speed = 6;

void DrawBall() {
    DrawCircle(Ball_x, Ball_y, Ball_Radius, YELLOW);
}

void UpdateBall() {
    Ball_x += Ball_Speed_x;
    Ball_y += Ball_Speed_y;

    // Corrected boundary check to prevent ball from getting stuck at the bottom
    if (Ball_y + Ball_Radius >= GetScreenHeight()) {
        Ball_y = GetScreenHeight() - Ball_Radius; // Prevent it from going below the screen
        Ball_Speed_y *= -1;
    }

    if (Ball_y - Ball_Radius <= 0) {
        Ball_y = Ball_Radius; // Prevent it from going above the screen
        Ball_Speed_y *= -1;
    }

    if (Ball_x + Ball_Radius >= GetScreenWidth()) {
        CPU_Score++;
        Ball_Speed_x *= -1;
    }

    if (Ball_x - Ball_Radius <= 0) {
        Ball_Speed_x *= -1;
        Player_Score++;
    }
}


void DrawPaddle(float x, float y) {
    DrawRectangle(x, y, 15, 120, WHITE);
}

void UpdatePlayerPaddle() {
    if (IsKeyDown(KEY_UP)) {
        PlayerP_y = PlayerP_y - PlayerP_Speed;
    }

    if (IsKeyDown(KEY_DOWN)) {
        PlayerP_y = PlayerP_y + PlayerP_Speed;
    }

    if (PlayerP_y >= GetScreenHeight() - PlayerP_Height) {
        PlayerP_y = PlayerP_y - PlayerP_Speed;
    }
    if (PlayerP_y <= 0) {
        PlayerP_y = PlayerP_y + PlayerP_Speed;
    }
}

void UpdateCpuPaddle(float ball_y) {
    if (CPU_y + CPU_Height / 2 > ball_y) {
        CPU_y = CPU_y - CPU_Speed;
    }

    if (CPU_y + CPU_Height / 2 < ball_y) {
        CPU_y = CPU_y + CPU_Speed;
    }

    if (CPU_y >= GetScreenHeight() - CPU_Height) {
        CPU_y = CPU_y - CPU_Speed;
    }
    if (CPU_y <= 0) {
        CPU_y = CPU_y + CPU_Speed;
    }
}

int main() {
    NameEntering();
    
    //screen height and width
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "My pong game");

    //player paddle initialization
    PlayerP_x = screen_width - PlayerP_Width - 5;
    PlayerP_y = screen_height / 2 - PlayerP_Height / 2;

    //cpu paddle initialization
    CPU_x = 5;
    CPU_y = screen_height / 2 - CPU_Height / 2;

    SetTargetFPS(60); // how fast the game should run
    
    while (WindowShouldClose() == false) {    //while return of Window Should Close value is false
        BeginDrawing(); //creates canvas

        ///// DRAWINGS /////
        ClearBackground(Dark_Green);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, 800, WHITE);

        //ball
        UpdateBall();
        DrawBall();

        //check for collisions
        if (CheckCollisionCircleRec(Vector2{ Ball_x, Ball_y }, Ball_Radius, Rectangle{ PlayerP_x, PlayerP_y, PlayerP_Width, PlayerP_Height })) {
            Ball_Speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ Ball_x, Ball_y }, Ball_Radius, Rectangle{ CPU_x, CPU_y, CPU_Width, CPU_Height })) {
            Ball_Speed_x *= -1;
        }

        //player paddle
        UpdatePlayerPaddle();
        DrawPaddle(PlayerP_x, PlayerP_y);

        //cpu paddle
        UpdateCpuPaddle(Ball_y);
        DrawPaddle(CPU_x, CPU_y);

        DrawText(TextFormat("%i", CPU_Score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", Player_Score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
        
        EndDrawing(); //closes canvas
    }
    ofstream file("Score.txt", ios::app);
    file << "The Score for"<< name     <<  "\n" << Player_Score;
    CloseWindow();
    return 0;
}