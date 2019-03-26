#include "RealCloud_EDU_PC_DEMO.h"
#include <qDebug>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRegExp>
#include <QValidator>


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
	m_roomId("2147483640")
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

}

void RealCloud_EDU_PC_DEMO::initLayout()
{
	// 左侧区域，控制按钮
	initLeftWidget();

	// 中间区域，消息显示
	m_msgListWgt = new QListWidget();
	m_msgListWgt->setMinimumWidth(600);
	m_msgListWgt->setStyleSheet("background-color:#99ff99");

	m_msgTextEdit = new QTextEdit();
	m_msgTextEdit->setFixedWidth(600);
	m_msgTextEdit->setFixedHeight(100);
	m_msgTextEdit->setStyleSheet("background-color:white");

	m_sendMessageBtn = new QPushButton(QString::fromLocal8Bit("发送"));
	m_sendMessageBtn->setFixedSize(100, 30);

	QVBoxLayout *vLayout1 = new QVBoxLayout();
	vLayout1->addWidget(m_msgListWgt, 1, Qt::AlignmentFlag::AlignHCenter);
	vLayout1->addWidget(m_msgTextEdit, 0, Qt::AlignmentFlag::AlignHCenter);
	vLayout1->addWidget(m_sendMessageBtn, 0, Qt::AlignmentFlag::AlignHCenter);

	// 右侧区域，视频图像
	m_localVideoRender = new VideoRender();
	m_remoteVideoRender = new VideoRender();

	QVBoxLayout *vLayout2 = new QVBoxLayout();
	vLayout2->addWidget(m_localVideoRender);
	vLayout2->addWidget(m_remoteVideoRender);

	QGridLayout *mainLayout = new QGridLayout();
	mainLayout->addWidget(m_leftPannelWidget, 0, 0);
	mainLayout->addLayout(vLayout1, 0, 1);
	mainLayout->addLayout(vLayout2, 0, 2);

	ui.centralWidget->setLayout(mainLayout);

	// 绑定信号槽
	bindSlots();
}

void RealCloud_EDU_PC_DEMO::initLeftWidget()
{
	m_leftPannelWidget = new QWidget();
	m_leftPannelWidget->setFixedWidth(400);

	QLabel *roomLbl = new QLabel(QString::fromLocal8Bit("房间ID："));

	m_roomEdit = new QLineEdit();
	m_roomEdit->setMinimumWidth(280);

	QRegExp regx("[0-9]+$");
	QValidator *validator = new QRegExpValidator(regx);
	m_roomEdit->setValidator(validator);
	m_roomEdit->setText(m_roomId);

	QHBoxLayout *hLayout1 = new QHBoxLayout();
	hLayout1->addWidget(roomLbl, 0);
	hLayout1->addWidget(m_roomEdit, 1);

	QLabel *userLbl = new QLabel(QString::fromLocal8Bit("用户ID："));

	m_userEdit = new QLineEdit();
	m_userEdit->setMinimumWidth(280);
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
	gridLayout->addLayout(hLayout1, 0, 0);
	gridLayout->addLayout(hLayout2, 1, 0);
	gridLayout->addWidget(m_loginBtn, 2, 0);
	gridLayout->addWidget(m_logoutBtn, 2, 1);
	gridLayout->addWidget(m_createClassroomBtn, 3, 0);
	gridLayout->addWidget(m_destoryClassroomBtn, 3, 1);
	gridLayout->addWidget(m_joinClassroomBtn, 4, 0);
	gridLayout->addWidget(m_exitClassroomBtn, 4, 1);
	gridLayout->addWidget(m_openCameraBtn, 5, 0);
	gridLayout->addWidget(m_closeCameraBtn, 5, 1);
	gridLayout->addWidget(m_openMicBtn, 6, 0);
	gridLayout->addWidget(m_closeMicBtn, 6, 1);
	gridLayout->addWidget(m_openPlayerBtn, 7, 0);
	gridLayout->addWidget(m_closePlayerBtn, 7, 1);

	gridLayout->setColumnMinimumWidth(0, 200);
	gridLayout->setColumnMinimumWidth(1, 200);
	m_leftPannelWidget->setLayout(gridLayout);
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


}

