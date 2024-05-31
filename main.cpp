#include "raylib.h"
#include <vector>
#include <string>
#include "raymath.h"

#include "rlgl.h"


#include <map>
#include <thread>
#include <chrono>


#include <iostream>



float PLAYER_SPEED = 250.0f;
float BULLET_SIZE = 3.0f;


enum GAME_STATES {


    MAIN_MENU, 
    MAIN_GAME, 
   

};

int CURRENT_GAME_STATE = MAIN_MENU;



struct platform {

    Vector2 position;
    Vector2 size;
    Rectangle collisionRect;
    Texture2D texture;

};

struct enemy {

    Vector2 position;
    Vector2 size;
    Vector2 direction;
    Rectangle collisionRect;
};

std::vector<enemy> enemies;


bool isOverlapping(const platform& p1, const platform& p2, int minDistance) {
    bool xOverlap = std::abs(p1.position.x - p2.position.x) < (p1.size.x + p2.size.x + minDistance);
    bool yOverlap = std::abs(p1.position.y - p2.position.y) < (p1.size.y + p2.size.y + minDistance);
    return xOverlap && yOverlap;
}


void timerFunc() {

    for (;;) {
    
        for (int i = 0; i < 5; i++) {

            enemy e1;
            e1.position.x = rand() % 800 + 1;
            e1.position.y = rand() % 1200 + 1;
            e1.size.x = 20;
            e1.size.y = 20;


            e1.collisionRect.height = 20;
            e1.collisionRect.width = 20;
            e1.collisionRect.x = e1.position.x;
            e1.collisionRect.y = e1.position.y;

            enemies.push_back(e1);
        
        }
        
    
       

        std::this_thread::sleep_for(std::chrono::seconds(3));

    }
}



