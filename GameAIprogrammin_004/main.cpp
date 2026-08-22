#include "raylib.h"
#include "globals.h"
#include "map.h"
#include "StaffManager.h"

int main()
{
    // Create Window and set FPS
    InitWindow(width, height, "Ai Movement");
    SetTargetFPS(60);




    // Create Map
    Map newMap;
    // Create Workers
    Scout scout1 = Scout(Vector2{ 0, 0 }, Vector2{ 210*resMult+3, 360*resMult+7 }, &newMap);
    Scout scout2 = Scout(Vector2{ 50, 0 }, Vector2{ 210*resMult+5, 360*resMult+7 }, &newMap);
    //Scout scout3 = Scout(Vector2{ 0, 50 }, Vector2{ 210*resMult+3, 360*resMult+2 }, &newMap);
    //Scout scout4 = Scout(Vector2{ 49, 49 }, Vector2{ 210*resMult+7, 360*resMult+2 }, &newMap);
    //StaffManager staff;


    //Game Loop
    while (WindowShouldClose() == false)
    {
        // Updating
        scout1.Update();
        scout2.Update();
        //scout3.Update();
        //scout4.Update();

        // Drawing
        BeginDrawing();
        ClearBackground(Mblack);

        // Draw Stuff
        newMap.Draw();
        scout1.Draw();
        scout2.Draw();
        //scout3.Draw();
        //scout4.Draw();
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}