void RealCloud_EDU_PC_DEMO::bindSlots()
{
	connect(m_loginBtn, SIGNAL(clicked()), this, SLOT(onLoginBtnClicked()));
	connect(m_logoutBtn, SIGNAL(clicked()), this, SLOT(onLogoutBtnClicked()));
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
}

void RealCloud_EDU_PC_DEMO::loadWhiteBoard()
{
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

		emit mainWindow->showMessage(userId, "login success ...");
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

		emit mainWindow->showMessage(userId, "logout success ...");
		break;
	case CREATE_ROOM:
		emit mainWindow->showMessage(userId, "create room success ...");
		break;
	case DESTORY_ROOM:
		emit mainWindow->showMessage(userId, "destory room success ...");
		break;
	case ENTER_ROOM:
		mainWindow->m_joinClassroomBtn->setEnabled(false);
		mainWindow->m_exitClassroomBtn->setEnabled(true);
		emit mainWindow->showMessage(userId, "enter room success ...");
		mainWindow->enterClassRoom();
		break;
	case EXIT_ROOM:
		mainWindow->m_joinClassroomBtn->setEnabled(true);
		mainWindow->m_exitClassroomBtn->setEnabled(false);
		emit mainWindow->showMessage(userId, "exit room success ...");
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
	QString msg = QString("code:%1, desc:%2").arg(code).arg(desc);
	switch (liveOperation)
	{
	case LOGIN:
		emit mainWindow->showMessage(userId, QString("login fail: %1").arg(msg));
		break;
	case LOGOUT:
		emit mainWindow->showMessage(userId, QString("logout fail: %1").arg(msg));
		break;
	case CREATE_ROOM:
		emit mainWindow->showMessage(userId, QString("create room fail: %1").arg(msg));
		break;
	case DESTORY_ROOM:
		emit mainWindow->showMessage(userId, QString("%1 destory room fail: %1").arg(msg));
		break;
	case ENTER_ROOM:
		emit mainWindow->showMessage(userId, QString("%1 enter room fail: %1").arg(msg));
		break;
	case EXIT_ROOM:
		emit mainWindow->showMessage(userId, QString("%1 exit room fail: %1").arg(msg));
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
	widget->getLocalVideoRender()->doRender(videoFrame);

}

void RealCloud_EDU_PC_DEMO::onRemoteVideo(const ilive::LiveVideoFrame * videoFrame, void * customData)
{
	qDebug("callback onLocalVideo ...");
	RealCloud_EDU_PC_DEMO *widget = (RealCloud_EDU_PC_DEMO *)customData;

	E_VideoSrc srcType = videoFrame->desc.srcType;
	widget->getRemoteVideoRender()->doRender(videoFrame);
}

void RealCloud_EDU_PC_DEMO::onDeviceOperation(ilive::E_DeviceOperationType oper, int retCode, void * data)
{
	qDebug("callback onDeviceOperation ...");
}

void RealCloud_EDU_PC_DEMO::onForceOffline()
{
	qDebug("callback onForceOffline ...");
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
}

void RealCloud_EDU_PC_DEMO::onUploadProgress(int percent, void * data)
{
}

void RealCloud_EDU_PC_DEMO::onUploadResult(bool success, int code, std::wstring objName, std::wstring fileName, void * data)
{
}

void RealCloud_EDU_PC_DEMO::onFileUploadResult(bool success, std::wstring objName, std::wstring fileName, int pageCount, void * data)
{
}

void RealCloud_EDU_PC_DEMO::onFileInfoChanged()
{
}

void RealCloud_EDU_PC_DEMO::onLoginBtnClicked()
{
	liveOperation = LOGIN;
	m_sdk->login(m_userEdit->text().toStdString().c_str(), m_userToken.toStdString().c_str(), onIliveSucCallback, onIliveErrCallback, this);
}

void RealCloud_EDU_PC_DEMO::onLogoutBtnClicked()
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


