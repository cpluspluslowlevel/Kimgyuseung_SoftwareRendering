#ifndef _RUN_H_
#define _RUN_H_

#include <list>
#include <string>

#include "Mathematics.h"
#include "Utility.h"

#include "Renderer.h"

class Runable{
private:
	Renderer* m_pRenderer;
		
	//Camera
	Utility::Camera_Model           m_Camera_Model;
	Utility::Projection_Perspective m_Camera_Projection;

	//ASE model loading
	std::list< Mathematics::Vector3 > m_vecASEvertexlist;
	Mathematics::Matrix4x4            m_matASErotate;

public:
	Runable( Renderer* pRenderer, std::string sASEpath );
	~Runable();

	void operator()( float fAngle_xaxis, float fAngle_zaxis );

};

#endif