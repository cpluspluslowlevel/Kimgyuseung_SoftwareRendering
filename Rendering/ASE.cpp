#include <Windows.h>
#include <fstream>
#include <string>

#include "Utility.h"
#include "Exporter.h"
#include "ASE.h"

using namespace std;
using namespace Utility;

#define ASE_PARSING_BUFFERSIZE 256
EExportResult Exporter::Export_ASE( string filePath, PASE* ppOutASE ){

	ifstream InputStream;

	InputStream.open( filePath.c_str(), ios::in );
	if( !InputStream.is_open() ) return EExportResult::EXPORT_FILEOPENFAIL;

	( *ppOutASE ) =  new ASE;
	char sBuf[ ASE_PARSING_BUFFERSIZE ];
	string sLine;
	string sNodeName;
	string sValue;
	string sMesh_Parent;

	while( !InputStream.eof() ){

		InputStream.getline( sBuf, ASE_PARSING_BUFFERSIZE );
		sLine = trim( string( sBuf ) );

		if( sLine == "" || sLine == "}" ) continue;

		ASE_Parsing_Line( sLine, &sNodeName, &sValue );
		ASE_Parsing_Data( ( *ppOutASE ), sNodeName, sValue, sMesh_Parent );

	}

	InputStream.close();

	return EExportResult::EXPORT_SUCCES;

}

void Exporter::ASE_Parsing_Line( string sLine, string* pNodeName, string* pValue ){

	string& refNodeName = ( *pNodeName );
	string& refValue	= ( *pValue );

	refNodeName = sLine.substr( sLine.find_first_not_of( " \t\r\n" ) );
	refNodeName = refNodeName.substr( 0, refNodeName.find_first_of( " \t\r\n" ) );

	refValue = sLine.substr( sLine.find_first_not_of( " \t\r\n" ) );
	refValue = refValue.substr( refValue.find_first_of( " \t\r\n" ) );
	refValue = refValue.substr( refValue.find_first_not_of( " \t\r\n" ), refValue.find_last_not_of( " \t\r\n" ) - refValue.find_first_not_of( " \t\r\n" ) + 1 );

}

