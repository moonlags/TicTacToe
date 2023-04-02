
#include <iostream>
#include "Window.h"

using namespace std;

int main()
{
	cout << "Creating window"<<endl;
	Window* pWindow = new Window();

	bool running = true;
	bool InMenu = true;
	while(running)
	{
		if(!pWindow->ProcessMessages())
		{
			cout << "Closing Window" << endl;
			running = false;
		}
		pWindow->Draw();
		Sleep(10);
	}
	delete pWindow;
	return 0;
}