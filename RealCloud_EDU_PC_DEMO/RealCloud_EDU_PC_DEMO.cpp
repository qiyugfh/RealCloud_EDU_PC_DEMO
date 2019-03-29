#include "RealCloud_EDU_PC_DEMO.h"
#include <qDebug>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRegExp>
#include <QValidator>
#include <QGroupBox>
#include <QDeskTopWidget>
#include "WndList.h"
#include <qwindow.h>
#include <QFileDialog>


#define USER_TOKEN_1 "eJxNjttOg0AQht*Fa2P3ACyY9AIainJQW23FpslmhYWsRorLQrHGd3dLaOLcTPJ9M-PPj-GcPF2zPD90taLqu*HG" \
		"jQGMqxGLgtdKlIJLDbuWS1FQCHS52MIOdimcBlnTaMUUxbL4t98WH3RUmkETAIiIbpPkQyMkp6xU43mIXFtfnmTPZSsOteYIQAs" \
		"ifE69SCU*z19Cy0IuIQg4lzhRaZwGq8Wdx2LzNlQ57vYzssjv2Zdg*1nwtqzi5MXc9LvSrvxsjUhuBydPeLEfpVE6ZM5QbKLd6-" \
		"LYP4SP8n1Nsl6a2yI5hTCVBPvb-jifG79-HqRbbw__"


static LiveOperation liveOperation = NONE;
static RealCloud_EDU_PC_DEMO *mainWindow = NULL;


RealCloud_EDU_PC_DEMO::RealCloud_EDU_PC_DEMO(QWidget *parent)
	: QMainWindow(parent),
	m_sdkappId("1400127140"),
	m_userId("userid_100009353839_1"),
	m_userToken(USER_TOKEN_1),
	m_roomId("2147483640"),
	m_fps(10),
	m_hLayoutWhiteBoard(NULL)
{
	ui.setupUi(this);

	mainWindow = this;
	qDebug("init mainwindow ...");

	// 无边框
	//setWindowFlags(Qt::FramelessWindowHint | windowFlags());


	initLayout();
	initParams();
}


RealCloud_EDU_PC_DEMO::~RealCloud_EDU_PC_DEMO()
{
	onLogoutClicked();
}

void RealCloud_EDU_PC_DEMO::initLayout()
{
	// 左侧区域，控制按钮
	initLeftWidget();

	// 中间区域，消息显示
	initMiddleWidget();

	// 右侧区域，白板区域
	initRightWidget();

	QGridLayout *mainLayout = new QGridLayout();
	mainLayout->addWidget(m_leftPannelWidget, 0, 0);
	mainLayout->addWidget(m_middlePannelWidget, 0, 1);
	mainLayout->addWidget(m_rightPannelWidget, 0, 2);

	ui.centralWidget->setLayout(mainLayout);
	ui.centralWidget->setFixedHeight(700);
	this->setStatusBar(0);
	this->setMenuBar(0);

	// 绑定信号槽
	bindSlots();
}

void RealCloud_EDU_PC_DEMO::initLeftWidget()
{
	m_leftPannelWidget = new QWidget();
	m_leftPannelWidget->setFixedWidth(300);

	QLabel *roomLbl = new QLabel(QString::fromLocal8Bit("房间ID："));

	m_roomEdit = new QLineEdit();
	m_roomEdit->setMinimumWidth(200);

	QRegExp regx("[0-9]+$");
	QValidator *validator = new QRegExpValidator(regx);
	m_roomEdit->setValidator(validator);
	m_roomEdit->setText(m_roomId);

	QHBoxLayout *hLayout1 = new QHBoxLayout();
	hLayout1->addWidget(roomLbl, 0);
	hLayout1->addWidget(m_roomEdit, 1);

	QLabel *userLbl = new QLabel(QString::fromLocal8Bit("用户ID："));

	m_userEdit = new QLineEdit();
	m_userEdit->setMinimumWidth(200);
	m_userEdit->setText(m_userId);

	QHBoxLayout *hLayout2 = new QHBoxLayout();
	hLayout2->addWidget(userLbl, 0);
	hLayout2->addWidget(m_userEdit, 1);

	m_loginBtn = new QPushButton(QString::fromLocal8Bit("登陆"));
	m_loginBtn->setEnabled(true);

	m_logoutBtn = new QPushButton(QString::fromLocal8Bit("登出"));
	m_logoutBtn->setEnabled(false);

	m_createClassroomBtn = new QPushButton(QString::fromLocal8Bit("创建房间"));
	m_createClassroomBtn->setEnabled(false);

	m_destoryClassroomBtn = new QPushButton(QString::fromLocal8Bit("销毁房间"));
	m_destoryClassroomBtn->setEnabled(false);

	m_joinClassroomBtn = new QPushButton(QString::fromLocal8Bit("加入房间"));
	m_joinClassroomBtn->setEnabled(false);

	m_exitClassroomBtn = new QPushButton(QString::fromLocal8Bit("退出房间"));
	m_exitClassroomBtn->setEnabled(false);

	m_openCameraBtn = new QPushButton(QString::fromLocal8Bit("打开摄像头"));
	m_openCameraBtn->setEnabled(false);

	m_closeCameraBtn = new QPushButton(QString::fromLocal8Bit("关闭摄像头"));
	m_closeCameraBtn->setEnabled(false);

	m_openMicBtn = new QPushButton(QString::fromLocal8Bit("打开麦克风"));
	m_openMicBtn->setEnabled(false);

	m_closeMicBtn = new QPushButton(QString::fromLocal8Bit("关闭麦克风"));
	m_closeMicBtn->setEnabled(false);

	m_openPlayerBtn = new QPushButton(QString::fromLocal8Bit("打开扬声器"));
	m_openPlayerBtn->setEnabled(false);

	m_closePlayerBtn = new QPushButton(QString::fromLocal8Bit("关闭扬声器"));
	m_closePlayerBtn->setEnabled(false);

	QGridLayout *gridLayout = new QGridLayout();
	gridLayout->addWidget(m_loginBtn, 0, 0);
	gridLayout->addWidget(m_logoutBtn, 0, 1);
	gridLayout->addWidget(m_createClassroomBtn, 1, 0);
	gridLayout->addWidget(m_destoryClassroomBtn, 1, 1);
	gridLayout->addWidget(m_joinClassroomBtn, 2, 0);
	gridLayout->addWidget(m_exitClassroomBtn, 2, 1);
	gridLayout->addWidget(m_openCameraBtn, 3, 0);
	gridLayout->addWidget(m_closeCameraBtn, 3, 1);
	gridLayout->addWidget(m_openMicBtn, 4, 0);
	gridLayout->addWidget(m_closeMicBtn, 4, 1);
	gridLayout->addWidget(m_openPlayerBtn, 5, 0);
	gridLayout->addWidget(m_closePlayerBtn, 5, 1);

	m_localVideoRender = new VideoRender();
	QGroupBox *group1 = new QGroupBox();
	QHBoxLayout *hLayout3 = new QHBoxLayout();
	hLayout3->addWidget(m_localVideoRender, 1, Qt::AlignCenter);
	group1->setLayout(hLayout3);
	group1->setTitle(QString::fromLocal8Bit("本地画面"));

	m_remoteVideoRender = new VideoRender();
	QGroupBox *group2 = new QGroupBox();
	QHBoxLayout *hLayout4 = new QHBoxLayout();
	hLayout4->addWidget(m_remoteVideoRender, 1, Qt::AlignCenter);
	group2->setLayout(hLayout4);
	group2->setTitle(QString::fromLocal8Bit("远程画面"));

	QVBoxLayout *vLayout1 = new QVBoxLayout();
	vLayout1->addLayout(hLayout1);
	vLayout1->addLayout(hLayout2);
	vLayout1->addLayout(gridLayout);
	vLayout1->addWidget(group1, 1, Qt::AlignHCenter);
	vLayout1->addWidget(group2, 1, Qt::AlignHCenter);

	m_leftPannelWidget->setLayout(vLayout1);
}

