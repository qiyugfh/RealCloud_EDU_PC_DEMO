#pragma once
#include "BoardSDK.h"


class EDUSDK_API BoardMgr
{
public:
	static BoardMgr* GetSDKInstance();

	virtual ~BoardMgr() {};

	/**
	* \brief 初始化SDK，初始化后白板SDK才可以用
	* \param userID				当前用户ID
	* \param userSig			用户签名sig
	* \param sdkappId			sdk appid
	*/
	void init(const char *userID, const char* userSig, int sdkappId);

	/**
	* \brief 初始化白板SDK
	* \param roomId				房间ID
	* \param parentHWnd			父窗口句柄，为空则白板没有父窗口
	*/
	void initBoardSDK(uint32_t roomId, HWND parentHWnd = nullptr, bool shareMode = false);

	/**
	* \brief 获得白板SDK指针
	* \return 白板SDK指针
	*/
	BoardSDK *getBoardSDK();

	/**
	* \brief 设置白板SDK指针
	* \param sdk				白板SDK指针
	*/
	void setBoardSDK(BoardSDK* sdk);

	/**
	* \brief 清空白板数据
	*/
	virtual void clearWhiteBoard() = 0;

	/**
	* \brief 设置cos参数
	* \param cosAppId	cos appid
	* \param bucket		bucket
	* \param path		文件上传路径
	* \param region	    园区
	*/
	virtual void setCosConfig(uint32_t cosAppId, const char* bucket, const char* path, const char* region) = 0;

	/**
	* \brief 获得上传地址
	* \param obj_name cos文件名
	*/
	virtual std::wstring getUploadUrl(const std::wstring &obj_name) = 0;

	/**
	* \brief 获得下载地址
	* \param obj_name cos文件名
	*/
	virtual std::wstring getDownloadUrl(const std::wstring &obj_name) = 0;

	/**
	* \brief 获得预览地址
	* \param obj_name cos文件名
	* \param page 页码
	*/
	virtual std::wstring getPreviewUrl(const std::wstring &obj_name, int page) = 0;

	/**
	* \brief 上传文件到cos，适用于内部大账号
	* \param fileName   文件名
	*/
	virtual void uploadFile(const std::wstring& fileName, void* data) = 0;

	/**
	* \brief 上传文件到cos，适用于旧版V4
	* \param fileName   文件名
	* \param sig			cos签名
	*/
	virtual void uploadFile(const std::wstring& fileName, std::string& sig, void* data) = 0;

	/**
	* \brief 上传文件到cos，适用于自定义账号
	* \param fileName    文件名
	* \param secretId    SecretID
	* \param secretKey   SecretKey
	* \param token		 临时token
	*/
	virtual void uploadFile(const std::wstring& fileName, std::string& secretId, std::string& secretKey, std::string& token, void* data) = 0;

	/**
	* \brief 获取当前页码
	* \return 当前页码
	*/
	virtual uint32_t getPageIndex() = 0;

	/**
	* \brief 获取总页数
	* \return 总页数
	*/
	virtual uint32_t getPageCount() = 0;

	/**
	* \brief 刷新页码
	*/
	virtual void refreshPageInfo() = 0;

	/**
	* \brief 页码跳转
	* \param pageIndex  跳转的页码
	*/
	virtual void gotoPage(uint32_t pageIndex) = 0;

	/**
	* \brief 跳转上一页
	*/
	virtual void gotoLastPage() = 0;

	/**
	* \brief 跳转下一页
	*/
	virtual void gotoNextPage() = 0;

	/**
	* \brief 插入新的一页
	*/
	virtual void insertPage() = 0;

	/**
	* \brief 删除当前页
	*/
	virtual void deletePage() = 0;

	/**
	* \brief 添加一个PPT所有页并生成白板
	* \return 文件id
	* \param urls     一个PPT所有的url
	* \param fileName PPT文件名
	*/
	virtual std::string addFile(std::vector<std::wstring>& urls, const wchar_t * fileName) = 0;

	/**
	* \brief 删除一个PPT下所有白板数据
	* \return 成功返回true，否则返回false
	* \param fid     PPT文件id
	*/
	virtual bool removeFile(const std::string fid) = 0;

	/**
	* \brief 切换显示PPT
	* \param fid     PPT文件id
	*/
	virtual void switchFile(std::string fid) = 0;

	/**
	* \brief 初始化白板数据
	*/
	virtual void initBoardsData() = 0;

	/**
	* \brief 设置URL本地缓存
	* \param urls	url数组
	* \param files	对应文件绝对路径
	*/
	void setURLLocalPath(std::vector<std::wstring>& urls, std::vector<std::wstring>& files) const;

	/**
	* \brief 设置日志路径
	* \param szLogPath				日志路径
	*/
	bool setLogPath(const char* szLogPath) const;

protected:
	BoardSDK *_sdk = nullptr;
};

