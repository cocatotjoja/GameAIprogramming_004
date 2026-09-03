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
    // Scout scout1 = Scout(Vector2{ 210*resMult+3, 360*resMult+7 }, &newMap);
    // Scout scout2 = Scout(Vector2{ 210*resMult+5, 360*resMult+7 }, &newMap);
    //StaffManager staff;


    //Game Loop
    while (WindowShouldClose() == false)
    {
        // Updating
        // scout1.Update();
        // scout2.Update();

        // Drawing
        BeginDrawing();
        ClearBackground(Mblack);

        // Draw Stuff
        newMap.Draw();
        // scout1.Draw();
        // scout2.Draw();
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}



// TODO: Ask Fredrik: 
// Severity	Code	Description	Project	File	Line	Suppression State	Details
// Warning	MSB8028	The intermediate directory(GameAIpr.28b59abf\x64\Debug\) contains files shared from another project(GameAIprogrammin_001.vcxproj).This can lead to incorrect clean and rebuild behavior.GameAIprogrammin_004	C : \Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Microsoft\VC\v170\Microsoft.CppBuild.targets	538
