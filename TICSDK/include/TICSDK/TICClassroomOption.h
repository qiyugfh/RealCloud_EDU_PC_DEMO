#pragma once
#ifndef TICSDK_CLASSROOM_OPTION_H_
#define TICSDK_CLASSROOM_OPTION_H_
#include "iLive.h"
#include "tim_msg_c.h"
#include "tim_conv_c.h"
#include "tim_c.h"

#ifdef TICSDK_EXPORTS
#define TICSDK_API __declspec(dllexport)
#else
#define TICSDK_API __declspec(dllimport)
#endif

struct ilive::iLiveRoomOption;

/**
* \brief �����¼���������
*/
class IClassroomEventListener
{
public:
	/**
	* \brief ��Ƶ����Ͽ��ص�
	* \param reason		������
	* \param errorinfo	��������
	* \param data		�û��Զ������ݵ�ָ��
	*/
	virtual void onLiveVideoDisconnect(int reason, const char *errorinfo, void* data) {};

	/**
	* \brief ��Ա״̬�ı�ص�
	* \param event_id		�¼�id
	* \param ids		����״̬�仯�ĳ�Աid�б�
	* \param data		�û��Զ������ݵ�ָ��
	*/
	virtual void onMemStatusChange(ilive::E_EndpointEventId event_id, const ilive::Vector<ilive::String> &ids, void* data) {};

	/**
	* \brief ��Ա���뷿��
	* \param identifier		���뷿���Աid�б�
	*/
	virtual void onMemberJoin(const char ** identifier, uint32_t num) {};

	/**
	* \brief ��Ա�˳�����
	* \param identifier		�˳������Աid�б�
	*/
	virtual void onMemberQuit(const char ** identifier, uint32_t num) {};

	/**
	* \brief ���÷��䱻����
	*/
	virtual void onClassroomDestroy() {};

	/**
	* \brief ���ڷ���ѡ��ṹ
	* \param hWnd ��Ҫ����Ĵ��ھ��(NULL��ʾȡ��)
	*/
	virtual void onShareWindow(HWND hwnd) {};

	/**
	* \brief ֪ͨ�װ�״̬�仯
	* \param canUndo	������
	* \param canRedo	��������
	* \param canCopy	������
	* \param canRemove	����ɾ��
	*/
	virtual void onStatusChanged(bool canUndo, bool canRedo, bool canCopy, bool canRemove) {};

	/**
	* \brief ֪ͨ�װ�����ͬ�����
	* \param bResult	ͬ�����
	*/
	virtual void onGetBoardData(bool bResult) = 0;

	/**
	* \brief ֪ͨ�ļ��ϴ�����
	* \param percent	���Ȱ��ٷֱ�
	* \param data		�û��Զ���ָ��
	*/
	virtual void onUploadProgress(int percent, void* data) {};

	/**
	* \brief ֪ͨ�ļ��ϴ����
	* \param success	�ϴ����
	* \param code		������
	* \param objName	cos�ļ���
	* \param fileName	�����ļ���
	* \param data		�û��Զ���ָ��
	*/
	virtual void onUploadResult(bool success, int code, std::wstring objName, std::wstring fileName, void* data) {};

	/**
	* \brief ֪ͨPPT�ļ��ϴ����
	* \param success	�ϴ����
	* \param objName	cos�ļ���
	* \param fileName	�����ļ���
	* \param fileId	    �ļ�Id
	* \param data		�û��Զ���ָ��
	*/
	virtual void onFileUploadResult(bool success, std::wstring objName, std::wstring fileName, int pageCount, void* data) {};

	/**
	* ֪ͨPPT�ļ���Ϣ�����ı䣬�û�Ҫ���»�ȡ�ļ��б�
	*/
	virtual void onFileInfoChanged() {};
};
/**
@brief ����IM��Ϣ��������
*/
class IClassroomIMListener
{
public:
	/**
	* \brief �����ı���Ϣ
	* \param fromId	��Ϣ������
	* \param msg	��Ϣ����
	* \param type	��Ϣ���ͣ�Ⱥ�Ļ��ߵ��ģ�
	*/
	virtual void onRecvTextMessage(const char * fromId, const char * msg, TIMConversationType type) {};