void RealCloud_EDU_PC_DEMO::initRightWidget()
{
	m_rightPannelWidget = new QWidget();

	m_msgListWgt = new QListWidget();
	m_msgListWgt->setMinimumWidth(220);
	m_msgListWgt->setStyleSheet("background-color:#99ff99");

	m_msgTextEdit = new QTextEdit();
	m_msgTextEdit->setMinimumWidth(220);
	m_msgTextEdit->setFixedHeight(100);
	m_msgTextEdit->setStyleSheet("background-color:white");

	m_sendMessageBtn = new QPushButton(QString::fromLocal8Bit("发送"));
	m_sendMessageBtn->setFixedSize(100, 30);

	QVBoxLayout *vLayout1 = new QVBoxLayout();
	vLayout1->addWidget(m_msgListWgt, 1);
	vLayout1->addWidget(m_msgTextEdit, 1);
	vLayout1->addWidget(m_sendMessageBtn, 0, Qt::AlignmentFlag::AlignHCenter);

	m_rightPannelWidget->setLayout(vLayout1);
}

void RealCloud_EDU_PC_DEMO::initScreenShareWidget()
{	// 屏幕分享
	m_shareVideoWgt = new QWidget();
	m_shareVideoWgt->setStyleSheet("background-color:#f0f0f0");

	m_shareVideoRender = new VideoRender();
	m_shareVideoRender->setMinimumWidth(580);

	QDesktopWidget desktopWgt;
	int maxv = 10000;

	QLabel *lblX0 = new QLabel("x0");
	m_sbX0 = new QSpinBox();
	m_sbX0->setMaximum(maxv);
	m_sbX0->setValue(0);

	QHBoxLayout *hLayout1 = new QHBoxLayout();
	hLayout1->addWidget(lblX0);
	hLayout1->addWidget(m_sbX0);

	QLabel *lblY0 = new QLabel("y0");
	m_sbY0 = new QSpinBox();
	m_sbY0->setMaximum(maxv);
	m_sbY0->setValue(0);

	QHBoxLayout *hLayout2 = new QHBoxLayout();
	hLayout2->addWidget(lblY0);
	hLayout2->addWidget(m_sbY0);

	QLabel *lblX1 = new QLabel("x1");
	m_sbX1 = new QSpinBox();
	m_sbX1->setMaximum(maxv);
	m_sbX1->setValue(desktopWgt.screenGeometry().width());

	QHBoxLayout *hLayout3 = new QHBoxLayout();
	hLayout3->addWidget(lblX1);
	hLayout3->addWidget(m_sbX1);

	QLabel *lblY1 = new QLabel("y1");
	m_sbY1 = new QSpinBox();
	m_sbY1->setMaximum(maxv);
	m_sbY1->setValue(desktopWgt.screenGeometry().height());

	QHBoxLayout *hLayout4 = new QHBoxLayout();
	hLayout4->addWidget(lblY1);
	hLayout4->addWidget(m_sbY1);

	m_openScreenShareBtn = new QPushButton(QString::fromLocal8Bit("分享指定区域"));
	m_openScreenShareBtn->setEnabled(false);

	m_openScreenShareWndBtn = new QPushButton(QString::fromLocal8Bit("分享指定窗口"));
	m_openScreenShareWndBtn->setEnabled(false);

	m_changeScreenShareBtn = new QPushButton(QString::fromLocal8Bit("更改分享区域"));
	m_changeScreenShareBtn->setEnabled(false);

	m_closeScreenShareBtn = new QPushButton(QString::fromLocal8Bit("关闭屏幕分享"));
	m_closeScreenShareBtn->setEnabled(false);

	QGridLayout *gLayout0 = new QGridLayout();
	gLayout0->addLayout(hLayout1, 0, 0);
	gLayout0->addLayout(hLayout2, 0, 1);
	gLayout0->addLayout(hLayout3, 0, 2);
	gLayout0->addLayout(hLayout4, 0, 3);
	gLayout0->addWidget(m_openScreenShareBtn, 1, 0);
	gLayout0->addWidget(m_openScreenShareWndBtn, 1, 1);
	gLayout0->addWidget(m_changeScreenShareBtn, 1, 2);
	gLayout0->addWidget(m_closeScreenShareBtn, 1, 3);

	QGridLayout *gLayout = new QGridLayout();
	gLayout->addWidget(m_shareVideoRender, 0, 0, Qt::AlignHCenter);
	gLayout->addLayout(gLayout0, 1, 0, Qt::AlignHCenter);
	m_shareVideoWgt->setLayout(gLayout);
}

