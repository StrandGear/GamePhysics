#pragma once
#include <iostream>
#include "core/Simple2DScene.h"

class PoolScene : public Simple2DScene {
public:
    PoolScene();
    ~PoolScene();

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Pool"; };

private:
    glm::vec2 ball_1_Position; 
    glm::vec2 ball_2_Position; 
    float ballsMass;
    glm::vec2 ball_1_Velocity;
    glm::vec2 ball_2_Velocity;
    float ballsRadius;
    bool isMoving;

    glm::vec2 mouseClickPos;
    glm::vec2 mouseCurrentPos;
    bool hasClicked;
    bool isDragging;

    void ApplyImpulse(glm::vec2 impulse);
};
