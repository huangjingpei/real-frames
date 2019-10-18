#pragma once  

#include <windows.h>  
#include <vector>  
#include <dshow.h>  


#define MAX_FRIENDLY_NAME_LENGTH    128  
#define MAX_MONIKER_NAME_LENGTH     256  
#define MAX_PARAM_COUNT 20


struct DeviceParam {
	int width;              //�ֱ��ʿ�
	int height;             //�ֱ��ʸ�
	int avgTimePerFrame;    //ÿ֡��ʱ��

	DeviceParam() {
		width = 0;
		height = 0;
		avgTimePerFrame = 1;
	}

	void Set(int w, int h, int avgTime) {
		width = w;
		height = h;
		avgTimePerFrame = avgTime;
	}

	void Copy(DeviceParam& param) {
		Set(param.width, param.height, param.avgTimePerFrame);
	}
};


struct DeviceInfo {
	WCHAR FriendlyName[MAX_FRIENDLY_NAME_LENGTH];   // �豸�Ѻ���  
	WCHAR MonikerName[MAX_MONIKER_NAME_LENGTH];     // �豸Moniker��

	int paramCount;                                 // ��������
	DeviceParam Params[MAX_PARAM_COUNT];           // ֧�ֵķֱ���
	DeviceParam BestParam;                         // ��ѷֱ���

	DeviceInfo() {
		paramCount = 0;
	}

	int SetResolution(int w, int h, int avgTime) {
		if (paramCount >= MAX_PARAM_COUNT)
			return -1;
		for (int i = 0; i < paramCount; i++) {
			if (Params[i].width == w && Params[i].height == h) {
				return 0;
			}
		}
		int insertIndex = 0;
		for (int i = 0; i < paramCount; i++) {
			if (w > Params[i].width || h > Params[i].height) {
				break;
			}
			else {
				insertIndex++;
			}
		}
		for (int i = paramCount - 1; i >= insertIndex; i--) {
			Params[i + 1].Copy(Params[i]);
		}
		Params[insertIndex].Set(w, h, avgTime);
		paramCount++;
		if (w > BestParam.width) {
			BestParam.Set(w, h, avgTime);
		}
	}
};


/*
	HRESULT hrrst;
	GUID guid = CLSID_VideoInputDeviceCategory;
	std::vector<DeviceInfo> videoDeviceVec;
	hrrst = DsGetAudioVideoInputDevices(videoDeviceVec, guid);

	guid = CLSID_AudioInputDeviceCategory;
	std::vector<DeviceInfo> audioDeviceVec;
	hrrst = DsGetAudioVideoInputDevices(audioDeviceVec, guid);

	guid = CLSID_AudioRendererCategory;
	std::vector<DeviceInfo> audioDeviceVec;
	hrrst = DsGetAudioVideoInputDevices(audioDeviceVec, guid);
*/
HRESULT DsGetAudioVideoInputDevices(std::vector<DeviceInfo>& deviceVec, REFGUID guidValue);
