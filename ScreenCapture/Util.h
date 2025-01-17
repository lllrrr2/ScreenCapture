#pragma once
#include "blend2d.h"
#include <string>
#include <Windows.h>
void SetBoxByPos(BLBox& box, const double& x1, const double& y1, const double& x2, const double& y2);
void SetBoxByPosSquare(BLBox& box, const double& x1, const double& y1, const double& x2, const double& y2,const int& draggerIndex);
std::string ConvertToUTF8(const std::wstring& wstr);
std::string ConvertToUTF8(const LPWSTR& wstr);
void ChangeCursor(LPCTSTR cursor);
void SetClipboardText(HWND hwnd, const std::wstring& text);
void Debug(const std::string& info);
