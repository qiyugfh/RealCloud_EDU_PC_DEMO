#pragma once
#ifndef TICSDK_WINDOW_SHARE_MGR_H_
#define TICSDK_WINDOW_SHARE_MGR_H_
#include "TICManager.h"


using namespace ilive;

class TICSDK_API TICWindowShareMgr
{
public:
	TICWindowShareMgr();
	~TICWindowShareMgr();

	static TICWindowShareMgr* getTICWindowShareMgr();

	/**
	* \brief 判断本机是否支持OpenGL
	* \return  支持返回true，否则返回false
	*/
	bool isOpenGLSupport() const;

	/**
	* \brief 指定要使用的涂鸦工具
	* \param tool					涂鸦工具
	*/
	void useTool(BoardTool tool) const;

	/**
	* \brief 指定要使用的宽度（对于铅笔、直线、椭圆、矩形工具，该参数指示了线宽；对于橡皮擦及激光笔工具，该参数指示了直径）
	* \param width					宽度
	*/
	void setLineWidth(uint32_t width) const;

	/**
	* \brief 指定要使用的颜色
	* \param red		颜色值Red分量
	* \param green		颜色值Green分量
	* \param blue		颜色值Blue分量
	* \param alpha		Alpha通道
	*/
	void setBrushColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const;

	/**
	* \brief 指定是否启用填充
	* \param fill					是否启用填充
	*/
	void setFill(bool fill) const;

	/**
	* \brief 指定要使用的半径（当前仅用于指定圆角矩形的圆角半径）
	* \param radius				半径
	*/
	void setRadius(uint32_t radius) const;

	/**
	* \brief 对已选中图形进行拷贝操作
	*/
	void copy() const;

	/**
	* \brief 对已选中图形进行删除操作
	*/
	void remove() const;

	/**
	* \brief 撤销
	*/
	void undo() const;

	/**
	* \brief 重做
	*/
	void redo() const;

	/**
	* \brief 清空涂鸦
	*/
	void clearDraws() const;

	/**
	* \brief 显示/隐藏窗口涂鸦工具
	*/
	void showWhiteboardTool(bool show) const;

	/**
	* \brief 获得窗口涂鸦工具显示/隐藏状况
	*/
	bool getWhiteBoardShowStatus() const;
};
#endif
