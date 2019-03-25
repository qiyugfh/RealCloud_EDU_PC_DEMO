#pragma once
#include "qwidget.h"
#include "TICSDK.h"
#include <QImage>



class VideoRender :
	public QWidget
{
	Q_OBJECT
public:
	VideoRender(QWidget *parent = Q_NULLPTR);
	~VideoRender();


	void setView(const char *userId, E_VideoSrc type);
	void doRender(const ilive::LiveVideoFrame *frame);

protected:
	virtual void paintEvent(QPaintEvent *);


private:
	ilive::iLiveRootView*	m_pRootView;

	QImage m_image;

};

