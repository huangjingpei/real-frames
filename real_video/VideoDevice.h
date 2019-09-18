#ifndef H_VIDEO_DEVICE
#define H_VIDEO_DEVICE


#include <string>
#include <list>
using namespace std;



class VideoDeviceOption {
public:
	VideoDeviceOption(int width, int height, int avg_time_perframe);
	~VideoDeviceOption(){}

	int getWidth() { return width; }
	int getHeight() { return height; }
	int getAvgTimePerFrame() { return avg_time_perframe; }

private:
	int width;               //�ֱ��ʿ�
	int height;              //�ֱ��ʸ�
	int avg_time_perframe;   //ÿ֡��ʱ��
};



class VideoDevice
{
public:
	VideoDevice(int device_id, const char *device_name);
	virtual ~VideoDevice() {}

	int getID() { return device_id; }
	char* getName() { return device_name; }
	char* getFFName() { return device_ff_name; }

	void addOption(int width, int height, int avg_time_perframe);
	list<VideoDeviceOption>& getOptionList() { return deviceOptionList; }

private:
	int  device_id;
	char device_name[256];
	char device_ff_name[256 + 6];  //"audio=xxx"

	list<VideoDeviceOption> deviceOptionList;
};


typedef shared_ptr<VideoDevice> VideoDevicePtr;


#endif //H_VIDEO_DEVICE
