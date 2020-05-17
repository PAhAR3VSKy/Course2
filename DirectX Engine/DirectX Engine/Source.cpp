#include "RenderWindow.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"DirectXTK.lib")
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
_In_opt_ HINSTANCE hPrevInstance,
_In_ LPWSTR lpCmdLine , 
_In_ int nCmdShow )
{
	RenderWindow rend;
	rend.Initialize(hInstance, "Title", "MyWindowClass", 800, 600);
	while(rend.ProccessMessages() == true)
	{

	}
	return 0;
}