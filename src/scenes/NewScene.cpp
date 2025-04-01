#include "NewScene.h"

#include "core/Draw.h"
#include "imgui.h"

NewScene::NewScene() : circlePosition(0, 1), circleRadius(1) {}

NewScene::~NewScene() {}

void NewScene::OnEnable() {}

void NewScene::OnDisable() {}

void NewScene::Update(float deltaTime) {}

void NewScene::Draw() {

}

void NewScene::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::Button("Drop");
    ImGui::End();
}
