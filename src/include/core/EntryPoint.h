#include "EditorApp.h"

int main()
{
	Application* App = CreateEditorApplication();
	App->run();
	delete App;
}
   