#include <math.h>

#include "Mathematics.h"

using namespace Mathematics;

/* Vector3 */
/*--------------------------------------------------------------------*/
//생성자, 소멸자-------------------------
Vector3::Vector3() :
	m_fX( 0.0f ),
	m_fY( 0.0f ),
	m_fZ( 0.0f )
{
}

Vector3::Vector3( float fX, float fY, float fZ ) :
	m_fX( fX ),
	m_fY( fY ),
	m_fZ( fZ )
{
}

Vector3::Vector3( const Vector3& refVector ) :
	m_fX( refVector.m_fX ),
	m_fY( refVector.m_fY ),
	m_fZ( refVector.m_fZ )
{
}

Vector3::Vector3( const Vector3* pVector ) :
	m_fX( pVector->m_fX ),
	m_fY( pVector->m_fY ),
	m_fZ( pVector->m_fZ )
{
}

Vector3::Vector3( const Vector4& refVector ) :
	m_fX( refVector.m_fX / refVector.m_fRHW ),
	m_fY( refVector.m_fY / refVector.m_fRHW ),
	m_fZ( refVector.m_fZ / refVector.m_fRHW )
{
}

Vector3::Vector3( const Vector4* pVector ) :
	m_fX( pVector->m_fX / pVector->m_fRHW ),
	m_fY( pVector->m_fY / pVector->m_fRHW ),
	m_fZ( pVector->m_fZ / pVector->m_fRHW )
{
}

Vector3::~Vector3(){
}
//------------------------- /* 생성자, 소멸자 */

//Operator-----------------------------------
Vector3 Vector3::operator+( const Vector3& refVector ) const {
	return Vector3( m_fX + refVector.m_fX, m_fY + refVector.m_fY, m_fZ + refVector.m_fZ );
}

Vector3 Vector3::operator-( const Vector3& refVector ) const {
	return Vector3( m_fX - refVector.m_fX, m_fY - refVector.m_fY, m_fZ - refVector.m_fZ );
}

Vector3 Vector3::operator*( float fValue ) const {
	return Vector3( m_fX * fValue, m_fY * fValue, m_fZ * fValue );
}

Vector3 Vector3::operator/( float fValue ) const {
	return Vector3( m_fX / fValue, m_fY / fValue, m_fZ / fValue );
}

Vector3& Vector3::operator=( const Vector3& refVector ){
	m_fX = refVector.m_fX;
	m_fY = refVector.m_fY;
	m_fZ = refVector.m_fZ;
	return *this;
}

Vector3& Vector3::operator=( const Vector4& refVector ){
	m_fX = refVector.m_fX / refVector.m_fRHW;
	m_fY = refVector.m_fY / refVector.m_fRHW;;
	m_fZ = refVector.m_fZ / refVector.m_fRHW;;
	return *this;
}

Vector3& Vector3::operator+=( const Vector3& refVector ){
	m_fX += refVector.m_fX;
	m_fY += refVector.m_fY;
	m_fZ += refVector.m_fZ;
	return *this;
}

Vector3& Vector3::operator-=( const Vector3& refVector ){
	m_fX -= refVector.m_fX;
	m_fY -= refVector.m_fY;
	m_fZ -= refVector.m_fZ;
	return *this;
}

Vector3& Vector3::operator*=( float fValue ){
	m_fX *= m_fX * fValue;
	m_fY *= m_fY * fValue;
	m_fZ *= m_fZ * fValue;
	return *this;
}

Vector3& Vector3::operator/=( float fValue ){
	m_fX /= fValue;
	m_fY /= fValue;
	m_fZ /= fValue;
	return *this;
}
//----------------------------------- /* Operator */
/*--------------------------------------------------------------------*/

/* Vector3 Function */
/*--------------------------------------------------------------------*/
//3차원 벡터의 길이
float Mathematics::Vector3Length( const Vector3& refVector ){
	return sqrtf( 
		( refVector.m_fX * refVector.m_fX ) +
		( refVector.m_fY * refVector.m_fY ) +
		( refVector.m_fZ * refVector.m_fZ )
		);
}

//3차원 벡터의 내적
float Mathematics::Vector3Dot( const Vector3& refVector1, const Vector3& refVector2 ){
	return ( refVector1.m_fX * refVector2.m_fX ) + ( refVector1.m_fY * refVector2.m_fY ) + ( refVector1.m_fZ * refVector2.m_fZ );
}