void RealCloud_EDU_PC_DEMO::initWhiteBoardWidget()
{
	m_whiteBoardWgt = new QWidget();
	m_whiteBoardWgt->setStyleSheet("background-color:#f0f0f0");

	m_whiteBoardContainer = new QWidget();
	m_whiteBoardContainer->setMinimumWidth(580);

	m_createWhiteBoardBtn = new QPushButton(QString::fromLocal8Bit("创建白板"));
	m_destoryWhiteBoardBtn = new QPushButton(QString::fromLocal8Bit("销毁白板"));
	m_addWhiteBoardBtn = new QPushButton(QString::fromLocal8Bit("新增一页"));
	m_delWhiteBoardBtn = new QPushButton(QString::fromLocal8Bit("删除一页"));
	m_prePageBtn = new QPushButton(QString::fromLocal8Bit("上一页"));
	m_nextPageBtn = new QPushButton(QString::fromLocal8Bit("下一页"));
	m_currentPage = new QLabel("1/1");
	m_uploadBkFileBtn = new QPushButton(QString::fromLocal8Bit("上传背景图"));
	m_clearWhiteBoardBtn = new QPushButton(QString::fromLocal8Bit("清除涂鸦"));

	QGridLayout *gLayout0 = new QGridLayout();
	gLayout0->addWidget(m_createWhiteBoardBtn, 0, 0);
	gLayout0->addWidget(m_destoryWhiteBoardBtn, 0, 1);
	gLayout0->addWidget(m_addWhiteBoardBtn, 1, 0);
	gLayout0->addWidget(m_delWhiteBoardBtn, 1, 1);
	gLayout0->addWidget(m_prePageBtn, 2, 0);
	gLayout0->addWidget(m_nextPageBtn, 2, 1);
	gLayout0->addWidget(m_currentPage, 3, 0);
	gLayout0->addWidget(m_uploadBkFileBtn, 3, 1);
	gLayout0->addWidget(m_clearWhiteBoardBtn, 4, 0);


	QGridLayout *gLayout1 = new QGridLayout();
	gLayout1->addWidget(m_whiteBoardContainer, 0, 0, Qt::AlignHCenter);
	gLayout1->addLayout(gLayout0, 1, 0, Qt::AlignHCenter);
	m_whiteBoardWgt->setLayout(gLayout1);
}

void RealCloud_EDU_PC_DEMO::initMiddleWidget()
{
	m_middlePannelWidget = new QWidget();

	m_dispalyTabWidget = new QTabWidget();
	m_dispalyTabWidget->setMinimumSize(600, 600);

	initScreenShareWidget();
	initWhiteBoardWidget();

	m_dispalyTabWidget->addTab(m_shareVideoWgt, QString::fromLocal8Bit("屏幕分享"));
	m_dispalyTabWidget->addTab(m_whiteBoardWgt, QString::fromLocal8Bit("白板"));

	QGridLayout *glayout11 = new QGridLayout();
	glayout11->addWidget(m_dispalyTabWidget, 0, 0, Qt::AlignCenter);

	m_middlePannelWidget->setLayout(glayout11);
}

void RealCloud_EDU_PC_DEMO::initParams()
{
	m_sdk = TICManager::GetTICManager();
	m_opt.setClassroomEventListener(this);
	m_opt.setClassroomIMListener(this);
	//m_opt.setClassroomRecordEventListener(this);


	m_sdk->initSDK(m_sdkappId.toInt());
	// 设置本地视频预览回调
	m_sdk->setLocalVideoCallBack(onLocalVideo, this);
	m_sdk->setRemoteVideoCallBack(onRemoteVideo, this);
	// 设置设备操作回调
	m_sdk->setDeviceOperationCallback(onDeviceOperation, this);
	// 设置被踢下线回调
	m_sdk->setForceOfflineCallback(onForceOffline);
	// 设置网络状态监听回调
	m_sdk->setNetworkConnCallBack(onNetworkConnect, onNetworkDisconn);


	emit mainWindow->showMessage(mainWindow->m_userId, QString::fromLocal8Bit("被踢下线 ..."));
}

