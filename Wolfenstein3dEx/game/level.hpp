//
//  level.hpp
//  SuperMarioEx
//
//  Created by chen caibin on 2022/7/22.
//

#ifndef level_hpp
#define level_hpp

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "basic_mesh.hpp"
#include "basic_vertex.h"
#include "shader.h"
#include "camera.h"
#include "stb_image.h"
#include "wolf_player.hpp"
#include "door.hpp"
#include "global.hpp"
#include "resource_manager.hpp"

class Level{
    
public:
    const int NUM_TEX_EXP = 4;
    const int NUM_TEXTURES = 16;

    const float SPOT_LENGTH = 1.0f;
    const float SPOT_WIDTH = 1.0f;
    const float SPOT_HEIGHT = 1.0f;
    const float OPEN_DISTANCE = 2.0f;
    const float DOOR_OPEN_MOVEMENT_AMOUNT = 0.9f;
    
    void GenerateLevel(const char *fileName);
    void Update();
    void Render();
    glm::vec3 CheckCollision(glm::vec3 oldPos, glm::vec3 newPos, float objectWidth, float objectHeight);
    void AddSpecial(int blueValue, int x, int y);
    void AddDoor(int x, int y);
    void OpenDoors(glm::vec3 position);
    
    WolfPlayer* GetPlayer(){
        return wolfPlayer;
    }
    
    static Level* GetInstance()
    {
        if(s_instance == nullptr)
        {
            s_instance = new Level();
        }
        return s_instance;
    }

private:
    
    void flipX(int *pixels,int width,int height);
    void flipY(int *pixels,int width,int height);
    void calcTexCoords(float result[],int value);
    int getPixel(int x, int y);
    glm::vec2 rectCollide(glm::vec2 oldPos, glm::vec2 newPos, glm::vec2 size1, glm::vec2 pos2, glm::vec2 size2);
    
    BasicVertex roomVertices[10000];
    int roomIndices[10000];
    int levelPixel[4096];
    int levelWidth = 0,levelHeight = 0;
    
    BasicMesh *mapMesh;
    WolfPlayer *wolfPlayer;
    std::vector<Door*> doors;
    
    static Level *s_instance;
    
};

#endif /* level_hpp */