	/**
	* \brief �����Զ�����Ϣ
	* \param fromId	��Ϣ������
	* \param msg	��Ϣ����
	* \param type	��Ϣ���ͣ�Ⱥ�Ļ��ߵ��ģ�
	*/
	virtual void onRecvCustomMessage(const char * fromId, const char * msg, TIMConversationType type) {};

	/**
	* \brief ���յ��ǰװ�ȫ����Ϣ�ص�
	* \param handles	��Ϣ���
	* \param elemCount	Ԫ�ظ���
	*/
	virtual void onRecvMessage(TIMMessageHandle handle, uint32_t elemCount) {};

	/**
	* \brief ������Ϣ�ص�,�ѷ���
	*/
	Deprecated virtual void onSendMsg(int err, const char * errMsg, void* data) {};

	/**
	* \brief ���Ͱװ���Ϣ�ص�
	* \param err	������
	* \param errMsg	��������
	*/
	virtual void onSendWBData(int err, const char * errMsg) {};

};

/**
@brief ���������ͳһʱ��ص�
*/
class IClassroomRecordTimeStampRespCallback
{
public:
	virtual ~IClassroomRecordTimeStampRespCallback(){ }
	/**
	* \brief �û�����sdkͳһʱ��ص�;
	* \param timestamp	����sdk��ͳһʱ��(��λ: ����);
	*/
	virtual void onRecordTimeStamp(int64_t timestamp) = 0;
};

/**
@brief ����¼���¼�����
*/
class IClassroomRecordEventListener
{
public:
	virtual ~IClassroomRecordEventListener() { }

	/**
	* \brief �������ͳһʱ��;���һ�������ڶ�·�û�������Ƶ����¼�ƣ�ҵ�����Ҫʵ�ָ���һ�µ�ʱ��(��ͳһ��ȡ������ʱ��)��
	* \param callback	��ȡͳһʱ���ͨ���˻ص�֪ͨ��sdk;
	*/
	virtual void onRecordTimestampRequest(IClassroomRecordTimeStampRespCallback* callback) {};
};

/**
����������
*/
class TICSDK_API TICClassroomOption
{
public:
	TICClassroomOption();
	~TICClassroomOption();
	/**
	* \brief �ÿ����ڽ�ɫ�Ƿ�Ϊ��ʦ
	*/
	bool getIsTeacher();
	void setIsTeacher(bool bTeacher);

	bool getIsAutoRecord();
	void setIsAutoRecord(bool bAutoRecord);

	/**
	* \brief ���ÿ��÷���ID
	*/
	uint32_t getRoomID();
	void setRoomID(uint32_t roomId);

	/**
	* \brief ���ý��������
	*/
	void setRoomOption(ilive::iLiveRoomOption& opt); 
	ilive::iLiveRoomOption& getRoomOption();

	/**
	* \brief ���ü��������ڲ��¼�
	*/
	void setClassroomEventListener(IClassroomEventListener* listener);
	IClassroomEventListener* getClassroomEventListener() const;

	/**
	* \brief ���ü���������IM��Ϣ
	*/
	void setClassroomIMListener(IClassroomIMListener* listener);
	IClassroomIMListener* getClassroomIMListener() const;

	/**
	* \brief ���ü���¼����Ϣ
	*/
	void setClassroomRecordEventListener(IClassroomRecordEventListener* listener);
	IClassroomRecordEventListener* getClassroomRecordEventListener();
private:
	bool m_enableCamera;
	bool m_enableMic;
	bool m_enablePlayer;
	bool m_bTeacher;
	bool m_autoRecord;
	uint32_t  m_roomId;
	ilive::iLiveRoomOption m_option;

	IClassroomEventListener* m_classroomEventListener;
	IClassroomIMListener* m_classroomIMListener;
	IClassroomRecordEventListener* m_classroomRecordEventListener;
};
#endif
