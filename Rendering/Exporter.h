#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <string>
#include <vector>

#include "ASE.h"

namespace Utility{

enum EExportResult{
	EXPORT_FILEOPENFAIL,
	EXPORT_SIGNATUREERROR,
	EXPORT_SUCCES
};

class Exporter{
private:

	static void ASE_Parsing_Line( std::string sLine, std::string* pNodeName, std::string* pValue );
	static void ASE_Parsing_Data( PASE pASE, std::string& sNodeName, std::string& sValue, std::string& sMesh_Parent );
	static std::vector< std::string > ASE_Parsing_ValueToList( std::string& sValue );

public:
	
	//ASE 파일을 파싱합니다.
	static EExportResult Export_ASE( std::string filePath, PASE* ppOutASE );

};

};

#endif