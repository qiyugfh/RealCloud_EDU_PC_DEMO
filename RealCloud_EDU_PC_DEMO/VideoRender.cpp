#include "VideoRender.h"
#include <QPainter>
#include <qdebug.h>



VideoRender::VideoRender(QWidget *parent)
	: QWidget(parent)
{
	this->setFixedWidth(640);
	this->setFixedHeight(480);

	this->setAttribute(Qt::WA_StyledBackground, true);
	this->setStyleSheet("background-color: rgb(255, 255, 255)");

	m_pRootView = ilive::iLiveCreateRootView();
	m_pRootView->init((HWND)this->winId());
	m_pRootView->setBackgroundColor(0xFF000000);

	m_image = QImage(640, 480, QImage::Format_RGB888);
}


VideoRender::~VideoRender()
{
	if (m_pRootView != NULL) {

		m_pRootView->uninit();
		m_pRootView->destroy();
	}
}

void VideoRender::setView(const char * userId, E_VideoSrc type)
{
	iLiveView view;
	view.mode = VIEW_MODE_HIDDEN;
	view.exclusive = true;
	m_pRootView->setView(userId, type, view, false);
}

void VideoRender::doRender(const ilive::LiveVideoFrame * frame)
{
	E_ColorFormat colorFormat = frame->desc.colorFormat;
	if (colorFormat == COLOR_FORMAT_I420)
	{
		m_pRootView->doRender(frame);
	}
	else if (colorFormat == COLOR_FORMAT_RGB24)
	{
		int w = frame->desc.width;
		int h = frame->desc.height;

		int i;
		int r, g, b;
		QRgb *point;
		uchar *bit;
		i = 0;
		bit = (uchar *)(frame->data);
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				/* Please attion the Littile-Edian and Big-Edian,
				* The Order maybe R-G-B.
				*/
				b = (int)bit[i];
				g = (int)bit[i + 1];
				r = (int)bit[i + 2];
				point = (QRgb *)m_image.scanLine(y) + x;
				*point = qRgb(r, g, b);
				i += 3;
			}

		}
		this->update();
	}
}

void VideoRender::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawImage(0, 0, m_image);
}