void RealCloud_EDU_PC_DEMO::bindSlots()
{
	connect(m_loginBtn, SIGNAL(clicked()), this, SLOT(onLoginClicked()));
	connect(m_logoutBtn, SIGNAL(clicked()), this, SLOT(onLogoutClicked()));
	connect(m_createClassroomBtn, SIGNAL(clicked()), this, SLOT(onCreateClassroomClicked()));
	connect(m_destoryClassroomBtn, SIGNAL(clicked()), this, SLOT(onDestoryClassroomClicked()));
	connect(m_joinClassroomBtn, SIGNAL(clicked()), this, SLOT(onJoinClassroomClicked()));
	connect(m_exitClassroomBtn, SIGNAL(clicked()), this, SLOT(onExitClassroomClicked()));

	connect(m_openCameraBtn, SIGNAL(clicked()), this, SLOT(onOpenCameraClicked()));
	connect(m_closeCameraBtn, SIGNAL(clicked()), this, SLOT(onCloseCameraClicked()));
	connect(m_openMicBtn, SIGNAL(clicked()), this, SLOT(onOpenMicClicked()));
	connect(m_closeMicBtn, SIGNAL(clicked()), this, SLOT(onCloseMicClicked()));
	connect(m_openPlayerBtn, SIGNAL(clicked()), this, SLOT(onOpenPlayerClicked()));
	connect(m_closePlayerBtn, SIGNAL(clicked()), this, SLOT(onClosePlayerClicked()));

	connect(this, SIGNAL(showMessage(const QString &, const QString &)), this, SLOT(addMsgContent(const QString &, const QString &)));
	connect(m_sendMessageBtn, SIGNAL(clicked()), this, SLOT(onSendMessageClicked()));

	connect(m_openScreenShareBtn, SIGNAL(clicked()), this, SLOT(onOpenScreenShareClicked()));
	connect(m_openScreenShareWndBtn, SIGNAL(clicked()), this, SLOT(onOpenScreenShareWndClicked()));
	connect(m_changeScreenShareBtn, SIGNAL(clicked()), this, SLOT(onChangeScreenShareClicked()));
	connect(m_closeScreenShareBtn, SIGNAL(clicked()), this, SLOT(onCloseScreenShareClicked()));

	connect(m_createWhiteBoardBtn, SIGNAL(clicked()), this, SLOT(onCreateWhiteBoardClicked()));
	connect(m_destoryWhiteBoardBtn, SIGNAL(clicked()), this, SLOT(onDestoryWhiteBoardClicked()));
	connect(m_addWhiteBoardBtn, SIGNAL(clicked()), this, SLOT(onAddWhiteBoardPageClicked()));
	connect(m_delWhiteBoardBtn, SIGNAL(clicked()), this, SLOT(onDelWhiteBoardPageClicked()));
	connect(m_clearWhiteBoardBtn, SIGNAL(clicked()), this, SLOT(onClearWhiteBoardPageClicked()));
	connect(m_prePageBtn, SIGNAL(clicked()), this, SLOT(onPrePageClicked()));
	connect(m_nextPageBtn, SIGNAL(clicked()), this, SLOT(onNextPageClicked()));
	connect(m_uploadBkFileBtn, SIGNAL(clicked()), this, SLOT(onUploadBkFileClicked()));
}

void RealCloud_EDU_PC_DEMO::updatePage()
{
	uint32_t pageIndex = m_sdk->getTICWhiteBoardManager()->getPageIndex();
	uint32_t pageCount = m_sdk->getTICWhiteBoardManager()->getPageCount();
	QString curtext = QString("%1/%2").arg(pageIndex).arg(pageCount);
	qDebug() << "current page: " << curtext;
	m_currentPage->setText(curtext);

	if (pageCount <= 1) {
		m_prePageBtn->setEnabled(false);
		m_nextPageBtn->setEnabled(false);
	}
	else if (pageIndex == pageCount)
	{
		m_prePageBtn->setEnabled(true);
		m_nextPageBtn->setEnabled(false);
	}
	else if (pageIndex <= 1)
	{
		m_prePageBtn->setEnabled(false);
		m_nextPageBtn->setEnabled(true);
	}
	else
	{
		m_prePageBtn->setEnabled(true);
		m_nextPageBtn->setEnabled(true);
	}
}

void RealCloud_EDU_PC_DEMO::enterClassRoom()
{
	m_opt.setIsTeacher(true);
	m_opt.setRoomID(m_roomEdit->text().toInt());

	onOpenCameraClicked();
	onOpenMicClicked();
	onOpenPlayerClicked();

	m_localVideoRender->setView(m_userEdit->text().toStdString().c_str(), ilive::VIDEO_SRC_TYPE_CAMERA);
	m_remoteVideoRender->setView(m_userEdit->text().toStdString().c_str(), ilive::VIDEO_SRC_TYPE_CAMERA);
	m_shareVideoRender->setView(m_userEdit->text().toStdString().c_str(), ilive::VIDEO_SRC_TYPE_SCREEN);
}

void RealCloud_EDU_PC_DEMO::exitClassRoom()
{
	m_sdk->enableCamera(false);
	m_sdk->enableMic(false);
	m_sdk->enablePlayer(false);

	mainWindow->m_openCameraBtn->setEnabled(false);
	mainWindow->m_closeCameraBtn->setEnabled(false);
	mainWindow->m_openMicBtn->setEnabled(false);
	mainWindow->m_closeMicBtn->setEnabled(false);
	mainWindow->m_openPlayerBtn->setEnabled(false);
	mainWindow->m_closePlayerBtn->setEnabled(false);
}

VideoRender * RealCloud_EDU_PC_DEMO::getLocalVideoRender()
{
	return m_localVideoRender;
}

VideoRender * RealCloud_EDU_PC_DEMO::getRemoteVideoRender()
{
	return m_remoteVideoRender;
}

VideoRender * RealCloud_EDU_PC_DEMO::getScreenShareRender()
{
	return m_shareVideoRender;
}

