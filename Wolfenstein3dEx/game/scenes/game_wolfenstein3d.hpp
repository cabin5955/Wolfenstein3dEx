//
//  game_wolfenstein3d.hpp
//  SuperMarioEx
//
//  Created by chen caibin on 2022/7/10.
//

#ifndef game_wolfenstein3d_hpp
#define game_wolfenstein3d_hpp

#include "glad.h"
#include <vector>
#include "scene.h"
#include <string>
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"
#include "text_renderer.hpp"
#include "director.hpp"
#include "button.hpp"
#include "color_renderer.hpp"
#include "color.h"
#include "global.hpp"
#include "utils.h"
#include "mesh.hpp"
#include "libex.h"
#include "basic_vertex.h"
#include "basic_mesh.hpp"

class GameWolfenstein3D:public IScene
{
public:
    
    // Initialize game state (load all shaders/textures/levels)
    void Init(unsigned int width, unsigned int height);
    void OnEnter();
    void OnExit();
    // GameLoop
    void KeyboardInput(ExKeyCode keycode, ExKeyAction action);
    void Update(GLfloat dt);
    void Render();
    
    void Release();
    
    static GameWolfenstein3D* GetInstance()
    {
        if(s_instance == nullptr)
        {
            s_instance = new GameWolfenstein3D();
        }
        return s_instance;
    }
    GLchar                 preferPath[1024];
    
private:
    GLfloat deltaTime;
    
    SpriteRenderer      *uiRenderer;
    ColorRenderer       *colorRenderer;
    
    TextRenderer        *Text;

    Button *GoButton_Right,*GoButton_Left,*JumpButton;
    
    Camera2D camera;
    
    GameWolfenstein3D(){}
    
    ~GameWolfenstein3D(){}

    GameWolfenstein3D(const GameWolfenstein3D&);
    GameWolfenstein3D& operator =(const GameWolfenstein3D&);
    
    static GameWolfenstein3D *s_instance;
};

#endif /* game_wolfenstein3d_hpp */
