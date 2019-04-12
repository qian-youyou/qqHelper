#pragma once
class QQmessage
{
public:
	QQmessage();
	~QQmessage();

	//类的入口 
	static QQmessage *Instance()
	{
		static QQmessage object;
		
		return &object;
	}

	//入口函数
	void Start(const wchar_t *msg);

private:
	//开始线程
	static unsigned int WINAPI RunThreadproc(void* param);
	
	//发送主函数
	void SendAll();

	//找到QQ窗口
	HWND FindQQWindow();

	//模拟按键
	void PressKey(BYTE vkey);

	//发送消息
	void SendMsg();

	//添加文本到剪贴板
	void AddTextToClipboard();

private:
	CString m_msg;
};