void RealCloud_EDU_PC_DEMO::onSendTIMMsgSuccess(void * data)
{
	qDebug("callback onSendTIMMsgSuccess ...");
}

void RealCloud_EDU_PC_DEMO::onSendTIMMsgError(int code, const char * desc, void * data)
{
	qDebug("callback onSendTIMMsgError ...");
}

void RealCloud_EDU_PC_DEMO::onIliveSucCallback(void * data)
{
	qDebug("callback onIliveSucCallback ...");

	QString userId = mainWindow->m_userEdit->text();
	switch (liveOperation)
	{
	case LOGIN:
		mainWindow->m_loginBtn->setEnabled(false);
		mainWindow->m_logoutBtn->setEnabled(true);
		mainWindow->m_createClassroomBtn->setEnabled(true);
		mainWindow->m_destoryClassroomBtn->setEnabled(true);
		mainWindow->m_joinClassroomBtn->setEnabled(true);
		mainWindow->m_openCameraBtn->setEnabled(false);
		mainWindow->m_closeCameraBtn->setEnabled(false);
		mainWindow->m_openMicBtn->setEnabled(false);
		mainWindow->m_closeMicBtn->setEnabled(false);
		mainWindow->m_openPlayerBtn->setEnabled(false);
		mainWindow->m_closePlayerBtn->setEnabled(false);
		mainWindow->m_openScreenShareBtn->setEnabled(false);
		mainWindow->m_changeScreenShareBtn->setEnabled(false);
		mainWindow->m_closeScreenShareBtn->setEnabled(false);
		emit mainWindow->showMessage(userId, QString::fromLocal8Bit("登陆成功 ..."));
		break;
	case LOGOUT:
		mainWindow->m_loginBtn->setEnabled(true);
		mainWindow->m_logoutBtn->setEnabled(false);
		mainWindow->m_createClassroomBtn->setEnabled(false);
		mainWindow->m_destoryClassroomBtn->setEnabled(false);
		mainWindow->m_joinClassroomBtn->setEnabled(false);
		mainWindow->m_openCameraBtn->setEnabled(false);
		mainWindow->m_closeCameraBtn->setEnabled(false);
		mainWindow->m_openMicBtn->setEnabled(false);
		mainWindow->m_closeMicBtn->setEnabled(false);
		mainWindow->m_openPlayerBtn->setEnabled(false);
		mainWindow->m_closePlayerBtn->setEnabled(false);
		mainWindow->m_openScreenShareBtn->setEnabled(true);
		mainWindow->m_changeScreenShareBtn->setEnabled(false);
		mainWindow->m_closeScreenShareBtn->setEnabled(false);

		emit mainWindow->showMessage(userId, QString::fromLocal8Bit("登陆成功 ..."));
		break;
	case CREATE_ROOM:
		emit mainWindow->showMessage(userId, QString::fromLocal8Bit("创建房间成功 ..."));
		break;
	case DESTORY_ROOM:
		emit mainWindow->showMessage(userId, QString::fromLocal8Bit("销毁房间成功 ..."));
		break;
	case ENTER_ROOM:
		mainWindow->m_joinClassroomBtn->setEnabled(false);
		mainWindow->m_exitClassroomBtn->setEnabled(true);
		mainWindow->m_openScreenShareBtn->setEnabled(true);
		mainWindow->m_openScreenShareWndBtn->setEnabled(true);
		mainWindow->m_changeScreenShareBtn->setEnabled(false);
		mainWindow->m_closeScreenShareBtn->setEnabled(false);

		emit mainWindow->showMessage(userId, QString::fromLocal8Bit("进入房间成功 ..."));
		mainWindow->enterClassRoom();
		break;
	case EXIT_ROOM:
		mainWindow->m_joinClassroomBtn->setEnabled(true);
		mainWindow->m_exitClassroomBtn->setEnabled(false);
		mainWindow->m_openScreenShareBtn->setEnabled(false);
		mainWindow->m_openScreenShareWndBtn->setEnabled(false);
		mainWindow->m_changeScreenShareBtn->setEnabled(false);
		mainWindow->m_closeScreenShareBtn->setEnabled(false);

		emit mainWindow->showMessage(userId, QString::fromLocal8Bit("退出房间成功 ..."));
		mainWindow->exitClassRoom();
		break;
	default:
		break;
	}

}

void RealCloud_EDU_PC_DEMO::onIliveErrCallback(const int code, const char * desc, void * data)
{
	qDebug("callback onIliveErrCallback ...");

	QString userId = mainWindow->m_userEdit->text();
	QString msg = QString::fromLocal8Bit("code:%1, desc:%2").arg(code).arg(desc);
	switch (liveOperation)
	{
	case LOGIN:
		emit mainWindow->showMessage(userId, QString::fromLocal8Bit("登入失败: %1").arg(msg));
		break;
	case LOGOUT:
		emit mainWindow->showMessage(userId, QString::fromLocal8Bit("登出失败: %1").arg(msg));
		break;
	case CREATE_ROOM:
		emit mainWindow->showMessage(userId, QString::fromLocal8Bit("创建房间失败: %1").arg(msg));
		break;
	case DESTORY_ROOM:
		emit mainWindow->showMessage(userId, QString::fromLocal8Bit("销毁房间失败: %1").arg(msg));
		break;
	case ENTER_ROOM:
		emit mainWindow->showMessage(userId, QString::fromLocal8Bit("进入房间失败: %1").arg(msg));
		break;
	case EXIT_ROOM:
		emit mainWindow->showMessage(userId, QString::fromLocal8Bit("退出房间失败: %1").arg(msg));
		break;
	default:
		break;
	}
}

