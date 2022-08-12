//
//  level.cpp
//  SuperMarioEx
//
//  Created by chen caibin on 2022/7/22.
//

#include "level.hpp"

Level* Level::s_instance = nullptr;
void Level::GenerateLevel(const char *fileName){
    
    char des[1024];
    // Load image
    int nr;
    unsigned char* image = stbi_load(Global::ResFullPath(des, fileName), &levelWidth, &levelHeight, &nr, 0);
    int *data = (int*)image;
    for (int i=0; i<levelHeight; i++) {
        for (int j=0; j<levelWidth; j++)
        {
            if(data[i*levelHeight+j] == -16777216){
                levelPixel[i*levelHeight+j] = data[i*levelHeight+j];
            }
            else{
                levelPixel[i*levelHeight+j] = data[i*levelHeight+j];
            }
        }
    }
    stbi_image_free(image);
    
    //flipY(levelPixel, levelWidth, levelHeight);
    int m = 0, n = 0;
    
    for (int i=0; i<levelWidth; i++) {
        for (int j=0; j<levelHeight; j++) {
            
            if((levelPixel[j*levelWidth+i]&0xFFFFFF) == 0)continue;
            
            AddSpecial((getPixel(i,j) & 0xFF0000)>>16, i , j);
            
            int texX = 0;
            int texY = 0;
            float xHig = 1.0f - (float)texX/(float)NUM_TEX_EXP;
            float xLow = xHig - 1.0f/(float)NUM_TEX_EXP;
            float yHig = 1.0f - (float)texY/(float)NUM_TEX_EXP;
            float yLow = yHig - 1.0f/(float)NUM_TEX_EXP;
            
            roomVertices[m+0] = {{(i+1)*SPOT_WIDTH,  0.0f,  (j+1)*SPOT_HEIGHT}, { xHig, yLow}};
            roomVertices[m+1] = {{i*SPOT_WIDTH,      0.0f,  (j+1)*SPOT_HEIGHT}, { xLow, yLow}};
            roomVertices[m+2] = {{i*SPOT_WIDTH,      0.0f,  j*SPOT_HEIGHT},     { xLow, yHig}};
            roomVertices[m+3] = {{(i+1)*SPOT_WIDTH,  0.0f,  j*SPOT_HEIGHT},     { xHig, yHig}};
            
            roomIndices[n+0] = m + 0;
            roomIndices[n+1] = m + 1;
            roomIndices[n+2] = m + 2;
            roomIndices[n+3] = m + 0;
            roomIndices[n+4] = m + 2;
            roomIndices[n+5] = m + 3;
            
            m += 4;
            n += 6;
            
            roomVertices[m+0] = {{(i+1)*SPOT_WIDTH,  SPOT_HEIGHT,  (j+1)*SPOT_HEIGHT}, { xHig, yLow}};
            roomVertices[m+1] = {{i*SPOT_WIDTH,      SPOT_HEIGHT,  (j+1)*SPOT_HEIGHT}, { xLow, yLow}};
            roomVertices[m+2] = {{i*SPOT_WIDTH,      SPOT_HEIGHT,  j*SPOT_HEIGHT},     { xLow, yHig}};
            roomVertices[m+3] = {{(i+1)*SPOT_WIDTH,  SPOT_HEIGHT,  j*SPOT_HEIGHT},     { xHig, yHig}};
            
            roomIndices[n+0] = m + 0;
            roomIndices[n+1] = m + 2;
            roomIndices[n+2] = m + 1;
            roomIndices[n+3] = m + 0;
            roomIndices[n+4] = m + 3;
            roomIndices[n+5] = m + 2;
            
            m += 4;
            n += 6;
            
            texX = 3;
            texY = 3;
            xHig = 1.0f - (float)texX/(float)NUM_TEX_EXP;
            xLow = xHig - 1.0f/(float)NUM_TEX_EXP;
            yHig = 1.0f - (float)texY/(float)NUM_TEX_EXP;
            yLow = yHig - 1.0f/(float)NUM_TEX_EXP;
            
            if((getPixel(i, j-1)&0xFFFFFF) == 0){
                roomVertices[m+0] = {{(i+1)*SPOT_WIDTH,  SPOT_HEIGHT,  j*SPOT_HEIGHT}, { xHig, yLow}};
                roomVertices[m+1] = {{i*SPOT_WIDTH,      SPOT_HEIGHT,  j*SPOT_HEIGHT}, { xLow, yLow}};
                roomVertices[m+2] = {{i*SPOT_WIDTH,      0.0f,  j*SPOT_HEIGHT},     { xLow, yHig}};
                roomVertices[m+3] = {{(i+1)*SPOT_WIDTH,  0.0f,  j*SPOT_HEIGHT},     { xHig, yHig}};
                
                roomIndices[n+0] = m + 0;
                roomIndices[n+1] = m + 2;
                roomIndices[n+2] = m + 1;
                roomIndices[n+3] = m + 0;
                roomIndices[n+4] = m + 3;
                roomIndices[n+5] = m + 2;
                
                m += 4;
                n += 6;
            }
            
            if((getPixel(i, j+1)&0xFFFFFF) == 0){
                roomVertices[m+0] = {{(i+1)*SPOT_WIDTH,  SPOT_HEIGHT,  (j+1)*SPOT_HEIGHT}, { xHig, yLow}};
                roomVertices[m+1] = {{i*SPOT_WIDTH,      SPOT_HEIGHT,  (j+1)*SPOT_HEIGHT}, { xLow, yLow}};
                roomVertices[m+2] = {{i*SPOT_WIDTH,      0.0f,  (j+1)*SPOT_HEIGHT},     { xLow, yHig}};
                roomVertices[m+3] = {{(i+1)*SPOT_WIDTH,  0.0f,  (j+1)*SPOT_HEIGHT},     { xHig, yHig}};
                
                roomIndices[n+0] = m + 0;
                roomIndices[n+1] = m + 1;
                roomIndices[n+2] = m + 2;
                roomIndices[n+3] = m + 0;
                roomIndices[n+4] = m + 2;
                roomIndices[n+5] = m + 3;
                
                m += 4;
                n += 6;
            }
            
            if((getPixel(i-1, j)&0xFFFFFF) == 0){
                roomVertices[m+0] = {{i*SPOT_WIDTH,  SPOT_HEIGHT,  (j+1)*SPOT_HEIGHT}, { xHig, yLow}};
                roomVertices[m+1] = {{i*SPOT_WIDTH,      SPOT_HEIGHT,  j*SPOT_HEIGHT}, { xLow, yLow}};
                roomVertices[m+2] = {{i*SPOT_WIDTH,      0.0f,  j*SPOT_HEIGHT},     { xLow, yHig}};
                roomVertices[m+3] = {{i*SPOT_WIDTH,  0.0f,  (j+1)*SPOT_HEIGHT},     { xHig, yHig}};
                
                roomIndices[n+0] = m + 0;
                roomIndices[n+1] = m + 1;
                roomIndices[n+2] = m + 2;
                roomIndices[n+3] = m + 0;
                roomIndices[n+4] = m + 2;
                roomIndices[n+5] = m + 3;
                
                m += 4;
                n += 6;
            }
            
            if((getPixel(i+1, j)&0xFFFFFF) == 0){
                roomVertices[m+0] = {{(i+1)*SPOT_WIDTH,  SPOT_HEIGHT,  (j+1)*SPOT_HEIGHT}, { xHig, yLow}};
                roomVertices[m+1] = {{(i+1)*SPOT_WIDTH,      SPOT_HEIGHT,  j*SPOT_HEIGHT}, { xLow, yLow}};
                roomVertices[m+2] = {{(i+1)*SPOT_WIDTH,      0.0f,  j*SPOT_HEIGHT},     { xLow, yHig}};
                roomVertices[m+3] = {{(i+1)*SPOT_WIDTH,  0.0f,  (j+1)*SPOT_HEIGHT},     { xHig, yHig}};
                
                roomIndices[n+0] = m + 0;
                roomIndices[n+1] = m + 2;
                roomIndices[n+2] = m + 1;
                roomIndices[n+3] = m + 0;
                roomIndices[n+4] = m + 3;
                roomIndices[n+5] = m + 2;
                
                m += 4;
                n += 6;
            }
        }
    }
    Shader shader = ResourceManager::GetShader("depth");
    this->mapMesh = new BasicMesh(shader,roomVertices,m,roomIndices,n,false);
    
    wolfPlayer = new WolfPlayer(shader, glm::vec3(15.0f, 0.5f, 25.0f));
    //doors.push_back(new Door(shader, glm::vec3(16.0f, 0.0f, 24.0f), {1,1,1},0, {0,1,0}));
}

