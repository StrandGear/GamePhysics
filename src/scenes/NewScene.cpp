#include "NewScene.h"
#include <iostream>
#include "core/Draw.h"
#include "imgui.h"
#include "core/Colors.h"

NewScene::NewScene()
    : circlePosition(0, 5),
      circleRadius(1),
      topLeftCorner(-5,5),
      bottomRightCorner(5,-5),
      startMoving(false) {}

NewScene::~NewScene() {}

void NewScene::OnEnable() {
    bool buttonPressed = false;
    angledLine = glm::vec2(3, 1);
    lineLengthMultiplier = 10.0f;

    glm::vec2 startLine = -angledLine * lineLengthMultiplier;
    glm::vec2 endLine = angledLine * lineLengthMultiplier;

    normalVecOfLine = GetNormalOnLine(startLine, endLine);
}

void NewScene::OnDisable() {}

void NewScene::Update(float deltaTime) {
   
    if (startMoving == true) {
        
        //falling down
        circlePosition.y = circlePosition.y - velocity*deltaTime;

        // normal from the circle to the line
        projectedDistance = glm::dot(circlePosition, normalVecOfLine);

        if (projectedDistance < circleRadius) {      
            //how deep circle after line
            float intersectionDepth = circleRadius - projectedDistance;
            circlePosition += normalVecOfLine * intersectionDepth; //moving circle back to surface

            //reflecting velocity
            glm::vec2 velocityVec = glm::vec2(0, -velocity);
            glm::vec2 reflectedVec = velocityVec - 2.0f * glm::dot(velocityVec, normalVecOfLine) * normalVecOfLine;

            velocity = -reflectedVec.y;
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

    //Half space
    glm::vec2 origin = glm::vec2(0, 0);
    glm::vec2 direction = glm::normalize(angledLine);
    glm::vec2 p1 = origin - direction * lineLengthMultiplier;
    glm::vec2 p2 = origin + direction * lineLengthMultiplier;

    Draw::Line(p1, p2);
   
    //normal of the half space line
    Draw::SetColor(Colors::green);
    Draw::Line(origin, glm::vec2(0, normalVecOfLine.y));

    //distance from circle to line
    Draw::SetColor(Colors::cyan);
    Draw::Line(
        glm::vec2(circlePosition.x, circlePosition.y),
        glm::vec2(circlePosition.x, circlePosition.y - projectedDistance));
}

void NewScene::DrawGUI() {
    ImGui::Begin("Inspector");

    if (ImGui::Button("Drop") == true) {
        startMoving = true;
    }

     if (ImGui::Button("Stop") == true) {
        startMoving = false;
        circlePosition.y = 5;
        velocity = 9.81;
    }

    ImGui::End();
}