void RealCloud_EDU_PC_DEMO::onLocalVideo(const ilive::LiveVideoFrame *videoFrame, void *customData)
{
	qDebug("callback onLocalVideo ...");
	RealCloud_EDU_PC_DEMO *widget = (RealCloud_EDU_PC_DEMO *)customData;
	E_VideoSrc srcType = videoFrame->desc.srcType;
	if (srcType == VIDEO_SRC_TYPE_CAMERA) {
		widget->getLocalVideoRender()->doRender(videoFrame);
	}
	else if (srcType == VIDEO_SRC_TYPE_SCREEN || srcType == VIDEO_SRC_TYPE_MEDIA)
	{
		widget->getScreenShareRender()->doRender(videoFrame);
	}

}

void RealCloud_EDU_PC_DEMO::onRemoteVideo(const ilive::LiveVideoFrame * videoFrame, void * customData)
{
	qDebug("callback onRemoteVideo ...");
	RealCloud_EDU_PC_DEMO *widget = (RealCloud_EDU_PC_DEMO *)customData;

	E_VideoSrc srcType = videoFrame->desc.srcType;
	if (srcType == VIDEO_SRC_TYPE_CAMERA) {
		widget->getRemoteVideoRender()->doRender(videoFrame);
	}
	else if (srcType == VIDEO_SRC_TYPE_SCREEN || srcType == VIDEO_SRC_TYPE_MEDIA)
	{
		widget->getScreenShareRender()->doRender(videoFrame);
	}
}

void RealCloud_EDU_PC_DEMO::onDeviceOperation(ilive::E_DeviceOperationType oper, int retCode, void * data)
{
	qDebug("callback onDeviceOperation ...");
}

void RealCloud_EDU_PC_DEMO::onForceOffline()
{
	qDebug("callback onForceOffline ...");
	mainWindow->m_loginBtn->setEnabled(true);
	mainWindow->m_logoutBtn->setEnabled(false);
	mainWindow->m_createClassroomBtn->setEnabled(false);
	mainWindow->m_destoryClassroomBtn->setEnabled(false);
	mainWindow->m_joinClassroomBtn->setEnabled(false);
	mainWindow->exitClassRoom();
	emit mainWindow->showMessage(mainWindow->m_userId, QString::fromLocal8Bit("已被强制下线..."));
}

void RealCloud_EDU_PC_DEMO::onNetworkConnect()
{
	qDebug("callback onNetworkConnect ...");
}

void RealCloud_EDU_PC_DEMO::onNetworkDisconn()
{
	qDebug("callback onNetworkDisconn ...");
}

void RealCloud_EDU_PC_DEMO::onLiveVideoDisconnect(int reason, const char * errorinfo, void * data)
{
	mainWindow->m_loginBtn->setEnabled(false);
	mainWindow->m_logoutBtn->setEnabled(false);
	mainWindow->m_createClassroomBtn->setEnabled(true);
	mainWindow->m_destoryClassroomBtn->setEnabled(false);
	mainWindow->m_joinClassroomBtn->setEnabled(true);
	exitClassRoom();
	emit mainWindow->showMessage(mainWindow->m_userId, QString::fromLocal8Bit("房间网络断开 ..."));
}

void RealCloud_EDU_PC_DEMO::onMemStatusChange(ilive::E_EndpointEventId event_id, const ilive::Vector<ilive::String>& ids, void * data)
{
}

void RealCloud_EDU_PC_DEMO::onMemberJoin(const char ** identifier, uint32_t num)
{
}

void RealCloud_EDU_PC_DEMO::onMemberQuit(const char ** identifier, uint32_t num)
{
}

void RealCloud_EDU_PC_DEMO::onClassroomDestroy()
{
	if (m_sdk->GetILive()->isEnterRoom())
	{
		onExitClassroomClicked();
	}
	else
	{
		mainWindow->m_loginBtn->setEnabled(false);
		mainWindow->m_logoutBtn->setEnabled(true);
		mainWindow->m_destoryClassroomBtn->setEnabled(true);
		mainWindow->m_openCameraBtn->setEnabled(false);
		mainWindow->m_closeCameraBtn->setEnabled(false);
		mainWindow->m_openMicBtn->setEnabled(false);
		mainWindow->m_closeMicBtn->setEnabled(false);
		mainWindow->m_openPlayerBtn->setEnabled(false);
		mainWindow->m_closePlayerBtn->setEnabled(false);

		if (m_opt.getIsTeacher())
		{
			mainWindow->m_createClassroomBtn->setEnabled(true);
			mainWindow->m_joinClassroomBtn->setEnabled(true);
			mainWindow->m_exitClassroomBtn->setEnabled(false);
		}
		else
		{
			mainWindow->m_createClassroomBtn->setEnabled(false);
			mainWindow->m_joinClassroomBtn->setEnabled(false);
			mainWindow->m_exitClassroomBtn->setEnabled(true);
		}
	}
	emit showMessage(m_userId, QString::fromLocal8Bit("房间被集散 ..."));
}

void RealCloud_EDU_PC_DEMO::onShareWindow(HWND hwnd)
{
}

void RealCloud_EDU_PC_DEMO::onRecvTextMessage(const char * fromId, const char * msg, TIMConversationType type)
{
}

void RealCloud_EDU_PC_DEMO::onRecvCustomMessage(const char * fromId, const char * msg, TIMConversationType type)
{
}

void RealCloud_EDU_PC_DEMO::onRecvMessage(TIMMessageHandle handle, uint32_t elemCount)
{
}

void RealCloud_EDU_PC_DEMO::onSendWBData(int err, const char * errMsg)
{
}

