#include "VideoRender.h"
#include <qdebug.h>
#include <QStyleOption>



VideoRender::VideoRender(QWidget *parent)
	: QWidget(parent), m_pRootView(NULL)
{
	this->setMinimumSize(300, 300);
	this->setAttribute(Qt::WA_StyledBackground, true);
	this->setStyleSheet("background-color: rgb(255, 255, 255)");
	
	init();
}

VideoRender::~VideoRender()
{
	if (m_pRootView != NULL) {
		m_pRootView->uninit();
		m_pRootView->destroy();
	}
}

void VideoRender::clear()
{
	m_pRootView->removeAllView(true);
	m_userId = "";
}

void VideoRender::setView(const char * userId, E_VideoSrc type)
{
	m_userId = userId;
	iLiveView view;
	view.mode = VIEW_MODE_HIDDEN;
	view.exclusive = true;
	m_pRootView->setView(m_userId.toStdString().c_str(), type, view, false);
}

void VideoRender::doRender(const ilive::LiveVideoFrame * frame)
{
	assert(frame->desc.colorFormat == COLOR_FORMAT_I420);
	m_pRootView->doRender(frame);
}

QString VideoRender::getUserId()
{
	return m_userId;
}

void VideoRender::init()
{
	if (m_pRootView == NULL)
	{
		m_pRootView = ilive::iLiveCreateRootView();
		//iLiveSDK目前的渲染模块，D3D只支持I420格式，GDI只支持RGB24格式;
		E_ColorFormat fmt = (m_pRootView->getRootViewType() == ROOT_VIEW_TYPE_D3D) ? COLOR_FORMAT_I420 : COLOR_FORMAT_RGB24;
		GetILive()->setVideoColorFormat(fmt);

		bool bRet = m_pRootView->init((HWND)this->winId());
		assert(bRet);
	}

	m_pRootView->setBackgroundColor(0xFF000000);
}


