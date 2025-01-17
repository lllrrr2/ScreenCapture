﻿#pragma once
#include <Windows.h>
#include <blend2d.h>

#include "State.h"
#include "Icon.h"
#include "Util.h"
#include "Font.h"

#include "History.h"
#include "Shape/Box.h"
#include "Shape/Ellipse.h"
#include "Shape/Arrow.h"
#include "Shape/Number.h"
#include "Shape/Line.h"
#include "Shape/Pen.h"
#include "Shape/Text.h"
#include "Shape/Eraser.h"
#include "Shape/Mosaic.h"


#define WM_REFRESH (WM_APP+1)

class WindowBase
{
public:
	WindowBase();
	~WindowBase();
	static WindowBase* Get();
	void Show();
	void Close();
	void Refresh();
	static int GetQuitCode();
	int x, y;
	unsigned int w, h;
	HWND hwnd;

	State state;
	State PreState;
	int SelectedToolIndex = -1;

	//tool
	bool IsFill = false;
	std::vector<BLBoxI> screens;

	//paint
	BLContext* PaintCtx;
	BLImage* PrepareImage;
	BLImage* CanvasImage;
	BLImage* OriginalImage;
	BLImage* MosaicImage;
	BLImage* BottomImage;
	unsigned char* pixelData;
	HBITMAP bottomHbitmap;
	bool IsDrawing = false;
	bool IsMosaicUsePen = false;
	unsigned long stride;
	unsigned long dataSize;
	HDC hCompatibleDC = NULL;

	//mouse
	POINT MouseDownPos;
	bool IsLeftBtnDown = false;
	bool IsDoubleClick = false;
	//key
	bool IsShiftDown = false;
	bool IsCtrlDown = false;
	bool IsMainWin = true;

	

protected:
	virtual int OnHitTest(const int& x,const int& y) { return HTCLIENT; };
	virtual void SetCutBoxWhenLeftButtonDown() {};
	virtual void SetCutBox(const int& x, const int& y) {};
	virtual void SetCutBox(const int& x1, const int& y1, const int& x2, const int& y2) {};
	virtual void HighLightWindowBox(const int& x, const int& y) {};
	virtual void MouseMoveWhenMaskReady(const int& x, const int& y) {};
	virtual void PinWindow() {};
	virtual void BeforePaint() {};
	virtual void SaveFile(const std::string& filePath) {};
	void SaveFile();
	void InitWindow();
	void drawToolMain();
	void drawPixelInfo();
	BLBox cutBox;
	int cutBoxBorderWidth = 4;
	int mouseInMaskBoxIndex = -1; //todo


	bool checkMouseEnterToolBox(const int& x, const int& y);
	int mainToolBtnCount = 15;
	int toolBoxSpan = 12;//工具条距离截图区域的高度
	int toolBtnSpanWidth = 6;
	int toolBtnSpanCount = 2;
	int toolBtnWidth = 60;
	int toolBoxWidth = mainToolBtnCount * toolBtnWidth + toolBtnSpanWidth * toolBtnSpanCount;
	int toolBoxHeight = 56;
	int iconLeftMargin = 16;
	int iconTopMargin = 38;
	BLBox toolBoxMain;

private:
	static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);	
	void quitApp(const int& exitCode);
	bool OnTimer(const unsigned int& id);
	//get color
	std::wstring getPixelRgb();
	std::wstring getPixelHex();
	LONG pixelX{ -999999 }, pixelY{ -999999 };
	//save
	void saveClipboard();
	//key
	bool OnKeyDown(const unsigned int& key);
	bool OnKeyUp(const unsigned int& key);
	bool OnChar(const unsigned int& val);

	//mouse
	bool OnLeftButtonDown(const int& x, const int& y);
	bool OnRightButtonDown(const int& x, const int& y);
	bool OnMouseMove(const int& x, const int& y);
	bool OnLeftButtonUp(const int& x, const int& y);
	void leftBtnDownStartDraw();
	double strokeWidths[3]{ 2.0, 6.0, 16.0 };

	//tool
	void drawSplitter(const BLPoint& point);
	BLRoundRect getBtnRect(const BLPoint& point);
	void drawBtn(const BLPoint& point, const Icon::Name& name, const bool& hover);
	void drawBtnCheckable(const BLPoint& point, const Icon::Name& name, const bool& checked, const bool& hover);
	void drawBtnColors(const BLPoint& point, const Icon::Name& name, const bool& checked, const bool& hover, const BLRgba32& color);
	void drawBtnStrokeWidth(const BLPoint& point, const bool& checked, const bool& hover);
	void drawBtnEnable(const BLPoint& point, const Icon::Name& name, const bool& hover, const bool& enable);
	//tool main
	int mouseEnterMainToolIndex = -1;

	//tool sub
	void drawSubTool();
	void drawSubToolBackground(const int& btnCount, const bool isCenter = false);
	void drawSubToolNormal(const Icon::Name& icon);
	void drawSubToolPen();
	void drawSubToolEraser();
	void drawSubToolText();
	void drawSubToolMosaic();
	void drawSubToolLine();
	void drawColorBtns(BLPoint& point, const int& index);
	void drawStrokeWidthBtns(BLPoint& point, const int& index);
	void subToolBtnClick();
	void clickSubToolNormal();
	void clickSubToolPen();
	void clickSubToolMosaic();
	void clickSubToolEraser();
	void clickSubToolText();
	BLBox toolBoxSub;
	int mouseEnterSubToolIndex = -1;
	int strokeBtnIndex = 1;
	int colorBtnIndex = 0;
	BLRgba32 colors[8]{
		BLRgba32(207, 19, 34, 255),
		BLRgba32(212, 136, 6, 255),
		BLRgba32(56, 158, 13, 255),
		BLRgba32(19, 194, 194, 255),
		BLRgba32(9, 88, 217, 255),
		BLRgba32(114, 46, 209, 255),
		BLRgba32(235, 47, 150, 255),
		BLRgba32(0, 0, 0, 255),
	};
};

