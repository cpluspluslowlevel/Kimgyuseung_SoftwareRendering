#include <list>
#include <vector>

#include <Windows.h>

#include "Mathematics.h"
#include "Utility.h"
#include "Exporter.h"

#include "Window.h"
#include "Renderer.h"
#include "Runable.h"

using std::list;
using std::vector;

using namespace Utility;
using namespace Mathematics;

INT APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCommandstring, INT iShowstate ){

	Window* pWindow = new Window( hInstance );
	

	if( pWindow->Initialize() ){
		
		Runable* pRunable = new Runable( new Renderer( pWindow->GetWindowHandle() ), "Torus.ase" );
		pWindow->Run( pRunable );

	}else{
		MessageBox( NULL, TEXT( "Initialize fail" ), TEXT( "Error" ), MB_OK );
	}

	delete pWindow;

	return 0;

}