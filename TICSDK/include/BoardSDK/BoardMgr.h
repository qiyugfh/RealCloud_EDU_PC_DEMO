#pragma once
#include "BoardSDK.h"


class EDUSDK_API BoardMgr
{
public:
	static BoardMgr* GetSDKInstance();

	virtual ~BoardMgr() {};

	/**
	* \brief ��ʼ��SDK����ʼ����װ�SDK�ſ�����
	* \param userID				��ǰ�û�ID
	* \param userSig			�û�ǩ��sig
	* \param sdkappId			sdk appid
	*/
	void init(const char *userID, const char* userSig, int sdkappId);

	/**
	* \brief ��ʼ���װ�SDK
	* \param roomId				����ID
	* \param parentHWnd			�����ھ����Ϊ����װ�û�и�����
	*/
	void initBoardSDK(uint32_t roomId, HWND parentHWnd = nullptr, bool shareMode = false);

	/**
	* \brief ��ðװ�SDKָ��
	* \return �װ�SDKָ��
	*/
	BoardSDK *getBoardSDK();

	/**
	* \brief ���ðװ�SDKָ��
	* \param sdk				�װ�SDKָ��
	*/
	void setBoardSDK(BoardSDK* sdk);

	/**
	* \brief ��հװ�����
	*/
	virtual void clearWhiteBoard() = 0;

	/**
	* \brief ����cos����
	* \param cosAppId	cos appid
	* \param bucket		bucket
	* \param path		�ļ��ϴ�·��
	* \param region	    ԰��
	*/
	virtual void setCosConfig(uint32_t cosAppId, const char* bucket, const char* path, const char* region) = 0;

	/**
	* \brief ����ϴ���ַ
	* \param obj_name cos�ļ���
	*/
	virtual std::wstring getUploadUrl(const std::wstring &obj_name) = 0;

	/**
	* \brief ������ص�ַ
	* \param obj_name cos�ļ���
	*/
	virtual std::wstring getDownloadUrl(const std::wstring &obj_name) = 0;

	/**
	* \brief ���Ԥ����ַ
	* \param obj_name cos�ļ���
	* \param page ҳ��
	*/
	virtual std::wstring getPreviewUrl(const std::wstring &obj_name, int page) = 0;

	/**
	* \brief �ϴ��ļ���cos���������ڲ����˺�
	* \param fileName   �ļ���
	*/
	virtual void uploadFile(const std::wstring& fileName, void* data) = 0;

	/**
	* \brief �ϴ��ļ���cos�������ھɰ�V4
	* \param fileName   �ļ���
	* \param sig			cosǩ��
	*/
	virtual void uploadFile(const std::wstring& fileName, std::string& sig, void* data) = 0;

	/**
	* \brief �ϴ��ļ���cos���������Զ����˺�
	* \param fileName    �ļ���
	* \param secretId    SecretID
	* \param secretKey   SecretKey
	* \param token		 ��ʱtoken
	*/
	virtual void uploadFile(const std::wstring& fileName, std::string& secretId, std::string& secretKey, std::string& token, void* data) = 0;

	/**
	* \brief ��ȡ��ǰҳ��
	* \return ��ǰҳ��
	*/
	virtual uint32_t getPageIndex() = 0;

	/**
	* \brief ��ȡ��ҳ��
	* \return ��ҳ��
	*/
	virtual uint32_t getPageCount() = 0;

	/**
	* \brief ˢ��ҳ��
	*/
	virtual void refreshPageInfo() = 0;

	/**
	* \brief ҳ����ת
	* \param pageIndex  ��ת��ҳ��
	*/
	virtual void gotoPage(uint32_t pageIndex) = 0;

	/**
	* \brief ��ת��һҳ
	*/
	virtual void gotoLastPage() = 0;

	/**
	* \brief ��ת��һҳ
	*/
	virtual void gotoNextPage() = 0;

	/**
	* \brief �����µ�һҳ
	*/
	virtual void insertPage() = 0;

	/**
	* \brief ɾ����ǰҳ
	*/
	virtual void deletePage() = 0;

	/**
	* \brief ���һ��PPT����ҳ�����ɰװ�
	* \return �ļ�id
	* \param urls     һ��PPT���е�url
	* \param fileName PPT�ļ���
	*/
	virtual std::string addFile(std::vector<std::wstring>& urls, const wchar_t * fileName) = 0;

	/**
	* \brief ɾ��һ��PPT�����аװ�����
	* \return �ɹ�����true�����򷵻�false
	* \param fid     PPT�ļ�id
	*/
	virtual bool removeFile(const std::string fid) = 0;

	/**
	* \brief �л���ʾPPT
	* \param fid     PPT�ļ�id
	*/
	virtual void switchFile(std::string fid) = 0;

	/**
	* \brief ��ʼ���װ�����
	*/
	virtual void initBoardsData() = 0;

	/**
	* \brief ����URL���ػ���
	* \param urls	url����
	* \param files	��Ӧ�ļ�����·��
	*/
	void setURLLocalPath(std::vector<std::wstring>& urls, std::vector<std::wstring>& files) const;

	/**
	* \brief ������־·��
	* \param szLogPath				��־·��
	*/
	bool setLogPath(const char* szLogPath) const;

protected:
	BoardSDK *_sdk = nullptr;
};

