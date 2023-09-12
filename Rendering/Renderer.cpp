#include <vector>

#include <Windows.h>

#include "Renderer.h"

using std::vector;

using namespace Mathematics;

//생성자
//맴버변수 초기화
//브러쉬, 펜 등 사용할 자원 생성
Renderer::Renderer( HWND hWindow ) :
	m_hWindow( hWindow ),
	m_hBrush_background( NULL ),
	m_hBitmap_backbuffer( NULL ),
	m_iWidth( 0 ),
	m_iHeight( 0 ),
	m_vecVertexvector(),
	m_Matrix_modelview(),
	m_Matrix_projection(),
	m_pCurrentmatrix( NULL )
{

	RECT rtWorkarea;
	GetClientRect( hWindow, &rtWorkarea );
	m_iWidth             = rtWorkarea.right;
	m_iHeight            = rtWorkarea.bottom;
	m_hBrush_background  = CreateSolidBrush( RGB( 0, 0, 0 ) );
	m_hBitmap_backbuffer = CreateCompatibleBitmap( GetDC( hWindow ), m_iWidth, m_iHeight );
	
	MatrixMode( MATRIX_MODELVIEW );
	LoadIdentity();
	MatrixMode( MATRIX_PROJECTION );
	LoadIdentity();

}

//소멸자
//자원해제
Renderer::~Renderer(){
	HDC hDC = GetDC( m_hWindow );
	DeleteObject( SelectObject( hDC, m_hBrush_background ) );
	DeleteObject( m_hBitmap_backbuffer );
	ReleaseDC( m_hWindow, hDC );
}

//Set attribute--------------------------

//Vertex
VOID Renderer::Vertex3f( const Vector4& refVertex ){
	m_vecVertexvector.push_back( refVertex );
}

//Vertex
VOID Renderer::Vertex3f( float fX, float fY, float fZ ){
	m_vecVertexvector.push_back( Vector3( fX, fY, fZ ) );
}

//-------------------------- /* Set attribute */

//Matrix----------------------

//설정할 행렬 선택
VOID Renderer::MatrixMode( DWORD dwMatrixmode ){
	if( dwMatrixmode == MATRIX_MODELVIEW ) m_pCurrentmatrix = &m_Matrix_modelview;
	else if( dwMatrixmode == MATRIX_PROJECTION ) m_pCurrentmatrix = &m_Matrix_projection;
}

//행렬 배정
VOID Renderer::LoadMatrix( const Matrix4x4& refMatrix ){
	*m_pCurrentmatrix = refMatrix;
}

//행렬 곱
VOID Renderer::MultMatrix( const Matrix4x4& refMatrix ){
	*m_pCurrentmatrix = refMatrix * ( *m_pCurrentmatrix );
}

//행렬 초기화
VOID Renderer::LoadIdentity(){
	Matrix4x4Identity( m_pCurrentmatrix );
}

//---------------------- /* Matrix */

VOID Renderer::Begin(){
	m_vecVertexvector.clear();
}

