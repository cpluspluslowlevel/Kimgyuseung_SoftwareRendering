#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>

#include "Mathematics.h"

namespace Utility{

/* ī�޶� �𵨸� Ŭ���� */
//ī�޶��� ��ġ, �ٶ󺸴� ����, ���� ������ �Է¹޾� ī�޶� ����� ����ϴ�.
class Camera_Model{
private:

	//Eye: ī�޶� ��ġ, Look: ī�޶� ���� ����, Up: ī�޶� ���� ����
	Mathematics::Vector3 m_Eye;
	Mathematics::Vector3 m_Look;
	Mathematics::Vector3 m_Up;

	Mathematics::Matrix4x4 m_Matrix;

public:
	//������, �Ҹ���
	Camera_Model();
	Camera_Model( const Camera_Model* pCamera );
	Camera_Model( const Camera_Model& refCamera );
	~Camera_Model();

	//ī�޶� �̵�
	void CameraLocation( float fX, float fY, float fZ );
	void CameraLocation( const Mathematics::Vector3& refLocation );
	void MoveCamera( float fX, float fY, float fZ );
	void MoveCamera( const Mathematics::Vector3& refMoveVector );
	
	//����( �ٶ󺸴� �� ) �̵�
	void LookLocation( float fX, float fY, float fZ );
	void LookLocation( const Mathematics::Vector3& refLocation );
	void MoveLook( float fX, float fY, float fZ );
	void MoveLook( const Mathematics::Vector3& refMoveVector );

	//ȸ��( ī�޶� ����, ī�޶� ��ġ ����, ī�޶� ���� ���� )
	void Rotate_CameraAxis_X( float fAngle );
	void Rotate_CameraAxis_Y( float fAngle );
	void Rotate_CameraAxis_Z( float fAngle );
	void Rotate_EyeAxis_X( float fAngle );
	void Rotate_EyeAxis_Y( float fAngle );
	void Rotate_EyeAxis_Z( float fAngle );
	void Rotate_LookAxis_X( float fAngle );
	void Rotate_LookAxis_Y( float fAngle );
	void Rotate_LookAxis_Z( float fAngle );

	//getter
	Mathematics::Vector3		GetEye() const;
	Mathematics::Vector3		GetLook() const;
	Mathematics::Vector3		GetUp() const;
	Mathematics::Matrix4x4	GetCameraMatrix4x4() const;

};
typedef Camera_Model* PCamera_Model;

/* ī�޶� ���� ���̽� Ŭ���� */
//���� ����� ����� Ŭ�������� ���̽�
//�߻� ��� �Լ�------------------------
//Matrix4x4 GetProjectionMatrix4x4(): ���� ����� Matrix4x4 ��ü�� �����ϰԲ� ����
//--------------------------------------
class Camera_Projection{
private:
public:
	virtual Mathematics::Matrix4x4 GetProjectionMatrix4x4() const = 0;
};

/* ī�޶� ���� ���� Ŭ���� */
//�þ߰�, ��Ⱦ��, �����, ������� �Է¹޾� ���� ���� ����� ����ϴ�.
//���------------------
//Camera_Projection: ī�޶� ���� ���̽� Ŭ����
//----------------------
//������ ��� �Լ�------------------
//Matrix4x4 GetProjectionMatrix4x4(): ���� ���� ��� ����
//----------------------------------
class Projection_Perspective : public Camera_Projection{
private:
	float m_fFov;
	float m_fAspect;
	float m_fNear;
	float m_fFar;
	
	Mathematics::Matrix4x4 m_Matrix;

public:
	//������, �Ҹ���
	Projection_Perspective();
	~Projection_Perspective();

	//setter
	void SetFov( float fFov );
	void SetAspect( float fAspect );
	void SetNear( float fNear );
	void SetFar( float fFar );

	//getter
	float GetFov() const;
	float GetAspect() const;
	float GetNear() const;
	float GetFar() const;
	Mathematics::Matrix4x4 GetProjectionMatrix4x4() const;

};

//���
void Matrix4x4TranslateXYZ( Mathematics::Matrix4x4* pMatrix, float fX, float fY, float fZ );
void Matrix4x4TranslateXYZ( Mathematics::Matrix4x4* pMatrix, const Mathematics::Vector3& refPosition );
void Matrix4x4ScaleXYZ( Mathematics::Matrix4x4* pMatrix, float fX, float fY, float fZ );
void Matrix4x4ScaleXYZ( Mathematics::Matrix4x4* pMatrix, const Mathematics::Vector3& refScale );
void Matrix4x4Rotate_X( Mathematics::Matrix4x4* pMatrix, float fAngle );
void Matrix4x4Rotate_Y( Mathematics::Matrix4x4* pMatrix, float fAngle );
void Matrix4x4Rotate_Z( Mathematics::Matrix4x4* pMatrix, float fAngle );
void Matrix4x4LookAt( Mathematics::Matrix4x4* pMatrix, float fPosition_x, float fPosition_y, float fPosition_z, float fTarget_x, float fTarget_y, float fTarget_z, float fUp_x, float fUp_y, float fUp_z );
void Matrix4x4LookAt( Mathematics::Matrix4x4* pMatrix, const Mathematics::Vector3& Position, const Mathematics::Vector3& Target, const Mathematics::Vector3& Up );
void Matrix4x4Perspective( Mathematics::Matrix4x4* pMatrix, float fFov, float fAspect, float fNear, float fFar );

Mathematics::Matrix4x4 Matrix4x4CreateTranslateXYZ( float fX, float fY, float fZ );
Mathematics::Matrix4x4 Matrix4x4CreateTranslateXYZ( const Mathematics::Vector3& refPosition );
Mathematics::Matrix4x4 Matrix4x4CreateScaleXYZ( float fX, float fY, float fZ );
Mathematics::Matrix4x4 Matrix4x4CreateScaleXYZ( const Mathematics::Vector3& refScale );
Mathematics::Matrix4x4 Matrix4x4CreateRotate_X( float fAngle );
Mathematics::Matrix4x4 Matrix4x4CreateRotate_Y( float fAngle );
Mathematics::Matrix4x4 Matrix4x4CreateRotate_Z( float fAngle );
Mathematics::Matrix4x4 Matrix4x4CreateLookAt( float fPosition_x, float fPosition_y, float fPosition_z, float fTarget_x, float fTarget_y, float fTarget_z, float fUp_x, float fUp_y, float fUp_z );
Mathematics::Matrix4x4 Matrix4x4CreateLookAt( const Mathematics::Vector3& Position, const Mathematics::Vector3& Target, const Mathematics::Vector3& Up );
Mathematics::Matrix4x4 Matrix4x4CreatePerspective( float fFov, float fAspect, float fNear, float fFar );

std::string ltrim( std::string& s );
std::string rtrim( std::string& s );
std::string trim( std::string& s );

};;

#endif