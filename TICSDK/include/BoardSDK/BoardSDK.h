// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 EDUSDK_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// EDUSDK_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#pragma once

#ifdef EDUSDK_EXPORTS
#define EDUSDK_API __declspec(dllexport)
#else
#define EDUSDK_API __declspec(dllimport)
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdint>
#include <vector>
class BoardSDKImpl;

/**
 * \brief 白板回调接口，用户需自行实现这个接口并调用BoardSDK的setCallback方法将该通道设置给白板
 */
struct EDUSDK_API BoardCallback
{
	/**
	 * \brief 操作事件数据到达，当使用者在白板上执行操作时，SDK将操作的元数据按如下JSON格式打包，并触发该函数
	 * {
	 *		"boardId":"#DEFAULT", 	// 白板id，默认为#DEFAULT
	 *		"operator":"user1",
	 *		"actions":
	 *			[
	 *				...	//一系列白板操作
	 *			],
	 *	}
	 * \param data		保存有数据的字符串缓冲区
	 * \param length	字符串长度
	 */
	virtual void onActionsData(const char *data, uint32_t length) {};

	/**
	 * \brief 状态事件，当白板状态发生变化时触发
	 * \param canUndo	是否可撤销
	 * \param canRedo	是否可重做
	 * \param canCopy	是否可复制
	 * \param canRemove	是否可删除
	 */
	virtual void onStatusChanged(bool canUndo, bool canRedo, bool canCopy, bool canRemove) = 0;

	/**
	 * \brief 获取时间戳事件，SDK需要获取统一的时间戳时触发该事件
	 * \return 时间戳，单位毫秒
	 */
	virtual uint32_t onGetTime();

	/**
	* \brief 获取到白板数据事件
	* \param bResult  获取白板数据结果
	*/
	virtual void onGetBoardData(bool bResult) = 0;

	/**
	* \brief 白板数据上报结果
	* \param code  错误码
	* \param msg   错误描述
	*/
	virtual void onReportBoardData(const int code, const char * msg) {};

    /**
    * \brief 渲染完成一帧（此时所有添加到白板的操作元数据都已渲染完成）
	* \param buffer		图像数据内存
	* \param buffLength	图像数据大小
	* \param width		图像宽
	* \param height		图像高
    */
	virtual void onRenderFrame(uint8_t* buffer, int buffLength, uint32_t width, uint32_t height) {};

	/**
	* \brief 通知文件上传结果
	* \param success	上传结果 
	* \param code		错误码
	* \param objName	cos文件名
	* \param fileName	本地文件名
	* \param data       用户自定义指针
	*/
	virtual void onUploadResult(bool success, int code, const wchar_t* objName, const wchar_t*  fileName, void* data) = 0;

	/**
	* \brief 通知PPT文件转码结果
	* \param success	上传结果
	* \param objName	cos文件名
	* \param fileName	本地文件名
	* \param pageCount	   页数
	* \param data       用户自定义指针
	*/
	virtual void onFileUploadResult(bool success, const wchar_t* objName, const wchar_t* fileName, int pageCount, void* data) = 0;

	/**
	* \brief 通知文件上传进度
	* \param percent	进度按百分比
	* \param data       用户自定义指针
	*/
	virtual void onUploadProgress(int percent, void* data) {};

	/**
	* 通知文件信息发生改变，用户要重新获取文件列表
	*/
	virtual void onFileInfoChanged() {};
};

/**
 * \brief 白板工具定义
 */
enum class BoardTool
{
	None,			//不使用任何工具（禁止绘制）
	Pen,			//铅笔工具
	Eraser,			//橡皮擦工具
	Laser,			//激光笔
	Line,			//直线工具
	Ellipse,		//椭圆工具
	Rectangle,		//圆角矩形工具
	Select,			//选框工具
	Text,			//文字输入工具
	Shift,			//缩放模式下页面移动
};

