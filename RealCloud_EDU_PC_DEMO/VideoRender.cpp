#include "VideoRender.h"



VideoRender::VideoRender(QWidget *parent)
	: QWidget(parent)
{
	this->setGeometry(QRect(0, 0, 300, 300));
	m_pRootView = ilive::iLiveCreateRootView();
	m_pRootView->init((HWND)this->winId());
	m_pRootView->setBackgroundColor(0xFF000000);
}


VideoRender::~VideoRender()
{
	if (m_pRootView != NULL) {

		m_pRootView->uninit();
		m_pRootView->destroy();
	}
}

void VideoRender::doRender(const ilive::LiveVideoFrame * frame)
{
	m_pRootView->doRender(frame);
}
