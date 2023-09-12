#include <math.h>

#include "Utility.h"

using namespace std;
using namespace Mathematics;
using namespace Utility;

/* Camera_Model */
/*--------------------------------------------------------------------*/
//생성자, 소멸자---------------------
Camera_Model::Camera_Model() :
	m_Matrix(),
	m_Eye( 0.0f, 10.0f, 10.0f ),
	m_Look( 0.0f, 0.0f, 0.0f ),
	m_Up( 0.0f, 1.0f, 0.0f )
{
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );
}

Camera_Model::Camera_Model( const Camera_Model* pCamera ):
	m_Matrix( pCamera->m_Matrix ),
	m_Eye( pCamera->m_Eye ),
	m_Look( pCamera->m_Look ),
	m_Up( pCamera->m_Up )
{
}

Camera_Model::Camera_Model( const Camera_Model& refCamera ) :
	m_Matrix( refCamera.m_Matrix ),
	m_Eye( refCamera.m_Eye ),
	m_Look( refCamera.m_Look ),
	m_Up( refCamera.m_Up )
{
}

Camera_Model::~Camera_Model(){
}
//--------------------- /* 생성자, 소멸자 */

//카메라 이동-----------------
void Camera_Model::CameraLocation( float fX, float fY, float fZ ){
	m_Eye.m_fX = fX;
	m_Eye.m_fY = fY;
	m_Eye.m_fZ = fZ;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );
}

void Camera_Model::CameraLocation( const Mathematics::Vector3& refLocation ){
	m_Eye = refLocation;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );
}

void Camera_Model::MoveCamera( float fX, float fY, float fZ ){
	m_Eye.m_fX += fX;
	m_Eye.m_fY += fY;
	m_Eye.m_fZ += fZ;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );
}

void Camera_Model::MoveCamera( const Mathematics::Vector3& refMoveVector ){
	m_Eye += refMoveVector;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );
}
//----------------- /* 카메라 이동 */

//시점( 바라보는 곳 ) 이동------------------
void Camera_Model::LookLocation( float fX, float fY, float fZ ){
	m_Look.m_fX = fX;
	m_Look.m_fY = fY;
	m_Look.m_fZ = fZ;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );
}

void Camera_Model::LookLocation( const Mathematics::Vector3& refLocation ){
	m_Look = refLocation;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );
}

void Camera_Model::MoveLook( float fX, float fY, float fZ ){
	m_Look.m_fX += fX;
	m_Look.m_fY += fY;
	m_Look.m_fZ += fZ;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );
}

void Camera_Model::MoveLook( const Mathematics::Vector3& refMoveVector ){
	m_Look += refMoveVector;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );
}
//------------------ /* 시점( 바라보는 곳 ) 이동 */

//getter------------------------
Vector3 Camera_Model::GetEye() const {
	return m_Eye;
}

Vector3 Camera_Model::GetLook() const {
	return m_Look;
}

Vector3 Camera_Model::GetUp() const {
	return m_Up;
}

Matrix4x4 Camera_Model::GetCameraMatrix4x4() const {
	return m_Matrix;
}
//------------------------ /* getter */

//카메라 기준 회전------------------------------------
void Camera_Model::Rotate_CameraAxis_X( float fAngle ){

	//3개의 축을 구합니다.
	Vector3 Axis_z( Vector3Normalize( m_Look - m_Eye ) );
	Vector3 Axis_x( Vector3Normalize( Vector3Cross( m_Up, Axis_z ) ) );
	Vector3 Axis_y( Vector3Normalize( Vector3Cross( Axis_z, Axis_x ) ) );

	//xy평면상에서 회전한 값을 구합니다.
	float fLength_x = cosf( MATH_DEGREETORADIAN( fAngle + 90.0f ) );
	float fLength_y = sinf( MATH_DEGREETORADIAN( fAngle + 90.0f ) );

	//xy편면상에서 회전한 값을 카메라 xy평면상에 회전한 값으로 변환합니다.
	Vector3 Direction = Vector3Normalize( ( Axis_y * fLength_x ) + ( Axis_z * fLength_y ) );

	//z값( 회전된 z값 )이 변경되었으니 y축을 다시 계산합니다.
	m_Up = Vector3Cross( Direction, Axis_x );
	
	//회전된 z값에 이전 시점까지의 거리를 곱합니다.
	m_Look = m_Eye + ( Direction * Point3Distance( m_Eye, m_Look ) );

	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );

}

