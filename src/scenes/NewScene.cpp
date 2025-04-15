#include "NewScene.h"
#include <iostream>
#include "core/Draw.h"
#include "imgui.h"
#include "core/Colors.h"

NewScene::NewScene()
    : circlePosition(0, 5),
      circleRadius(1),
      bottomLinePositionY(0),
      topLinePositionY(5),
      startMoving(false) {}

NewScene::~NewScene() {}

void NewScene::OnEnable() {
    bool buttonPressed = false;

    // showing the normal of the line
    normalVecOfLine = GetNormalOnLine(glm::vec2(-5, 0), glm::vec2(5, 0));
}

void NewScene::OnDisable() {}

void NewScene::Update(float deltaTime) {
   
    glm::float32 distance = circlePosition.y - bottomLinePositionY;

    // normal from the circle to the line
    projectedDistance = glm::dot(circlePosition, normalVecOfLine);
    distanceToLine = projectedDistance - circleRadius;

    if (startMoving == true) {
    
        circlePosition.y = circlePosition.y - velocity*deltaTime;

        if (distance <= circleRadius) {     
            //velocity = -9.81;
        }
        if (circlePosition.y >= 5) {
            //velocity = 9.81;
        }

        if (distanceToLine <= 0) {
            velocity = -9.81;
        }
    }
}

glm::vec2 NewScene::GetNormalOnLine(glm::vec2 startPos, glm::vec2 endPos) {
    glm::vec2 vectorLength = endPos - startPos;
    float magnitude = glm::sqrt(vectorLength.x * vectorLength.x +
                                vectorLength.y * vectorLength.y);
    glm::vec2 normalizedPerpendicularVector = glm::vec2(vectorLength.x/magnitude, vectorLength.y/magnitude);
    glm::vec2 normalVecUpwords = glm::vec2(-normalizedPerpendicularVector.y,
                                           normalizedPerpendicularVector.x);

    return normalVecUpwords;
}

void NewScene::Draw() {
    Draw::Circle(circlePosition, circleRadius);
    Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));
   
    Draw::SetColor(Colors::green);
    Draw::Line(glm::vec2(0, 0), glm::vec2(0, normalVecOfLine.y));

    Draw::SetColor(Colors::cyan);
    Draw::Line(
        glm::vec2(circlePosition.x, circlePosition.y),
        glm::vec2(circlePosition.x, circlePosition.y - projectedDistance));
}

void NewScene::DrawGUI() {
    ImGui::Begin("Inspector");

    if (ImGui::Button("Drop") == true) {
        std::cout << "Pressed a btn" << std::endl;
        startMoving = true;
    }

     if (ImGui::Button("Stop") == true) {
        startMoving = false;
        circlePosition.y = 5;
        velocity = 9.81;
    }

    ImGui::End();
}