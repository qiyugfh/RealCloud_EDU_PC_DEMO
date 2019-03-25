#include "RealCloud_EDU_PC_DEMO.h"
#include <qDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#define USER_TOKEN_1 "eJxNjttOg0AQht*Fa2P3ACyY9AIainJQW23FpslmhYWsRorLQrHGd3dLaOLcTPJ9M-PPj-GcPF2zPD90taLqu*HG" \
		"jQGMqxGLgtdKlIJLDbuWS1FQCHS52MIOdimcBlnTaMUUxbL4t98WH3RUmkETAIiIbpPkQyMkp6xU43mIXFtfnmTPZSsOteYIQAs" \
		"ifE69SCU*z19Cy0IuIQg4lzhRaZwGq8Wdx2LzNlQ57vYzssjv2Zdg*1nwtqzi5MXc9LvSrvxsjUhuBydPeLEfpVE6ZM5QbKLd6-" \
		"LYP4SP8n1Nsl6a2yI5hTCVBPvb-jifG79-HqRbbw__"

LiveOperation RealCloud_EDU_PC_DEMO::m_liveOperation = NONE;


static RealCloud_EDU_PC_DEMO *mainWindow = NULL;

RealCloud_EDU_PC_DEMO::RealCloud_EDU_PC_DEMO(QWidget *parent)
	: QMainWindow(parent), m_sdkappId("1400127140"), m_userId("userid_100009353839_1"),
	m_userToken(USER_TOKEN_1),
	m_roomId("2147483640")
{
	ui.setupUi(this);

	mainWindow = this;
	qDebug("init mainwindow ...");

	QPushButton *loginBtn = new QPushButton(QString::fromLocal8Bit("登陆"));
	QPushButton *joinClassroomBtn = new QPushButton(QString::fromLocal8Bit("加入房间"));
	connect(loginBtn, SIGNAL(clicked()), this, SLOT(onLoginBtnClicked()));
	connect(joinClassroomBtn, SIGNAL(clicked()), this, SLOT(onJoinClassroomClicked()));

	QHBoxLayout *hLayout = new QHBoxLayout();
	hLayout->addWidget(loginBtn);
	hLayout->addWidget(joinClassroomBtn);
	loginBtn->setFixedSize(100, 30);
	joinClassroomBtn->setFixedSize(100, 30);


	QHBoxLayout *hLayout2 = new QHBoxLayout();
	m_videoRender = new VideoRender();
	m_remoteVideoRender = new VideoRender();
	hLayout2->addWidget(m_videoRender);
	hLayout2->addWidget(m_remoteVideoRender);

	QVBoxLayout *vLayout = new QVBoxLayout(ui.centralWidget);
	vLayout->addLayout(hLayout);
	vLayout->addLayout(hLayout2);

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

	m_opt.setIsTeacher(false);
	m_opt.setRoomID(m_roomId.toInt());

}


RealCloud_EDU_PC_DEMO::~RealCloud_EDU_PC_DEMO()
{

}

void RealCloud_EDU_PC_DEMO::loadWhiteBoard()
{
}

void RealCloud_EDU_PC_DEMO::enterClassRoom()
{
	m_sdk->enableCamera(true);
	m_sdk->enableMic(true);
	m_sdk->enablePlayer(true);
	m_videoRender->setView(m_userId.toStdString().c_str(), ilive::VIDEO_SRC_TYPE_CAMERA);
	m_remoteVideoRender->setView(m_userId.toStdString().c_str(), ilive::VIDEO_SRC_TYPE_CAMERA);
}

void RealCloud_EDU_PC_DEMO::exitClassRoom()
{
}

VideoRender * RealCloud_EDU_PC_DEMO::getLocalVideoRender()
{
	return m_videoRender;
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

	switch (m_liveOperation)
	{
	case ENTER_ROOM:
		mainWindow->enterClassRoom();
		break;
	default:
		break;
	}

}

void RealCloud_EDU_PC_DEMO::onIliveErrCallback(const int code, const char * desc, void * data)
{
	qDebug("callback onIliveErrCallback ...");
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
{	// 登陆
	int ret = -1;
	m_liveOperation = LOGIN;
	ret = m_sdk->login(m_userId.toStdString().c_str(), m_userToken.toStdString().c_str(), onIliveSucCallback, onIliveErrCallback, this);
	if (ret != 0)
	{
		qDebug("login fail ...");
		return;
	}
	qDebug("login success ...");
}

void RealCloud_EDU_PC_DEMO::onJoinClassroomClicked()
{
	qDebug("begin join classroom");
	ilive::iLiveRoomOption roomOption;
	roomOption.audioCategory = ilive::AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD;
	roomOption.roomId = m_roomId.toInt();
	roomOption.groupId = m_roomId.toStdString().c_str();
	roomOption.joinImGroup = true;
	roomOption.authBits = ilive::AUTH_BITS_DEFAULT;
	roomOption.autoRequestCamera = true;
	roomOption.autoRequestScreen = true;
	roomOption.controlRole = "user";
	//roomOption.privateMapKey = rsp.GetPrivMapEncrypt().c_str();
	m_opt.setRoomOption(roomOption);

	m_liveOperation = ENTER_ROOM;
	m_sdk->joinClassroom(m_opt, onIliveSucCallback, onIliveErrCallback, this);
}