void Camera_Model::Rotate_CameraAxis_Y( float fAngle ){

	//3개의 축을 구합니다.
	Vector3 Axis_z( Vector3Normalize( m_Look - m_Eye ) );
	Vector3 Axis_x( Vector3Normalize( Vector3Cross( m_Up, Axis_z ) ) );
	Vector3 Axis_y( Vector3Normalize( Vector3Cross( Axis_z, Axis_x ) ) );

	//xy평면상에서 회전한 값을 구합니다.
	float fLength_x = cosf( MATH_DEGREETORADIAN( fAngle + 90.0f ) );
	float fLength_y = sinf( MATH_DEGREETORADIAN( fAngle + 90.0f ) );

	//xy편면상에서 회전한 값을 카메라 xy평면상에 회전한 값으로 변환합니다.
	Vector3 Direction = Vector3Normalize( ( Axis_x * fLength_x ) + ( Axis_z * fLength_y ) );
	
	//회전된 z값에 이전 시점까지의 거리를 곱합니다.
	m_Look = m_Eye + ( Direction * Point3Distance( m_Eye, m_Look ) );

	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );

}

void Camera_Model::Rotate_CameraAxis_Z( float fAngle ){

	//3개의 축을 구합니다.
	Vector3 Axis_z( Vector3Normalize( m_Look - m_Eye ) );
	Vector3 Axis_x( Vector3Normalize( Vector3Cross( m_Up, Axis_z ) ) );
	Vector3 Axis_y( Vector3Normalize( Vector3Cross( Axis_z, Axis_x ) ) );

	//xy평면상에서 회전한 값을 구합니다.
	float fLength_x = cosf( MATH_DEGREETORADIAN( fAngle + 90.0f ) );
	float fLength_y = sinf( MATH_DEGREETORADIAN( fAngle + 90.0f ) );

	//xy편면상에서 회전한 값을 카메라 xy평면상에 회전한 값으로 변환합니다.
	m_Up = Vector3Normalize( ( Axis_x * fLength_x ) + ( Axis_y * fLength_y ) );

	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );

}
//------------------------------------ /* 카메라 기준 회전 */

///카메라 위치 기준 회전------------------------------------
void Camera_Model::Rotate_EyeAxis_X( float fAngle ){

	Matrix4x4 Matrix =	Matrix4x4CreateTranslateXYZ( m_Eye ) *
						Matrix4x4CreateRotate_X( fAngle ) *
						Matrix4x4CreateTranslateXYZ( m_Eye * ( -1 ) );

	m_Eye  = Matrix * m_Eye;
	m_Look = Matrix * m_Look;
	m_Up   = Matrix4x4CreateRotate_X( fAngle ) * m_Up;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );

}

void Camera_Model::Rotate_EyeAxis_Y( float fAngle ){

	Matrix4x4 Matrix =	Matrix4x4CreateTranslateXYZ( m_Eye ) *
						Matrix4x4CreateRotate_Y( fAngle ) *
						Matrix4x4CreateTranslateXYZ( m_Eye * ( -1 ) );

	m_Eye  = Matrix * m_Eye;
	m_Look = Matrix * m_Look;
	m_Up   = Matrix4x4CreateRotate_Y( fAngle ) * m_Up;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );

}

