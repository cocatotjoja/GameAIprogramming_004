#include "raylib.h"
#include "colors.h"
#include "mapReader.h"


int main()
{
    //Window size
    float width = 1200;
    float height = 1200;
    float margin = 0;

    // Create Window and set FPS
    InitWindow(width, height, "Ai Movement");
    SetTargetFPS(60);




    // Create Map

    // Create Workers
    // Create Objects



    //Game Loop
    while (WindowShouldClose() == false)
    {
        // Updating
        

        // Drawing
        BeginDrawing();
        ClearBackground(black);

        // Draw Stuff

        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}