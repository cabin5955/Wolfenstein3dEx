//
//  door.hpp
//  SuperMarioEx
//
//  Created by chen caibin on 2022/7/21.
//

#ifndef door_hpp
#define door_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "basic_mesh.hpp"
#include "basic_vertex.h"
#include "shader.h"
#include "camera.h"

class Door{
    
public:
    static constexpr float LENGTH = 1.0f;
    static constexpr float HEIGHT = 1.0f;
    static constexpr float WIDTH = 0.125f;
    static constexpr float START = 0.0f;
    static constexpr double TIME_TO_OPEN = 0.5f;
    static constexpr double CLOSE_DELAY = 2.0f;
    
    Door(Shader &shader,glm::vec3 position,glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f),
         float rotation= 0.0f, glm::vec3 axis = glm::vec3(0, 0, 1.0f));
    void Update();
    void Render(Camera *camera);
    void SetOpenPosition(glm::vec3 pos);
    glm::vec2 GetDoorSize();
    glm::vec3 GetPosition(){return position;}
    void Open();
    
private:
    glm::vec3 position;
    glm::vec3 axis;
    glm::vec3 scale;
    float rotationAngle;
    
    Shader shader;
    BasicMesh *mesh;
    
    glm::vec3 openPosition;
    glm::vec3 closePosition;

    bool isOpening;
    double openingStartTime;
    double openTime;
    double closingStartTime;
    double closeTime;

};

#endif /* door_hpp */
