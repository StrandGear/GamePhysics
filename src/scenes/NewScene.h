#pragma once

#include "core/Simple2DScene.h"

class NewScene : public Simple2DScene {
public:
    NewScene();
    ~NewScene();

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "NewScene"; };

    private:
    glm::vec2 circlePosition;
    float circleRadius;
    glm::float32 bottomLinePositionY;
    glm::float32 topLinePositionY;
    bool startMoving;
    float velocity = 9.81f;
};
