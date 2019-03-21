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
@brief 内容切换类型
*/
enum TICRecordSwitchContent
{
	TICREC_WHITE_BOARD,		///< 切换到白板
	TICREC_SCREEN_SHARE,	///< 切换到屏幕分享
	TICREC_MEDIA_PLAY,		///< 切换到文件播放
};

class TICSDK_API TICManager
{
public:

	/**
	@brief 获取TICManager实例指针
	@return TICManager指针
	*/
	static TICManager* GetTICManager();

	/**
	@brief 获取版本号
	@return 版本号
	*/
	static const char* GetVersion();

	/**
	@brief 初始化TICSDK
	@param iLiveSDKAppId 腾讯云控制台注册的应用ID
	@return 初始化结果，0代表成功，其他代表失败
	*/
	virtual int initSDK(int iLiveSDKAppId) = 0;

	/**
	@brief 反初始化TICSDK
	*/
	virtual void uninitSDK() = 0;

	/**
	* \brief 登录iliveSDK
	* \param id 用户ID
	* \param sig 用户签名
	* \param success 登录成功回调
	* \param err		登录错误回调
	* \param data   用户自定义数据
	* \return 结果，0表示成功
	*/
	virtual int login(const char * id, const char * userSig, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief 登录iliveSDK
	* \param id 用户ID
	* \param sig 用户签名
	* \param spearCfg spear配置，详见https://github.com/zhaoyang21cn/iLiveSDK_PC_Suixinbo/blob/master/doc/customSpearCfg.md;
	* \param success  登录成功回调
	* \param err		登录错误回调
	* \param data   用户自定义数据
	* \return 结果，0表示成功
	*/
	virtual int loginWithSpear(const char * id, const char * userSig, const char* spearCfg, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief 登出iliveSDK
	* \param success 成功回调
	* \param err 错误回调
	* \param data   用户自定义数据
	*/
	virtual void logout(ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief 获取iliveSDK实例指针
	* \return iliveSDK指针
	*/
	virtual ilive::iLive* GetILive() = 0;

	/**
	* \brief 创建课堂
	* \param roomID 课堂房间ID
	* \param success 加入课堂成功回调
	* \param err 加入课堂失败回调
	* \param data   用户自定义数据
	*/
	virtual void createClassroom(uint32_t roomID, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief 加入课堂
	* \param opt 课堂配置类对象
	* \param success 加入课堂成功回调
	* \param err 加入课堂失败回调
	* \param data   用户自定义数据
	*/
	virtual void joinClassroom(TICClassroomOption& opt, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief 退出课堂
	* \param success 退出课堂成功回调
	* \param err 退出课堂失败回调
	* \param data   用户自定义数据
	*/
	virtual void quitClassroom(ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief 老师销毁课堂
	* \param roomID  房间ID
	* \param success 销毁课堂成功回调
	* \param err 销毁课堂失败回调
	* \param data   用户自定义数据
	*/
	virtual void destroyClassroom(uint32_t roomID, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	@brief 初始化白板SDK，在加入房间之后
	@param id 用户id
	@param parentHWnd 白板父窗口句柄
	@return 结果，0表示成功
	*/
	virtual int initWhiteBoard(uint32_t roomId, HWND parentHWnd = nullptr, bool shareMode = false) = 0;

	/**
	@brief 获取白板管理类实例指针
	@return 白板管理类指针
	*/
	virtual BoardMgr* getTICWhiteBoardManager() = 0;
	
	/**
	* \brief 打开/关闭摄像头
	* \param enable   true：打开默认摄像头；false：关闭
	*/
	virtual void enableCamera(bool bEnable) = 0;

	/**
	* \brief 获得摄像头列表
	* \param cameraList 传回获取到的摄像头列表,第一个(索引0)为系统默认设备;
	* \return 错误码，0表示成功
	*/
	virtual int getCameraList(ilive::Vector< ilive::Pair<ilive::String/*id*/, ilive::String/*name*/> >& cameraList) = 0;

	/**
	* \brief 切换摄像头
	* \param cameraId   摄像头设备标识
	*/
	virtual void switchCamera(const char* cameraId) = 0;

	/**
	* \brief 打开/关闭麦克风
	* \param enable   true：打开默认麦克风；false：关闭
	*/
	virtual void enableMic(bool bEnable) = 0;

	/**
	* \brief 获得麦克风列表
	* \param micList 传回获取到的麦克风列表,第一个(索引0)为系统默认设备;
	* \return 错误码，0表示成功
	*/
	virtual int getMicList(ilive::Vector< ilive::Pair<ilive::String/*id*/, ilive::String/*name*/> >& micList) = 0;

	/**
	* \brief 切换麦克风
	* \param deviceID   麦克风设备标识
	*/
	virtual void switchMic(const char* deviceID) = 0;

	/**
	* \brief 打开/关闭扬声器
	* \param enable   true：打开默认扬声器；false：关闭
	*/
	virtual void enablePlayer(bool bEnable) = 0;

	/**
	* \brief 获得扬声器列表
	* \param micList 传回获取到的扬声器列表,第一个(索引0)为系统默认设备;
	* \return 错误码，0表示成功
	*/
	virtual int getPlayerList(ilive::Vector< ilive::Pair<ilive::String/*id*/, ilive::String/*name*/> >& playerList) = 0;

	/**
	* \brief 切换扬声器
	* \param deviceID   扬声器设备标识
	*/
	virtual void switchPlayer(const char* deviceID) = 0;

	/**
	* \brief 设置本地视频预览回调
	* \param OnLocalVideo   回调函数接口
	* \param data   用户自定义数据
	*/
	virtual void setLocalVideoCallBack(ilive::iLivePreviewCallback OnLocalVideo, void* data = nullptr) = 0;

	/**
	* \brief 设置远程视频数据接收
	* \param OnRemoteVideo   回调函数接口
	* \param data   用户自定义数据
	*/
	virtual void setRemoteVideoCallBack(ilive::iLivePreviewCallback OnRemoteVideo, void* data = nullptr) = 0;

	/**
	* \brief 设置设备操作回调
	* \param OnDeviceOperation   回调函数接口
	* \param data   用户自定义数据
	*/
	virtual void setDeviceOperationCallback(ilive::iLiveDeviceOperationCallback OnDeviceOperation, void* data = nullptr) = 0;

	/**
	* \brief 设置被踢下线回调
	* \param OnForceOffline   回调函数接口
	*/
	virtual void setForceOfflineCallback(ilive::ForceOfflineCallback OnForceOffline) = 0;

	/**
	* \brief 设置网络状态监听回调
	* \param onConn		 联网成功回调
	* \param onDisconn   断开连接回调
	*/
	virtual void setNetworkConnCallBack(ilive::onNetworkCallback onConn, ilive::onNetworkCallback onDisconn) = 0;

	/**
	* \brief 打开屏幕分享(指定窗口)
	* \param hWnd 所要捕获的窗口句柄(NULL表示全屏)
	* \param fps 捕获帧率
	*/
	virtual void openScreenShare(HWND hWnd, uint32& fps) = 0;

	/**
	* \brief 打开窗口分享(指定窗口抓取，必须支持OpenGL)
	* \return 非0表示失败，0表示成功
	*/
	virtual int openWindowShare() = 0;

	/**
	* \brief 打开窗口分享(传入窗口句柄，必须支持OpenGL)
	*/
	virtual void openWindowShare(HWND hwnd) = 0;

	/**
	* \brief 关闭窗口共享
	*/
	virtual void closeWindowShare() = 0;

	/**
	* \brief 打开屏幕共享(指定区域)
	* \param left/top/right/bottom 所要捕获屏幕画面的区域的左上角坐标(left, top)和右下角坐标(right, bottom)
	* \param fps 捕获帧率
	*/
	virtual void openScreenShare(int32& left, int32& top, int32& right, int32& bottom, uint32& fps) = 0;

	/**
	* \brief 动态修改屏幕分享的区域
	* \param left/top/right/bottom 所要捕获屏幕画面的区域的左上角坐标(left, top)和右下角坐标(right, bottom)
	* \param fps 捕获帧率
	*/
	virtual int changeScreenShareSize(int32& left, int32& top, int32& right, int32& bottom) = 0;

	/**
	* \brief 关闭屏幕共享
	*/
	virtual void closeScreenShare() = 0;

	/**
	* \brief 设置日志路径
	* \param szLogPath				日志路径
	*/
	virtual void setLogPath(const char* szLogPath) = 0;

	/**
	* \brief 发送文本消息
	* \param userId   消息接收者，填空（null或者""表示发送群消息）
	* \param msg	  发送内容
	* \param data	  用户自定义数据
	*/
	virtual void sendTextMessage(const char * userId, const char * msg, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief 发送自定义消息
	* \param userId   消息接收者，填空（null或者""表示发送群消息）
	* \param msg	  发送内容
	* \param data	  用户自定义数据
	*/
	virtual void sendCustomMessage(const char * userId, const char * msg, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;

	/**
	* \brief 发送消息(所有类型)
	* \param type	  消息类型
	* \param userId   消息接收者
	* \param msg	  消息对象
	* \param data	  用户自定义数据
	*/
	virtual void sendMessage(TIMConversationType type, const char * userId, TIMConversationHandle msg, ilive::iLiveSucCallback success = nullptr, ilive::iLiveErrCallback err = nullptr, void* data = nullptr) = 0;
};

#endif

