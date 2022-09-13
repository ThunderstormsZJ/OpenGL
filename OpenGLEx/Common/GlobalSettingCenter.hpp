#pragma once
#include "../Common/Templates.h"
#include "StructCollect.h"

#ifndef h_GlobalSettingCenter

class GlobalSettingCenter: public Singleton<GlobalSettingCenter>
{
public:
	// 后期处理
	bool FrameBuffEnable = true;
	int PostPrecessTypeValue = 0;
};


#endif // !h_GlobalSettingCenter