//3차원 벡터의 외적
Vector3 Mathematics::Vector3Cross( const Vector3& refVector1, const Vector3& refVector2 ){
	return Vector3(
		refVector1.m_fY * refVector2.m_fZ - refVector1.m_fZ * refVector2.m_fY,
		refVector1.m_fZ * refVector2.m_fX - refVector1.m_fX * refVector2.m_fZ,
		refVector1.m_fX * refVector2.m_fY - refVector1.m_fY * refVector2.m_fX
		);
}

//3차원 벡터의 정규화
Vector3 Mathematics::Vector3Normalize( const Vector3& refVector ){
	return refVector / Vector3Length( refVector );
}
/*--------------------------------------------------------------------*/

/* Vector3 Function */
/*--------------------------------------------------------------------*/
//4차원 벡터의 길이
float Mathematics::Vector4Length( const Vector4& refVector ){
	return sqrtf( 
				( refVector.m_fX * refVector.m_fX ) +
				( refVector.m_fY * refVector.m_fY ) +
				( refVector.m_fZ * refVector.m_fZ ) +
				( refVector.m_fRHW * refVector.m_fRHW )
				);
}

//4차원 벡터의 내적
float Mathematics::Vector4Dot( const Vector4& refVector1, const Vector4& refVector2 ){
	return	( refVector1.m_fX * refVector2.m_fX ) +
			( refVector1.m_fY * refVector2.m_fY ) +
			( refVector1.m_fZ * refVector2.m_fZ ) +
			( refVector1.m_fRHW * refVector2.m_fRHW );
}

//4차원 벡터의 정규화
Vector4 Mathematics::Vector4Normalize( const Vector4& refVector ){
	return refVector / Vector4Length( refVector );
}
/*--------------------------------------------------------------------*/

/* Point3 Function */
//점하고 벡터의 차이가 거의 없어 모두 Vector로 사용합니다.
/*--------------------------------------------------------------------*/
float Mathematics::Point3Distance( const Vector3& refVector1, const Vector3& refVector2 ){
	return sqrtf( powf( refVector2.m_fX - refVector1.m_fX, 2 ) +
		          powf( refVector2.m_fY - refVector1.m_fY, 2 ) +
				  powf( refVector2.m_fZ - refVector1.m_fZ, 2 ) );
}
/*--------------------------------------------------------------------*/

//4x4 전치
void Mathematics::Matrix4x4Transpose( Matrix4x4* const pMatrix ){

	float fTemp;

	for( int i = 0; i < 4; i++ ){
		for( int j = i; j < 4 ; j++ ){
			fTemp = ( *pMatrix )( i, j );
			( *pMatrix )( i, j ) = ( *pMatrix )( j, i );
			( *pMatrix )( j, i ) = fTemp;
		}
	}

}

//4x4 역행렬
void Mathematics::Matrix4x4Inverse( Matrix4x4* const pMatrix ){

	float fDeterminant = Matrix4x4Determinant( *pMatrix );
	if( fDeterminant == 0 ) return;

	Matrix4x4 Matrix;

	for( int i = 0; i < 4; i++ ){
		for( int j = 0; j < 4; j++ ){
			Matrix( i, j ) = Matrix4x4MinorDeterminant( *pMatrix, i, j ) * ( ( ( i + j ) % 2 == 0 )? 1 : -1 );
		}
	}

	( *pMatrix ) = Matrix4x4CreateTranspose( Matrix );

	( *pMatrix ) *= ( 1 / fDeterminant );

}

//4x4 단위 행렬
void Mathematics::Matrix4x4Identity( Matrix4x4* const pMatrix ){
	for( int i = 0; i < 4; i++ ){
		for( int j = 0; j < 4; j++ ){
			if( i == j ) ( *pMatrix )( i, j ) = 1.0f;
			else ( *pMatrix )( i, j ) = 0.0f;
		}
	}
}

//4x4 전치 리턴
Matrix4x4 Mathematics::Matrix4x4CreateTranspose( const Matrix4x4& refMatrix ){

	Matrix4x4 Matrix( refMatrix );
	Matrix4x4Transpose( &Matrix );
	return Matrix;

}

//4x4 역행렬 리턴
Matrix4x4 Mathematics::Matrix4x4CreateInverse( Matrix4x4& refMatrix ){

	Matrix4x4 Matrix( refMatrix );
	Matrix4x4Inverse( &Matrix );
	return Matrix;

}

//4x4 단위 행렬 리턴
Matrix4x4 Mathematics::Matrix4x4CreateIdentity(){
	Matrix4x4 Matrix;
	Matrix4x4Identity( &Matrix );
	return Matrix;
}

