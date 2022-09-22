#include "Controller.hpp"

Controller controller(std::vector<std::string>({"/home/neniu/Projects/grantig/orgel1.wav", "/home/neniu/Projects/grantig/orgel2.wav", "/home/neniu/Projects/grantig/bruckner.wav"}));

int main(int argc, char *argv[]) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "remote arena");

    SetTargetFPS(FPS);

    controller.init();

    // SetTextureFilter(mapTexture.texture, FILTER_POINT); // TODO
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        controller.update(delta);
        controller.draw(delta);
    }

    CloseWindow();

    return 0;
}