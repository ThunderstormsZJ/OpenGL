#pragma once
#include "../Common/Templates.h"
#include "StructCollect.h"

#ifndef h_GlobalSettingCenter

class GlobalSettingCenter: public Singleton<GlobalSettingCenter>
{
public:
	bool ShowPolygonLineMode = false; // 线框模式
	bool CullFaceEnable = false; // 面剔除
	// 后期处理
	bool FrameBuffEnable = false;
	int PostPrecessTypeValue = 0;
};


#endif // !h_GlobalSettingCenter
