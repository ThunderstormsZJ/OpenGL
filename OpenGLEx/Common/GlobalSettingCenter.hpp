#pragma once
#include "../Common/Templates.h"
#include "StructCollect.h"

#ifndef h_GlobalSettingCenter

class GlobalSettingCenter: public Singleton<GlobalSettingCenter>
{
public:
	bool ShowPolygonLineMode = false; // �߿�ģʽ
	bool CullFaceEnable = false; // ���޳�
	// ���ڴ���
	bool FrameBuffEnable = false;
	int PostPrecessTypeValue = 0;
};


#endif // !h_GlobalSettingCenter