#define ISNAME( s ) if( sNodeName == s )
#define ELSE else
#define GEOMOBJECT ( pASE->GeomObject[ pASE->GeomObject.size() - 1 ] )
#define MESH ( GEOMOBJECT.Mesh )
#define ANIMATION ( GEOMOBJECT.Mesh_Animation )
#define CURRENTANIMATION ( ANIMATION[ ANIMATION.size() - 1 ] )
void Exporter::ASE_Parsing_Data( PASE pASE, string& sNodeName, string& sValue, string& sMesh_Parent ){

#if defined ENGIN_DEBUG
	printf( "[ ase line ] name: %s, value %s\n", sNodeName.c_str(), sValue.c_str() );
#endif
	ISNAME( "*SCENE_FILENAME" ){
		pASE->Scene.FileName = sValue;
	}
	ISNAME( "*SCENE_FIRSTFRAME" ){
		pASE->Scene.FirstFrame = atoi( sValue.c_str() );
	}
	ELSE
	ISNAME( "*SCENE_LASTFRAME" ){
		pASE->Scene.LastFrame = atoi( sValue.c_str() );
	}
	ELSE
	ISNAME( "*SCENE_FRAMESPEED" ){
		pASE->Scene.FrameSpeed = atoi( sValue.c_str() );
	}
	ELSE
	ISNAME( "*SCENE_TICKSPERFRAME" ){
		pASE->Scene.TicksperFrame = atoi( sValue.c_str() );
	}
	ELSE
	ISNAME( "*SCENE_BACKGROUND_STATIC" ){
		vector< string > sList = ASE_Parsing_ValueToList( sValue );
		pASE->Scene.Background_Static.X = ( float )atof( sList[ 0 ].c_str() );
		pASE->Scene.Background_Static.Y = ( float )atof( sList[ 1 ].c_str() );
		pASE->Scene.Background_Static.Z = ( float )atof( sList[ 2 ].c_str() );
	}
	ELSE
	ISNAME( "*SCENE_AMBIENT_STATIC" ){
		vector< string > sList = ASE_Parsing_ValueToList( sValue );
		pASE->Scene.Background_Static.X = ( float )atof( sList[ 0 ].c_str() );
		pASE->Scene.Background_Static.Y = ( float )atof( sList[ 1 ].c_str() );
		pASE->Scene.Background_Static.Z = ( float )atof( sList[ 2 ].c_str() );
	}
	ELSE
	ISNAME( "*GEOMOBJECT" ){
		pASE->GeomObject.push_back( ASE_GeomObject() );
		sMesh_Parent = "GEOMOBJECT";
	}
	ELSE
	ISNAME( "*NODE_NAME" ){
		GEOMOBJECT.Node_Name = sValue;
		GEOMOBJECT.Node_TM.Node_Name = sValue;
	}
	ELSE
	ISNAME( "*INHERIT_POS" ){
	}
	ELSE
	ISNAME( "*INHERIT_ROT" ){
	}
	ELSE
	ISNAME( "*INHERIT_SCL" ){
	}
	ELSE
	ISNAME( "*TM_ROW0" ){
		vector< string > sList = ASE_Parsing_ValueToList( sValue );
		GEOMOBJECT.Node_TM.Row0 = ASE_Vector3(
			( float )atof( sList[ 0 ].c_str() ),
			( float )atof( sList[ 1 ].c_str() ),
			( float )atof( sList[ 2 ].c_str() )
		);
	}
	ELSE
	ISNAME( "*TM_ROW1" ){
		vector< string > sList = ASE_Parsing_ValueToList( sValue );
		GEOMOBJECT.Node_TM.Row1 = ASE_Vector3(
			( float )atof( sList[ 0 ].c_str() ),
			( float )atof( sList[ 1 ].c_str() ),
			( float )atof( sList[ 2 ].c_str() )
		);
	}
	ELSE
	ISNAME( "*TM_ROW2" ){
		vector< string > sList = ASE_Parsing_ValueToList( sValue );
		GEOMOBJECT.Node_TM.Row2 = ASE_Vector3(
			( float )atof( sList[ 0 ].c_str() ),
			( float )atof( sList[ 1 ].c_str() ),
			( float )atof( sList[ 2 ].c_str() )
		);
	}
	ELSE
	ISNAME( "*TM_ROW3" ){
		vector< string > sList = ASE_Parsing_ValueToList( sValue );
		GEOMOBJECT.Node_TM.Row3 = ASE_Vector3(
			( float )atof( sList[ 0 ].c_str() ),
			( float )atof( sList[ 1 ].c_str() ),
			( float )atof( sList[ 2 ].c_str() )
		);
	}
	ELSE
	ISNAME( "*TM_ROTAXIS" ){
	}
	ELSE
	ISNAME( "*TM_ROTANGLE" ){
	}
	ELSE
	ISNAME( "*TM_SCALE" ){
	}
	ELSE
	ISNAME( "*TM_SCALEAXIS" ){
	}
	ELSE
	ISNAME( "*TM_SCALEAXISANG" ){
	}
	ELSE
	ISNAME( "*MESH" ){
		if( sMesh_Parent == "*MESH_ANIMATION" ) ANIMATION.push_back( ASE_Mesh() );
	}
	ELSE
	ISNAME( "*TIMEVALUE" ){
		if( sMesh_Parent == "*MESH_ANIMATION" ) CURRENTANIMATION.TimeValue = atoi( sValue.c_str() );
		else MESH.TimeValue = atoi( sValue.c_str() );
	}
	ELSE
	ISNAME( "*MESH_NUMVERTEX" ){
		if( sMesh_Parent == "*MESH_ANIMATION" ) CURRENTANIMATION.NumVertex = atoi( sValue.c_str() );
		else MESH.NumVertex = atoi( sValue.c_str() );
	}
	ELSE
	ISNAME( "*MESH_NUMFACES" ){
		if( sMesh_Parent == "*MESH_ANIMATION" ) CURRENTANIMATION.NumFaces = atoi( sValue.c_str() );
		else MESH.NumFaces = atoi( sValue.c_str() );
	}
	ELSE
	ISNAME( "*MESH_VERTEX_LIST" ){
	}
	ELSE
	ISNAME( "*MESH_VERTEX" ){
		vector< string > sList = ASE_Parsing_ValueToList( sValue );
		ASE_Vector3 Vector3 = ASE_Vector3(
			( float )atof( sList[ 1 ].c_str() ),
			( float )atof( sList[ 2 ].c_str() ),
			( float )atof( sList[ 3 ].c_str() )
		);
		if( sMesh_Parent == "*MESH_ANIMATION" ) CURRENTANIMATION.VertexList.push_back( Vector3 );
		else MESH.VertexList.push_back( Vector3 );
	}
	ELSE
	ISNAME( "*MESH_FACE_LIST" ){
	}
	ELSE
	ISNAME( "*MESH_FACE" ){
		vector< string > sList = ASE_Parsing_ValueToList( sValue );
		ASE_Face Face;
		Face.A			= atoi( sList[ 2 ].c_str() );
		Face.B			= atoi( sList[ 4 ].c_str() );
		Face.C			= atoi( sList[ 6 ].c_str() );
		Face.AB			= atoi( sList[ 8 ].c_str() );
	//	Face.BC			= atoi( sList[ 10 ].c_str() );
	//	Face.CA			= atoi( sList[ 12 ].c_str() );
	//	Face.Smoothing	= atoi( sList[ 14 ].c_str() );
	//	Face.MTLID		= atoi( sList[ 16 ].c_str() );
		if( sMesh_Parent == "*MESH_ANIMATION" ) CURRENTANIMATION.FaceList.push_back( Face );
		else MESH.FaceList.push_back( Face );
	}
	ELSE
	ISNAME( "*PROP_MOTIONBLUR" ){
		GEOMOBJECT.Prop_Motionblur = atoi( sValue.c_str() );
	}
	ELSE
	ISNAME( "*PROP_CASTSHADOW" ){
		GEOMOBJECT.Prop_CastShadow = atoi( sValue.c_str() );
	}
	ELSE
	ISNAME( "*PROP_RECVSHADOW" ){
		GEOMOBJECT.Prop_RecvShadow = atoi( sValue.c_str() );
	}
	ELSE
	ISNAME( "*WIREFRAME_COLOR" ){
		vector< string > sList = ASE_Parsing_ValueToList( sValue );
		GEOMOBJECT.WireFrame_Color = ASE_Vector3( 
			( float )atof( sList[ 0 ].c_str() ) ,
			( float )atof( sList[ 1 ].c_str() ) ,
			( float )atof( sList[ 2 ].c_str() )
		);
	}
	ELSE
	ISNAME( "*MESH_NUMTVERTEX" ){
		if( sMesh_Parent == "*MESH_ANIMATION" ) CURRENTANIMATION.NumTVertex = atoi( sValue.c_str() );
		else MESH.NumTVertex = atoi( sValue.c_str() );
	}
	ELSE
	ISNAME( "*MESH_TVERTLIST" ){
	}
	ELSE
	ISNAME( "*MESH_TVERT" ){
		vector< string > sList = ASE_Parsing_ValueToList( sValue );
		ASE_Vector3 Vector3 = ASE_Vector3(
			( float )atof( sList[ 1 ].c_str() ),
			( float )atof( sList[ 2 ].c_str() ),
			( float )atof( sList[ 3 ].c_str() )
		);
		if( sMesh_Parent == "*MESH_ANIMATION" ) CURRENTANIMATION.TVertList.push_back( Vector3 );
		else MESH.TVertList.push_back( Vector3 );
	}
	ELSE
	ISNAME( "*MESH_NUMTVFACES" ){
		if( sMesh_Parent == "*MESH_ANIMATION" ) CURRENTANIMATION.NumTVFaces = atoi( sValue.c_str() );
		else MESH.NumTVFaces = atoi( sValue.c_str() );
	}
	ELSE
	ISNAME( "*MESH_TFACELIST" ){
	}
	ELSE
	ISNAME( "*MESH_TFACE" ){
		vector< string > sList = ASE_Parsing_ValueToList( sValue );
		ASE_Face Face;
		Face.A = atoi( sList[ 1 ].c_str() );
		Face.B = atoi( sList[ 2 ].c_str() );
		Face.C = atoi( sList[ 3 ].c_str() );
		if( sMesh_Parent == "*MESH_ANIMATION" ) CURRENTANIMATION.TFaceList.push_back( Face );
		else MESH.TFaceList.push_back( Face );
	}
	ELSE
	ISNAME( "*MESH_ANIMATION" ){
		sMesh_Parent = "*MESH_ANIMATION";
	}

}

vector< string > Exporter::ASE_Parsing_ValueToList( std::string& sValue ){
	vector< string > sList;

	string s = trim( sValue ) + " ";
	int iFirst = 0;

	while( s.find_first_not_of( " \t\r\n" ) != string::npos ){
		iFirst = s.find_first_of( " \t\r\n" );
		sList.push_back( s.substr( 0, iFirst ) );
		s = ltrim( s.substr( iFirst ) );
	}

	return sList;
}

#undef ISNAME
#undef ELSE
#undef PARENT
#undef GEOMOBJECT
#undef MESH
#undef ANIMATION
#undef CURRENTANIMATION
#undef ASE_PARSING_BUFFERSIZE