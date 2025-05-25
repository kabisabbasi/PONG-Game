#include <raylib.h>
#include <iostream>
#include <string>
#include<fstream>
using namespace std;


// Some of the Colors that will be used later
Color Green = Color{ 6, 115, 162 ,255 };
Color Dark_Green = Color{ 6, 115, 162 ,255 };
Color Light_Green = Color{ 129,104,154,255 };
Color Yellow = Color{ 255, 131, 88,255 };



// Global Variables
float Ball_x = 640;  // Default x position of the ball
float Ball_y = 400;  // Default y position of ball
int Ball_Speed_x = 7; // This is the rate at which the ball will move like this is in x direction
int Ball_Speed_y = 7; // same speed but it is in y direction
float Ball_Radius = 20; // this is the radius of ball 


// Global Variables that will be used in different functions.
// First for Player 1 or Player's Paddle 
float PlayerP_x, PlayerP_y;  // Player's paddle position in x and y direction 
float PlayerP_Width = 15, PlayerP_Height = 125, PlayerP_Speed = 6; // Some Attributes or details about paddle

// Player 2 Paddle 
float Player2_x, Player2_y; // this is also paddle positions
float PlayerP2_Width = 25, PlayerP2_Height = 125, Player2_Speed = 6; // some attributes like speed, width and height 
//CPU paddle
float CPU_x, CPU_y;
float CPUP_Width = 25, CPUP_Height = 125, CPUP_Speed = 6;

// Global Variables whose values increases during the program
int Player_Score = 0;
int CPU_Score = 0;


string name1;
string name2;

void UpdateCpu1Paddle(float ball_y);
void NameEntering();
void NameEntering2();
void UpdatePlayerPaddle();
void UpdateCpuPaddle(float ball_y);
void DrawBall();
void DrawPaddle(float x, float y);
void UpdateBall();


int main() {
    char NumberOfPlayers;
    cout << "Do you want to play one player or two player ( S / M)";
    cin >> NumberOfPlayers;

    //Multiplayer game
    if (NumberOfPlayers == 'M') {
        NameEntering();
        NameEntering2();
        //screen height and width
        const int screen_width = 800; //1280 is standard screen width
        const int screen_height = 600; // 800 is also a strandard screen height
        InitWindow(screen_width, screen_height, "My pong game");

        //player paddle initialization it includes the position of the padddle
        PlayerP_x = screen_width - PlayerP_Width - 5; //this equation is because of the distance from the boundary of the screen
        PlayerP_y = screen_height / 2 - PlayerP_Height / 2; //this centers the paddle because the rectangle starts from its top left corner that is why equation is used

        //cpu paddle initialization it has the position of paddle
        Player2_x = 5; //x is 5 because of the distance from the boundary of the screen
        Player2_y = screen_height / 2 - PlayerP2_Height / 2;

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
            //CheckCollision Circle Rec is a builtin function in raylib library that checks if the circle and rectangle have touched or not
            // vector 2 is also a builtin function that gets the current location like x and y values
            if (CheckCollisionCircleRec(Vector2{ Ball_x, Ball_y }, Ball_Radius, Rectangle{ PlayerP_x, PlayerP_y, PlayerP_Width, PlayerP_Height }))
            {
                Ball_Speed_x *= -1;
            }
            if (CheckCollisionCircleRec(Vector2{ Ball_x, Ball_y }, Ball_Radius, Rectangle{ Player2_x, Player2_y, PlayerP2_Width, PlayerP2_Height }))
            {
                Ball_Speed_x *= -1;
            }

            //player paddle
            UpdatePlayerPaddle();
            DrawPaddle(PlayerP_x, PlayerP_y);

            //cpu paddle
            UpdateCpuPaddle(Ball_y);
            DrawPaddle(Player2_x, Player2_y);

            // The circle in the center of the screen 
            DrawCircleLines(640, 400, 80, WHITE);

            // Scores on the screen are used using this function
            DrawText(TextFormat("%i", CPU_Score), screen_width / 4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i", Player_Score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
            //text on the screen
            DrawText("by Kabis and Shaban", 520, 690, 25, WHITE);
            EndDrawing(); //closes canvas
        }
        ofstream file("Score.txt", ios::app);
        file << "The Score for" << name1 << " " << CPU_Score << "\n";
        file << "The Score for" << name2 << " " << Player_Score << "\n";
        CloseWindow();
    }

    //  This part is for Sinle PLayer Game 
    if (NumberOfPlayers == 'S') {
        NameEntering();
        //screen height and width
        const int screen_width = 800; //1280 is standard screen width
        const int screen_height = 600; // 800 is also a strandard screen height
        InitWindow(screen_width, screen_height, "My pong game");

        //player paddle initialization it includes the position of the padddle
        PlayerP_x = screen_width - PlayerP_Width - 5; //this equation is because of the distance from the boundary of the screen
        PlayerP_y = screen_height / 2 - PlayerP_Height / 2; //this centers the paddle because the rectangle starts from its top left corner that is why equation is used

        //cpu paddle initialization it has the position of paddle
        CPU_x = 5; //x is 5 because of the distance from the boundary of the screen
        CPU_y = screen_height / 2 - CPUP_Height / 2;

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
            //CheckCollision Circle Rec is a builtin function in raylib library that checks if the circle and rectangle have touched or not
            // vector 2 is also a builtin function that gets the current location like x and y values
            if (CheckCollisionCircleRec(Vector2{ Ball_x, Ball_y }, Ball_Radius, Rectangle{ PlayerP_x, PlayerP_y, PlayerP_Width, PlayerP_Height }))
            {
                Ball_Speed_x *= -1;
            }
            if (CheckCollisionCircleRec(Vector2{ Ball_x, Ball_y }, Ball_Radius, Rectangle{ CPU_x, CPU_y, CPUP_Width, CPUP_Height }))
            {
                Ball_Speed_x *= -1;
            }

            //player paddle
            UpdatePlayerPaddle();
            DrawPaddle(PlayerP_x, PlayerP_y);

            //cpu paddle
            UpdateCpu1Paddle(Ball_y);
            DrawPaddle(CPU_x, CPU_y);

            // The circle in the center of the screen 
            DrawCircleLines(640, 400, 80, WHITE);

            // Scores on the screen are used using this function
            DrawText(TextFormat("%i", CPU_Score), screen_width / 4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i", Player_Score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
            //text on the screen
            DrawText("by Kabis and Shaban", 520, 690, 25, WHITE);
            EndDrawing(); //closes canvas
        }
        ofstream file("Score.txt", ios::app);
        file << "The Score for" << name1 << " " << CPU_Score << "\n";
        file << "The Score for" << name2 << " " << Player_Score << "\n";
        CloseWindow();
    }
    return 0;
}

