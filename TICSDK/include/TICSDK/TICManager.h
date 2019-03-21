#pragma once
#ifndef TICSDK_MANAGER_H_
#define TICSDK_MANAGER_H_

#ifdef TICSDK_EXPORTS
#define TICSDK_API __declspec(dllexport)
#else
#define TICSDK_API __declspec(dllimport)
#endif

#include "BoardMgr.h"
#include "TICClassroomOption.h"

/**
@brief �����л�����
*/
enum TICRecordSwitchContent
{
	TICREC_WHITE_BOARD,		///< �л����װ�
	TICREC_SCREEN_SHARE,	///< �л�����Ļ����
	TICREC_MEDIA_PLAY,		///< �л����ļ�����
};

class TICSDK_API TICManager
{
public:

	/**
	@brief ��ȡTICManagerʵ��ָ��
	@return TICManagerָ��
	*/
	static TICManager* GetTICManager();

	/**
	@brief ��ȡ�汾��
	@return �汾��
	*/
	static const char* GetVersion();

	/**
	@brief ��ʼ��TICSDK
	@param iLiveSDKAppId ��Ѷ�ƿ���̨ע���Ӧ��ID
	@return ��ʼ�������0����ɹ�����������ʧ��
	*/
	virtual int initSDK(int iLiveSDKAppId) = 0;

	/**
	@brief ����ʼ��TICSDK
	*/
	virtual void uninitSDK() = 0;

