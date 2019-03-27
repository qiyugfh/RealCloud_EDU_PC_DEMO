#pragma once
#include "qwidget.h"
#include "TICSDK.h"
#include <QImage>
#include <QPainter>


class VideoRender :
	public QWidget
{
	Q_OBJECT
public:
	VideoRender(QWidget *parent = Q_NULLPTR);
	~VideoRender();

	void clear();
	void setView(const char *userId, E_VideoSrc type);
	void doRender(const ilive::LiveVideoFrame *frame);

	QString getUserId();
		

private:
	void init();

private:
	ilive::iLiveRootView*	m_pRootView;

	QString m_userId;
};

