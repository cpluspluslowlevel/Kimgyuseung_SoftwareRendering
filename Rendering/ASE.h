#ifndef _ASE_H_
#define _ASE_H_

#include <string>
#include <vector>

namespace Utility{

struct ASE_Vector3{
	float X;
	float Y;
	float Z;
	ASE_Vector3() : X( 0.0f ), Y( 0.0f ), Z( 0.0f ) {}
	ASE_Vector3( float fX, float fY, float fZ ) : X( fX ), Y( fY ), Z( fZ ) {}
};

struct ASE_Scene{
	std::string FileName;
	int FirstFrame;
	int LastFrame;
	int FrameSpeed;
	int TicksperFrame;
	ASE_Vector3 Background_Static;
	ASE_Vector3 Ambient_Static;
};

struct ASE_Node_TM{
	std::string Node_Name;
	ASE_Vector3 Inherit_Pos;
	ASE_Vector3 Inherit_Rot;
	ASE_Vector3 Inherit_Scl;
	ASE_Vector3 Row0;
	ASE_Vector3 Row1;
	ASE_Vector3 Row2;
	ASE_Vector3 Row3;
	ASE_Vector3 Pos;
	ASE_Vector3 RotAxis;
	ASE_Vector3 RotAngle;
	ASE_Vector3 Scale;
	ASE_Vector3 ScaleAxis;
	ASE_Vector3 ScaleAxisAng;
};

struct ASE_Face{
	unsigned int A;
	unsigned int B;
	unsigned int C;
	unsigned int AB;
	unsigned int BC;
	unsigned int CA;
	unsigned int Smoothing;
	unsigned int MTLID;
};

struct ASE_Mesh{
	unsigned int TimeValue;
	unsigned int NumVertex;
	unsigned int NumFaces;
	std::vector< ASE_Vector3 > VertexList;
	std::vector< ASE_Face > FaceList;
	unsigned int NumTVertex;
	std::vector< ASE_Vector3 > TVertList;
	unsigned int NumTVFaces;
	std::vector< ASE_Face > TFaceList;
};

struct ASE_GeomObject{
	std::string Node_Name;
	ASE_Node_TM Node_TM;
	ASE_Mesh Mesh;
	unsigned int Prop_Motionblur;
	unsigned int Prop_CastShadow;
	unsigned int Prop_RecvShadow;
	ASE_Vector3 WireFrame_Color;
	std::vector< ASE_Mesh > Mesh_Animation;
};

struct ASE{
	ASE_Scene Scene;
	std::vector< ASE_GeomObject > GeomObject;
};
typedef ASE* PASE;

};

#endif