void Camera_Model::Rotate_EyeAxis_Z( float fAngle ){

	Matrix4x4 Matrix =	Matrix4x4CreateTranslateXYZ( m_Eye ) *
						Matrix4x4CreateRotate_Z( fAngle ) *
						Matrix4x4CreateTranslateXYZ( m_Eye * ( -1 ) );

	m_Eye  = Matrix * m_Eye;
	m_Look = Matrix * m_Look;
	m_Up   = Matrix4x4CreateRotate_Z( fAngle ) * m_Up;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );

}
//------------------------------------ /* /카메라 위치 기준 회전 */

//시점( 바라보는 곳 ) 기준 회전------------------------------------
void Camera_Model::Rotate_LookAxis_X( float fAngle ){

	Matrix4x4 Matrix =	Matrix4x4CreateTranslateXYZ( m_Look ) *
						Matrix4x4CreateRotate_X( fAngle ) *
						Matrix4x4CreateTranslateXYZ( m_Look * ( -1 ) );

	m_Eye  = Matrix * m_Eye;
	m_Look = Matrix * m_Look;
	m_Up   = Matrix4x4CreateRotate_X( fAngle ) * m_Up;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );

}

void Camera_Model::Rotate_LookAxis_Y( float fAngle ){

	Matrix4x4 Matrix =	Matrix4x4CreateTranslateXYZ( m_Look ) *
						Matrix4x4CreateRotate_Y( fAngle ) *
						Matrix4x4CreateTranslateXYZ( m_Look * ( -1 ) );

	m_Eye  = Matrix * m_Eye;
	m_Look = Matrix * m_Look;
	m_Up   = Matrix4x4CreateRotate_Y( fAngle ) * m_Up;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );

}

void Camera_Model::Rotate_LookAxis_Z( float fAngle ){

	Matrix4x4 Matrix =	Matrix4x4CreateTranslateXYZ( m_Look ) *
						Matrix4x4CreateRotate_Z( fAngle ) *
						Matrix4x4CreateTranslateXYZ( m_Look * ( -1 ) );

	m_Eye  = Matrix * m_Eye;
	m_Look = Matrix * m_Look;
	m_Up   = Matrix4x4CreateRotate_Z( fAngle ) * m_Up;
	Matrix4x4LookAt( &m_Matrix, m_Eye, m_Look, m_Up );

}
//------------------------------------ /* 시점( 바라보는 곳 ) 기준 회전 */
/*--------------------------------------------------------------------*/

/* Projection_Perspective */
/*--------------------------------------------------------------------*/
//생성자, 소멸저---------------------------
//생성자
Projection_Perspective::Projection_Perspective() :
	m_fFov( 45.0f ),
	m_fAspect( 1.0f ),
	m_fNear( 1.0f ),
	m_fFar( 100.0f )
{
	Matrix4x4Identity( &m_Matrix );
}

//소멸자
Projection_Perspective::~Projection_Perspective(){
}
//--------------------------- /* 생성자, 소멸저 */

//setter---------------------------
void Projection_Perspective::SetFov( float fFov ){
	m_fFov = fFov;
	Matrix4x4Perspective( &m_Matrix, m_fFov, m_fAspect, m_fNear, m_fFar );
}

void Projection_Perspective::SetAspect( float fAspect ){
	m_fAspect = fAspect;
	Matrix4x4Perspective( &m_Matrix, m_fFov, m_fAspect, m_fNear, m_fFar );
}

void Projection_Perspective::SetNear( float fNear ){
	m_fNear = fNear;
	Matrix4x4Perspective( &m_Matrix, m_fFov, m_fAspect, m_fNear, m_fFar );
}

void Projection_Perspective::SetFar( float fFar ){
	m_fFar = fFar;
	Matrix4x4Perspective( &m_Matrix, m_fFov, m_fAspect, m_fNear, m_fFar );
}
//--------------------------- /* setter */

//getter---------------------------
float Projection_Perspective::GetFov() const {
	return m_fFov;
}

float Projection_Perspective::GetAspect() const {
	return m_fAspect;
}

