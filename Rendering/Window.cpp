#include <Windows.h>

#include "Mathematics.h"

#include "Window.h"
#include "Runable.h"

using namespace Mathematics;

Window::Window( HINSTANCE hInstance ) :
	m_hInstance( hInstance ),
	m_hWindow( NULL ),
	m_fRotate_xaxis( 0.0f ),
	m_fRotate_yaxis( 0.0f ),
	m_fRotate_xaxis_increment( 0.0f ),
	m_fRotate_yaxis_increment( 0.0f ),
	m_vecClickpoint()
{
}

Window::~Window(){
	UnregisterClass( WINDOW_CLASSNAME, m_hInstance );
}

BOOL Window::Initialize(){

	//메인 윈도우
	WNDCLASSEX WindowClass;
	WindowClass.cbSize            = sizeof( WindowClass );
	WindowClass.cbClsExtra        = NULL;
	WindowClass.cbWndExtra        = 4;
	WindowClass.hbrBackground     = static_cast< HBRUSH >( GetStockObject( WHITE_BRUSH ) );
	WindowClass.hCursor           = LoadCursor( NULL, IDC_ARROW );
	WindowClass.hIcon             = LoadIcon( NULL, IDI_APPLICATION );
	WindowClass.hIconSm           = LoadIcon( NULL, IDI_APPLICATION );
	WindowClass.lpfnWndProc       = static_cast< WNDPROC >( MessageHandlerCaller );
	WindowClass.lpszClassName     = WINDOW_CLASSNAME;
	WindowClass.lpszMenuName      = NULL;
	WindowClass.hInstance         = m_hInstance;
	WindowClass.style             = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx( &WindowClass );

	RECT rtWindow = { 0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT };
	AdjustWindowRect( &rtWindow, WS_OVERLAPPEDWINDOW, TRUE );
	m_hWindow = CreateWindowEx( NULL, WINDOW_CLASSNAME, WINDOW_CAPTION,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rtWindow.right, rtWindow.bottom,
		NULL, NULL, m_hInstance, NULL );
	SetWindowLong( m_hWindow, GWL_USERDATA, reinterpret_cast< LONG >( this ) );

	ShowWindow( m_hWindow, SW_SHOWDEFAULT );
	UpdateWindow( m_hWindow );
	
	return reinterpret_cast< BOOL >( m_hWindow );

}

VOID Window::Run( Runable* pRun ){
	MSG Message;
	ZeroMemory( &Message, sizeof( Message ) );
	while( Message.message != WM_QUIT ){
		if( PeekMessage( &Message, NULL, NULL, NULL, PM_REMOVE ) ){
			TranslateMessage( &Message );
			DispatchMessage( &Message );
		}else{
			( *pRun )( m_fRotate_xaxis + m_fRotate_xaxis_increment, m_fRotate_yaxis + m_fRotate_yaxis_increment );
		}
	}
}

//메인 윈도우 메시지 핸들러
LRESULT Window::MessageHandler( HWND hWindow, UINT iMessage, WPARAM wParameter, LPARAM lParameter ){

	switch( iMessage ){
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	case WM_LBUTTONDOWN:
		m_vecClickpoint.m_fX = static_cast< float >( LOWORD( lParameter ) );
		m_vecClickpoint.m_fY = static_cast< float >( HIWORD( lParameter ) );
		SetCapture( hWindow );
		return 0;
	case WM_MOUSEMOVE:
		if( wParameter & MK_LBUTTON ){
			Vector3 vecMousepoint;
			vecMousepoint.m_fX = static_cast< float >( static_cast< short >( LOWORD( lParameter ) ) );
			vecMousepoint.m_fY = static_cast< float >( static_cast< short >( HIWORD( lParameter ) ) );
			m_fRotate_yaxis_increment = 360.0f * ( ( -1 * ( vecMousepoint.m_fX - m_vecClickpoint.m_fX ) ) * 0.002f );
			m_fRotate_xaxis_increment = 360.0f * ( ( vecMousepoint.m_fY - m_vecClickpoint.m_fY ) * 0.002f );
		}
		return 0;
	case WM_LBUTTONUP:
		m_fRotate_xaxis += m_fRotate_xaxis_increment;
		m_fRotate_yaxis += m_fRotate_yaxis_increment;
		m_fRotate_xaxis_increment = 0.0f;
		m_fRotate_yaxis_increment = 0.0f;
		ReleaseCapture();
		return 0;
	}

	return DefWindowProc( hWindow, iMessage, wParameter, lParameter );

}

LRESULT CALLBACK MessageHandlerCaller( HWND hWindow, UINT iMessage, WPARAM wParameter, LPARAM lParameter ){

	Window* pWindow = reinterpret_cast< Window* >( GetWindowLong( hWindow, GWL_USERDATA ) );

	if( pWindow ) return pWindow->MessageHandler( hWindow, iMessage, wParameter, lParameter );
	else return DefWindowProc( hWindow, iMessage, wParameter, lParameter );

}

HWND Window::GetWindowHandle() const {
	return m_hWindow;
}