	/**
	* \brief ��¼iliveSDK
	* \param id �û�ID
	* \param sig �û�ǩ��
	* \param success ��¼�ɹ��ص�
	* \param err		��¼����ص�
	* \param data   �û��Զ�������
	* \return �����0��ʾ�ɹ�
	*/
	virtual int login(const char * id, const char * userSig, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief ��¼iliveSDK
	* \param id �û�ID
	* \param sig �û�ǩ��
	* \param spearCfg spear���ã����https://github.com/zhaoyang21cn/iLiveSDK_PC_Suixinbo/blob/master/doc/customSpearCfg.md;
	* \param success  ��¼�ɹ��ص�
	* \param err		��¼����ص�
	* \param data   �û��Զ�������
	* \return �����0��ʾ�ɹ�
	*/
	virtual int loginWithSpear(const char * id, const char * userSig, const char* spearCfg, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief �ǳ�iliveSDK
	* \param success �ɹ��ص�
	* \param err ����ص�
	* \param data   �û��Զ�������
	*/
	virtual void logout(ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief ��ȡiliveSDKʵ��ָ��
	* \return iliveSDKָ��
	*/
	virtual ilive::iLive* GetILive() = 0;

	/**
	* \brief ��������
	* \param roomID ���÷���ID
	* \param success ������óɹ��ص�
	* \param err �������ʧ�ܻص�
	* \param data   �û��Զ�������
	*/
	virtual void createClassroom(uint32_t roomID, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief �������
	* \param opt �������������
	* \param success ������óɹ��ص�
	* \param err �������ʧ�ܻص�
	* \param data   �û��Զ�������
	*/
	virtual void joinClassroom(TICClassroomOption& opt, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief �˳�����
	* \param success �˳����óɹ��ص�
	* \param err �˳�����ʧ�ܻص�
	* \param data   �û��Զ�������
	*/
	virtual void quitClassroom(ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief ��ʦ���ٿ���
	* \param roomID  ����ID
	* \param success ���ٿ��óɹ��ص�
	* \param err ���ٿ���ʧ�ܻص�
	* \param data   �û��Զ�������
	*/
	virtual void destroyClassroom(uint32_t roomID, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	@brief ��ʼ���װ�SDK���ڼ��뷿��֮��
	@param id �û�id
	@param parentHWnd �װ常���ھ��
	@return �����0��ʾ�ɹ�
	*/
	virtual int initWhiteBoard(uint32_t roomId, HWND parentHWnd = nullptr, bool shareMode = false) = 0;

	/**
	@brief ��ȡ�װ������ʵ��ָ��
	@return �װ������ָ��
	*/
	virtual BoardMgr* getTICWhiteBoardManager() = 0;
	
	/**
	* \brief ��/�ر�����ͷ
	* \param enable   true����Ĭ������ͷ��false���ر�
	*/
	virtual void enableCamera(bool bEnable) = 0;

	/**
	* \brief �������ͷ�б�
	* \param cameraList ���ػ�ȡ��������ͷ�б�,��һ��(����0)ΪϵͳĬ���豸;
	* \return �����룬0��ʾ�ɹ�
	*/
	virtual int getCameraList(ilive::Vector< ilive::Pair<ilive::String/*id*/, ilive::String/*name*/> >& cameraList) = 0;

	/**
	* \brief �л�����ͷ
	* \param cameraId   ����ͷ�豸��ʶ
	*/
	virtual void switchCamera(const char* cameraId) = 0;

	/**
	* \brief ��/�ر���˷�
	* \param enable   true����Ĭ����˷磻false���ر�
	*/
	virtual void enableMic(bool bEnable) = 0;

	/**
	* \brief �����˷��б�
	* \param micList ���ػ�ȡ������˷��б�,��һ��(����0)ΪϵͳĬ���豸;
	* \return �����룬0��ʾ�ɹ�
	*/
	virtual int getMicList(ilive::Vector< ilive::Pair<ilive::String/*id*/, ilive::String/*name*/> >& micList) = 0;

	/**
	* \brief �л���˷�
	* \param deviceID   ��˷��豸��ʶ
	*/
	virtual void switchMic(const char* deviceID) = 0;

	/**
	* \brief ��/�ر�������
	* \param enable   true����Ĭ����������false���ر�
	*/
	virtual void enablePlayer(bool bEnable) = 0;

	/**
	* \brief ����������б�
	* \param micList ���ػ�ȡ�����������б�,��һ��(����0)ΪϵͳĬ���豸;
	* \return �����룬0��ʾ�ɹ�
	*/
	virtual int getPlayerList(ilive::Vector< ilive::Pair<ilive::String/*id*/, ilive::String/*name*/> >& playerList) = 0;

	/**
	* \brief �л�������
	* \param deviceID   �������豸��ʶ
	*/
	virtual void switchPlayer(const char* deviceID) = 0;

	/**
	* \brief ���ñ�����ƵԤ���ص�
	* \param OnLocalVideo   �ص������ӿ�
	* \param data   �û��Զ�������
	*/
	virtual void setLocalVideoCallBack(ilive::iLivePreviewCallback OnLocalVideo, void* data = nullptr) = 0;

	/**
	* \brief ����Զ����Ƶ���ݽ���
	* \param OnRemoteVideo   �ص������ӿ�
	* \param data   �û��Զ�������
	*/
	virtual void setRemoteVideoCallBack(ilive::iLivePreviewCallback OnRemoteVideo, void* data = nullptr) = 0;

	/**
	* \brief �����豸�����ص�
	* \param OnDeviceOperation   �ص������ӿ�
	* \param data   �û��Զ�������
	*/
	virtual void setDeviceOperationCallback(ilive::iLiveDeviceOperationCallback OnDeviceOperation, void* data = nullptr) = 0;

	/**
	* \brief ���ñ������߻ص�
	* \param OnForceOffline   �ص������ӿ�
	*/
	virtual void setForceOfflineCallback(ilive::ForceOfflineCallback OnForceOffline) = 0;

	/**
	* \brief ��������״̬�����ص�
	* \param onConn		 �����ɹ��ص�
	* \param onDisconn   �Ͽ����ӻص�
	*/
	virtual void setNetworkConnCallBack(ilive::onNetworkCallback onConn, ilive::onNetworkCallback onDisconn) = 0;

	/**
	* \brief ����Ļ����(ָ������)
	* \param hWnd ��Ҫ����Ĵ��ھ��(NULL��ʾȫ��)
	* \param fps ����֡��
	*/
	virtual void openScreenShare(HWND hWnd, uint32& fps) = 0;

	/**
	* \brief �򿪴��ڷ���(ָ������ץȡ������֧��OpenGL)
	* \return ��0��ʾʧ�ܣ�0��ʾ�ɹ�
	*/
	virtual int openWindowShare() = 0;

	/**
	* \brief �򿪴��ڷ���(���봰�ھ��������֧��OpenGL)
	*/
	virtual void openWindowShare(HWND hwnd) = 0;

	/**
	* \brief �رմ��ڹ���
	*/
	virtual void closeWindowShare() = 0;

	/**
	* \brief ����Ļ����(ָ������)
	* \param left/top/right/bottom ��Ҫ������Ļ�������������Ͻ�����(left, top)�����½�����(right, bottom)
	* \param fps ����֡��
	*/
	virtual void openScreenShare(int32& left, int32& top, int32& right, int32& bottom, uint32& fps) = 0;

	/**
	* \brief ��̬�޸���Ļ���������
	* \param left/top/right/bottom ��Ҫ������Ļ�������������Ͻ�����(left, top)�����½�����(right, bottom)
	* \param fps ����֡��
	*/
	virtual int changeScreenShareSize(int32& left, int32& top, int32& right, int32& bottom) = 0;

	/**
	* \brief �ر���Ļ����
	*/
	virtual void closeScreenShare() = 0;

	/**
	* \brief ������־·��
	* \param szLogPath				��־·��
	*/
	virtual void setLogPath(const char* szLogPath) = 0;

	/**
	* \brief �����ı���Ϣ
	* \param userId   ��Ϣ�����ߣ���գ�null����""��ʾ����Ⱥ��Ϣ��
	* \param msg	  ��������
	* \param data	  �û��Զ�������
	*/
	virtual void sendTextMessage(const char * userId, const char * msg, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief �����Զ�����Ϣ
	* \param userId   ��Ϣ�����ߣ���գ�null����""��ʾ����Ⱥ��Ϣ��
	* \param msg	  ��������
	* \param data	  �û��Զ�������
	*/
	virtual void sendCustomMessage(const char * userId, const char * msg, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief ������Ϣ(��������)
	* \param type	  ��Ϣ����
	* \param userId   ��Ϣ������
	* \param msg	  ��Ϣ����
	* \param data	  �û��Զ�������
	*/
	virtual void sendMessage(TIMConversationType type, const char * userId, TIMConversationHandle msg, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;
};

#endif

