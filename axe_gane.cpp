#include "raylib.h"
#include <cmath>
#include <string>
#include <string.h>
#include <vector>
#include <map>

using std::string;
using std::to_string;
using std::map;
using std::vector;



//global variables (ick)
    double wWidth{1280};
    double wHeight{720};

//player and enemy structs
struct Player
{
    double xPos{wWidth/2};
    double yPos{wHeight/2};
    double xVel{0};
    double yVel{0};
    int size{25};
    double velScaler{wWidth/150};
    double colTop{yPos - size};
    double colBot{yPos + size};
    double colLeft{xPos - size};
    double colRight{yPos + size};

    void setPos(double x, double y)
    {
        this->xPos = x;
        this->yPos = y;
    }
    void setCol()
    {
        this->colTop = this->yPos - this->size;
        this->colBot = this->yPos + this->size;
        this->colLeft = this->xPos - this->size;
        this->colRight = this->xPos + this->size;
    }
};

struct Axe
{
    int xPos{0};
    int yPos{0};
    int height{50};
    int width{50};

    int xVel{10};
    int yVel{10};

//collision boxes
    int colTop{yPos};
    int colBot{yPos + height};
    int colLeft{xPos};
    int colRight{xPos + width};


    void setPos(double x, double y)
    {
        xPos = x;
        yPos = y;
    }
    void setCol()
    {
        this->colTop = this->yPos;
        this->colBot = this->yPos + this->height;
        this->colLeft = this->xPos;
        this->colRight = this->xPos + this->width;
    }
};

  

void setPlayerPos(double* circleX, double* circleY)
{
    *circleX = wWidth/2;
    *circleY = wHeight/2;
}

bool isCollision(Axe axe, Player player)
{
    if(
    (axe.colBot >= player.colTop) && 
    (axe.colTop <= player.colBot) && 
    (axe.colLeft <= player.colRight) && 
    (axe.colRight >= player.colLeft))
        return true;
    else
        return false;
}


int main()
{
    InitWindow(wWidth, wHeight, "Axe Game");
    SetTargetFPS(60);
    Player p1; 
    Axe nme1;

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLUE);

        if (isCollision(nme1, p1))
        {
            DrawText("Game Over!", wWidth/3, wHeight/3, 20, RED);
            DrawText("Would you like to continue? (y/n)", wWidth/3, wHeight/3 + 40, 20, RED);
                if(IsKeyDown(KEY_Y))
                {
                    p1.setPos(wWidth/2, wHeight/2);
                    nme1.setPos(0, 0);
                    p1.setCol();
                    nme1.setCol();
                    continue;
                }
                else if(IsKeyDown(KEY_N))
                    break;
        }
        else
        {
            //game logic
            DrawCircle(p1.xPos, p1.yPos, p1.size, GREEN);
            DrawRectangle(nme1.xPos, nme1.yPos, nme1.width, nme1.height, RED);

            nme1.xPos += nme1.xVel;
            nme1.yPos += nme1.yVel;

            if(nme1.yPos > (wHeight - nme1.height) || nme1.yPos < 0)
            {
                if(nme1.yPos < 0)
                    nme1.yPos = 0;
                else
                    nme1.yPos = wHeight - nme1.height;

                nme1.yVel = -(nme1.yVel + .5);
                nme1.xVel += GetRandomValue(-5, 5);
            }
            if(nme1.xPos > (wWidth - nme1.width) || nme1.xPos < 0)
            {
                if(nme1.xPos < 0)
                    nme1.xPos = 0;
                else
                    nme1.xPos = wWidth - nme1.width;

                nme1.xVel = -(nme1.xVel + .5);
                nme1.yVel += GetRandomValue(-5, 5);
            }


            //player input
            
            if (IsKeyDown(KEY_D))
            {
                p1.xVel = 1;
            }
            if (IsKeyDown(KEY_A))
            {
                p1.xVel = -1;
            }
            if (IsKeyDown(KEY_W))
            {
                p1.yVel = -1;
            }
            if (IsKeyDown(KEY_S))
            {
                p1.yVel = 1;
            }
            if(p1.xVel != 0 && p1.yVel != 0)
            {
                p1.velScaler *= (sqrt(2)/2);
            }


           

            string debugVelX = to_string(p1.xVel * p1.velScaler);
            string debugVelY = to_string(p1.yVel * p1.velScaler); 
            DrawText(debugVelX.c_str(), 0, 0, 20, RED);
            DrawText(debugVelY.c_str(), 0, 20, 20, RED);

            p1.xPos += p1.xVel * p1.velScaler;
            p1.yPos += p1.yVel * p1.velScaler;

            //window-based player boundaries
            if(p1.xPos < p1.size)
                p1.xPos = p1.size;
            if(p1.xPos > wWidth - p1.size)
                p1.xPos = wWidth - p1.size;
            if(p1.yPos < p1.size)
                p1.yPos = p1.size;
            if(p1.yPos > wHeight - p1.size)
                p1.yPos = wHeight - p1.size;

                 

            p1.xVel = 0;
            p1.yVel = 0;
            p1.velScaler = wWidth/150;
            p1.setCol();
            nme1.setCol();

        

        }
  

        //End
        EndDrawing();
    }

    return 0;
}