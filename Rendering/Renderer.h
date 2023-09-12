#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <vector>

#include <Windows.h>

#include "Mathematics.h"

#define MATRIX_MODELVIEW  0
#define MATRIX_PROJECTION 1

class Renderer{
private:

	//Window
	HWND    m_hWindow;
	UINT    m_iWidth;
	UINT    m_iHeight;
	HBRUSH  m_hBrush_background;
	HBITMAP m_hBitmap_backbuffer;

	//Attribute
	std::vector< Mathematics::Vector4 > m_vecVertexvector;

	//Uniform
	Mathematics::Matrix4x4  m_Matrix_modelview;
	Mathematics::Matrix4x4  m_Matrix_projection;
	Mathematics::Matrix4x4* m_pCurrentmatrix;

	VOID DrawLine( HDC hDC, Mathematics::Vector3 vecStart, Mathematics::Vector3 vecEnd );

public:
	Renderer( HWND hWindow );
	~Renderer();
	
	//Set attribute
	VOID Vertex3f( const Mathematics::Vector4& refVertex );
	VOID Vertex3f( float fX, float fY, float fZ );

	//Matrix
	VOID MatrixMode( DWORD dwMatrixmode );
	VOID LoadMatrix( const Mathematics::Matrix4x4& refMatrix );
	VOID MultMatrix( const Mathematics::Matrix4x4& refMatrix );
	VOID LoadIdentity();

	VOID Begin();
	VOID End();

	VOID Clear();
	VOID SwapBuffer();

};

#endif