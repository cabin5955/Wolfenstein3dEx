//
//  game_wolfenstein3d.cpp
//  SuperMarioEx
//
//  Created by chen caibin on 2022/7/10.
//

#include "game_wolfenstein3d.hpp"
#include "camera.h"
#include "level.hpp"

GameWolfenstein3D* GameWolfenstein3D::s_instance = nullptr;

BasicVertex vertices[] = {
//    {{-0.5f,  0.5f, 0.0f}, {0.0f,1.0f}},
//    {{-0.5f, -0.5f, 0.0f}, {0.0f,0.0f}},
//    {{0.5f, -0.5f,  0.0f}, {1.0f,0.0f}},
//    {{0.5f,  0.5f,  0.0f}, {1.0f,1.0f}}
    
    {{1.0f,  0.0f,  1.0f}, { 1.0f, 0.0f}},
    {{0.0f,  0.0f,  1.0f}, { 0.0f, 0.0f}},
    {{0.0f,  0.0f,  0.0f}, { 0.0f, 1.0f}},
    {{1.0f,  0.0f,  0.0f}, { 1.0f, 1.0f}}
};

int indices[] = {
//    0, 1, 2,
//    2, 3, 0
    0, 1, 2,
    0, 2, 3
    };

glm::vec3 cameraPos   = glm::vec3(0.0f, 3.0f,  -3.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
glm::vec3 cameraTarget = {0,0,0};

float cameraZOOM      =  60.0f;

void GameWolfenstein3D::Init(unsigned int width, unsigned int height)
{
    this->Width = width;
    this->Height = height;
    char des[1024] = {0};
    ResourceManager::LoadTexture(Global::ResFullPath(des,"WolfCollection.png"), GL_TRUE, "wolfenstein");
    ResourceManager::LoadTexture(Global::ResFullPath(des,"PISGB0.png"), GL_TRUE, "gun");
    
    // 配置着色器
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
                                        static_cast<GLfloat>(this->Height),0.0f,
                                        -1.0f, 1.0f);
    
    Shader colorShader = ResourceManager::GetShader("color");
    colorShader.use();
    colorShader.setMat4("view", glm::mat4(1.0));
    colorShader.setMat4("projection", projection);
    
    Shader uiShader = ResourceManager::GetShader("ui");
    uiShader.use();
    uiShader.setMat4("projection", projection);
    
    Shader cubeShader = ResourceManager::GetShader("cube");
    cubeShader.use();
    cubeShader.setMat4("projection", projection);
    
    //Shader simpleShader = ResourceManager::GetShader("simple");
    
    Shader textShader = ResourceManager::GetShader("text");
    Text = new TextRenderer(textShader, this->Width, this->Height);
    Text->Load(Global::ResFullPath(des,"default.ttf"),48);
    
    // 设置专用于渲染的控制
    colorRenderer = new ColorRenderer(colorShader);
    uiRenderer = new SpriteRenderer(uiShader);
    
    float scal = 1.0f;
    int btn_size = 64;
    GoButton_Right = new Button(this,glm::vec2(this->Width/2+btn_size*scal-btn_size*4,this->Height-128*scal),
                                glm::vec2(btn_size*scal,btn_size*scal),
                                0,
                                ResourceManager::GetTexture("arrow"),
                                0,0);
    
    GoButton_Left = new Button(this,glm::vec2(this->Width/2-btn_size*scal-btn_size*4,this->Height-128*scal),
                               glm::vec2(btn_size*scal,btn_size*scal),
                               180.0f*DEG2RAD,
                               ResourceManager::GetTexture("arrow"),
                               0,0);
    
    JumpButton = new Button(this,glm::vec2(this->Width-btn_size*4,this->Height-128*scal),
                            glm::vec2(btn_size*scal,btn_size*scal),
                            -90.0f*DEG2RAD,
                            ResourceManager::GetTexture("arrow"),
                            0,0);
    
    camera.target = {0,0};
    camera.offset = { width/2.0f, height/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void GameWolfenstein3D::OnEnter()
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
                                        static_cast<GLfloat>(this->Height),0.0f,
                                        -1.0f, 1.0f);
    
    Shader spriteShader = ResourceManager::GetShader("sprite");
    spriteShader.use();
    spriteShader.setMat4("projection", projection);
    
    Shader colorShader = ResourceManager::GetShader("color");
    colorShader.use();
    colorShader.setMat4("projection", projection);
    
    glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
    
    glm::mat4 projection3d = glm::perspective(glm::radians(cameraZOOM),
                                                 (float)this->Width / (float)this->Height, 0.1f, 100.0f);
    
    Shader simpleShader = ResourceManager::GetShader("simple");
    simpleShader.use();
    simpleShader.setMat4("view", view);
    simpleShader.setMat4("projection", projection3d);
    
    Level::GetInstance()->GenerateLevel("levelTest.png");
}

void GameWolfenstein3D::OnExit(){
    
}

void GameWolfenstein3D::KeyboardInput(ExKeyCode keycode, ExKeyAction action)
{
    deltaTime = Global::GetFrameTime();
    WolfPlayer *wolfPlayer = Level::GetInstance()->GetPlayer();
    //if(action == ExActionPressed)
    {
        switch (keycode) {
            case ExKeyEscape:
                Level::GetInstance()->OpenDoors(wolfPlayer->GetCamera()->Position);
                break;
            case ExKeyLeft:
                wolfPlayer->ProcessKeyboard(LEFT, deltaTime);
                break;
            case ExKeyRight:
                wolfPlayer->ProcessKeyboard(RIGHT, deltaTime);
                break;
            case ExKeyUp:
                wolfPlayer->ProcessKeyboard(FORWARD, deltaTime);
                break;
            case ExKeyDown:
                wolfPlayer->ProcessKeyboard(BACKWARD, deltaTime);
                break;
            default:
                break;
        }
    }
}

void GameWolfenstein3D::Update(GLfloat dt)
{
    Level::GetInstance()->Update();
}

void GameWolfenstein3D::Render()
{
    Shader colorShader = ResourceManager::GetShader("color");
    colorShader.use();
    colorShader.setMat4("view", GetCameraMatrix2D(camera));
    
    WolfPlayer *wolfPlayer = Level::GetInstance()->GetPlayer();
    //glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = wolfPlayer->GetCamera()->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(wolfPlayer->GetCamera()->Zoom), (float)this->Width / (float)this->Height, 0.1f, 100.0f);
    
    Shader depthShader = ResourceManager::GetShader("depth");
    depthShader.use();
    depthShader.setMat4("view", view);
    depthShader.setMat4("projection", projection);
    
    Level::GetInstance()->Render();
    
    GoButton_Left->Draw(*uiRenderer);
    GoButton_Right->Draw(*uiRenderer);
    JumpButton->Draw(*uiRenderer);
    
    std::stringstream ss; ss << this->fps;
    Text->RenderText("fps:"+ss.str(), 200.0f, 10.0f, 0.75f, glm::vec3(1.0f,1.0f,1.0f));
}

void GameWolfenstein3D::Release()
{
    
}