//3x3 행렬식
#define ELEMENT( row, col ) ( pMatrix[ row * 3 + col ] )
float Mathematics::Matrix3x3Determinant( const float* pMatrix ){
	return 
		ELEMENT( 0, 0 ) * ( ( ELEMENT( 1, 1 ) * ELEMENT( 2, 2 ) ) - ( ELEMENT( 1, 2 ) * ELEMENT( 2, 1 ) ) ) + 
		ELEMENT( 0, 1 ) * ( ( ELEMENT( 1, 0 ) * ELEMENT( 2, 2 ) ) - ( ELEMENT( 1, 2 ) * ELEMENT( 2, 0 ) ) )  * ( -1 ) +
		ELEMENT( 0, 2 ) * ( ( ELEMENT( 1, 0 ) * ELEMENT( 2, 1 ) ) - ( ELEMENT( 1, 1 ) * ELEMENT( 2, 0 ) ) );
}
#undef ELEMENT

//4x4 마이너( 3x3 ) 행렬식
float Mathematics::Matrix4x4MinorDeterminant( const Matrix4x4& refMatrix, int iRow, int iCol ){
	
	float fMinor[ 9 ];//소행렬
	int loop = 0;

	for( int i = 0; i < 4; i++ ){
		for( int j = 0; j < 4; j++ ){
			if( i != iRow && j != iCol ) fMinor[ loop++ ] = refMatrix.m_fElementArray[ ( i * 4 ) + j ];
		}
	}

	return Matrix3x3Determinant( fMinor );

}

//4x4 행렬식
float Mathematics::Matrix4x4Determinant( const Matrix4x4& refMatrix ){

	float fDeterminant = 0.0f;

	for( int i = 0; i < 4; i++ ){
		fDeterminant += refMatrix.m_fElementArray[ i ] * ( Matrix4x4MinorDeterminant( refMatrix, 0, i ) * ( ( i % 2 == 0 )? 1.0f : -1.0f ) );
	}

	return fDeterminant;
}

//실수와 4차원 정사각 행렬의 곱
Matrix4x4 Mathematics::operator*( float fValue, const Matrix4x4& refMatrix ){
	Matrix4x4 Matrix( refMatrix );
	for( int i = 0; i < 16; i++ ) Matrix.m_fElementArray[ i ] *= fValue;
	return Matrix;
}

//실수와 4차원 정사각 행렬의 곱
Matrix4x4& Mathematics::operator*=( float fValue, Matrix4x4& refMatrix ){
	for( int i = 0; i < 16; i++ ) refMatrix.m_fElementArray[ i ] *= fValue;
	return refMatrix;
}

//4차원 정사각 행렬과 4차원 벡터의 곱
Vector4 Mathematics::operator*( const Matrix4x4& refMatrix, const Vector4& refVector ){
	
	Vector4 Vector;

	Vector.m_fX =	refMatrix.m_fElementArray[ 0 * 4 + 0 ] * refVector.m_fX +
					refMatrix.m_fElementArray[ 0 * 4 + 1 ] * refVector.m_fY +
					refMatrix.m_fElementArray[ 0 * 4 + 2 ] * refVector.m_fZ +
					refMatrix.m_fElementArray[ 0 * 4 + 3 ] * refVector.m_fRHW;
	Vector.m_fY =	refMatrix.m_fElementArray[ 1 * 4 + 0 ] * refVector.m_fX +
					refMatrix.m_fElementArray[ 1 * 4 + 1 ] * refVector.m_fY +
					refMatrix.m_fElementArray[ 1 * 4 + 2 ] * refVector.m_fZ +
					refMatrix.m_fElementArray[ 1 * 4 + 3 ] * refVector.m_fRHW;
	Vector.m_fZ =	refMatrix.m_fElementArray[ 2 * 4 + 0 ] * refVector.m_fX +
					refMatrix.m_fElementArray[ 2 * 4 + 1 ] * refVector.m_fY +
					refMatrix.m_fElementArray[ 2 * 4 + 2 ] * refVector.m_fZ +
					refMatrix.m_fElementArray[ 2 * 4 + 3 ] * refVector.m_fRHW;
	Vector.m_fRHW = refMatrix.m_fElementArray[ 3 * 4 + 0 ] * refVector.m_fX +
					refMatrix.m_fElementArray[ 3 * 4 + 1 ] * refVector.m_fY +
					refMatrix.m_fElementArray[ 3 * 4 + 2 ] * refVector.m_fZ +
					refMatrix.m_fElementArray[ 3 * 4 + 3 ] * refVector.m_fRHW;
	return Vector;

}