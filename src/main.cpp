#include "core/Application.h"
#include "scenes/TestScene.h"
#include "scenes/NewScene.h"

int main(int argc, char** argv) {
    // Add newly created scenes here so that they show up in the menu.
    std::vector<Scene*> scenes = { 
        new TestScene(), new NewScene()
    };
    Application app(scenes);
    return app.Run();
}
