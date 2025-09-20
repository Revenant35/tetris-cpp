#include "Application.h"
#include "AppLayer.h"
#include "MenuLayer.h"

int main() {
    Core::ApplicationSpecification appspec;
    appspec.Name = "Tetris";
    appspec.WindowSpec.Width = 800;
    appspec.WindowSpec.Height = 600;

    Game game;

    Core::Application application(appspec);
    application.PushLayer<AppLayer>();
    application.PushLayer<MenuLayer>();
    application.Run();
}
