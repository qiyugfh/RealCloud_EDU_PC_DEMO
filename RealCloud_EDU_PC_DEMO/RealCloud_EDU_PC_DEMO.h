#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RealCloud_EDU_PC_DEMO.h"

class RealCloud_EDU_PC_DEMO : public QMainWindow
{
	Q_OBJECT

public:
	RealCloud_EDU_PC_DEMO(QWidget *parent = Q_NULLPTR);

private:
	Ui::RealCloud_EDU_PC_DEMOClass ui;
};
