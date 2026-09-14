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

    // Decission Tree interval timer
    float interval = 10.0;
    float timer = 0.0;

    // Create Map, Staff, & Decision Tree
    auto map = std::make_unique<Map>();
    StaffManager staff;
    DecisionTree tree = DecisionTree(map.get(), &staff);


    
    map->AddStaffManager(&staff);
    map->MakeMap();
    staff.AddMap(map.get());
    staff.MakeWorkers();

    staff.MakeScout();
    staff.MakeScout();
    staff.MakeScout();
    staff.MakeScout();



    //Game Loop
    while (WindowShouldClose() == false)
    {
        timer += GetFrameTime();

        if (timer >= interval)
        {
            tree.WalkTree();
            
            timer = 0.0;
        }


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
        map->PrintProduction();
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}