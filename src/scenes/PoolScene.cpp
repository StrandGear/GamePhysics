#include "PoolScene.h"
#include "core/Draw.h"
#include "imgui.h"

PoolScene::PoolScene(): 
      ball_1_Position(0.0f, 0.0f),
      ball_2_Position(2.0f, 2.0f),
      ballsMass(2.0f),
      ball_1_Velocity(0.0f),
      ball_2_Velocity(0.0f),
      ballsRadius(1.0f),
      isMoving(false),
      hasClicked(false),
      isDragging(false)
    {}

void PoolScene::OnEnable() {}

void PoolScene::OnDisable() {}

void PoolScene::Update(float deltaTime) {

    float friction = 0.99f; // коэффициент трения

    ball_1_Velocity *= friction;
    ball_2_Velocity *= friction;

    //tracking cursor position
    if (isDragging) {
        mouseCurrentPos = Input::GetMousePos();
    } else {
        ball_1_Position += ball_1_Velocity * deltaTime;
        ball_2_Position += ball_2_Velocity * deltaTime;
        //reduce velocity
    }

    if (glm::length(ball_1_Velocity) > 0.0f) { // TODO: check every ball if isMoving
        
        isMoving = true;

        float distance = glm::length(ball_2_Position - ball_1_Position);
        float minDistance = ballsRadius + ballsRadius;

        if (distance < minDistance) // collding  TODO:cycle it through all elems
        {
            //normal of the collision (to know the direction of further movement)
            glm::vec2 collisionNormal =
                glm::normalize(ball_2_Position - ball_1_Position);

            // avoiding overlapping 
            float penetration = minDistance - distance; 
            glm::vec2 correction = collisionNormal * (penetration / 2.0f); 
            ball_1_Position -= correction;
            ball_2_Position += correction;

            //projecting velocities onto normal
            float velocityAlongNormal1 =
                glm::dot(ball_1_Velocity, collisionNormal);
            float velocityAlongNormal2 =
                glm::dot(ball_2_Velocity, collisionNormal);

            glm::vec2 relativeVelocity = ball_1_Velocity - ball_2_Velocity;

            float velocityAlongNormal =
                glm::dot(relativeVelocity, collisionNormal);


            //so that they arent weirdly launched away from each other  
            if (velocityAlongNormal > 0.0f &&
                ball_2_Velocity != glm::vec2(0.0f))
                return;

            float restitution = 1.0f; //perfectly elastic body
            float impulseMagnitude = -(1.0f + restitution) *
                                     velocityAlongNormal /
                                     (1.0f / ballsMass + 1.0f / ballsMass);

            glm::vec2 impulse = impulseMagnitude * collisionNormal;

            ball_1_Velocity -= impulse / ballsMass;
            ball_2_Velocity += impulse / ballsMass;

        }
    }
}

void PoolScene::Draw() {

    //drawing a ball 1
    Draw::Circle(ball_1_Position, ballsRadius);

   // drawing a ball 2 
    Draw::Circle(ball_2_Position, ballsRadius);

    //drawing trajectory
    if (isDragging) {

        glm::vec2 impulse = (mouseCurrentPos - mouseClickPos) * 3.0f; //impulse force = 3.0f
        glm::vec2 predictedVelocity = ball_1_Velocity + impulse / ballsMass;
        glm::vec2 predictedPosition = ball_1_Position;

        float timeStep = 0.1f;
        int numSteps = 20;

        for (size_t i = 0; i < numSteps; i++) {
            predictedPosition += predictedVelocity * timeStep;

            Draw::SetColor(ImColor::HSV(0.0f, 0.0f, 0.5f));
            Draw::Circle(predictedPosition, ballsRadius * 0.2f);
        }
    }
}

void PoolScene::DrawGUI() {
    ImGui::Begin("Inspector");

    if (ImGui::Button("Reset") == true) {
        ball_1_Position = glm::vec2(0.0f);
        ball_2_Position = glm::vec2(2.0f, 2.0f);
        ball_1_Velocity = glm::vec2(0.0f);
        ball_2_Velocity = glm::vec2(0.0f);
        isDragging = false;
    }

    //if mouse is pressed
    if (Input::IsMouseClicked(ImGuiMouseButton_Left)) {

        float distance = glm::length(Input::GetMousePos() - ball_1_Position);

        if (distance <= ballsRadius) {
            mouseClickPos = Input::GetMousePos();
            isDragging = true;
        }
    }

    if (Input::IsMouseReleased(ImGuiMouseButton_Left) && isDragging) {
        float impulseForce = 3.0f;
        glm::vec2 impulse = (mouseCurrentPos - mouseClickPos) * impulseForce;
        ApplyImpulse(impulse);
        isDragging = false;
    }


    ImGui::End();
}

void PoolScene::ApplyImpulse(glm::vec2 impulse) {
    ball_1_Velocity += impulse / ballsMass;
}