void RealCloud_EDU_PC_DEMO::onStatusChanged(bool canUndo, bool canRedo, bool canCopy, bool canRemove)
{
}

void RealCloud_EDU_PC_DEMO::onGetBoardData(bool bResult)
{
	updatePage();
}

void RealCloud_EDU_PC_DEMO::onUploadProgress(int percent, void * data)
{
}

void RealCloud_EDU_PC_DEMO::onUploadResult(bool success, int code, std::wstring objName, std::wstring fileName, void * data)
{
	if (success) 
	{
		emit showMessage(m_userId, QString::fromLocal8Bit("上传文件成功 ..."));
		std::wstring fileUrl = m_sdk->getTICWhiteBoardManager()->getDownloadUrl(objName);
		m_sdk->getTICWhiteBoardManager()->getBoardSDK()->setBackgroundImage(m_userId.c_str());
		m_whiteBoardWid->update();
	}
	else 
	{
		emit showMessage(m_userId, QString::fromLocal8Bit("上传文件失败！"));
	}
}

void RealCloud_EDU_PC_DEMO::onFileUploadResult(bool success, std::wstring objName, std::wstring fileName, int pageCount, void * data)
{
	if (success)
	{
		emit showMessage(m_userId, QString::fromLocal8Bit("正在生成文件预览 ..."));
	}
	else
	{
		emit showMessage(m_userId, QString::fromLocal8Bit("生成预览失败！"));
	}
}

void RealCloud_EDU_PC_DEMO::onFileInfoChanged()
{
	emit showMessage(m_userId, QString::fromLocal8Bit("文件内容发生改变 ..."));
}

void RealCloud_EDU_PC_DEMO::onLoginClicked()
{
	liveOperation = LOGIN;
	m_sdk->login(m_userEdit->text().toStdString().c_str(), m_userToken.toStdString().c_str(), onIliveSucCallback, onIliveErrCallback, this);
}

void RealCloud_EDU_PC_DEMO::onLogoutClicked()
{
	liveOperation = LOGOUT;
	m_sdk->logout(onIliveSucCallback, onIliveErrCallback, this);
}

void RealCloud_EDU_PC_DEMO::onCreateClassroomClicked()
{
	liveOperation = CREATE_ROOM;
	int roomId = m_roomEdit->text().toInt();
	m_opt.setRoomID(roomId);
	m_sdk->createClassroom(roomId, onIliveSucCallback, onIliveErrCallback, this);
}

void RealCloud_EDU_PC_DEMO::onDestoryClassroomClicked()
{
	liveOperation = DESTORY_ROOM;
	int roomId = m_roomEdit->text().toInt();
	m_sdk->destroyClassroom(roomId, onIliveSucCallback, onIliveErrCallback, this);
}

void RealCloud_EDU_PC_DEMO::onJoinClassroomClicked()
{
	qDebug("begin join classroom");
	int roomid = m_roomEdit->text().toInt();

	ilive::iLiveRoomOption roomOption;
	roomOption.audioCategory = ilive::AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD;
	roomOption.roomId = roomid;
	roomOption.groupId = m_roomEdit->text().toStdString().c_str();
	roomOption.joinImGroup = true;
	roomOption.authBits = ilive::AUTH_BITS_DEFAULT;
	roomOption.autoRequestCamera = true;
	roomOption.autoRequestScreen = true;
	roomOption.controlRole = "user";
	//roomOption.privateMapKey = rsp.GetPrivMapEncrypt().c_str();
	m_opt.setRoomOption(roomOption);
	m_opt.setRoomID(roomid);

	liveOperation = ENTER_ROOM;
	m_sdk->joinClassroom(m_opt, onIliveSucCallback, onIliveErrCallback, this);
}

void RealCloud_EDU_PC_DEMO::onExitClassroomClicked()
{
	liveOperation = EXIT_ROOM;
	m_sdk->quitClassroom(onIliveSucCallback, onIliveErrCallback, this);
}

void RealCloud_EDU_PC_DEMO::onSendMessageClicked()
{
	QString userId = m_userEdit->text();
	QString text = m_msgTextEdit->toPlainText();
	emit showMessage(userId, text);
}

void RealCloud_EDU_PC_DEMO::onOpenCameraClicked()
{
	m_sdk->enableCamera(true);
	m_openCameraBtn->setEnabled(false);
	m_closeCameraBtn->setEnabled(true);
}

void RealCloud_EDU_PC_DEMO::onCloseCameraClicked()
{
	m_sdk->enableCamera(false);
	m_openCameraBtn->setEnabled(true);
	m_closeCameraBtn->setEnabled(false);
}

void RealCloud_EDU_PC_DEMO::onOpenMicClicked()
{
	m_sdk->enableMic(true);
	m_openMicBtn->setEnabled(false);
	m_closeMicBtn->setEnabled(true);
}

void RealCloud_EDU_PC_DEMO::onCloseMicClicked()
{
	m_sdk->enableMic(false);
	m_openMicBtn->setEnabled(true);
	m_closeMicBtn->setEnabled(false);
}

void RealCloud_EDU_PC_DEMO::onOpenPlayerClicked()
{
	m_sdk->enablePlayer(true);
	m_openPlayerBtn->setEnabled(false);
	m_closePlayerBtn->setEnabled(true);
}

void RealCloud_EDU_PC_DEMO::onClosePlayerClicked()
{
	m_sdk->enablePlayer(false);
	m_openPlayerBtn->setEnabled(true);
	m_closePlayerBtn->setEnabled(false);
}

