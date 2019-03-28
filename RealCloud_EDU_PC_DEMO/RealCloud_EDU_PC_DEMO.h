#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RealCloud_EDU_PC_DEMO.h"

#include "TICSDK.h"
#include "VideoRender.h"


#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QSpinBox>
#include <QTabWidget>
#include <QColor>
#include <QLabel>
#include <QHBoxLayout>


enum LiveOperation
{
	NONE,
	LOGIN,
	LOGOUT,
	CREATE_ROOM,
	DESTORY_ROOM,
	ENTER_ROOM,
	EXIT_ROOM
};

class RealCloud_EDU_PC_DEMO : public QMainWindow, public IClassroomEventListener, public IClassroomIMListener, public IClassroomRecordEventListener
{
	Q_OBJECT

public:
	RealCloud_EDU_PC_DEMO(QWidget *parent = Q_NULLPTR);
	~RealCloud_EDU_PC_DEMO();

	void  enterClassRoom();
	void  exitClassRoom();

	VideoRender *getLocalVideoRender();

	VideoRender *getRemoteVideoRender();

	VideoRender *getScreenShareRender();

private:

	void initLayout();
	void initLeftWidget();
	void initMiddleWidget();
	void initRightWidget();
	void initScreenShareWidget();
	void initWhiteBoardWidget();

	void initParams();
	void bindSlots();


	void onLiveVideoDisconnect(int reason, const char *errorinfo, void* data) override;

	void onMemStatusChange(ilive::E_EndpointEventId event_id, const ilive::Vector<ilive::String> &ids, void* data) override;

	void onMemberJoin(const char ** identifier, uint32_t num) override;

	void onMemberQuit(const char ** identifier, uint32_t num) override;

	void onClassroomDestroy() override;

	void onShareWindow(HWND hwnd) override;

	void onRecvTextMessage(const char * fromId, const char * msg, TIMConversationType type) override;

	void onRecvCustomMessage(const char * fromId, const char * msg, TIMConversationType type) override;

	void onRecvMessage(TIMMessageHandle handle, uint32_t elemCount) override;

	void onSendWBData(int err, const char * errMsg) override;

	void onStatusChanged(bool canUndo, bool canRedo, bool canCopy, bool canRemove) override;

	void onGetBoardData(bool bResult) override;

	void onUploadProgress(int percent, void* data) override;

	void onUploadResult(bool success, int code, std::wstring objName, std::wstring fileName, void* data) override;

	void onFileUploadResult(bool success, std::wstring objName, std::wstring fileName, int pageCount, void* data) override;

	void onFileInfoChanged() override;



private:

	static void onSendTIMMsgSuccess(void* data);

	static void onSendTIMMsgError(int code, const char* desc, void* data);

	static void onIliveSucCallback(void *data);

	static void onIliveErrCallback(const int code, const char *desc, void* data);

	static void onLocalVideo(const ilive::LiveVideoFrame* videoFrame, void* customData);

	static void onRemoteVideo(const ilive::LiveVideoFrame* videoFrame, void* customData);

	static void onDeviceOperation(ilive::E_DeviceOperationType oper, int retCode, void* data);

	static void onForceOffline();

	static void onNetworkConnect();

	static void onNetworkDisconn();




signals:
	// 消息展示
	void showMessage(const QString &userId, const QString &msg);

public slots:

	void addMsgContent(const QString &userId, const QString &msg);

private slots:

	void onLoginBtnClicked();
	void onLogoutBtnClicked();
	void onCreateClassroomClicked();
	void onDestoryClassroomClicked();
	void onJoinClassroomClicked();
	void onExitClassroomClicked();
	void onSendMessageClicked();

	void onOpenCameraClicked();
	void onCloseCameraClicked();
	void onOpenMicClicked();
	void onCloseMicClicked();
	void onOpenPlayerClicked();
	void onClosePlayerClicked();
	
	void onOpenScreenShareClicked();
	void onOpenScreenShareWndClicked();
	void onChangeScreenShareClicked();
	void onCloseScreenShareClicked();

	void onCreateWhiteBoardClicked();
	void onDestoryWhiteBoardClicked();
	void onAddWhiteBoardPageClicked();
	void onDelWhiteBoardPageClicked();
	void onClearWhiteBoardPageClicked();
	void onPrePageClicked();
	void onNextPageClicked();


public:
	// 按钮区域
	QLineEdit *m_roomEdit;
	QLineEdit *m_userEdit;

	QPushButton *m_loginBtn;
	QPushButton *m_logoutBtn;
	QPushButton *m_createClassroomBtn;
	QPushButton *m_destoryClassroomBtn;
	QPushButton *m_joinClassroomBtn;
	QPushButton *m_exitClassroomBtn;
	QPushButton *m_openCameraBtn;
	QPushButton *m_closeCameraBtn;
	QPushButton *m_openMicBtn;
	QPushButton *m_closeMicBtn;
	QPushButton *m_openPlayerBtn;
	QPushButton *m_closePlayerBtn;

	// 通知消息
	QPushButton *m_sendMessageBtn;
	QListWidget *m_msgListWgt;
	QTextEdit *m_msgTextEdit;


	// 屏幕分享
	QPushButton *m_openScreenShareBtn;
	QPushButton *m_openScreenShareWndBtn;
	QPushButton *m_changeScreenShareBtn;
	QPushButton *m_closeScreenShareBtn;

	// 白板操作
	QPushButton *m_createWhiteBoardBtn;
	QPushButton *m_destoryWhiteBoardBtn;
	QPushButton *m_addWhiteBoardBtn;
	QPushButton *m_delWhiteBoardBtn;
	QPushButton *m_clearWhiteBoardBtn;
	QPushButton *m_prePageBtn;
	QPushButton *m_nextPageBtn;
	QColor m_whiteBoardColor;
	QLabel *m_currentPage;
	QPushButton *m_uploadBkPicBtn;

	QTabWidget *m_dispalyTabWidget;


	QSpinBox *m_sbX0;
	QSpinBox *m_sbX1;
	QSpinBox *m_sbY0;
	QSpinBox *m_sbY1;


private:
	Ui::RealCloud_EDU_PC_DEMOClass ui;

	TICManager *m_sdk;
	TICClassroomOption m_opt;

	VideoRender *m_localVideoRender;
	VideoRender *m_remoteVideoRender;
	VideoRender *m_shareVideoRender;
	
	QWidget *m_whiteBoardContainer;
	QWidget *m_whiteBoardWid;
	QHBoxLayout *m_hLayoutWhiteBoard;


	QString m_userId;
	QString m_roomId;
	QString m_userToken;
	QString m_sdkappId;

	QWidget *m_leftPannelWidget;
	QWidget *m_middlePannelWidget;
	QWidget *m_rightPannelWidget;
	QWidget *m_shareVideoWgt;
	QWidget *m_whiteBoardWgt;
	uint32 m_fps;
};
