#pragma once
class Timer
{
private:
	bool		_isHardware;			//���� Ÿ�̸Ӹ� �����ϳ�
	float		_timeScale;				//�ð������
	float		_timeElapsed;			//�������Ӵ� �����
	__int64		_curTime;				//����ð�
	__int64		_lastTime;				//�������ð�
	__int64		_periodFrequency;	    //�ð��ֱ�

	unsigned long _frameRate;			//FPS
	unsigned long _FPSFrameCount;		//FPSī��Ʈ

	float _FPStimeElapsed;				//FPS������ �ð��� ����ð��� �����
	float _worldTime;					//��ü�ð� �����
public:
	HRESULT init();
	//����ð� ���
	void tick(float lockFPS = 0.0f);
public:
	Timer();
	~Timer();
public:
	//����FPS��������
	unsigned long get_frameRate(char* str = nullptr)const;
	//�������Ӵ� ����ð�
	float get_elapsedTime()const { return _timeElapsed; }
	//��ü ����ð� ��������
	float get_worldTime()const { return _worldTime; }
};

