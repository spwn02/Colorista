#include "Core.h"
#include "AppLayer.h"
#include "ImGuiLayer.h"

int main()
{
  Core::ApplicationSpecification appSpec;
  appSpec.name = "Colorista";
  appSpec.windowSpec.width = 1000;
  appSpec.windowSpec.height = 1000;

  Core::Application app(appSpec);
  app.pushLayer<AppLayer>();
  app.pushOverlay<ImGuiLayer>();
  app.start();
}
