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
	// 左侧区域，操作按钮
	QLabel *roomLbl = new QLabel(QString::fromLocal8Bit("房间ID"));
	roomLbl->setFixedHeight(30);

	m_roomEdit = new QLineEdit();
	m_roomEdit->setFixedSize(150, 30);
	m_roomEdit->setText(m_roomId);
	QRegExp regx("[0-9]+$");
	QValidator *validator = new QRegExpValidator(regx);
	m_roomEdit->setValidator(validator);

	QLabel *userLbl = new QLabel(QString::fromLocal8Bit("用户ID："));
	userLbl->setFixedHeight(30);

	m_userEdit = new QLineEdit();
	m_userEdit->setFixedSize(150, 30);
	m_userEdit->setText(m_userId);

	m_loginBtn = new QPushButton(QString::fromLocal8Bit("登陆"));
	m_loginBtn->setFixedSize(100, 30);
	m_loginBtn->setEnabled(true);

	m_logoutBtn = new QPushButton(QString::fromLocal8Bit("登出"));
	m_logoutBtn->setFixedSize(100, 30);
	m_logoutBtn->setEnabled(false);

	m_createClassroomBtn = new QPushButton(QString::fromLocal8Bit("创建房间"));
	m_createClassroomBtn->setFixedSize(100, 30);
	m_createClassroomBtn->setEnabled(false);

	m_destoryClassroomBtn = new QPushButton(QString::fromLocal8Bit("销毁房间"));
	m_destoryClassroomBtn->setFixedSize(100, 30);
	m_destoryClassroomBtn->setEnabled(false);

	m_joinClassroomBtn = new QPushButton(QString::fromLocal8Bit("加入房间"));
	m_joinClassroomBtn->setFixedSize(100, 30);	
	m_joinClassroomBtn->setEnabled(false);

	m_exitClassroomBtn = new QPushButton(QString::fromLocal8Bit("退出房间"));
	m_exitClassroomBtn->setFixedSize(100, 30);
	m_exitClassroomBtn->setEnabled(false);

	QVBoxLayout *vLayout = new QVBoxLayout();
	vLayout->addWidget(roomLbl);
	vLayout->addWidget(m_roomEdit);
	vLayout->addWidget(userLbl);
	vLayout->addWidget(m_userEdit);
	vLayout->addWidget(m_loginBtn);
	vLayout->addWidget(m_logoutBtn);
	vLayout->addWidget(m_createClassroomBtn);
	vLayout->addWidget(m_destoryClassroomBtn);
	vLayout->addWidget(m_joinClassroomBtn);
	vLayout->addWidget(m_exitClassroomBtn);

	// 中间区域，消息显示
	m_msgListWgt = new QListWidget();
	m_msgListWgt->setMinimumWidth(300);
	m_msgListWgt->setStyleSheet("background-color:#99ff99");

	m_msgTextEdit = new QTextEdit();
	m_msgTextEdit->setFixedWidth(300);
	m_msgTextEdit->setFixedHeight(100);
	m_msgTextEdit->setStyleSheet("background-color:white");

	QPushButton *sendMessageBtn = new QPushButton(QString::fromLocal8Bit("发送"));
	sendMessageBtn->setFixedSize(100, 30);

	QVBoxLayout *vLayout1 = new QVBoxLayout();
	vLayout1->addWidget(m_msgListWgt, 1, Qt::AlignmentFlag::AlignHCenter);
	vLayout1->addWidget(m_msgTextEdit, 0, Qt::AlignmentFlag::AlignHCenter);
	vLayout1->addWidget(sendMessageBtn, 0, Qt::AlignmentFlag::AlignHCenter);

	// 右侧区域，视频图像
	m_localVideoRender = new VideoRender();
	m_remoteVideoRender = new VideoRender();

	QVBoxLayout *vLayout2 = new QVBoxLayout();
	vLayout2->addWidget(m_localVideoRender);
	vLayout2->addWidget(m_remoteVideoRender);

	QGridLayout *mainLayout = new QGridLayout();
	mainLayout->addLayout(vLayout, 0, 0);
	mainLayout->addLayout(vLayout1, 0, 1);
	mainLayout->addLayout(vLayout2, 0, 2);

	ui.centralWidget->setLayout(mainLayout);

	// 绑定信号槽
	connect(m_loginBtn, SIGNAL(clicked()), this, SLOT(onLoginBtnClicked()));
	connect(m_logoutBtn, SIGNAL(clicked()), this, SLOT(onLogoutBtnClicked()));
	connect(m_createClassroomBtn, SIGNAL(clicked()), this, SLOT(onCreateClassroomClicked()));
	connect(m_destoryClassroomBtn, SIGNAL(clicked()), this, SLOT(onDestoryClassroomClicked()));
	connect(m_joinClassroomBtn, SIGNAL(clicked()), this, SLOT(onJoinClassroomClicked()));
	connect(m_exitClassroomBtn, SIGNAL(clicked()), this, SLOT(onExitClassroomClicked()));


	connect(this, SIGNAL(showMessage(const QString &, const QString &)), this, SLOT(addMsgContent(const QString &, const QString &)));
	connect(sendMessageBtn, SIGNAL(clicked()), this, SLOT(onSendMessageClicked()));
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

void RealCloud_EDU_PC_DEMO::loadWhiteBoard()
{
}

void RealCloud_EDU_PC_DEMO::enterClassRoom()
{
	m_opt.setIsTeacher(true);
	m_opt.setRoomID(m_roomEdit->text().toInt());

	m_sdk->enableCamera(true);
	m_sdk->enableMic(true);
	m_sdk->enablePlayer(true);
	m_localVideoRender->setView(m_userEdit->text().toStdString().c_str(), ilive::VIDEO_SRC_TYPE_CAMERA);
	m_remoteVideoRender->setView(m_userEdit->text().toStdString().c_str(), ilive::VIDEO_SRC_TYPE_CAMERA);
}

void RealCloud_EDU_PC_DEMO::exitClassRoom()
{

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
		emit mainWindow->showMessage(userId, "login success ...");
		break;
	case LOGOUT:
		mainWindow->m_loginBtn->setEnabled(true);
		mainWindow->m_logoutBtn->setEnabled(false);
		mainWindow->m_createClassroomBtn->setEnabled(false);
		mainWindow->m_destoryClassroomBtn->setEnabled(false);
		mainWindow->m_joinClassroomBtn->setEnabled(false);
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
		mainWindow->enterClassRoom();
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
	ilive::iLiveRoomOption roomOption;
	roomOption.audioCategory = ilive::AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD;
	roomOption.roomId = m_roomEdit->text().toInt();
	roomOption.groupId = m_roomEdit->text().toStdString().c_str();
	roomOption.joinImGroup = true;
	roomOption.authBits = ilive::AUTH_BITS_DEFAULT;
	roomOption.autoRequestCamera = true;
	roomOption.autoRequestScreen = true;
	roomOption.controlRole = "user";
	//roomOption.privateMapKey = rsp.GetPrivMapEncrypt().c_str();
	m_opt.setRoomOption(roomOption);

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

void RealCloud_EDU_PC_DEMO::addMsgContent(const QString & userId, const QString & msg)
{
	m_msgListWgt->addItem(QString::fromLocal8Bit("%1：%2").arg(userId).arg(msg));
}


