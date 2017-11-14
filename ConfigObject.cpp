
#include "ConfigObject.h"

ConfigObject::ConfigObject(TCHAR *filename){

	m_filename = filename;

}

ConfigObject::~ConfigObject(){


}

UINT ConfigObject::getIntValue(TCHAR *sectionname, TCHAR *keyname, int defaultkey){

	UINT intValue;
	
	intValue = GetPrivateProfileInt(sectionname,  // section name
									keyname,  // key name
									defaultkey,       // return value if key name not found
									m_filename);  // initialization file name

	
	return intValue;
}

DWORD ConfigObject::getStringValue(TCHAR *sectionname,   //the name of the section in the .ini file ie. [AppOptions]
								   TCHAR *keyname,       //the desired value of the section key ie. Title
								   TCHAR *defaultstring, //the string value to default to if we don't find it
								   TCHAR *returnString){ //our returned value from the result of this function

	TCHAR keyvalue[MAX_PATH];
	DWORD sizeVal = MAX_PATH;
	DWORD retVal = 0;

	//initialize our temporary string buffer
	ZeroMemory(&keyvalue, sizeof(keyvalue));

	//grab the value of our desired string and dump it into the string buffer
	//if the desired sectionname/keyname cannot be found, then the 
	//defaultstring string will get copied into the temporary string buffer
	retVal = GetPrivateProfileString(sectionname,        // section name
									  keyname,        // key name
									  defaultstring,        // default string
									  keyvalue,  // destination buffer
									  sizeVal,              // size of destination buffer
									  m_filename);        // initialization file name

	strcpy(returnString, keyvalue);

	return retVal;
}