#pragma once
#include "qwidget.h"
#include "TICSDK.h"


class VideoRender :
	public QWidget
{
	Q_OBJECT
public:
	VideoRender(QWidget *parent = Q_NULLPTR);
	~VideoRender();


	void doRender(const ilive::LiveVideoFrame *frame);

private:
	ilive::iLiveRootView*	m_pRootView;
};

