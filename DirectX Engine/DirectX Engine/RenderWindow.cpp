#include "RenderWindow.h"

bool RenderWindow::Initialize(HINSTANCE hInstance, string window_title, string window_class, int width, int height)
{
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(this->window_class);
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);

	this->RegisterWindowClass();

	this->handle = CreateWindowEx(0,//Extended windows style 
		this->window_class_wide.c_str(),//Window class name
		this->window_title_wide.c_str(),//Window title name
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //Windows style
		0,//Windows X position 
		0,//Windows Y position
		this->width,//Windows width
		this->height,//Windows height
		NULL,//Handle to parent of this window
		NULL,//Handle to menu or child window indentifier
		this->hInstance, //Handle to the instance of module used with this window
		nullptr);//Param to create window
	if (this->handle == NULL) 
	{
		ErrorLogger::Log(GetLastError(), "CreateWindowEX failed for window: " + this->window_title);
		return false;
	}
	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);
	return true;
}

bool RenderWindow::ProccessMessages()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));//Initialize message structure

	if (PeekMessage(&msg,//Where storage message
		this->handle,//Handel to window we are checking message for 
		0,//Minimum filter for Msg value
		0,//MAximum filter for Msg value
		PM_REMOVE))//Remove message aftre capturing
	{
		TranslateMessage(&msg);//Translate message from virtual key message into character message
		DispatchMessage(&msg);//Dispatch message to our Window proc for this window
	}

	//Check the window was closed
	if(msg.message == WM_NULL)
	{
		if (!IsWindow(this->handle)) 
		{
			this->handle = NULL;
			UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
			return false;
		}

	}
	return true;
}

RenderWindow::~RenderWindow()
{
	if (this->handle != NULL) 
	{
		UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
		DestroyWindow(handle);
	}
}

void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->window_class_wide.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&wc);
}