enum class ImageFitMode
{
	FitAdapter = 0,			//默认自适应，宽高比例不变
	FitWidthHeight = 1,		//平铺铺满
	FitWidth = 2,			//宽度适应，宽高比例不变
	FitHeight = 3,			//高度适应，宽高比例不变
	FitAlignLeft = 4,		//居左对齐
	FitAlignTop = 5,		//居上对齐
	FitAlignRight = 6,		//居右对齐
	FitAlignBottom = 7,		//居下对齐
};

// 此类是从 BoardSDK.dll 导出的
class EDUSDK_API BoardSDK {
public:
	/**
	* \brief 白板SDK构造函数
	* \param userID				当前用户ID
	* \param userSig			用户签名sig
	* \param sdkappId			sdk appid
	* \param roomId				房间id
	* \param parentHWnd			父窗口句柄，为空则白板没有父窗口
	* \param 
	*/
	BoardSDK(const char *userID, const char* userSig, int sdkappId, uint32_t roomId, HWND parentHWnd = nullptr, bool shareMode = false);

	~BoardSDK();

	/**
	 * \brief 获取白板渲染窗口句柄
	 * \return 渲染窗口句柄
	 */
	HWND getRenderWindow() const;

	/**
	* \brief 获取白板消息窗口句柄
	* \return 消息窗口句柄
	*/
	HWND getRenderMsgWindow() const;

	/**
	* \brief 启用默认的上报通道
	* \param appId
	* \param classId
	* \param userSig
	*/
	void enableDefaultReporter(int sdkappId, uint32_t classId, const char* userSig) const;

	/**
	 * \brief 设置回调接口
	 * \param callback				回调接口
	 */
	void setCallback(BoardCallback *callback) const;

	/**
	* \brief 清空白板数据
	*/
	void clearWhiteBoard() const;

	/**
	 * \brief 指定要使用的白板工具
	 * \param tool					白板工具
	 */
	void useTool(BoardTool tool) const;

	/**
	 * \brief 指定要使用的宽度（对于铅笔、直线、椭圆、矩形工具，该参数指示了线宽；对于橡皮擦及激光笔工具，该参数指示了直径）
	 * \param width					宽度
	 */
	void setLineWidth(uint32_t width) const;

	/**
	 * \brief 指定要使用的颜色
	 * \param red		颜色值Red分量
	 * \param green		颜色值Green分量
	 * \param blue		颜色值Blue分量
	 * \param alpha		Alpha通道
	 */
	void setBrushColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const;

	/**
	 * \brief 指定是否启用填充
	 * \param fill					是否启用填充
	 */
	void setFill(bool fill) const;

	/**
	 * \brief 指定要使用的半径（当前仅用于指定圆角矩形的圆角半径）
	 * \param radius				半径
	 */
	void setRadius(uint32_t radius) const;

	/**
	* \brief 指定要使用的文字字号，默认16号
	* \param size				字号大小
	*/
	void setFontSize(uint32_t size) const;

	/**
	* \brief 设置当前页面缩放比例
	* \param scale		缩放百分比例系数，为百分比乘以100
	*/
	void setScale(uint32_t scale) const;

	/**
	* \brief 获取当前页面缩放比例
	* \return 缩放百分比例系数，为百分比乘以100
	*/
	uint32_t getCurrentScale() const;

	/**
	 * \brief 对已选中图形进行拷贝操作
	 */
	void copy() const;

	/**
	 * \brief 对已选中图形进行删除操作
	 */
	void remove() const;

	/**
	 * \brief 撤销
	 */
	void undo() const;

	/**
	 * \brief 重做
	 */
	void redo() const;

	/**
	 * \brief 清空白板(包括涂鸦和背景)
	 */
	void clear() const;

	/**
	* \brief 清空涂鸦
	*/
	void clearDraws() const;

	/**
	* \brief 清空房间所有数据
	*/
	void cleanAll() const;

