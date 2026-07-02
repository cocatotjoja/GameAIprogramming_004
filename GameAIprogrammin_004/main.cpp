#include "raylib.h"
#include "globals.h"
#include "map.h"
#include "StaffManager.h"

int main()
{
    //Window size
    float width = 1000 * resMult;
    float height = 1000 * resMult;
    float margin = 0;

    // Create Window and set FPS
    InitWindow(width, height, "Ai Movement");
    SetTargetFPS(60);




    // Create Map
    Map newMap;
    // Create Workers
    //StaffManager staff;


    //Game Loop
    while (WindowShouldClose() == false)
    {
        // Updating
        

        // Drawing
        BeginDrawing();
        ClearBackground(Mblack);

        // Draw Stuff
        newMap.Draw();
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}