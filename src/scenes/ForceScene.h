#pragma once
#include <iostream>
#include "core/Simple2DScene.h"

class ForceScene : public Simple2DScene {
public:
    ForceScene();
    ~ForceScene(); //destructor called when object get deleted

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "ApplyForce"; };

    private:
    glm::vec2 circleInitPosition;
    glm::vec2 circleCurrPosition = circleInitPosition;
    glm::float32 circleRadius;
    glm::float32 circleMass;
    glm::float32 xScreenPos;
    glm::float32 yScreenPos;
    const double gravity = 9.81;
    glm::vec2 totalForce;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    glm::float32 windPower;
    glm::float32 restitution;
    
    enum class ForceType {
        Gravity,
        WindToTheLeft,
        WindToTheRight,
        SteamFromTheGround
    };

    void ApplyForce(ForceType);
};
