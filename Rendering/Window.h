#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <Windows.h>

#include "Mathematics.h"

#include "Runable.h"

#define WINDOW_SIZE_WIDTH  512
#define WINDOW_SIZE_HEIGHT 512
#define WINDOW_CAPTION     TEXT( "3D Rendering pipeline" )
#define WINDOW_CLASSNAME   TEXT( "Main window" )

class Window{
private:

	//윈도우 관련 변수
	HINSTANCE m_hInstance;
	HWND      m_hWindow;

	//마우스 회전
	FLOAT                m_fRotate_xaxis;
	FLOAT                m_fRotate_yaxis;
	FLOAT                m_fRotate_xaxis_increment;
	FLOAT                m_fRotate_yaxis_increment;
	Mathematics::Vector3 m_vecClickpoint;

public:
	Window( HINSTANCE hInstance );
	~Window();

	BOOL Initialize();
	VOID Run( Runable* pRun );

	LRESULT MessageHandler( HWND hWindow, UINT iMessage, WPARAM wParameter, LPARAM lParameter );

	HWND GetWindowHandle()const;

};

LRESULT CALLBACK MessageHandlerCaller( HWND hWindow, UINT iMessage, WPARAM wParameter, LPARAM lParameter );

#endif