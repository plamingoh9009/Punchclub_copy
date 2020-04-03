#pragma once
enum IMAGE_LOAD_KIND
{
	LOAD_RESOURCE = 0,	//리소스 로딩
	LOAD_FILE,			//파일 로딩
	LOAD_EMPTY,			//빈 비트맵 파일
	LOAD_END
};
typedef struct tagImage
{
	DWORD		resID;		//리소스 ID
	HDC			hMemDC;		//메모리 DC
	HBITMAP		hBit;				//비트맵(새로운 비트맵 핸들)
	HBITMAP		hOBit;				//올드 비트맵(기존 비트맵 핸들)
	int			width;				//이미지 가로크기
	int			height;				//이미지 세로크기
	BYTE		loadType;			//로드 타입
	float		x;					//이미지 x좌표
	float		y;					//이미지 Y좌표
	RECT*		rc;					//이미지 좌표 RECT 버전
	int			currentFrameX;		//현재프레임X
	int			currentFrameY;		//현재프레임Y
	int			maxFrameX;			//최대 X프레임 갯수
	int			maxFrameY;			//최대 Y프레임 갯수
	int			frameWidth;			//1프레임 가로길이
	int			frameHeight;		//1프레임 세로길이
	// 프레임 돌릴 때 3구간으로 나눠서 속도 조절 가능한 옵션 추가
	// Section:		Frame's start ~ end 
	// Option:		Frame's delay, cntSpeed
	// Counter:		각 프레임을 돌릴 카운터
	// bSection:	어느 섹션을 활성화 할건지
	// bEnable:		어느 섹션이 활성화 된건지
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
	// 이미지 회전 시킬 때 사용할 평행사변형을 폴리곤 형태로 정의한다.
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
		// 프레임 돌릴 때 3구간으로 나눠서 속도 조절 가능한 옵션 추가
		// Section:		Frame's start ~ end 
		// Option:		Frame's delay, cntSpeed
		// Counter:		각 프레임을 돌릴 카운터
		// bSection:	어느 섹션을 활성화 할건지
		// bEnable:		어느 섹션이 활성화 된건지
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
		// 이미지 회전할 때 사용할 평행사변형 폴리곤
		parallelogram = nullptr;
	}// tagImage
}IMAGE_INFO, *LPIMAGE_INFO;
class Image
{
private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	LPIMAGE_INFO	_rotateImage;	//Rotate 이미지 정보
	char*			_fileName;		//이미지 이름
	bool			_isTrans;		//배경색 날릴꺼니?
	COLORREF		_transColor;	//배경색 없앨 RGB

	BLENDFUNCTION	_blendFunc;		//알파블렌드 위한정보
	LPIMAGE_INFO	_blendImage;	//알파 블렌드를 사용하기 위한 이미지 정보
protected:
	// 이미지 프레임 돌릴 때 쓰는 함수
	void reselect_frameSection(int section);
	void run_frameDefault();
	void run_frameSection(int section);
	void run_frameSection_reverse(int section);
	void run_frameUpdate(bool bDefualt, bool bReverse);
	void set_fSectionEnd_false();
public:
	//빈 비트맵 이미지 초기화
	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName,
		float x, float y, int width, int height,
		bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	//프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans = true,
		COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY,
		bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	//투명값 셋팅
	void set_transColor(bool isTrans, COLORREF transColor);
	//============================================================
	//==		이미지 회전을 위한 평행사변형 처리함수				==
	//============================================================
	// 이미지 회전을 위해서 평행사변형, rotateImage를 전부 설정한다.
	void init_forRotate(HDC hdc);
	void update_parallelogram(RECT imageRect, double radian);
	//============================================================
	//==			프레임 애니메이션을 위한 함수					==
	//============================================================
	// enableSectionCount: How many you want use section (MAX:3)
	// Start-End: Frame image's Index (0 is start)
	// Delay: How fast you want running frame image (1: 1 fps)
	void set_frameSection(int enableSectionCount,
		int firstStart, int firstEnd, float firstDelay = 1,
		int secondStart = 0, int secondEnd = 0, float secondDelay = 1,
		int thirdStart = 0, int thirdEnd = 0, float thirdDelay = 1);
	// 프레임 이미지 업데이트
	void frameUpdate(bool bDefault = true, bool bReverse = false);
	void set_breakFrame(int breakFrame = -1);

	//삭제
	void release();

	//렌더(내가 지정한 위치에 이미지 출력)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int width, int height);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	//프레임렌더
	void frameRender(HDC hdc);
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int width, int height);
	void frameAlphaRender(HDC hdc, BYTE alpha);
	void frameAlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	//루프렌더(hdc, 루프시킬영역, x오프셋, y오프셋)
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);
	//알파렌더
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
	// 프레임이 끝났는지
	inline bool is_end_firstSection() { return _imageInfo->fFirstEnd; }
	inline bool is_end_secondSection() { return _imageInfo->fSecondEnd; }
	inline bool is_end_thirdSection() { return _imageInfo->fThirdEnd; }
	// 회전할 이미지의 평행사변형 가져오기
	inline POINT * get_rotateParallelogram() { return _rotateImage->parallelogram; }
	inline POINT * get_parallelogram() { return _imageInfo->parallelogram; }

	//DC가져와라
	inline HDC get_memDC() { return _imageInfo->hMemDC; }
	//이미지 좌표x 얻기
	inline float getX() { return _imageInfo->x; }
	inline void setX(float x) 
	{ 
		_imageInfo->x = x;
	}
	//이미지 좌표y 얻기
	inline float getY() { return _imageInfo->y; }
	inline void setY(float y) 
	{ 
		_imageInfo->y = y;
	}
	// 이미지 좌표 셋
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
	// 이미지 RECT 얻기
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
	//이미지 센터 좌표 셋팅
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
	//가로,세로크기 얻기
	inline int get_width() { return _imageInfo->width; }
	inline int get_height() { return _imageInfo->height; }
	//바운딩 박스(충돌용)
	inline RECT get_boundingBox()
	{
		RECT rc = RectMakeCenter((int)(_imageInfo->x), (int)(_imageInfo->y),
			_imageInfo->width, _imageInfo->height);
		return rc;
	}
	//프레임 x 셋팅
	inline int get_frameX() { return _imageInfo->currentFrameX; }
	inline void set_frameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	//프레임 y 셋팅
	inline int get_frameY() { return _imageInfo->currentFrameY; }
	inline void set_frameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}
	//1프레임 가로세로 크기
	inline int get_frameWidth() { return _imageInfo->frameWidth; }
	inline int get_frameHeight() { return _imageInfo->frameHeight; }
	//맥스프레임 x,y
	inline int get_maxFrameX() { return _imageInfo->maxFrameX; }
	inline int get_maxFrameY() { return _imageInfo->maxFrameY; }
};

