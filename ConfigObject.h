
#ifndef __CONFIGOBJECT_H_
#define __CONFIGOBJECT_H_

//////////////////////////////////
// ConfigObject
//////////////////////////////////
// This object allows us to communicate via the digital plane to a 
// .ini file in the same directory...thereby avoiding the long and
// boring recompilation involved with changing 2 variables..
// 
// I can't really brag about this class, because it's almost a near
// cut and paste from the MSDN documentation...:(
//
// BUT at least it gives everyone an idea of the coolness things that
// you can do with your OpenGL code!...right?? :)

// @author - <a href="mailto:wazoo@wazooenterprises.com">Wazoo</a>
// @version - 1.0
//
// More cool stuff can be found at WazooEnterprises.com 

#include <windows.h>

class ConfigObject {
 
protected:
	TCHAR	*m_filename;

public:
	ConfigObject(TCHAR *filename);
	virtual ~ConfigObject();

	UINT getIntValue(TCHAR *sectionname, TCHAR *keyname, int defaultkey);
	DWORD getStringValue(TCHAR *sectionname, TCHAR *keyname, TCHAR *defaultstring, TCHAR *returnString);
		                 
};

#endif //__CONFIGOBJECT_H_
