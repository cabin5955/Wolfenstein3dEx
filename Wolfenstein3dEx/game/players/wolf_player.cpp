//
//  wolf_player.cpp
//  SuperMarioEx
//
//  Created by chen caibin on 2022/7/19.
//

#include "wolf_player.hpp"
#include "global.hpp"
#include "level.hpp"

WolfPlayer::WolfPlayer(Shader &shader,glm::vec3 position):shader(shader){
    camera = new Camera(position, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f});
    movement = {0.0f,0.0f,0.0f};
    
    BasicVertex vertices[4];
    int indices[6];
    float xHig = 1.0f;
    float xLow = 0.0f;
    float yHig = 1.0f;
    float yLow = 0.01f;
    
    vertices[0] = {{SIZEX,SIZEY,START}, { xHig, yLow}};
    vertices[1] = {{-SIZEX,SIZEY,START},{ xLow, yLow}};
    vertices[2] = {{-SIZEX,START,START},{ xLow, yHig}};
    vertices[3] = {{SIZEX,START,START}, { xHig, yHig}};
    
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
    
    mesh = new BasicMesh(shader,vertices,4,indices,6,false);
    
    TouchDispatcher *dispatcher = TouchDispatcher::get_instance();
    dispatcher->addTargetedDelegate(Director::GetInstance()->GetTopScene()->GetSceneID(), this, 0);
    
//    float width = Global::ScreenWidth;
//    float height = Global::ScreenHeight;
//    char des[1024];
//    Shader textShader = ResourceManager::GetShader("text");
//    Text = new TextRenderer(textShader, width, height);
//    Text->Load(Global::ResFullPath(des,"default.ttf"),48);
}

bool WolfPlayer::TouchBegan(double x, double y)
{
    firstMouse = true;
    return true;
}

void WolfPlayer::TouchMoved(double xpos, double ypos){
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

void WolfPlayer::TouchEnded(double x, double y){
    
}

void WolfPlayer::TouchCancelled(double x, double y){
    
}

void WolfPlayer::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    movement = {0,0,0};
    if (direction == FORWARD)
        movement += camera->Front;
    if (direction == BACKWARD)
        movement -= camera->Front;
    if (direction == LEFT)
        movement -= camera->Right;
    if (direction == RIGHT)
        movement += camera->Right;
}

Camera* WolfPlayer::GetCamera(){
    return camera;
}

void WolfPlayer::Update()
{
    float movAmt = camera->MovementSpeed * Global::GetFrameTime();
    movement.y = 0.0f;
    if(glm::length(movement) > 0){
        movement = glm::normalize(movement);
    }
    
    glm::vec3 oldPos = camera->Position;
    glm::vec3 newPos = oldPos + movement * movAmt;
    
    float PLAYER_SIZE = 0.2f;
    glm::vec3 collision = Level::GetInstance()->CheckCollision(oldPos, newPos, PLAYER_SIZE, PLAYER_SIZE);
    movement *= collision;
    
    if(glm::length(movement) > 0){
        camera->Position += movement * movAmt;
    }
    movement = {0,0,0};
    
    //Gun movement
    gunPosition = camera->Position + (glm::normalize(camera->Front) * 0.105f);
    gunPosition.y += GUN_OFFSET;

    glm::vec3 directionToCamera = camera->Position - gunPosition;
    float angleToFaceTheCamera = (float)glm::degrees(glm::atan(directionToCamera.z / directionToCamera.x));

    if(directionToCamera.x < 0)
        angleToFaceTheCamera += 180;

    gunRotation = angleToFaceTheCamera + 90;
    gunRotation = 180 - gunRotation;
}

void WolfPlayer::Render()
{
    float width = Global::ScreenWidth;
    float height = Global::ScreenHeight;
    
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), width / height, 0.1f, 100.0f);
    
    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    
    Texture2D texture = ResourceManager::GetTexture("gun");
    mesh->Draw(texture,gunPosition,{1.0f,1.0f,1.0f},glm::radians(gunRotation),{0.0f,1.0f,0.0f});
    
    //std::stringstream ss; ss << gunRotation;
    //Text->RenderText("rotation:"+ss.str(), 200.0f, 30.0f, 0.75f, glm::vec3(1.0f,1.0f,1.0f));
}
