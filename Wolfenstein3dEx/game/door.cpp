//
//  door.cpp
//  SuperMarioEx
//
//  Created by chen caibin on 2022/7/21.
//

#include "door.hpp"
#include "resource_manager.hpp"
#include "global.hpp"
#include "utils.h"

Door::Door(Shader &sha,glm::vec3 pos,glm::vec3 sca,float rot, glm::vec3 ax):
shader(sha),position(pos),scale(sca),rotationAngle(rot),axis(rot)
{
    
    isOpening = false;
    closePosition = position * 1.0f;
    
    BasicVertex vertices[16];
    int indices[24];
    int texX = 1;
    int texY = 0;
    int NUM_TEX_EXP = 4;
    float xHig = 1.0f - (float)texX/(float)NUM_TEX_EXP;
    float xLow = xHig - 1.0f/(float)NUM_TEX_EXP;
    float yHig = 1.0f - (float)texY/(float)NUM_TEX_EXP;
    float yLow = yHig - 1.0f/(float)NUM_TEX_EXP;
    
    vertices[0] = {{LENGTH,HEIGHT,START}, { xHig, yLow}};
    vertices[1] = {{START,HEIGHT,START},  { xLow, yLow}};
    vertices[2] = {{START,START,START},   { xLow, yHig}};
    vertices[3] = {{LENGTH,START,START},  { xHig, yHig}};
    
    vertices[4] = {{START,HEIGHT,START},  { xHig, yLow}};
    vertices[5] = {{START,HEIGHT,WIDTH},  { xHig-0.02f, yLow}};
    vertices[6] = {{START,START,WIDTH},   { xHig-0.02f, yHig}};
    vertices[7] = {{START,START,START},   { xHig, yHig}};
    
    vertices[8]  = {{LENGTH,HEIGHT,WIDTH}, { xHig, yLow}};
    vertices[9]  = {{START,HEIGHT,WIDTH},  { xLow, yLow}};
    vertices[10] = {{START,START,WIDTH},   { xLow, yHig}};
    vertices[11] = {{LENGTH,START,WIDTH},  { xHig, yHig}};
    
    vertices[12] = {{LENGTH,HEIGHT,START},  { xHig, yLow}};
    vertices[13] = {{LENGTH,HEIGHT,WIDTH},  { xHig-0.02f, yLow}};
    vertices[14] = {{LENGTH,START,WIDTH},   { xHig-0.02f, yHig}};
    vertices[15] = {{LENGTH,START,START},   { xHig, yHig}};
    
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
    
    indices[6] = 4;
    indices[7] = 5;
    indices[8] = 6;
    indices[9] = 4;
    indices[10] = 6;
    indices[11] = 7;
    
    indices[12] = 10;
    indices[13] = 9;
    indices[14] = 8;
    indices[15] = 11;
    indices[16] = 10;
    indices[17] = 8;
    
    indices[18] = 14;
    indices[19] = 13;
    indices[20] = 12;
    indices[21] = 15;
    indices[22] = 14;
    indices[23] = 12;
    
    int m = 16;
    int n = 24;
    
    mesh = new BasicMesh(shader,vertices,m,indices,n,false);
}

void Door::SetOpenPosition(glm::vec3 pos){
    openPosition = pos;
}

void Door::Update()
{
    if(isOpening)
    {
        double time = Global::GetTime();

        if(time < openTime)
        {
            if(rotationAngle == 0)
                openPosition = closePosition - glm::vec3(0.9f, 0.0f, 0.0f);
            else
                openPosition = closePosition - glm::vec3(0.0f, 0.0f, 0.9f);
            
            float fact = (float)((time - openingStartTime) / TIME_TO_OPEN);
            position = Lerp(closePosition, openPosition, fact);
        }
        else if(time < closingStartTime)
        {
            position = openPosition;
        }
        else if(time < closeTime)
        {
            float fact = (float)((time - closingStartTime) / TIME_TO_OPEN);
            position = Lerp(openPosition, closePosition, fact);
        }
        else
        {
            position = closePosition;
            isOpening = false;
        }
    }
}

void Door::Render(Camera *camera)
{
    float width = Global::ScreenWidth;
    float height = Global::ScreenHeight;
    
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), width / height, 0.1f, 100.0f);
    
    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    
    Texture2D texture = ResourceManager::GetTexture("wolfenstein");
    mesh->Draw(texture,position,scale,rotationAngle,axis);
}

glm::vec2 Door::GetDoorSize()
{
    if(rotationAngle == 0)
        return glm::vec2(LENGTH, WIDTH);
    else
        return glm::vec2(WIDTH, LENGTH);
}

void Door::Open()
{
    if(isOpening)
        return;

    openingStartTime = Global::GetTime();
    openTime = openingStartTime + TIME_TO_OPEN;
    closingStartTime = openTime + CLOSE_DELAY;
    closeTime = closingStartTime + TIME_TO_OPEN;

    isOpening = true;
}
