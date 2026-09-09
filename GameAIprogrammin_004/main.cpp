#include "raylib.h"
#include <iostream>


#include "globals.h"
#include "map.h"
#include "StaffManager.h"
#include "DecisionTree.h"


int main()
{
    // Create Window and set FPS
    InitWindow(width, height, "Ai Movement");
    SetTargetFPS(60);



    // Create Map, Staff, & Decision Tree
    // Map map;
    auto map = std::make_unique<Map>();
    StaffManager staff;
    DecisionTree tree = DecisionTree(map.get(), &staff);



    map->AddStaffManager(&staff);
    staff.AddMap(map.get());

    staff.MakeScout();
    staff.MakeScout();
    staff.MakeScout();
    staff.MakeScout();



    //Game Loop
    while (WindowShouldClose() == false)
    {
        // Updating
        map->Update();
        staff.Update();

        // Drawing
        BeginDrawing();
        ClearBackground(Mblack);

        // Draw Stuff
        map->Draw();
        staff.Draw();
        map->DrawFog();

        staff.PrintSoldierCount();
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}