VOID Renderer::End(){

	HDC hDC            = GetDC( m_hWindow );
	HDC hMemorydc      = CreateCompatibleDC( hDC );
	HBITMAP hOldbitmap = static_cast< HBITMAP >( SelectObject( hMemorydc, m_hBitmap_backbuffer ) );

	Matrix4x4 Matrix_transform = m_Matrix_projection * m_Matrix_modelview;

#define VERTEX1 m_vecVertexvector[ ( i * 3 ) + 0 ]
#define VERTEX2 m_vecVertexvector[ ( i * 3 ) + 1 ]
#define VERTEX3 m_vecVertexvector[ ( i * 3 ) + 2 ]
	int iTrianglenumber = m_vecVertexvector.size() / 3;
	for( int i = 0; i < iTrianglenumber; i++ ){

		//행렬변환
		VERTEX1 = Matrix_transform * VERTEX1;
		VERTEX2 = Matrix_transform * VERTEX2;
		VERTEX3 = Matrix_transform * VERTEX3;

		//3차원으로 사상
		VERTEX1 = VERTEX1 / VERTEX1.m_fRHW;
		VERTEX2 = VERTEX2 / VERTEX2.m_fRHW;
		VERTEX3 = VERTEX3 / VERTEX3.m_fRHW;

		//뷰포트 변환
		VERTEX1.m_fX = ( VERTEX1.m_fX * ( m_iWidth * 0.5f ) ) + ( m_iWidth * 0.5f );
		VERTEX1.m_fY = ( ( VERTEX1.m_fY * -1 ) * ( m_iHeight * 0.5f ) ) + ( m_iHeight * 0.5f );
		VERTEX2.m_fX = ( VERTEX2.m_fX * ( m_iWidth * 0.5f ) ) + ( m_iWidth * 0.5f );
		VERTEX2.m_fY = ( ( VERTEX2.m_fY * -1 ) * ( m_iHeight * 0.5f ) ) + ( m_iHeight * 0.5f );
		VERTEX3.m_fX = ( VERTEX3.m_fX * ( m_iWidth * 0.5f ) ) + ( m_iWidth * 0.5f );
		VERTEX3.m_fY = ( ( VERTEX3.m_fY * -1 ) * ( m_iHeight * 0.5f ) ) + ( m_iHeight * 0.5f );

		DrawLine( hMemorydc, VERTEX1, VERTEX2 );
		DrawLine( hMemorydc, VERTEX2, VERTEX3 );
		DrawLine( hMemorydc, VERTEX3, VERTEX1 );

	}
#undef VERTEX1
#undef VERTEX2
#undef VERTEX3

	SelectObject( hMemorydc, hOldbitmap );
	DeleteDC( hMemorydc );
	ReleaseDC( m_hWindow, hDC );

}

VOID Renderer::Clear(){

	HDC hDC            = GetDC( m_hWindow );
	HDC hMemorydc      = CreateCompatibleDC( hDC );
	HBITMAP hOldbitmap = static_cast< HBITMAP >( SelectObject( hMemorydc, m_hBitmap_backbuffer ) );

	RECT rtFillarea = { 0, 0, (LONG)m_iWidth, (LONG)m_iHeight };
	FillRect( hMemorydc, &rtFillarea, m_hBrush_background );

	SelectObject( hMemorydc, hOldbitmap );
	DeleteDC( hMemorydc );
	ReleaseDC( m_hWindow, hDC );

}

VOID Renderer::SwapBuffer(){

	HDC hDC            = GetDC( m_hWindow );
	HDC hMemorydc      = CreateCompatibleDC( hDC );
	HBITMAP hOldbitmap = static_cast< HBITMAP >( SelectObject( hMemorydc, m_hBitmap_backbuffer ) );

	BitBlt( hDC, 0, 0, m_iWidth, m_iHeight, hMemorydc, 0, 0, SRCCOPY );

	SelectObject( hMemorydc, hOldbitmap );
	DeleteDC( hMemorydc );
	ReleaseDC( m_hWindow, hDC );
	
}

//선그리기
//vecStart: 시작점
//vecEnd: 끝점
VOID Renderer::DrawLine( HDC hDC, Vector3 vecStart, Vector3 vecEnd ){

	Vector3 vecDirection = vecEnd - vecStart;
	float   fLength      = Vector3Length( vecDirection );

	vecDirection = Vector3Normalize( vecDirection );

	Vector3 vecCurrentPoint;
	for( int i = 0; i < static_cast< int >( fLength ); i++ ){
		vecCurrentPoint = vecStart + ( vecDirection * static_cast< float >( i ) );
		SetPixel( hDC, static_cast< int >( vecCurrentPoint.m_fX ), static_cast< int >( vecCurrentPoint.m_fY ), RGB( 255, 255, 255 ) );
	}

}