void UpdateCpu1Paddle(float ball_y) {
    if (CPU_y + CPUP_Height / 2 > ball_y) {
        CPU_y = CPU_y - CPUP_Speed;
    }

    if (CPU_y + CPUP_Height / 2 < ball_y) {
        CPU_y = CPU_y + CPUP_Speed;
    }

    if (CPU_y >= GetScreenHeight() - CPUP_Height) {
        CPU_y = CPU_y - CPUP_Speed;
    }
    if (CPU_y <= 0) {
        CPU_y = CPU_y + CPUP_Speed;
    }
}


void NameEntering() {
    InitWindow(640, 400, "Enter Your Name");
    name1.clear();

    while (!WindowShouldClose()) {
        // Capture typed characters
        int key = GetCharPressed();
        if (key >= 32 && key <= 125) {
            name1.push_back((char)key);
        }
        // Backspace removes last char
        if (IsKeyPressed(KEY_BACKSPACE)) {
            name1.pop_back();
        }

        // Enter finishes input
        if (IsKeyPressed(KEY_ENTER)) {
            break;
        }

        BeginDrawing();
        ClearBackground(Green);
        DrawText("Enter Player 1 Name:", 20, 20, 20, DARKGRAY);
        DrawText(name1.c_str(), 20, 60, 30, WHITE);
        EndDrawing();
    }

    CloseWindow();
}



void NameEntering2() {
    InitWindow(640, 400, "Enter Your Name");
    name2.clear();

    while (!WindowShouldClose()) {
        // Capture typed characters
        int key = GetCharPressed();
        if (key >= 32 && key <= 125) {
            name2.push_back((char)key);
        }

        // Backspace removes last char
        if (IsKeyPressed(KEY_BACKSPACE)) {
            name2.pop_back();
        }

        // Enter finishes input
        if (IsKeyPressed(KEY_ENTER)) {
            break;
        }

        BeginDrawing();
        ClearBackground(Green);
        DrawText("Enter Player 2 Name:", 20, 20, 20, DARKGRAY);
        DrawText(name2.c_str(), 20, 60, 30, WHITE);
        EndDrawing();
    }

    CloseWindow();
}
// this function draws paddle 
void DrawPaddle(float x, float y) {
    DrawRectangle(x, y, 15, 120, GRAY);
}

// this updates and moves player 1's paddle
void UpdatePlayerPaddle() {
    if (IsKeyDown(KEY_UP)) {
        PlayerP_y = PlayerP_y - PlayerP_Speed;// this gets the key up and then moves the paddle upwards
    }

    if (IsKeyDown(KEY_DOWN)) {
        PlayerP_y = PlayerP_y + PlayerP_Speed; // this gets key down and moves the paddle downward
    }

    if (PlayerP_y >= GetScreenHeight() - PlayerP_Height) {
        PlayerP_y = PlayerP_y - PlayerP_Speed; // this checks if paddle has crossed the edges or not then it does the counter
    }
    if (PlayerP_y <= 0) {
        PlayerP_y = PlayerP_y + PlayerP_Speed; // again this checks whether paddle is on edge or not 
    }
}

//this function updates CPU's or Player 2's Paddle
void UpdateCpuPaddle(float ball_y) {
    if (IsKeyDown('W')) {
        Player2_y = Player2_y - Player2_Speed; // this gets the key w and then moves the paddle upwards
    }

    if (IsKeyDown('S')) {
        Player2_y = Player2_y + Player2_Speed; // this gets key s and moves the paddle downward
    }

    if (Player2_y >= GetScreenHeight() - PlayerP2_Height) {
        Player2_y = Player2_y - Player2_Speed; // this checks if paddle has crossed the edges or not then it does the counter
    }
    if (Player2_y <= 0) {
        Player2_y = Player2_y + Player2_Speed; // again this checks whether paddle is on edge or not 
    }
}
// this draws a ball on the screen
void DrawBall() {
    DrawCircle(Ball_x, Ball_y, Ball_Radius, Yellow);
}

// this functions like updates or moves the ball per frame rate 
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
        Ball_Speed_y *= -1; // changes the direction of ball
    }

    if (Ball_x + Ball_Radius >= GetScreenWidth()) { // here ballx + ball radius is used because the ball is always checked from center like it position is got from its center that is why its radius is added with its x position
        CPU_Score++;
        Ball_Speed_x *= -1; // checks if it has crossed the right boundary if the touches the boundary its direction is reversed and score is also increased
    }

    if (Ball_x - Ball_Radius <= 0) {
        Ball_Speed_x *= -1;
        Player_Score++;
    }
}
