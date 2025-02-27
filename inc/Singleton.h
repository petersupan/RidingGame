#ifndef SINGLETON_H
#define SINGLETON_H

#include "Defines.h"
#include "SmartPtr.h"
#include "stdio.h"

#define SINGLETONFUNCTIONS(ClassName) \
SmartPtr<ClassName> ClassName::mInstance = SmartPtr<ClassName>(); \
\
ClassName* ClassName::getInstance() {\
    if(ClassName::mInstance.Get() == NULL) {\
		ClassName* inst = SAFE_NEW ClassName();\
        ClassName::mInstance.SetPtr(inst);\
    }\
    return ClassName::mInstance.GetUnConst();\
}\



#define SINGLETONDECLARATIONS(ClassName) \
    ClassName();\
    ClassName(ClassName&);\
    static ClassName* getInstance();\
    static SmartPtr<ClassName> mInstance;\


#endif