	/**
	* \brief 指定要使用的背景图片
	* \param url					背景图片URL（本地文件以file://开头表示，为空表示清空背景）
	* \param pageID				制定要设置背景图片的页面ID（为空表示当前页面）
	* \param fillMode				制定要设置背景图片的填充模式（默认0为自适应）
	*/
	void setBackgroundImage(const wchar_t *url, const char *pageID = nullptr, ImageFitMode fillMode = ImageFitMode::FitAdapter) const;

	/**
	* \brief 更新当前背景图片填充模式
	* \param fillMode				背景图片的填充模式
	*/
	void updateCurrentFillMode(ImageFitMode fillMode) const;

	/**
	* \brief 指定背景要使用的颜色
	* \param red		颜色值Red分量
	* \param green		颜色值Green分量
	* \param blue		颜色值Blue分量
	* \param alpha		Alpha通道
	*/
	void setBackgroundColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const;

	/**
	* \brief 指定全局背景要使用的颜色
	* \param red		颜色值Red分量
	* \param green		颜色值Green分量
	* \param blue		颜色值Blue分量
	* \param alpha		Alpha通道
	*/
	void setAllBackgroundColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const;

	/**
	 * \brief 向白板添加操作元数据（通过BoardCallback的sendData方法获取的数据，按如下JSON格式打包）
	 * {
	 *		"boardId":"#DEFAULT", 	// 白板id，默认为#DEFAULT
	 *		"operator":"user1",
	 *		"actions":
	 *			[
	 *				...	//一系列白板操作
	 *			],
	 *	}
	 * \param data					保存有数据的字符串缓冲区
	 * \param length				字符串长度
	 */
	void appendActionsData(const char *data, uint32_t length) const;

	/**
	* \brief 拉全量白板离线数据
	*/
	void getBoardData();

	/**
	* \brief 创建白板
	* \return 白板id
	*/
	std::string addBoard() const;

	/**
	* \brief 白板页面操作
	* \param toPageID				要跳转到页面ID
	* \param deletePagesID			要删除的页面ID集合
	* \param deletePagesCount		要删除的页面ID个数
	*/
	int pageOperate(const char *toPageID, const char **deletePagesID = nullptr, uint32_t deletePagesCount = 0) const;

	/**
	* \brief 新增一个白板文件，并生成对应白板id和文件id，默认为ppt
	* \param urls	ppt分页url数组
	* \param boardIds	ppt白板分页数组
	* \param title	ppt文件名
	* \param type	文件类型，目前默认为0-ppt
	* \return 文件id
	*/
	std::string addFile(std::vector<std::wstring>& urls, std::vector<std::string>& boardIds, const wchar_t * title, int type = 0) const;

	/**
	* \brief 移除文件
	* \param fid	文件id
	*/
	void deleteFile(const char * fid) const;

	/**
	* \brief 获取保存的所有文件
	* \param titles	文件名
	* \param fids	文件id
	*/
	uint32_t getAllFiles(std::vector<std::wstring>& titles, std::vector<std::string>& fids) const;

	/**
	* \brief 获取保存的所有白板id
	* \param boardIds	白板列表
	*/
	void getAllBoards(std::vector<std::string>& boardIds) const;

	/**
	* \brief 获取当前展示的白板id
	* \return 白板id
	*/
	std::string getCurrentBoard() const;

	/**
	* \brief 清空对应fid所有白板的涂鸦      
	* \param fids  要清空的fid数组
	*/                                                                  
	void clearFileDraws(std::vector<std::string>& fids) const;

	/**
	* \brief 获取白板id对应的背景图片URL
	* \return 背景图片URL
	*/
	std::wstring getBGImageURL(const char * boardId) const;

	/**
	* \brief 窗口分享模式下显示/隐藏窗口涂鸦工具笔
	*/
	void showWhiteboardTool(bool show) const;

	/**
	* \brief 窗口分享模式下获得窗口涂鸦工具笔显示/隐藏状况
	*/
	bool getWhiteBoardShowStatus() const;

	bool getCustomData(char **data, uint32_t& length);

private:
	BoardSDKImpl *_impl;
};
