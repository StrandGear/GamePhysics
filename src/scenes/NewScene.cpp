#include "NewScene.h"
#include <iostream>
#include "core/Draw.h"
#include "imgui.h"

NewScene::NewScene()
    : circlePosition(0, 5),
      circleRadius(1),
      linePositionY(0),
      startMoving(false) {}

NewScene::~NewScene() {}

void NewScene::OnEnable() {
    bool buttonPressed = false;
}

void NewScene::OnDisable() {}

void NewScene::Update(float deltaTime) {
   
    glm::float32 distance = circlePosition.y - linePositionY;

    if (startMoving == true) {
    
        circlePosition.y = circlePosition.y - velocity*deltaTime;

        if (distance <= circleRadius) {     
            velocity = -9.81;
        }
        if (circlePosition.y >= 5) {
            velocity = 9.81;
        }
    }
}

void NewScene::Draw() {
    Draw::Circle(circlePosition, circleRadius);
    Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));

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