float Projection_Perspective::GetNear() const {
	return m_fNear;
}

float Projection_Perspective::GetFar() const {
	return m_fFar;
}

Matrix4x4 Projection_Perspective::GetProjectionMatrix4x4() const {
	return m_Matrix;
}
//--------------------------- /* getter */
/*--------------------------------------------------------------------*/

/* Matrix */
/*--------------------------------------------------------------------*/
//이동 행렬------------------------
void Utility::Matrix4x4TranslateXYZ( Matrix4x4* pMatrix, float fX, float fY, float fZ ){
	Matrix4x4Identity( pMatrix );
	( *pMatrix )( 0, 3 ) = fX;
	( *pMatrix )( 1, 3 ) = fY;
	( *pMatrix )( 2, 3 ) = fZ;
}

void Utility::Matrix4x4TranslateXYZ( Matrix4x4* pMatrix, const Vector3& refPosition ){
	Matrix4x4TranslateXYZ( pMatrix, refPosition.m_fX, refPosition.m_fY, refPosition.m_fZ );
}
//------------------------ /* 이동 행렬 */

//확대 행렬----------------------------
void Utility::Matrix4x4ScaleXYZ( Matrix4x4* pMatrix, float fX, float fY, float fZ ){
	Matrix4x4Identity( pMatrix );
	( *pMatrix )( 0, 0 ) = fX;
	( *pMatrix )( 1, 1 ) = fY;
	( *pMatrix )( 2, 2 ) = fZ;
}

void Utility::Matrix4x4ScaleXYZ( Matrix4x4* pMatrix, const Vector3& refScale ){
	Matrix4x4ScaleXYZ( pMatrix, refScale.m_fX, refScale.m_fY, refScale.m_fZ );
}
//---------------------------- /* 확대 행렬 */

//회전 행렬----------------------------
//X축
void Utility::Matrix4x4Rotate_X( Matrix4x4* pMatrix, float fAngle ){
	Matrix4x4Identity( pMatrix );
	( *pMatrix )( 1, 1 ) = static_cast< float >( cos( MATH_DEGREETORADIAN( fAngle ) ) );
	( *pMatrix )( 2, 1 ) = static_cast< float >( sin( MATH_DEGREETORADIAN( fAngle ) ) );
	( *pMatrix )( 1, 2 ) = static_cast< float >( -sin( MATH_DEGREETORADIAN( fAngle ) ) );
	( *pMatrix )( 2, 2 ) = static_cast< float >( cos( MATH_DEGREETORADIAN( fAngle ) ) );
}

//Y축
void Utility::Matrix4x4Rotate_Y( Matrix4x4* pMatrix, float fAngle ){
	Matrix4x4Identity( pMatrix );
	( *pMatrix )( 0, 0 ) = static_cast< float >( cos( MATH_DEGREETORADIAN( fAngle ) ) );
	( *pMatrix )( 2, 0 ) = static_cast< float >( -sin( MATH_DEGREETORADIAN( fAngle ) ) );
	( *pMatrix )( 0, 2 ) = static_cast< float >( sin( MATH_DEGREETORADIAN( fAngle ) ) );
	( *pMatrix )( 2, 2 ) = static_cast< float >( cos( MATH_DEGREETORADIAN( fAngle ) ) );
}

//Z축
void Utility::Matrix4x4Rotate_Z( Matrix4x4* pMatrix, float fAngle ){
	Matrix4x4Identity( pMatrix );
	( *pMatrix )( 0, 0 ) = static_cast< float >( cos( MATH_DEGREETORADIAN( fAngle ) ) );
	( *pMatrix )( 1, 0 ) = static_cast< float >( sin( MATH_DEGREETORADIAN( fAngle ) ) );
	( *pMatrix )( 0, 1 ) = static_cast< float >( -sin( MATH_DEGREETORADIAN( fAngle ) ) );
	( *pMatrix )( 1, 1 ) = static_cast< float >( cos( MATH_DEGREETORADIAN( fAngle ) ) );
}
//---------------------------- /* 회전 행렬 */

