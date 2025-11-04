#include "Core.h"
#include "DemoLayer.h"
#include "ImGuiLayer.h"
#include "AppLayer.h"

int main()
{
  Core::ApplicationSpecification appSpec;
  appSpec.name = "Colorista";
  appSpec.windowSpec.width = 1000;
  appSpec.windowSpec.height = 1000;

  EditorState editorState;
  
  Core::Application app(appSpec);
  app.pushOverlay<ImGuiLayer>(editorState);
  app.pushLayer<AppLayer>(editorState);
  app.start();
}