int main(void)
{
    InitWindow(400, 600, "raylib [core] example - basic window");

    Texture2D background_tile = LoadTexture("background_brick_3.png"); 
    Texture2D sky_texture = LoadTexture("sky_1.png");
    Texture2D platform_1 = LoadTexture("platform_1.png");
    Texture2D level_1_enemy_1 = LoadTexture("level_1_enemy_3.png");
    Texture2D player_1 = LoadTexture("player_2_walking.png");


    float frameWidth = (float)(player_1.width / 3);



    RenderTexture2D renderTexture = LoadRenderTexture(400, 600);



    float player_vel_x = 0.0, player_vel_y = 0.0;

    float player_pos_x = 200, player_pos_y = 200;

    bool isJumping = true;

    struct bullet{

        Vector2 position;
        Vector2 direction;
   

    };

   
    
    bool validPosition = false;

    std::vector<bullet> bullets;
    std::vector<platform> platforms;




    Rectangle player_rect;


    std::map<int, int> platform_side;

    float temp_position = 0;

    enemy e1;
    e1.position.x = 100;
    e1.position.y = 200;
    e1.size.x = 20;
    e1.size.y = 20;

    e1.collisionRect.height = 20;
    e1.collisionRect.width = 20;
    e1.collisionRect.x = 100;
    e1.collisionRect.y = 200;


    enemies.push_back(e1);


    BeginTextureMode(renderTexture);

    ClearBackground(RAYWHITE);


    DrawTexture(sky_texture, 0, 0, SKYBLUE);
  
    EndTextureMode();

    for (int i = 0;i < 7; i++) {
    
        platform p1;
        
    do{

        validPosition = true;

        p1.size.x = rand() % 100 + 50;
        p1.size.y = 30;

        p1.position.x = ((rand() % 2 + 0) == 1) ? 0 : 400 - p1.size.x;
        p1.position.y = rand() % 600 + 0;


        for (const auto& platform : platforms) {
            if (isOverlapping(p1, platform, 50)) {
                validPosition = false;
                break;
            }
        }
    } while (!validPosition);

    p1.collisionRect.height = 30;
    p1.collisionRect.width = p1.size.x;
    p1.collisionRect.x = p1.position.x;
    p1.collisionRect.y = p1.position.y;


    


    p1.texture = LoadTexture("platform_2.png");;
    p1.texture.height = p1.size.y;
    p1.texture.width = p1.size.x;


    platforms.push_back(p1);
    
    }


    std::thread t1(timerFunc);

    float timer = 0.0f;
    int frame = 0;
    

    int maxFrames = 3;

    while (!WindowShouldClose())
    {


        if (CURRENT_GAME_STATE == MAIN_MENU) {
        

        
        }

        else if (CURRENT_GAME_STATE == MAIN_GAME) {
        

        
        }




        float deltaTime = GetFrameTime();


        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyDown(KEY_A)) {
        
            player_vel_x = -PLAYER_SPEED;
            if (!isJumping) {

                timer += GetFrameTime();
                if (frameWidth >= 0) {
                    frameWidth *= -1;
                }

            }
        
        }

        if (IsKeyDown(KEY_D)) {

            player_vel_x = PLAYER_SPEED;
            if (!isJumping) {

                timer += GetFrameTime();
                if (frameWidth < 0) {
                    frameWidth *= -1;
                }

            }


        }

        if (IsKeyReleased(KEY_A) || IsKeyReleased(KEY_D)) {
        
            player_vel_x = 0;

        
        }

        if (IsKeyPressed(KEY_SPACE) && !isJumping) {
            player_vel_y = -300;
            isJumping = true;
        }


      /*  while (true) {*/
        

        player_rect.height = 50;
        player_rect.width = 50;
        player_rect.x = player_pos_x;
        player_rect.y = player_pos_y;




        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
           

            Vector2 direction_bullet = Vector2Normalize({ GetMousePosition().x - player_pos_x, GetMousePosition().y - player_pos_y });


            bullet b1;
            b1.position.x = player_pos_x + 25;
            b1.position.y = player_pos_y + 25;

            b1.direction = direction_bullet;
            bullets.push_back(b1);
           
        }

        

       /* }*/


        player_vel_y += 400.0f * deltaTime;       

        

        if (player_pos_y >= 600 - player_1.height) {
            player_pos_y = 600 - (player_1.height + 0.001);
            player_vel_y = 0;
            isJumping = false;
        }

        if (player_pos_x + frameWidth > 400 ) {
            player_pos_x = 400 - (frameWidth + 0.001);
            player_vel_x = 0;
        }


        if (player_pos_x < 0) {
            player_pos_x = 1;
            player_vel_x = 0;
        }


        player_pos_x += player_vel_x * GetFrameTime();
        player_pos_y += player_vel_y * GetFrameTime();


        for (int i = 0; i < bullets.size(); i++) {

            bullets[i].position.x += bullets[i].direction.x * 700 * deltaTime;
            bullets[i].position.y += bullets[i].direction.y * 700 * deltaTime;

            

            if (bullets[i].position.x < 0 || bullets[i].position.x > 400 || bullets[i].position.y < 0 || bullets[i].position.y > 600) {
            
                bullets.erase(bullets.begin() + i);
            
            }

            
        }

        for (int i = 0; i < bullets.size(); i++) {
        
            for (int j = 0; j < enemies.size(); j++) {

                if (CheckCollisionCircleRec(bullets[i].position, 6, enemies[j].collisionRect)) {
    
                    enemies.erase(enemies.begin() + j);
                    bullets.erase(bullets.begin() + i);
                    break;

                }

            }
        

   


        }

        for (int i = 0;i < bullets.size(); i++) {
        
            for (int j = 0; j < platforms.size(); j++) {

                if (CheckCollisionCircleRec(bullets[i].position, 6, platforms[j].collisionRect)) {

                    bullets.erase(bullets.begin() + i);
                    break;

                }

            }
        
        
        }


       

        for (int i = 0; i < enemies.size();i++) {

            enemies[i].direction = Vector2Normalize({ player_pos_x - enemies[i].position.x, player_pos_y - enemies[i].position.y });

            enemies[i].position.x += enemies[i].direction.x * 80 * deltaTime;
            enemies[i].position.y += enemies[i].direction.y * 80 * deltaTime;


            enemies[i].collisionRect.x = enemies[i].position.x;
            enemies[i].collisionRect.y = enemies[i].position.y;

            
            if (CheckCollisionRecs(enemies[i].collisionRect, player_rect)) {
            


            }


        }



        //platform player collision

        for (int i = 0; i < platforms.size(); i++) {
        
           
            
            
            if (player_pos_y > platforms[i].position.y - (player_1.height + 1) &&

                player_pos_x >= platforms[i].position.x &&
                 
                player_pos_x <= platforms[i].position.x + platforms[i].size.x && 

                platforms[i].position.y > player_pos_y + (player_1.height)

                
                ) {


                player_pos_y = platforms[i].position.y - (player_1.height + 1);
                player_vel_y = 0;
                isJumping = false;
            
            }


            if (player_pos_y < platforms[i].position.y + platforms[i].size.y &&

                player_pos_x >= platforms[i].position.x &&

                player_pos_x <= platforms[i].position.x + platforms[i].size.x &&

                platforms[i].position.y < player_pos_y


                ) {

                player_pos_y = platforms[i].position.y + platforms[i].size.y + 1;
                player_vel_y = 0;
                isJumping = true;

            }






            if ((player_pos_x + frameWidth > platforms[i].position.x && platforms[i].position.x!=0 && 
                
                platforms[i].position.y > player_pos_y && 

                platforms[i].position.y < player_pos_y + (player_1.height )) ||


                (player_pos_x + frameWidth > platforms[i].position.x && platforms[i].position.x != 0 &&

                    platforms[i].position.y + platforms[i].size.y > player_pos_y &&

                    platforms[i].position.y + platforms[i].size.y < player_pos_y + (player_1.height))



                ) {

                player_pos_x = platforms[i].position.x - (frameWidth + 1);
                player_vel_x = 0;
                isJumping = true;

            }




            if ((player_pos_x < platforms[i].size.x && platforms[i].position.x == 0 &&

                platforms[i].position.y > player_pos_y &&

                platforms[i].position.y < player_pos_y + (player_1.height)) ||


                (player_pos_x < platforms[i].size.x && platforms[i].position.x == 0 &&

                    platforms[i].position.y + platforms[i].size.y > player_pos_y &&

                    platforms[i].position.y + platforms[i].size.y < player_pos_y + (player_1.height))


                ) {


                player_pos_x = platforms[i].position.x + platforms[i].size.x + 1;
                player_vel_x = 0;
                isJumping = true;

            }
            


        
        }

      

        DrawTexture(renderTexture.texture, 0, 0, WHITE);


        for (int i = 0; i < bullets.size(); i++) {

            DrawCircle(bullets[i].position.x, bullets[i].position.y, BULLET_SIZE, BLACK);

        }



        for (int i = 0; i < platforms.size(); i++) {

            DrawTexture(platforms[i].texture, platforms[i].position.x, platforms[i].position.y, WHITE);

                  
        }

        for (int i = 0; i < enemies.size(); i++) {

            DrawTexture(level_1_enemy_1, enemies[i].position.x, enemies[i].position.y, WHITE);

        }

        
        DrawText(std::to_string(GetFPS()).c_str(), 300, 20, 20, BLACK);
 

        if (timer >= 0.1f) {
        
            timer = 0.0f;
            frame += 1;
        
        }

        

        frame = frame % maxFrames;
        
        DrawTextureRec(player_1, {frameWidth * frame,0.0f,frameWidth,(float)player_1.height}, {player_pos_x, player_pos_y}, YELLOW);
        EndDrawing();
    }

    t1.detach();



    CloseWindow();

    return 0;
}