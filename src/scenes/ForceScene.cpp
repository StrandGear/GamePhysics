#include "ForceScene.h"
#include "core/Draw.h"
#include "imgui.h"

ForceScene::ForceScene()
    : circleInitPosition(0, 0),
      circleRadius(1.0f),
      circleMass(2.0f),
      xScreenPos(8),
      yScreenPos(5),
      totalForce(0.0f),
      windPower(5.0f),
      acceleration(0.0f),
      velocity(0.0f),
      restitution(0.8f) {}

ForceScene::~ForceScene() {}

void ForceScene::OnEnable() {}

void ForceScene::OnDisable() {}

void ForceScene::Update(float deltaTime) {

    //a = F / m
    acceleration = totalForce / static_cast<float>(circleMass);

    // semi implicit euler
    velocity += acceleration * deltaTime;

    circleCurrPosition += velocity * deltaTime;

   // bouncing from the walls
    if (circleCurrPosition.y - circleRadius <= -yScreenPos ||
        circleCurrPosition.y + circleRadius >= yScreenPos) {
        //velocity.y *= -1.0f;
        velocity.y *= -restitution; // assume we are loosing 20% of the velocity
    }
    if (circleCurrPosition.x - circleRadius <= -xScreenPos ||
        circleCurrPosition.x + circleRadius >= xScreenPos) {
        velocity.x *= -restitution;
    }
   
}

void ForceScene::Draw() {

    Draw::Circle(circleCurrPosition, circleRadius);
    
    //top border
    Draw::Line(glm::vec2(-xScreenPos, yScreenPos),
               glm::vec2(xScreenPos, yScreenPos));
    //bottom border
    Draw::Line(glm::vec2(-xScreenPos, -yScreenPos),
               glm::vec2(xScreenPos, -yScreenPos));
    //left border
    Draw::Line(glm::vec2(-xScreenPos, yScreenPos),
               glm::vec2(-xScreenPos, -yScreenPos));
    //right border
    Draw::Line(glm::vec2(xScreenPos, yScreenPos),
               glm::vec2(xScreenPos, -yScreenPos));
}

void ForceScene::ApplyForce(ForceType forceType) {
    glm::vec2 force(0.0f);

    switch (forceType) {
        case ForceType::Gravity:
            // F = m * g
            force = glm::vec2(0.0f, -circleMass * gravity); 
            break;
        case ForceType::WindToTheLeft:
            force = glm::vec2(circleMass * -windPower, 0.0f);
            break;
        case ForceType::WindToTheRight:
            force = glm::vec2(circleMass * windPower, 0.0f);
            break;
        case ForceType::SteamFromTheGround:
            force = glm::vec2(0.0f, circleMass * windPower);
    }

    totalForce += force;
}

void ForceScene::DrawGUI() {
    ImGui::Begin("Inspector");

    if (ImGui::Button("Gravity") == true) {
        //std::cout << "Apply gravity force." << std::endl;
        ApplyForce(ForceType::Gravity);
    }
    if (ImGui::Button("WindToTheLeft") == true) {
        //std::cout << "Apply WindToTheLeft force." << std::endl;
        ApplyForce(ForceType::WindToTheLeft);
    }
    if (ImGui::Button("WindToTheRight") == true) {
        //std::cout << "Apply WindToTheRight force." << std::endl;
        ApplyForce(ForceType::WindToTheRight);
    }
    if (ImGui::Button("SteamFromTheGround") == true) {
        //std::cout << "Apply SteamFromTheGround force." << std::endl;
        ApplyForce(ForceType::SteamFromTheGround);
    }
    if (ImGui::Button("Reset") == true) {
        totalForce = glm::vec2(0.0f);
        acceleration = glm::vec2(0.0f);
        velocity = glm::vec2(0.0f);
        circleCurrPosition = circleInitPosition;
    }

    ImGui::SliderFloat("Restitution", &restitution, 0.0f, 1.0f);
    ImGui::SliderFloat("Mass", &circleMass, 0.1f, 5.0f);

    ImGui::End();
}
