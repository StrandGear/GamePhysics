#include "core/Application.h"
#include "scenes/TestScene.h"
#include "scenes/NewScene.h"
#include "scenes/ForceScene.h"
#include "scenes/PoolScene.h"

int main(int argc, char** argv) {
    // Add newly created scenes here so that they show up in the menu.
    std::vector<Scene*> scenes = { 
        new TestScene(),
        new ForceScene(), 
        new NewScene(), 
        new PoolScene()
    };
    Application app(scenes);
    return app.Run();
}
