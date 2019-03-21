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
* \brief 课堂事件监听对象
*/
class IClassroomEventListener
{
public:
	/**
	* \brief 视频房间断开回调
	* \param reason		错误码
	* \param errorinfo	错误描述
	* \param data		用户自定义数据的指针
	*/
	virtual void onLiveVideoDisconnect(int reason, const char *errorinfo, void* data) {};

	/**
	* \brief 成员状态改变回调
	* \param event_id		事件id
	* \param ids		发生状态变化的成员id列表
	* \param data		用户自定义数据的指针
	*/
	virtual void onMemStatusChange(ilive::E_EndpointEventId event_id, const ilive::Vector<ilive::String> &ids, void* data) {};

	/**
	* \brief 成员加入房间
	* \param identifier		加入房间成员id列表
	*/
	virtual void onMemberJoin(const char ** identifier, uint32_t num) {};

	/**
	* \brief 成员退出房间
	* \param identifier		退出房间成员id列表
	*/
	virtual void onMemberQuit(const char ** identifier, uint32_t num) {};

	/**
	* \brief 课堂房间被销毁
	*/
	virtual void onClassroomDestroy() {};

	/**
	* \brief 窗口分享选择结构
	* \param hWnd 所要捕获的窗口句柄(NULL表示取消)
	*/
	virtual void onShareWindow(HWND hwnd) {};

	/**
	* \brief 通知白板状态变化
	* \param canUndo	允许撤销
	* \param canRedo	允许重来
	* \param canCopy	允许复制
	* \param canRemove	允许删除
	*/
	virtual void onStatusChanged(bool canUndo, bool canRedo, bool canCopy, bool canRemove) {};

	/**
	* \brief 通知白板数据同步完毕
	* \param bResult	同步结果
	*/
	virtual void onGetBoardData(bool bResult) = 0;

	/**
	* \brief 通知文件上传进度
	* \param percent	进度按百分比
	* \param data		用户自定义指针
	*/
	virtual void onUploadProgress(int percent, void* data) {};

	/**
	* \brief 通知文件上传结果
	* \param success	上传结果
	* \param code		错误码
	* \param objName	cos文件名
	* \param fileName	本地文件名
	* \param data		用户自定义指针
	*/
	virtual void onUploadResult(bool success, int code, std::wstring objName, std::wstring fileName, void* data) {};

	/**
	* \brief 通知PPT文件上传结果
	* \param success	上传结果
	* \param objName	cos文件名
	* \param fileName	本地文件名
	* \param fileId	    文件Id
	* \param data		用户自定义指针
	*/
	virtual void onFileUploadResult(bool success, std::wstring objName, std::wstring fileName, int pageCount, void* data) {};

	/**
	* 通知PPT文件信息发生改变，用户要重新获取文件列表
	*/
	virtual void onFileInfoChanged() {};
};
/**
@brief 课堂IM消息监听对象
*/
class IClassroomIMListener
{
public:
	/**
	* \brief 接收文本消息
	* \param fromId	消息发送者
	* \param msg	消息内容
	* \param type	消息类型（群聊或者单聊）
	*/
	virtual void onRecvTextMessage(const char * fromId, const char * msg, TIMConversationType type) {};

	/**
	* \brief 接收自定义消息
	* \param fromId	消息发送者
	* \param msg	消息内容
	* \param type	消息类型（群聊或者单聊）
	*/
	virtual void onRecvCustomMessage(const char * fromId, const char * msg, TIMConversationType type) {};

	/**
	* \brief 接收到非白板全部消息回调
	* \param handles	消息句柄
	* \param elemCount	元素个数
	*/
	virtual void onRecvMessage(TIMMessageHandle handle, uint32_t elemCount) {};

	/**
	* \brief 发送消息回调,已废弃
	*/
	Deprecated virtual void onSendMsg(int err, const char * errMsg, void* data) {};

	/**
	* \brief 发送白板消息回调
	* \param err	错误码
	* \param errMsg	错误描述
	*/
	virtual void onSendWBData(int err, const char * errMsg) {};

};

/**
@brief 传回请求的统一时间回调
*/
class IClassroomRecordTimeStampRespCallback
{
public:
	virtual ~IClassroomRecordTimeStampRespCallback(){ }
	/**
	* \brief 用户传回sdk统一时间回调;
	* \param timestamp	传回sdk的统一时间(单位: 毫秒);
	*/
	virtual void onRecordTimeStamp(int64_t timestamp) = 0;
};

/**
@brief 课堂录制事件监听
*/
class IClassroomRecordEventListener
{
public:
	virtual ~IClassroomRecordEventListener() { }

	/**
	* \brief 请求各端统一时间;如果一个房间内多路用户连麦视频进行录制，业务侧需要实现各端一致的时间(如统一获取服务器时间)。
	* \param callback	获取统一时间后，通过此回调通知回sdk;
	*/
	virtual void onRecordTimestampRequest(IClassroomRecordTimeStampRespCallback* callback) {};
};

/**
课堂配置类
*/
class TICSDK_API TICClassroomOption
{
public:
	TICClassroomOption();
	~TICClassroomOption();
	/**
	* \brief 置课堂内角色是否为老师
	*/
	bool getIsTeacher();
	void setIsTeacher(bool bTeacher);

	bool getIsAutoRecord();
	void setIsAutoRecord(bool bAutoRecord);

	/**
	* \brief 设置课堂房间ID
	*/
	uint32_t getRoomID();
	void setRoomID(uint32_t roomId);

	/**
	* \brief 设置进房间参数
	*/
	void setRoomOption(ilive::iLiveRoomOption& opt); 
	ilive::iLiveRoomOption& getRoomOption();

	/**
	* \brief 设置监听课堂内部事件
	*/
	void setClassroomEventListener(IClassroomEventListener* listener);
	IClassroomEventListener* getClassroomEventListener() const;

	/**
	* \brief 设置监听课堂内IM消息
	*/
	void setClassroomIMListener(IClassroomIMListener* listener);
	IClassroomIMListener* getClassroomIMListener() const;

	/**
	* \brief 设置监听录制消息
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
