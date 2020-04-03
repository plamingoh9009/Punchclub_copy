#pragma once
enum IMAGE_LOAD_KIND
{
	LOAD_RESOURCE = 0,	//���ҽ� �ε�
	LOAD_FILE,			//���� �ε�
	LOAD_EMPTY,			//�� ��Ʈ�� ����
	LOAD_END
};
typedef struct tagImage
{
	DWORD		resID;		//���ҽ� ID
	HDC			hMemDC;		//�޸� DC
	HBITMAP		hBit;				//��Ʈ��(���ο� ��Ʈ�� �ڵ�)
	HBITMAP		hOBit;				//�õ� ��Ʈ��(���� ��Ʈ�� �ڵ�)
	int			width;				//�̹��� ����ũ��
	int			height;				//�̹��� ����ũ��
	BYTE		loadType;			//�ε� Ÿ��
	float		x;					//�̹��� x��ǥ
	float		y;					//�̹��� Y��ǥ
	RECT*		rc;					//�̹��� ��ǥ RECT ����
	int			currentFrameX;		//����������X
	int			currentFrameY;		//����������Y
	int			maxFrameX;			//�ִ� X������ ����
	int			maxFrameY;			//�ִ� Y������ ����
	int			frameWidth;			//1������ ���α���
	int			frameHeight;		//1������ ���α���
	// ������ ���� �� 3�������� ������ �ӵ� ���� ������ �ɼ� �߰�
	// Section:		Frame's start ~ end 
	// Option:		Frame's delay, cntSpeed
	// Counter:		�� �������� ���� ī����
	// bSection:	��� ������ Ȱ��ȭ �Ұ���
	// bEnable:		��� ������ Ȱ��ȭ �Ȱ���
	int		firstSection[2];
	float	firstDelay;
	float	firstCounter;
	bool	fFirstEnd;
	int		secondSection[2];
	float	secondDelay;
	float	secondCounter;
	bool	fSecondEnd;
	int		thirdSection[2];
	float	thirdDelay;
	float	thirdCounter;
	bool	fThirdEnd;
	bool	bSection[3];
	bool	bEnable[3];
	int		breakFrame;
	// �̹��� ȸ�� ��ų �� ����� ����纯���� ������ ���·� �����Ѵ�.
	POINT * parallelogram;

	tagImage()
	{
		resID = 0;
		hMemDC = NULL;
		hBit = NULL;
		hOBit = NULL;
		width = 0;
		height = 0;
		x = 0;
		y = 0;
		rc = nullptr;
		currentFrameX = 0;
		currentFrameY = 0;
		maxFrameX = 0;
		maxFrameY = 0;
		frameWidth = 0;
		frameHeight = 0;
		loadType = LOAD_RESOURCE;
		// ������ ���� �� 3�������� ������ �ӵ� ���� ������ �ɼ� �߰�
		// Section:		Frame's start ~ end 
		// Option:		Frame's delay, cntSpeed
		// Counter:		�� �������� ���� ī����
		// bSection:	��� ������ Ȱ��ȭ �Ұ���
		// bEnable:		��� ������ Ȱ��ȭ �Ȱ���
		firstSection[2] = { 0, };
		firstDelay = 1;
		firstCounter = 0;
		fFirstEnd = false;
		secondSection[2] = { 0, };
		secondDelay = 1;
		secondCounter = 0;
		fSecondEnd = false;
		thirdSection[2] = { 0, };
		thirdDelay = 1;
		thirdCounter = 0;
		fThirdEnd = false;
		bSection[3] = { 0, };
		bEnable[3] = { 0, };
		breakFrame = -1;
		// �̹��� ȸ���� �� ����� ����纯�� ������
		parallelogram = nullptr;
	}// tagImage
}IMAGE_INFO, *LPIMAGE_INFO;
class Image
{
private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	LPIMAGE_INFO	_rotateImage;	//Rotate �̹��� ����
	char*			_fileName;		//�̹��� �̸�
	bool			_isTrans;		//���� ��������?
	COLORREF		_transColor;	//���� ���� RGB

	BLENDFUNCTION	_blendFunc;		//���ĺ��� ��������
	LPIMAGE_INFO	_blendImage;	//���� ���带 ����ϱ� ���� �̹��� ����
protected:
	// �̹��� ������ ���� �� ���� �Լ�
	void reselect_frameSection(int section);
	void run_frameDefault();
	void run_frameSection(int section);
	void run_frameSection_reverse(int section);
	void run_frameUpdate(bool bDefualt, bool bReverse);
	void set_fSectionEnd_false();
public:
	//�� ��Ʈ�� �̹��� �ʱ�ȭ
	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName,
		float x, float y, int width, int height,
		bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	//������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans = true,
		COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY,
		bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	//���� ����
	void set_transColor(bool isTrans, COLORREF transColor);
	//============================================================
	//==		�̹��� ȸ���� ���� ����纯�� ó���Լ�				==
	//============================================================
	// �̹��� ȸ���� ���ؼ� ����纯��, rotateImage�� ���� �����Ѵ�.
	void init_forRotate(HDC hdc);
	void update_parallelogram(RECT imageRect, double radian);
	//============================================================
	//==			������ �ִϸ��̼��� ���� �Լ�					==
	//============================================================
	// enableSectionCount: How many you want use section (MAX:3)
	// Start-End: Frame image's Index (0 is start)
	// Delay: How fast you want running frame image (1: 1 fps)
	void set_frameSection(int enableSectionCount,
		int firstStart, int firstEnd, float firstDelay = 1,
		int secondStart = 0, int secondEnd = 0, float secondDelay = 1,
		int thirdStart = 0, int thirdEnd = 0, float thirdDelay = 1);
	// ������ �̹��� ������Ʈ
	void frameUpdate(bool bDefault = true, bool bReverse = false);
	void set_breakFrame(int breakFrame = -1);