void Level::flipX(int *pixels,int width,int height)
{
    int temp[10000];
    
    for(int i = 0; i < width; i++)
        for(int j = 0; j < height; j++)
            temp[i + j * width] = pixels[(width - i - 1) + j * width];
    
    memcpy(pixels, temp, width*height*sizeof(int));
}
    
void Level::flipY(int *pixels,int width,int height)
{
    int temp[10000];
    
    for(int i = 0; i < width; i++)
        for(int j = 0; j < height; j++)
            temp[i + j * width] = pixels[i + (height - j - 1)  * width];
    
    memcpy(pixels, temp, width*height*sizeof(int));
}

int Level::getPixel(int x, int y)
{
    return levelPixel[x + y * levelWidth];
}

void Level::calcTexCoords(float result[],int value)
{
        int texX = value / NUM_TEXTURES;
        int texY = texX % NUM_TEX_EXP;
        texX /= NUM_TEX_EXP;
        
        result[0] = 1.0f - (float)texX/(float)NUM_TEX_EXP;
        result[1] = result[0] - 1.0f/(float)NUM_TEX_EXP;
        result[3] = 1.0f - (float)texY/(float)NUM_TEX_EXP;
        result[2] = result[3] - 1.0f/(float)NUM_TEX_EXP;
}

