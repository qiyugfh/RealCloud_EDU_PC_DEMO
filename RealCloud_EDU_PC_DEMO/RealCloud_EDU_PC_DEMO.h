#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RealCloud_EDU_PC_DEMO.h"

#include "TICSDK.h"


class RealCloud_EDU_PC_DEMO : public QMainWindow, public IClassroomEventListener, public IClassroomIMListener, public IClassroomRecordEventListener
{
	Q_OBJECT

public:
	RealCloud_EDU_PC_DEMO(QWidget *parent = Q_NULLPTR);

	void  loadWhiteBoard();
	void  enterClassRoom();
	void  exitClassRoom();


private:

	static void onSendTIMMsgSuccess(void* data);

	static void onSendTIMMsgError(int code, const char* desc, void* data);

	static void onIliveSucCallback(void *data);

	static void onIliveErrCallback(const int code, const char *desc, void* data);

	static void onLocalVideo(const ilive::LiveVideoFrame* videoFrame, void* customData);

	static void onDeviceOperation(ilive::E_DeviceOperationType oper, int retCode, void* data);

	static void onForceOffline();

	static void onNetworkConnect();

	static void onNetworkDisconn();


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
	Ui::RealCloud_EDU_PC_DEMOClass ui;

	TICManager *m_sdk;
	TICClassroomOption m_opt;
	ilive::iLiveRootView*	m_pRootView;
	QString m_sdkappId;
	QString m_userId;
	QString m_userToken;
	QString m_roomId;
};
