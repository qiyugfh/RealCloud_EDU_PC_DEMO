// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� EDUSDK_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// EDUSDK_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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
 * \brief �װ�ص��ӿڣ��û�������ʵ������ӿڲ�����BoardSDK��setCallback��������ͨ�����ø��װ�
 */
struct EDUSDK_API BoardCallback
{
	/**
	 * \brief �����¼����ݵ����ʹ�����ڰװ���ִ�в���ʱ��SDK��������Ԫ���ݰ�����JSON��ʽ������������ú���
	 * {
	 *		"boardId":"#DEFAULT", 	// �װ�id��Ĭ��Ϊ#DEFAULT
	 *		"operator":"user1",
	 *		"actions":
	 *			[
	 *				...	//һϵ�аװ����
	 *			],
	 *	}
	 * \param data		���������ݵ��ַ���������
	 * \param length	�ַ�������
	 */
	virtual void onActionsData(const char *data, uint32_t length) {};

	/**
	 * \brief ״̬�¼������װ�״̬�����仯ʱ����
	 * \param canUndo	�Ƿ�ɳ���
	 * \param canRedo	�Ƿ������
	 * \param canCopy	�Ƿ�ɸ���
	 * \param canRemove	�Ƿ��ɾ��
	 */
	virtual void onStatusChanged(bool canUndo, bool canRedo, bool canCopy, bool canRemove) = 0;

	/**
	 * \brief ��ȡʱ����¼���SDK��Ҫ��ȡͳһ��ʱ���ʱ�������¼�
	 * \return ʱ�������λ����
	 */
	virtual uint32_t onGetTime();

	/**
	* \brief ��ȡ���װ������¼�
	* \param bResult  ��ȡ�װ����ݽ��
	*/
	virtual void onGetBoardData(bool bResult) = 0;

	/**
	* \brief �װ������ϱ����
	* \param code  ������
	* \param msg   ��������
	*/
	virtual void onReportBoardData(const int code, const char * msg) {};

    /**
    * \brief ��Ⱦ���һ֡����ʱ������ӵ��װ�Ĳ���Ԫ���ݶ�����Ⱦ��ɣ�
	* \param buffer		ͼ�������ڴ�
	* \param buffLength	ͼ�����ݴ�С
	* \param width		ͼ���
	* \param height		ͼ���
    */
	virtual void onRenderFrame(uint8_t* buffer, int buffLength, uint32_t width, uint32_t height) {};

	/**
	* \brief ֪ͨ�ļ��ϴ����
	* \param success	�ϴ���� 
	* \param code		������
	* \param objName	cos�ļ���
	* \param fileName	�����ļ���
	* \param data       �û��Զ���ָ��
	*/
	virtual void onUploadResult(bool success, int code, const wchar_t* objName, const wchar_t*  fileName, void* data) = 0;

	/**
	* \brief ֪ͨPPT�ļ�ת����
	* \param success	�ϴ����
	* \param objName	cos�ļ���
	* \param fileName	�����ļ���
	* \param pageCount	   ҳ��
	* \param data       �û��Զ���ָ��
	*/
	virtual void onFileUploadResult(bool success, const wchar_t* objName, const wchar_t* fileName, int pageCount, void* data) = 0;

	/**
	* \brief ֪ͨ�ļ��ϴ�����
	* \param percent	���Ȱ��ٷֱ�
	* \param data       �û��Զ���ָ��
	*/
	virtual void onUploadProgress(int percent, void* data) {};

	/**
	* ֪ͨ�ļ���Ϣ�����ı䣬�û�Ҫ���»�ȡ�ļ��б�
	*/
	virtual void onFileInfoChanged() {};
};

/**
 * \brief �װ幤�߶���
 */
enum class BoardTool
{
	None,			//��ʹ���κι��ߣ���ֹ���ƣ�
	Pen,			//Ǧ�ʹ���
	Eraser,			//��Ƥ������
	Laser,			//�����
	Line,			//ֱ�߹���
	Ellipse,		//��Բ����
	Rectangle,		//Բ�Ǿ��ι���
	Select,			//ѡ�򹤾�
	Text,			//�������빤��
	Shift,			//����ģʽ��ҳ���ƶ�
};

enum class ImageFitMode
{
	FitAdapter = 0,			//Ĭ������Ӧ����߱�������
	FitWidthHeight = 1,		//ƽ������
	FitWidth = 2,			//�����Ӧ����߱�������
	FitHeight = 3,			//�߶���Ӧ����߱�������
	FitAlignLeft = 4,		//�������
	FitAlignTop = 5,		//���϶���
	FitAlignRight = 6,		//���Ҷ���
	FitAlignBottom = 7,		//���¶���
};

