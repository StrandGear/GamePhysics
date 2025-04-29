#pragma once
#include <iostream>
#include "core/Simple2DScene.h"

struct Ball {
    glm::vec2 position;
    glm::vec2 velocity;
    float radius;
    float mass;
};

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

    static const int BALL_COUNT = 5;
    Ball ballsArray[BALL_COUNT];

    bool isMoving;

    glm::vec2 mouseClickPos;
    glm::vec2 mouseCurrentPos;
    bool hasClicked;
    bool isDragging;

    float damping;

    void ApplyImpulse(glm::vec2 impulse);

    glm::vec2 TestCollision(Ball, Ball);
};