//카메라 행렬------------------------------
void Utility::Matrix4x4LookAt( Matrix4x4* pMatrix, float fPosition_x, float fPosition_y, float fPosition_z, float fTarget_x, float fTarget_y, float fTarget_z, float fUp_x, float fUp_y, float fUp_z ){
	Matrix4x4LookAt( pMatrix, Vector3( fPosition_x, fPosition_y, fPosition_z ), Vector3( fTarget_x, fTarget_y, fTarget_z ), Vector3( fUp_x, fUp_y, fUp_z ) );
}

//OpenGL은 오른손 좌표계를 사용하기 때문에 화면으로 들어가는 방향( 음의 z 방향 )으로 원점들을 변환하기 위해 z변화에 -1을 곱합니다.
#define MATRIX ( *pMatrix )
void Utility::Matrix4x4LookAt( Matrix4x4* pMatrix, const Vector3& Position, const Vector3& Target, const Vector3& Up ){

	Vector3 Axis_z( Vector3Normalize( Target - Position ) );
	Vector3 Axis_x( Vector3Normalize( Vector3Cross( Up, Axis_z ) ) );
	Vector3 Axis_y( Vector3Normalize( Vector3Cross( Axis_z, Axis_x ) ) );
	/*Vector3 Axis_x( Vector3Normalize( Vector3Cross( Axis_z, Up ) ) );
	Vector3 Axis_y( Vector3Normalize( Vector3Cross( Axis_x, Axis_z ) ) );*/
	
	MATRIX( 0, 0 ) = Axis_x.m_fX; MATRIX( 0, 1 ) = Axis_x.m_fY; MATRIX( 0, 2 ) = Axis_x.m_fZ; MATRIX( 0, 3 ) = -Vector3Dot( Position, Axis_x );
	MATRIX( 1, 0 ) = Axis_y.m_fX; MATRIX( 1, 1 ) = Axis_y.m_fY; MATRIX( 1, 2 ) = Axis_y.m_fZ; MATRIX( 1, 3 ) = -Vector3Dot( Position, Axis_y );
	MATRIX( 2, 0 ) = -Axis_z.m_fX;MATRIX( 2, 1 ) = -Axis_z.m_fY;MATRIX( 2, 2 ) = -Axis_z.m_fZ;MATRIX( 2, 3 ) = Vector3Dot( Position, Axis_z );
	MATRIX( 3, 0 ) = 0.0f;		  MATRIX( 3, 1 ) = 0.0f;		MATRIX( 3, 2 ) = 0.0f;		  MATRIX( 3, 3 ) = 1.0f;

}
#undef MATIRX
//------------------------------ /* 카메라 행렬 */

//원근투영 행렬
void Utility::Matrix4x4Perspective( Matrix4x4* pMatrix, float fFov, float fAspect, float fNear, float fFar ){

	float fDistant = 1.0f / tanf( MATH_DEGREETORADIAN( fFov * 0.5f ) );

	Matrix4x4Identity( pMatrix );

	( *pMatrix )( 0, 0 ) = fDistant / fAspect;
	( *pMatrix )( 1, 1 ) = fDistant;
	( *pMatrix )( 2, 2 ) = ( fNear + fFar ) / ( fNear - fFar );
	( *pMatrix )( 2, 3 ) = ( fNear * fFar * 2.0f ) / ( fNear - fFar );
	( *pMatrix )( 3, 2 ) = -1.0f;

}

//이동 행렬 리턴------------------------------
Matrix4x4 Utility::Matrix4x4CreateTranslateXYZ( float fX, float fY, float fZ ){
	Matrix4x4 Matrix;
	Matrix4x4TranslateXYZ( &Matrix, fX, fY, fZ );
	return Matrix;
}