	//����
	void release();

	//����(���� ������ ��ġ�� �̹��� ���)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int width, int height);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	//�����ӷ���
	void frameRender(HDC hdc);
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int width, int height);
	void frameAlphaRender(HDC hdc, BYTE alpha);
	void frameAlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	//��������(hdc, ������ų����, x������, y������)
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);
	//���ķ���
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
public:
	Image();
	~Image();
public:
	//========================================================
	//==				Getter, Setter						==
	//========================================================
	// �������� ��������
	inline bool is_end_firstSection() { return _imageInfo->fFirstEnd; }
	inline bool is_end_secondSection() { return _imageInfo->fSecondEnd; }
	inline bool is_end_thirdSection() { return _imageInfo->fThirdEnd; }
	// ȸ���� �̹����� ����纯�� ��������
	inline POINT * get_rotateParallelogram() { return _rotateImage->parallelogram; }
	inline POINT * get_parallelogram() { return _imageInfo->parallelogram; }

	//DC�����Ͷ�
	inline HDC get_memDC() { return _imageInfo->hMemDC; }
	//�̹��� ��ǥx ���
	inline float getX() { return _imageInfo->x; }
	inline void setX(float x) 
	{ 
		_imageInfo->x = x;
	}
	//�̹��� ��ǥy ���
	inline float getY() { return _imageInfo->y; }
	inline void setY(float y) 
	{ 
		_imageInfo->y = y;
	}
	// �̹��� ��ǥ ��
	inline void set_pos(POINT pos)
	{
		RECT rc;
		_imageInfo->x = (float)(pos.x);
		_imageInfo->y = (float)(pos.y);
		if (_imageInfo->frameWidth != 0 && _imageInfo->frameHeight != 0)
		{
			rc = RectMake(pos.x, pos.y, _imageInfo->frameWidth, _imageInfo->frameHeight);
		}
		else
		{
			rc = RectMake(pos.x, pos.y, _imageInfo->width, _imageInfo->height);
		}
		set_rect(rc);
	}
	// �̹��� RECT ���
	inline void set_rect(RECT rc)
	{
		if (_imageInfo->rc == nullptr)
		{
			_imageInfo->rc = new RECT;
			*_imageInfo->rc = rc;
		}
		else
		{
			*_imageInfo->rc = rc;
		}
		_imageInfo->x = (float)(rc.left);
		_imageInfo->y = (float)(rc.top);
	}
	inline RECT get_rect() { return *_imageInfo->rc; }
	//�̹��� ���� ��ǥ ����
	inline void set_center(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
		int width, height;
		if (_imageInfo->frameWidth != 0 && _imageInfo->frameHeight != 0)
		{
			width = _imageInfo->frameWidth;
			height = _imageInfo->frameHeight;
		}
		else
		{
			width = _imageInfo->width;
			height = _imageInfo->height;
		}

		if (_imageInfo->rc == nullptr)
		{
			_imageInfo->rc = new RECT;
			*_imageInfo->rc = RectMakeCenter((int)(x), (int)(y),
				width, height);
		}
		else
		{
			*_imageInfo->rc = RectMakeCenter((int)(x), (int)(y),
				width, height);
		}
	}
	inline void set_center(POINT center)
	{
		set_center((float)(center.x), (float)(center.y));
	}
	inline void set_center(RECT rc)
	{
		set_center((float)(rc.left), (float)(rc.top));
	}
	inline POINT get_center()
	{
		POINT center;
		center.x = (LONG)(_imageInfo->rc->left + (_imageInfo->rc->right - _imageInfo->rc->left) * 0.5);
		center.y = (LONG)(_imageInfo->rc->top + (_imageInfo->rc->bottom - _imageInfo->rc->top) * 0.5);
		return center;
	}
	//����,����ũ�� ���
	inline int get_width() { return _imageInfo->width; }
	inline int get_height() { return _imageInfo->height; }
	//�ٿ�� �ڽ�(�浹��)
	inline RECT get_boundingBox()
	{
		RECT rc = RectMakeCenter((int)(_imageInfo->x), (int)(_imageInfo->y),
			_imageInfo->width, _imageInfo->height);
		return rc;
	}
	//������ x ����
	inline int get_frameX() { return _imageInfo->currentFrameX; }
	inline void set_frameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	//������ y ����
	inline int get_frameY() { return _imageInfo->currentFrameY; }
	inline void set_frameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}
	//1������ ���μ��� ũ��
	inline int get_frameWidth() { return _imageInfo->frameWidth; }
	inline int get_frameHeight() { return _imageInfo->frameHeight; }
	//�ƽ������� x,y
	inline int get_maxFrameX() { return _imageInfo->maxFrameX; }
	inline int get_maxFrameY() { return _imageInfo->maxFrameY; }
};

