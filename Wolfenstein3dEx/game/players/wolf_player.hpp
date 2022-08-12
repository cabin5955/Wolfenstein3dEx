//
//  wolf_player.hpp
//  SuperMarioEx
//
//  Created by chen caibin on 2022/7/19.
//

#ifndef wolf_player_hpp
#define wolf_player_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "touch_delegate_protocol.h"
#include "touch_dispatcher.hpp"
#include "director.hpp"
#include "camera.h"
#include "basic_mesh.hpp"
#include "basic_vertex.h"
#include "shader.h"
#include "text_renderer.hpp"

class WolfPlayer:public TouchDelegate
{
public:
    static constexpr float GUN_OFFSET = -0.075f;
    static constexpr float SCALE = 0.0625f;
    static constexpr float SIZEY = SCALE;
    static constexpr float SIZEX = (float)((double)SIZEY / (1.0379746835443037974683544303797 * 2.0));
    static constexpr float START = 0;
    
    WolfPlayer(Shader &shader,glm::vec3 position);
    
    bool TouchBegan(double x, double y);
    // optional

    void TouchMoved(double x, double y);
    void TouchEnded(double x, double y);
    void TouchCancelled(double x, double y);
    
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    Camera* GetCamera();
    void Update();
    void Render();
    
private:
    Camera *camera;
    glm::vec3 movement;
    glm::vec2 centerPosition;
    glm::vec3 gunPosition;
    float gunRotation;
    
    Shader          shader;
    BasicMesh       *mesh;
    TextRenderer    *Text;
    
    float lastX;
    float lastY;
    bool firstMouse = true;
};

#endif /* wolf_player_hpp */
