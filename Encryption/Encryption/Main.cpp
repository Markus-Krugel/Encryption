#include "Application.h"

int main()
{
	// hides console in release version
	#if !_DEBUG
		HWND hwnd = GetConsoleWindow();
		ShowWindow(hwnd, 0);
	#endif 

	Application* app = new Application();

	app->Run();

	delete app;
}