// �����Ǵ� BoardSDK.dll ������
class EDUSDK_API BoardSDK {
public:
	/**
	* \brief �װ�SDK���캯��
	* \param userID				��ǰ�û�ID
	* \param userSig			�û�ǩ��sig
	* \param sdkappId			sdk appid
	* \param roomId				����id
	* \param parentHWnd			�����ھ����Ϊ����װ�û�и�����
	* \param 
	*/
	BoardSDK(const char *userID, const char* userSig, int sdkappId, uint32_t roomId, HWND parentHWnd = nullptr, bool shareMode = false);

	~BoardSDK();

	/**
	 * \brief ��ȡ�װ���Ⱦ���ھ��
	 * \return ��Ⱦ���ھ��
	 */
	HWND getRenderWindow() const;

	/**
	* \brief ��ȡ�װ���Ϣ���ھ��
	* \return ��Ϣ���ھ��
	*/
	HWND getRenderMsgWindow() const;

	/**
	* \brief ����Ĭ�ϵ��ϱ�ͨ��
	* \param appId
	* \param classId
	* \param userSig
	*/
	void enableDefaultReporter(int sdkappId, uint32_t classId, const char* userSig) const;

	/**
	 * \brief ���ûص��ӿ�
	 * \param callback				�ص��ӿ�
	 */
	void setCallback(BoardCallback *callback) const;

	/**
	* \brief ��հװ�����
	*/
	void clearWhiteBoard() const;

	/**
	 * \brief ָ��Ҫʹ�õİװ幤��
	 * \param tool					�װ幤��
	 */
	void useTool(BoardTool tool) const;

	/**
	 * \brief ָ��Ҫʹ�õĿ�ȣ�����Ǧ�ʡ�ֱ�ߡ���Բ�����ι��ߣ��ò���ָʾ���߿�������Ƥ��������ʹ��ߣ��ò���ָʾ��ֱ����
	 * \param width					���
	 */
	void setLineWidth(uint32_t width) const;

	/**
	 * \brief ָ��Ҫʹ�õ���ɫ
	 * \param red		��ɫֵRed����
	 * \param green		��ɫֵGreen����
	 * \param blue		��ɫֵBlue����
	 * \param alpha		Alphaͨ��
	 */
	void setBrushColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const;

	/**
	 * \brief ָ���Ƿ��������
	 * \param fill					�Ƿ��������
	 */
	void setFill(bool fill) const;

	/**
	 * \brief ָ��Ҫʹ�õİ뾶����ǰ������ָ��Բ�Ǿ��ε�Բ�ǰ뾶��
	 * \param radius				�뾶
	 */
	void setRadius(uint32_t radius) const;

	/**
	* \brief ָ��Ҫʹ�õ������ֺţ�Ĭ��16��
	* \param size				�ֺŴ�С
	*/
	void setFontSize(uint32_t size) const;

	/**
	* \brief ���õ�ǰҳ�����ű���
	* \param scale		���Űٷֱ���ϵ����Ϊ�ٷֱȳ���100
	*/
	void setScale(uint32_t scale) const;

	/**
	* \brief ��ȡ��ǰҳ�����ű���
	* \return ���Űٷֱ���ϵ����Ϊ�ٷֱȳ���100
	*/
	uint32_t getCurrentScale() const;

	/**
	 * \brief ����ѡ��ͼ�ν��п�������
	 */
	void copy() const;

	/**
	 * \brief ����ѡ��ͼ�ν���ɾ������
	 */
	void remove() const;

	/**
	 * \brief ����
	 */
	void undo() const;

	/**
	 * \brief ����
	 */
	void redo() const;

	/**
	 * \brief ��հװ�(����Ϳѻ�ͱ���)
	 */
	void clear() const;

	/**
	* \brief ���Ϳѻ
	*/
	void clearDraws() const;

	/**
	* \brief ��շ�����������
	*/
	void cleanAll() const;

	/**
	* \brief ָ��Ҫʹ�õı���ͼƬ
	* \param url					����ͼƬURL�������ļ���file://��ͷ��ʾ��Ϊ�ձ�ʾ��ձ�����
	* \param pageID				�ƶ�Ҫ���ñ���ͼƬ��ҳ��ID��Ϊ�ձ�ʾ��ǰҳ�棩
	* \param fillMode				�ƶ�Ҫ���ñ���ͼƬ�����ģʽ��Ĭ��0Ϊ����Ӧ��
	*/
	void setBackgroundImage(const wchar_t *url, const char *pageID = nullptr, ImageFitMode fillMode = ImageFitMode::FitAdapter) const;

