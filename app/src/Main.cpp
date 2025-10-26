#include <iostream>

#include "Core.h"
#include "AppLayer.h"
#include "ImGuiLayer.h"

int main()
{
  Core::ApplicationSpecification appSpec;
  appSpec.name = "Colorista";
  appSpec.windowSpec.width = 1920;
  appSpec.windowSpec.height = 1080;

  Core::Application app(appSpec);
  app.pushLayer<AppLayer>();
  //app.pushLayer<ImGuiLayer>();
  app.start();
}
