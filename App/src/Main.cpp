#include "Application.h"
#include "AppLayer.h"

int main() {
    Core::ApplicationSpecification appspec;
    appspec.Name = "Tetris";
    appspec.WindowSpec.Width = 800;
    appspec.WindowSpec.Height = 600;

    Core::Application application(appspec);
    application.PushLayer<AppLayer>();
    application.Run();
}