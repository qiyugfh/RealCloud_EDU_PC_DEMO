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
	* \brief �жϱ����Ƿ�֧��OpenGL
	* \return  ֧�ַ���true�����򷵻�false
	*/
	bool isOpenGLSupport() const;

	/**
	* \brief ָ��Ҫʹ�õ�Ϳѻ����
	* \param tool					Ϳѻ����
	*/
	void useTool(BoardTool tool) const;

	/**
	* \brief ָ��Ҫʹ�õĿ�ȣ�����Ǧ�ʡ�ֱ�ߡ���Բ�����ι��ߣ��ò���ָʾ���߿�������Ƥ��������ʹ��ߣ��ò���ָʾ��ֱ����
	* \param width					���
	*/
	void setLineWidth(uint32_t width) const;

	/**
	* \brief ָ��Ҫʹ�õ���ɫ
	* \param red		��ɫֵRed����
	* \param green		��ɫֵGreen����
	* \param blue		��ɫֵBlue����
	* \param alpha		Alphaͨ��
	*/
	void setBrushColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const;

	/**
	* \brief ָ���Ƿ��������
	* \param fill					�Ƿ��������
	*/
	void setFill(bool fill) const;

	/**
	* \brief ָ��Ҫʹ�õİ뾶����ǰ������ָ��Բ�Ǿ��ε�Բ�ǰ뾶��
	* \param radius				�뾶
	*/
	void setRadius(uint32_t radius) const;

	/**
	* \brief ����ѡ��ͼ�ν��п�������
	*/
	void copy() const;

	/**
	* \brief ����ѡ��ͼ�ν���ɾ������
	*/
	void remove() const;

	/**
	* \brief ����
	*/
	void undo() const;

	/**
	* \brief ����
	*/
	void redo() const;

	/**
	* \brief ���Ϳѻ
	*/
	void clearDraws() const;

	/**
	* \brief ��ʾ/���ش���Ϳѻ����
	*/
	void showWhiteboardTool(bool show) const;

	/**
	* \brief ��ô���Ϳѻ������ʾ/����״��
	*/
	bool getWhiteBoardShowStatus() const;
};
#endif
