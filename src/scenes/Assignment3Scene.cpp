#include "Assignment3Scene.h"

#include "imgui.h"

//#include @Color include header or bamnespace

void Assignment3Scene::OnEnable() {}

void Assignment3Scene::OnDisable() {}

void Assignment3Scene::Update(float deltaTime) {}

void Assignment3Scene::Draw() {
    //Draw::Circle(circlePosition, circleRadius);
    //Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));

    //if (Input::IsMouseClicked(0)) {
    //    mouseDownPos = Input::GetMousePos() - mouseposdownPos;

    //}
    //if (Input::IsMouseDown(0)) {
    //    glm::vec2 impulse = Input::GetMousePos() - mouseDownPos;
    //    Draw::SetColor(Colors::orange);
    //    Draw::Arrow(position, position + impulse);

    //    Draw::SetColor(Colors::gray);
    //    for (float i = 0; i < trajectoryTime; i += trajectoryStepSize) {

    //    }
    //}
    //if (Input::IsMouseReleased(0)) {
    //    glm::vec2 impulse = Input::GetMousePos() - mouseDownPos;
    //    AddImpulse(impulse);
    //    isSimulating = true;
    //}
}

void Assignment3Scene::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}
