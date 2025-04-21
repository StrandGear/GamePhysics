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
    glm::vec2 topLeftCorner;
    glm::vec2 bottomRightCorner;
    bool startMoving;
    float velocity = 9.81f;
    float distanceToLine;
    float projectedDistance;
    glm::vec2 normalVecOfLine;
    glm::vec2 angledLine;
    float lineLengthMultiplier;

    glm::vec2 GetNormalOnLine(glm::vec2 startPos, glm::vec2 endPos);
};
