#ifndef _MATRIX_H_
#define _MATRIX_H_

namespace Mathematics{

//클래스 선언------------
class Vector3;
class Vector4;
//------------ /* 클래스 선언 */

class Vector3{
private:
public:
	float m_fX;
	float m_fY;
	float m_fZ;

	//생성자, 소멸자
	Vector3();
	Vector3( float fX, float fY, float fZ );
	Vector3( const Vector3& refVector );
	Vector3( const Vector3* pVector );
	Vector3( const Vector4& refVector );
	Vector3( const Vector4* pVector );
	~Vector3();

	//Operator
	Vector3 operator+( const Vector3& refVector ) const;
	Vector3 operator-( const Vector3& refVector ) const;
	Vector3 operator*( float fValue ) const;
	Vector3 operator/( float fValue ) const;
	Vector3& operator=( const Vector3& refVector );
	Vector3& operator=( const Vector4& refVector );
	Vector3& operator+=( const Vector3& refVector );
	Vector3& operator-=( const Vector3& refVector );
	Vector3& operator*=( float fValue );
	Vector3& operator/=( float fValue );

};

class Vector4{
private:
public:
	float m_fX;
	float m_fY;
	float m_fZ;
	float m_fRHW;

	Vector4() : m_fX( 0.0f ), m_fY( 0.0f ), m_fZ( 0.0f ), m_fRHW( 1.0f ){}
	Vector4( float fX, float fY, float fZ, float fRHW ) : m_fX( fX ), m_fY( fY ), m_fZ ( fZ ), m_fRHW( fRHW ){}
	Vector4( const Vector3* pVector ) : m_fX( pVector->m_fX ), m_fY( pVector->m_fY ), m_fZ( pVector->m_fZ ), m_fRHW( 1.0f ){}
	Vector4( const Vector3& refVector ) : m_fX( refVector.m_fX ), m_fY( refVector.m_fY ), m_fZ( refVector.m_fZ ), m_fRHW( 1.0f ){}
	Vector4( const Vector4* pVector ) : m_fX( pVector->m_fX ), m_fY( pVector->m_fY ), m_fZ( pVector->m_fZ ), m_fRHW( pVector->m_fRHW ){}
	Vector4( const Vector4& refVector ) : m_fX( refVector.m_fX ), m_fY( refVector.m_fY ), m_fZ( refVector.m_fZ ), m_fRHW( refVector.m_fRHW ){}

	Vector4 operator+( const Vector4& refVector ) const { return Vector4( m_fX + refVector.m_fX, m_fY + refVector.m_fY, m_fZ + refVector.m_fZ, m_fRHW + m_fRHW ); }
	Vector4 operator-( const Vector4& refVector ) const { return Vector4( m_fX - refVector.m_fX, m_fY - refVector.m_fY, m_fZ - refVector.m_fZ, m_fRHW - m_fRHW ); }
	Vector4 operator*( float fValue ) const { return Vector4( m_fX * fValue, m_fY * fValue, m_fZ * fValue, m_fRHW * fValue ); }
	Vector4 operator/( float fValue ) const { return Vector4( m_fX / fValue, m_fY / fValue, m_fZ / fValue, m_fRHW / fValue ); }

	Vector4& operator=( const Vector3& refVector ){
		m_fX	= refVector.m_fX;
		m_fY	= refVector.m_fY;
		m_fZ	= refVector.m_fZ;
		m_fRHW	= 1.0f;
		return *this;
	}
	Vector4& operator=( const Vector4& refVector ){
		m_fX	= refVector.m_fX;
		m_fY	= refVector.m_fY;
		m_fZ	= refVector.m_fZ;
		m_fRHW	= refVector.m_fRHW;
		return *this;
	}
	Vector4& operator+=( const Vector4& refVector ){
		m_fX += refVector.m_fX;
		m_fY += refVector.m_fY;
		m_fZ += refVector.m_fZ;
		m_fRHW += m_fRHW;
		return *this;
	}
	Vector4& operator-=( const Vector4& refVector ){
		m_fX	-= refVector.m_fX;
		m_fY	-= refVector.m_fY;
		m_fZ	-= refVector.m_fZ;
		m_fRHW	-= refVector.m_fRHW;
		return *this;
	}
	Vector4& operator*=( float fValue ){
		m_fX	*= fValue;
		m_fY	*= fValue;
		m_fZ	*= fValue;
		m_fRHW	*= fValue;
		return *this;
	}
	Vector4& operator/=( float fValue ){
		m_fX	/= fValue;
		m_fY	/= fValue;
		m_fZ	/= fValue;
		m_fRHW	/= fValue;
		return *this;
	}

};

class Matrix4x4{
private:
public:
	float m_fElementArray[ 16 ];

	Matrix4x4(){ for( int i = 0; i < 16; i++ )m_fElementArray[ i ] = 0.0f; }
	Matrix4x4( const Matrix4x4* pMatrix ){ for( int i = 0; i < 16; i++ )m_fElementArray[ i ] = pMatrix->m_fElementArray[ i ]; }
	Matrix4x4( const Matrix4x4& refMatrix ){ for( int i = 0; i < 16; i++ )m_fElementArray [ i ] = refMatrix.m_fElementArray[ i ]; }

	float& operator()( int iRow, int iCol ){ return m_fElementArray[ ( iRow * 4 ) + iCol ]; }

