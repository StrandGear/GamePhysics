#include "PoolScene.h"
#include "core/Draw.h"
#include "imgui.h"

PoolScene::PoolScene() :
      isMoving(false),
      hasClicked(false),
      isDragging(false),
      damping(2.0f)
    {}

void PoolScene::OnEnable() {
    for (size_t i = 0; i < BALL_COUNT; i++) {
        Ball ball;
        ball.mass = 2.0f;
        ball.position = glm::vec2(-5.0f + i * 2.5f, 2.0f);
        ball.velocity = glm::vec2(0.0);
        ball.radius = 1.0f;
        ballsArray[i] = ball;
    }

    ballsArray[0].position = glm::vec2(0.0f);
}

void PoolScene::OnDisable() {}

void PoolScene::Update(float deltaTime) {

    float dampingFactor = glm::clamp(1.0f - damping * deltaTime, 0.0f, 1.0f);


    //tracking cursor position
    if (isDragging) {
        mouseCurrentPos = Input::GetMousePos();
    } else {
        for (size_t i = 0; i < BALL_COUNT; i++) {
            ballsArray[i].position += ballsArray[i].velocity * deltaTime;
            ballsArray[i].velocity *= dampingFactor;
        }
    }

    for (size_t i = 0; i < BALL_COUNT; i++) {
        for (size_t j = i + 1; j < BALL_COUNT; j++) {
            glm::vec2 correction = TestCollision(ballsArray[i], ballsArray[j]);
            
            if (correction != glm::vec2(0.0f)) { //colliding

                ballsArray[i].position -= correction;
                ballsArray[j].position += correction;

                //normal of the collision for both balls to know into which direction to move
                glm::vec2 normal = glm::normalize(ballsArray[j].position -
                                                  ballsArray[i].position);
                //change velocit accordingly
                glm::vec2 relativeVelocity =
                    ballsArray[j].velocity - ballsArray[i].velocity;

                float velocityAlongNormal = glm::dot(relativeVelocity, normal);

                if (velocityAlongNormal > 0.0f)
                    return; 

                float restitution = 1.0f;
                float impulseMagnitude = -(1.0f + restitution) *
                                         velocityAlongNormal /
                    (1.0f / ballsArray[i].mass + 1.0f / ballsArray[j].mass);

                glm::vec2 impulse = impulseMagnitude * normal;

                ballsArray[i].velocity -= impulse / ballsArray[i].mass;
                ballsArray[j].velocity += impulse / ballsArray[j].mass;

            }
        }
    }

 
}

void PoolScene::Draw() {

    for (size_t i = 0; i < BALL_COUNT; i++) {
        Draw::Circle(ballsArray[i].position, ballsArray[i].radius);
    }

    //drawing trajectory
    if (isDragging) {

        glm::vec2 impulse = (mouseCurrentPos - mouseClickPos) * 3.0f; //impulse force = 3.0f
        glm::vec2 predictedVelocity =
            ballsArray[0].velocity + impulse / ballsArray[0].mass;
        glm::vec2 predictedPosition = ballsArray[0].position;

        float timeStep = 0.1f;
        int numSteps = 20;

        for (size_t i = 0; i < numSteps; i++) {
            predictedPosition += predictedVelocity * timeStep;

            Draw::SetColor(ImColor::HSV(0.0f, 0.0f, 0.5f));
            Draw::Circle(predictedPosition, ballsArray[0].radius * 0.2f);
        }
    }
}

void PoolScene::DrawGUI() {
    ImGui::Begin("Inspector");

    if (ImGui::Button("Reset") == true) {
        ballsArray[0].position = glm::vec2(0.0f);
        ballsArray[1].position = glm::vec2(2.0f, 2.0f);
        ballsArray[0].velocity = glm::vec2(0.0f);
        ballsArray[1].velocity = glm::vec2(0.0f);
        isDragging = false;
    }

    ImGui::SliderFloat("Damping", &damping, 0.0f, 10.0f);

    //if mouse is pressed
    if (Input::IsMouseClicked(ImGuiMouseButton_Left)) {

        float distance =
            glm::length(Input::GetMousePos() - ballsArray[0].position);

        if (distance <= ballsArray[0].radius) {
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
    ballsArray[0].velocity += impulse / ballsArray[0].mass;
}

glm::vec2 PoolScene::TestCollision(Ball ball1, Ball ball2) {
    float distance = glm::length(ball2.position - ball1.position);
    float minDistance = ball1.radius + ball2.radius;

    if (distance <= minDistance) {
        
        glm::vec2 collisionNormal =
            glm::normalize(ball2.position - ball1.position);

        // avoiding overlapping
        float penetration = minDistance - distance;
        glm::vec2 correction = collisionNormal * (penetration / 2.0f);

        return correction;

    } else {
        return glm::vec2(0, 0);
    }
}