#ifndef DEFINES_H
#define DEFINES_H

#define NULL 0

#ifdef VSTUDIO
    #include <crtdbg.h>
#endif

#ifdef _DEBUG
    #ifdef VSTUDIO
        #define SAFE_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
    #else
        #define SAFE_NEW new
    #endif
#else
	#define SAFE_NEW new
#endif

//  This needs to be defined before the project includes
#define SAFE_DELETE(x) { if ((x)!=NULL) { delete((x)); (x)=NULL; } };
#define SAFE_DELETE_ARRAY(x) { if ((x)!=NULL) { delete[] ((x)); (x)=NULL; } };



#endif

