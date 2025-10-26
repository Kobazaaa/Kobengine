#ifndef KOBENGINE_ENTRY_POINT_H
#define KOBENGINE_ENTRY_POINT_H

// -- Kobengine Includes --
#include "Application.h"

extern kobengine::Application* CreateApplication();

int main(int, char**)
{
	kobengine::Application* application = kobengine::CreateApplication();
	application->Run();
	delete application;
}

#endif // KOBENGINE_ENTRY_POINT_H