	/**
	* \brief ���µ�ǰ����ͼƬ���ģʽ
	* \param fillMode				����ͼƬ�����ģʽ
	*/
	void updateCurrentFillMode(ImageFitMode fillMode) const;

	/**
	* \brief ָ������Ҫʹ�õ���ɫ
	* \param red		��ɫֵRed����
	* \param green		��ɫֵGreen����
	* \param blue		��ɫֵBlue����
	* \param alpha		Alphaͨ��
	*/
	void setBackgroundColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const;

	/**
	* \brief ָ��ȫ�ֱ���Ҫʹ�õ���ɫ
	* \param red		��ɫֵRed����
	* \param green		��ɫֵGreen����
	* \param blue		��ɫֵBlue����
	* \param alpha		Alphaͨ��
	*/
	void setAllBackgroundColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const;

	/**
	 * \brief ��װ���Ӳ���Ԫ���ݣ�ͨ��BoardCallback��sendData������ȡ�����ݣ�������JSON��ʽ�����
	 * {
	 *		"boardId":"#DEFAULT", 	// �װ�id��Ĭ��Ϊ#DEFAULT
	 *		"operator":"user1",
	 *		"actions":
	 *			[
	 *				...	//һϵ�аװ����
	 *			],
	 *	}
	 * \param data					���������ݵ��ַ���������
	 * \param length				�ַ�������
	 */
	void appendActionsData(const char *data, uint32_t length) const;

	/**
	* \brief ��ȫ���װ���������
	*/
	void getBoardData();

	/**
	* \brief �����װ�
	* \return �װ�id
	*/
	std::string addBoard() const;

	/**
	* \brief �װ�ҳ�����
	* \param toPageID				Ҫ��ת��ҳ��ID
	* \param deletePagesID			Ҫɾ����ҳ��ID����
	* \param deletePagesCount		Ҫɾ����ҳ��ID����
	*/
	int pageOperate(const char *toPageID, const char **deletePagesID = nullptr, uint32_t deletePagesCount = 0) const;

	/**
	* \brief ����һ���װ��ļ��������ɶ�Ӧ�װ�id���ļ�id��Ĭ��Ϊppt
	* \param urls	ppt��ҳurl����
	* \param boardIds	ppt�װ��ҳ����
	* \param title	ppt�ļ���
	* \param type	�ļ����ͣ�ĿǰĬ��Ϊ0-ppt
	* \return �ļ�id
	*/
	std::string addFile(std::vector<std::wstring>& urls, std::vector<std::string>& boardIds, const wchar_t * title, int type = 0) const;

	/**
	* \brief �Ƴ��ļ�
	* \param fid	�ļ�id
	*/
	void deleteFile(const char * fid) const;

	/**
	* \brief ��ȡ����������ļ�
	* \param titles	�ļ���
	* \param fids	�ļ�id
	*/
	uint32_t getAllFiles(std::vector<std::wstring>& titles, std::vector<std::string>& fids) const;

	/**
	* \brief ��ȡ��������аװ�id
	* \param boardIds	�װ��б�
	*/
	void getAllBoards(std::vector<std::string>& boardIds) const;

	/**
	* \brief ��ȡ��ǰչʾ�İװ�id
	* \return �װ�id
	*/
	std::string getCurrentBoard() const;

	/**
	* \brief ��ն�Ӧfid���аװ��Ϳѻ      
	* \param fids  Ҫ��յ�fid����
	*/                                                                  
	void clearFileDraws(std::vector<std::string>& fids) const;

	/**
	* \brief ��ȡ�װ�id��Ӧ�ı���ͼƬURL
	* \return ����ͼƬURL
	*/
	std::wstring getBGImageURL(const char * boardId) const;

	/**
	* \brief ���ڷ���ģʽ����ʾ/���ش���Ϳѻ���߱�
	*/
	void showWhiteboardTool(bool show) const;

	/**
	* \brief ���ڷ���ģʽ�»�ô���Ϳѻ���߱���ʾ/����״��
	*/
	bool getWhiteBoardShowStatus() const;

	bool getCustomData(char **data, uint32_t& length);

private:
	BoardSDKImpl *_impl;
};