	Matrix4x4 operator+( const Matrix4x4& refMatrix ) const {
		Matrix4x4 Matrix( this );
		for( int i = 0; i < 16; i++ ) Matrix.m_fElementArray[ i ] += refMatrix.m_fElementArray[ i ];
		return Matrix;
	}
	Matrix4x4 operator-( const Matrix4x4& refMatrix ) const {
		Matrix4x4 Matrix( this );
		for( int i = 0; i < 16; i++ ) Matrix.m_fElementArray[ i ] -= refMatrix.m_fElementArray[ i ];
		return Matrix;
	}
	Matrix4x4 operator*( const Matrix4x4& refMatrix ) const {
		Matrix4x4 Matrix;
		for( int i = 0; i < 4; i++ ){
			for( int j = 0; j < 4; j++ ){
				Matrix.m_fElementArray[ ( i * 4 ) + j ] =	m_fElementArray[ i * 4 ] * refMatrix.m_fElementArray[ j ] +
															m_fElementArray[ ( i * 4 ) + 1 ] * refMatrix.m_fElementArray[ j + ( 1 * 4 ) ] +
															m_fElementArray[ ( i * 4 ) + 2 ] * refMatrix.m_fElementArray[ j + ( 2 * 4 ) ] +
															m_fElementArray[ ( i * 4 ) + 3 ] * refMatrix.m_fElementArray[ j + ( 3 * 4 ) ];
			}
		}
		return Matrix;
	}
	Matrix4x4 operator*( float fValue ) const {
		Matrix4x4 Matrix( this );
		for( int i = 0; i < 16; i++ ) Matrix.m_fElementArray[ i ] *= fValue;
		return Matrix;
	}
	Matrix4x4& operator=( const Matrix4x4& refMatrix ){
		for( int i = 0; i < 16; i++ ){
			m_fElementArray[ i ] = refMatrix.m_fElementArray[ i ];
		}
		return *this;
	}
	Matrix4x4& operator+=( const Matrix4x4& refMatrix ){
		for( int i = 0; i < 16; i++ ){
			m_fElementArray[ i ] += refMatrix.m_fElementArray[ i ];
		}
		return *this;
	}
	Matrix4x4& operator-=( const Matrix4x4& refMatrix ){
		for( int i = 0; i < 16; i++ ){
			m_fElementArray[ i ] -= refMatrix.m_fElementArray[ i ];
		}
		return *this;
	}
	Matrix4x4& operator*=( const Matrix4x4& refMatrix ){
		for( int i = 0; i < 4; i++ ){
			for( int j = 0; j < 4; j++ ){
				m_fElementArray[ ( i * 4 ) + j ] =	m_fElementArray[ i * 4 ] * refMatrix.m_fElementArray[ j ] +
													m_fElementArray[ ( i * 4 ) + 1 ] * refMatrix.m_fElementArray[ j + ( 1 * 4 ) ] +
													m_fElementArray[ ( i * 4 ) + 2 ] * refMatrix.m_fElementArray[ j + ( 2 * 4 ) ] +
													m_fElementArray[ ( i * 4 ) + 3 ] * refMatrix.m_fElementArray[ j + ( 3 * 4 ) ];
			}
		}
		return *this;
	}
	Matrix4x4& operator*=( float fValue ){
		for( int i = 0; i < 16; i++ ){
			m_fElementArray[ i ] *= fValue;
		}
		return *this;
	}

	//실수형 배열로 리턴
	void GetFloatBuffer_Row( float* pBuffer ){
		for( int i = 0; i < 16; i++ ){
			pBuffer[ i ] = m_fElementArray[ i ];
		}
	}

	//실수형 배열로 리턴
	void GetFloatBuffer_Col( float* pBuffer ){
		for( int i = 0; i < 16; i++ ){
			pBuffer[ i ] = m_fElementArray[ ( ( i % 4 ) * 4 ) + ( i / 4 ) ];
		}
	}

};

//3차원 벡터
float Vector3Length( const Vector3& refVector );
float Vector3Dot( const Vector3& refVector1, const Vector3& refVector2 );
Vector3 Vector3Cross( const Vector3& refVector1, const Vector3& refVector2 );
Vector3 Vector3Normalize( const Vector3& refVector );
Vector3 Vector3Projection( const Vector3& refVector1, const Vector3& refVector2 );

//4차원 벡터
float Vector4Length( const Vector4& refVector );
float Vector4Dot( const Vector4& refVector1, const Vector4& refVector2 );
Vector4 Vector4Normalize( const Vector4& refVector );

//3차원 점
float Point3Distance( const Vector3& refVector1, const Vector3& refVector2 );

//4x4 행렬
void Matrix4x4Transpose( Matrix4x4* const pMatrix );
void Matrix4x4Inverse( Matrix4x4* const pMatrix );
void Matrix4x4Identity( Matrix4x4* const pMatirx );
Matrix4x4 Matrix4x4CreateTranspose( const Matrix4x4& refMatrix );
Matrix4x4 Matrix4x4CreateInverse( Matrix4x4& refMatrix );
Matrix4x4 Matrix4x4CreateIdentity();
float Matrix3x3Determinant( const float* pMatrix );
float Matrix4x4MinorDeterminant( const Matrix4x4& refMatrix, int iRow, int iCol );
float Matrix4x4Determinant( const Matrix4x4& refMatrix );

Matrix4x4  operator*( float fValue, const Matrix4x4& refMatrix );
Matrix4x4& operator*=( float fValue, Matrix4x4& refMatrix );

Vector4 operator*( const Matrix4x4& refMatrix, const Vector4& refVector );

};

#define MATH_PI 3.141592f
#define MATH_RADIANTODEGREE( a ) ( ( a ) * ( 180.0f / MATH_PI ) )
#define MATH_DEGREETORADIAN( a ) ( ( a ) * ( MATH_PI / 180.0f ) )


#endif