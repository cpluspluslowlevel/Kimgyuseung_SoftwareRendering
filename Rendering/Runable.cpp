#include <vector>
#include <list>

#include "Mathematics.h"
#include "Exporter.h"
#include "Utility.h"

#include "Runable.h"

using std::list;
using std::vector;

using namespace Mathematics;
using namespace Utility;

Runable::Runable( Renderer* pRenderer, std::string sASEpath ) :
	m_pRenderer( pRenderer ),
	m_Camera_Model(),
	m_Camera_Projection(),
	m_vecASEvertexlist(),
	m_matASErotate()
{

	m_Camera_Model.CameraLocation( 0.0f, 0.0f, 200.0f );
	m_Camera_Model.LookLocation( 0.0f, 0.0f, 0.0f );
	m_Camera_Projection.SetFov( 45.0f );
	m_Camera_Projection.SetAspect( 512.0f / 512.0f );
	m_Camera_Projection.SetNear( 1.0f );
	m_Camera_Projection.SetFar( 100.0f );

	//ASE model loading
	PASE pASE;

	Exporter::Export_ASE( sASEpath, &pASE );

	//모델링 추출
	for( vector< ASE_Face >::iterator iter = pASE->GeomObject[ 0 ].Mesh.FaceList.begin();
		iter != pASE->GeomObject[ 0 ].Mesh.FaceList.end(); ++iter ){
			m_vecASEvertexlist.push_back(
				Vector3( 
					pASE->GeomObject[ 0 ].Mesh.VertexList[ ( *iter ).A ].X,
					pASE->GeomObject[ 0 ].Mesh.VertexList[ ( *iter ).A ].Y,
					pASE->GeomObject[ 0 ].Mesh.VertexList[ ( *iter ).A ].Z
				)
			);
			m_vecASEvertexlist.push_back(
				Vector3(
					pASE->GeomObject[ 0 ].Mesh.VertexList[ ( *iter ).C ].X,
					pASE->GeomObject[ 0 ].Mesh.VertexList[ ( *iter ).C ].Y,
					pASE->GeomObject[ 0 ].Mesh.VertexList[ ( *iter ).C ].Z
				)
			);
			m_vecASEvertexlist.push_back(
				Vector3(
					pASE->GeomObject[ 0 ].Mesh.VertexList[ ( *iter ).B ].X,
					pASE->GeomObject[ 0 ].Mesh.VertexList[ ( *iter ).B ].Y,
					pASE->GeomObject[ 0 ].Mesh.VertexList[ ( *iter ).B ].Z
				)
			);
	}

		//회전 추출
		Matrix4x4Identity( &m_matASErotate );
#define MATRIX( row, col ) m_matASErotate.m_fElementArray[ ( row * 4 ) + col ]
#define ASETM pASE->GeomObject[ 0 ].Node_TM
		MATRIX( 0, 0 ) = ASETM.Row0.X; MATRIX( 0, 1 ) = ASETM.Row1.X; MATRIX( 0, 2 ) = ASETM.Row2.X;
		MATRIX( 1, 0 ) = ASETM.Row0.Y; MATRIX( 1, 1 ) = ASETM.Row1.Y; MATRIX( 1, 2 ) = ASETM.Row2.Y;
		MATRIX( 2, 0 ) = ASETM.Row0.Z; MATRIX( 2, 1 ) = ASETM.Row1.Z; MATRIX( 2, 2 ) = ASETM.Row2.Z;
#undef MATRIX
#undef ASETM

		delete pASE;

}

Runable::~Runable(){
	delete m_pRenderer;
}

void Runable::operator()( float fAngle_xaxis, float fAngle_yaxis ){
	
	m_pRenderer->Clear();

	m_pRenderer->MatrixMode( MATRIX_MODELVIEW );
	m_pRenderer->LoadIdentity();
	m_pRenderer->MultMatrix( m_matASErotate );
	m_pRenderer->MultMatrix( Matrix4x4CreateRotate_X( fAngle_xaxis ) );
	m_pRenderer->MultMatrix( Matrix4x4CreateRotate_Y( fAngle_yaxis ) );
	m_pRenderer->MultMatrix( m_Camera_Model.GetCameraMatrix4x4() );
	m_pRenderer->MatrixMode( MATRIX_PROJECTION );
	m_pRenderer->LoadMatrix( m_Camera_Projection.GetProjectionMatrix4x4() );

	m_pRenderer->Begin();
	for( list< Vector3 >::iterator iter = m_vecASEvertexlist.begin(); iter != m_vecASEvertexlist.end(); ++iter ){
		m_pRenderer->Vertex3f( *iter );
	}
	m_pRenderer->End();

	m_pRenderer->SwapBuffer();

}