void RealCloud_EDU_PC_DEMO::onOpenScreenShareClicked()
{
	m_openScreenShareBtn->setEnabled(false);
	m_openScreenShareWndBtn->setEnabled(false);
	m_changeScreenShareBtn->setEnabled(true);
	m_closeScreenShareBtn->setEnabled(true);

	int32 x0 = m_sbX0->value();
	int32 y0 = m_sbY0->value();
	int32 x1 = m_sbX1->value();
	int32 y1 = m_sbY1->value();
	m_sdk->openScreenShare(x0, y0, x1, y1, m_fps);
}

void RealCloud_EDU_PC_DEMO::onOpenScreenShareWndClicked()
{
	m_openScreenShareBtn->setEnabled(false);
	m_openScreenShareWndBtn->setEnabled(false);
	m_changeScreenShareBtn->setEnabled(true);
	m_closeScreenShareBtn->setEnabled(true);
	m_sbX0->setEnabled(false);
	m_sbY0->setEnabled(false);
	m_sbX1->setEnabled(false);
	m_sbY1->setEnabled(false);

	HWND hwnd = WndList::GetSelectWnd();
	m_sdk->openWindowShare(hwnd);
}

void RealCloud_EDU_PC_DEMO::onChangeScreenShareClicked()
{
	int32 x0 = m_sbX0->value();
	int32 y0 = m_sbY0->value();
	int32 x1 = m_sbX1->value();
	int32 y1 = m_sbY1->value();

	int ret = m_sdk->changeScreenShareSize(x0, y0, x1, y1);
	if (ret != NO_ERR)
	{
		emit showMessage(m_userId, QString::fromLocal8Bit("更改分享区域失败"));
		return;
	}
}

void RealCloud_EDU_PC_DEMO::onCloseScreenShareClicked()
{
	m_openScreenShareBtn->setEnabled(true);
	m_openScreenShareWndBtn->setEnabled(true);
	m_changeScreenShareBtn->setEnabled(false);
	m_closeScreenShareBtn->setEnabled(false);

	m_sbX0->setEnabled(true);
	m_sbY0->setEnabled(true);
	m_sbX1->setEnabled(true);
	m_sbY1->setEnabled(true);

	m_sdk->closeScreenShare();
}

void RealCloud_EDU_PC_DEMO::onCreateWhiteBoardClicked()
{
	m_sdk->initWhiteBoard(m_opt.getRoomID(), (HWND)m_whiteBoardContainer->winId());
	HWND hwnd = m_sdk->getTICWhiteBoardManager()->getBoardSDK()->getRenderWindow();
	m_whiteBoardWid = QWidget::createWindowContainer(QWindow::fromWinId((WId)hwnd));
	m_hLayoutWhiteBoard = new QHBoxLayout();
	m_hLayoutWhiteBoard->addWidget(m_whiteBoardWid, 1);
	m_whiteBoardContainer->setLayout(m_hLayoutWhiteBoard);

	m_createWhiteBoardBtn->setEnabled(false);
	m_destoryWhiteBoardBtn->setEnabled(true);

	m_sdk->getTICWhiteBoardManager()->getBoardSDK()->getBoardData();
	m_whiteBoardWid->update();
	m_whiteBoardWid->show();
	// 此处结束的时候，获取到的白板页数是0，必须在onGetBoardData回调函数中才能获取到初始白板的页数
}

void RealCloud_EDU_PC_DEMO::onDestoryWhiteBoardClicked()
{
	m_sdk->getTICWhiteBoardManager()->clearWhiteBoard();
	m_whiteBoardWid->update();
	if (m_hLayoutWhiteBoard != NULL) {
		delete m_hLayoutWhiteBoard;
		m_hLayoutWhiteBoard = NULL;
	}

	m_createWhiteBoardBtn->setEnabled(true);
	m_destoryWhiteBoardBtn->setEnabled(false);
}

void RealCloud_EDU_PC_DEMO::onAddWhiteBoardPageClicked()
{
	m_sdk->getTICWhiteBoardManager()->insertPage();
	updatePage();
}

void RealCloud_EDU_PC_DEMO::onDelWhiteBoardPageClicked()
{
	m_sdk->getTICWhiteBoardManager()->deletePage();
	updatePage();
}

void RealCloud_EDU_PC_DEMO::onClearWhiteBoardPageClicked()
{
	m_sdk->getTICWhiteBoardManager()->getBoardSDK()->clear();
}

void RealCloud_EDU_PC_DEMO::onPrePageClicked()
{
	m_sdk->getTICWhiteBoardManager()->gotoLastPage();
	updatePage();
}

void RealCloud_EDU_PC_DEMO::onNextPageClicked()
{
	m_sdk->getTICWhiteBoardManager()->gotoNextPage();
	updatePage();
}

void RealCloud_EDU_PC_DEMO::onUploadBkFileClicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择背景文件"),
		"", QString::fromLocal8Bit("背景文件(*.png *.jpg *.jpeg *.bmp *.ppt *.pptx *.pdf *.doc)"));
	if (fileName.isEmpty())
	{
		return;
	}

	m_sdk->getTICWhiteBoardManager()->uploadFile(fileName.toStdWString(), nullptr);
}

void RealCloud_EDU_PC_DEMO::addMsgContent(const QString & userId, const QString & msg)
{
	QString str = QString::fromLocal8Bit("%1：%2").arg(userId).arg(msg);
	//QLabel *lbl = new QLabel(str);
	//lbl->setWordWrap(true);
	//lbl->adjustSize();
	//lbl->setAlignment(Qt::AlignTop);
	//lbl->setFixedWidth(400);
	//QListWidgetItem *item = new QListWidgetItem();
	//m_msgListWgt->addItem(item);
	//m_msgListWgt->setItemWidget(item, lbl);

	m_msgListWgt->addItem(str);
}