Matrix4x4 Utility::Matrix4x4CreateTranslateXYZ( const Vector3& refPosition ){
	Matrix4x4 Matrix;
	Matrix4x4TranslateXYZ( &Matrix, refPosition.m_fX, refPosition.m_fY, refPosition.m_fZ );
	return Matrix;
}
//------------------------------ /* 이동 행렬 리턴 */

//확대 행렬 리턴
Matrix4x4 Utility::Matrix4x4CreateScaleXYZ( float fX, float fY, float fZ ){
	Matrix4x4 Matrix;
	Matrix4x4ScaleXYZ( &Matrix, fX, fY, fZ );
	return Matrix;
}

//회전 행렬 리턴------------------------------
//X축
Matrix4x4 Utility::Matrix4x4CreateRotate_X( float fAngle ){
	Matrix4x4 Matrix;
	Matrix4x4Rotate_X( &Matrix, fAngle );
	return Matrix;
}

//Y축
Matrix4x4 Utility::Matrix4x4CreateRotate_Y( float fAngle ){
	Matrix4x4 Matrix;
	Matrix4x4Rotate_Y( &Matrix, fAngle );
	return Matrix;
}

//Z축
Matrix4x4 Utility::Matrix4x4CreateRotate_Z( float fAngle ){
	Matrix4x4 Matrix;
	Matrix4x4Rotate_Z( &Matrix, fAngle );
	return Matrix;
}
//------------------------------ /* 회전 행렬 리턴 */

//카메라 행렬 리턴------------------------------
Matrix4x4 Utility::Matrix4x4CreateLookAt( float fPosition_x, float fPosition_y, float fPosition_z, float fTarget_x, float fTarget_y, float fTarget_z, float fUp_x, float fUp_y, float fUp_z ){
	Matrix4x4 Matrix;
	Matrix4x4LookAt( &Matrix, Vector3( fPosition_x, fPosition_y, fPosition_z ), Vector3( fTarget_x, fTarget_y, fTarget_z ), Vector3( fUp_x, fUp_y, fUp_z ) );
	return Matrix;
}

//카메라 행렬 리턴
Matrix4x4 Utility::Matrix4x4CreateLookAt( const Mathematics::Vector3& Position, const Mathematics::Vector3& Target, const Mathematics::Vector3& Up ){
	Matrix4x4 Matrix;
	Matrix4x4LookAt( &Matrix, Position, Target, Up );
	return Matrix;
}
//------------------------------ /* 카메라 행렬 리턴 */

//원근투영 행렬 리턴
Matrix4x4 Utility::Matrix4x4CreatePerspective( float fFov, float fAspect, float fNear, float fFar ){
	Matrix4x4 Matrix;
	Matrix4x4Perspective( &Matrix, fFov, fAspect, fNear, fFar );
	return Matrix;
}
/*--------------------------------------------------------------------*/

/* String */
/*--------------------------------------------------------------------*/
//trim-----------------------------------------------------
//trim 은 문자열의 양 끝에 공백문자를 지우는 함수입니다.
//왼쪽 공백 제거
string Utility::ltrim( string& s ){

	int iStartIndex = s.find_first_not_of( " \t\r\n" );

	if( iStartIndex == std::string::npos ) return s;

	return s.substr( iStartIndex );

}

//오른쪽 공백 제거
string Utility::rtrim( string& s ){

	int iEndIndex = s.find_last_not_of( " \t\r\n" ) + 1;

	if( iEndIndex == std::string::npos ) return s;

	return s.substr( 0, iEndIndex + 1 );

}

//양쪽 공백 제거
string Utility::trim( string& s ){

	int iStartIndex = s.find_first_not_of( " \t\r\n" );

	if( iStartIndex == std::string::npos ) return s;

	return s.substr( iStartIndex, s.find_last_not_of( " \t\r\n" ) - iStartIndex + 1 );

}
//----------------------------------------------------- /* trim */
/*--------------------------------------------------------------------*/