glm::vec2 Level::rectCollide(glm::vec2 oldPos, glm::vec2 newPos, glm::vec2 size1, glm::vec2 pos2, glm::vec2 size2)
{
    glm::vec2 result = {0,0};
    
    if(newPos.x + size1.x < pos2.x ||
       newPos.x - size1.x > pos2.x + size2.x * size2.x ||
       oldPos.y + size1.y < pos2.y ||
       oldPos.y - size1.y > pos2.y + size2.y * size2.y)
    {
        result.x = 1.0f;
    }
    
    if(oldPos.x + size1.x < pos2.x ||
       oldPos.x - size1.x > pos2.x + size2.x * size2.x ||
       newPos.y + size1.y < pos2.y ||
       newPos.y - size1.y > pos2.y + size2.y * size2.y)
    {
        result.y = 1.0f;
    }
    return result;
}

glm::vec3 Level::CheckCollision(glm::vec3 oldPos, glm::vec3 newPos, float objectWidth, float objectHeight)
{
    glm::vec2 collisionVector = {1,1};
    glm::vec3 movementVector = newPos - oldPos;
    
    if(movementVector.length() > 0)
    {
        glm::vec2 blockSize = {SPOT_WIDTH, SPOT_HEIGHT};
        glm::vec2 objectSize = {objectWidth, objectHeight};
        
        glm::vec2 oldPos2 = {oldPos.x, oldPos.z};
        glm::vec2 newPos2 = {newPos.x, newPos.z};
        
        for(int i = 0; i < levelWidth; i++)
        for(int j = 0; j < levelHeight; j++){
            if((getPixel(i,j) & 0xFFFFFF) == 0){
                collisionVector *= rectCollide(oldPos2, newPos2, objectSize, blockSize * glm::vec2(i,j), blockSize);
            }
        }
        for(Door *door : doors)
        {
            glm::vec2 doorSize = door->GetDoorSize();
            glm::vec3 doorPos3f = door->GetPosition();
            glm::vec2 doorPos2f = glm::vec2(doorPos3f.x, doorPos3f.z);
            collisionVector *= rectCollide(oldPos2, newPos2, objectSize, doorPos2f, doorSize);
        }
    }
    return {collisionVector.x, 0, collisionVector.y};
}

void Level::Update()
{
    wolfPlayer->Update();
    for(Door *door : doors){
        door->Update();
    }
}

void Level::Render(){
    Texture2D texture = ResourceManager::GetTexture("wolfenstein");
    mapMesh->Draw(texture,{0,0,0});
    
    for(Door *door : doors){
        door->Render(wolfPlayer->GetCamera());
    }
    wolfPlayer->Render();
}

void Level::AddSpecial(int blueValue, int x, int y)
{
    if(blueValue == 16)
        AddDoor(x, y);
}

void Level::AddDoor(int x, int y)
{
    glm::vec3 doorPosition;

    bool xDoor = (getPixel(x, y - 1) & 0xFFFFFF) == 0 && (getPixel(x, y + 1) & 0xFFFFFF) == 0;
    bool yDoor = (getPixel(x - 1, y) & 0xFFFFFF) == 0 && (getPixel(x + 1, y) & 0xFFFFFF) == 0;

    if(!(xDoor ^ yDoor))
    {
        printf("Level Generation has failed! :( You placed a door in an invalid location at %d,%d " , x , y);
        return;
    }

    glm::vec3 openPosition;
    Shader shader = ResourceManager::GetShader("depth");
    
    if(yDoor)
    {
        doorPosition = {x, 0, y + SPOT_LENGTH / 2};
        openPosition = doorPosition - glm::vec3(DOOR_OPEN_MOVEMENT_AMOUNT, 0.0f, 0.0f);
        Door *door = new Door(shader, doorPosition);
        door->SetOpenPosition(openPosition);
        doors.push_back(door);
    }

    if(xDoor)
    {
        doorPosition = {x + SPOT_WIDTH / 2, 0, y};
        openPosition = doorPosition - glm::vec3(0.0f, 0.0f, DOOR_OPEN_MOVEMENT_AMOUNT);
        Door *door = new Door(shader, doorPosition, {1,1,1}, 90.0f, {0,1.0f,0});
        door->SetOpenPosition(openPosition);
        doors.push_back(door);
    }
}

void Level::OpenDoors(glm::vec3 position)
{
    for(Door *door : doors)
    {
        float result = glm::length(door->GetPosition()-position);
        if(result < OPEN_DISTANCE)
        {
            door->Open();
        }
    }
}
