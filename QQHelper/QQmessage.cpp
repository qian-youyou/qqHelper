#include "stdafx.h"
#include "QQmessage.h"


QQmessage::QQmessage()
{
}


QQmessage::~QQmessage()
{
}

//入口函数
void QQmessage::Start(const wchar_t *msg)
{
	m_msg = CString(msg); //输入的文本

	_beginthreadex(NULL, 0, QQmessage::RunThreadproc, NULL, 0, NULL);
}

//开始线程
unsigned int QQmessage::RunThreadproc(void* param)
{
	QQmessage::Instance()->SendAll();
	return 0;
}

//发送主函数
void QQmessage::SendAll()
{
	int errorTimes = 0;  //打开对话框错误的次数!
	//把text复制到剪贴板
	AddTextToClipboard();

	//技术到家. 做项目能力.
	while (errorTimes<= 4)
	{
		HWND hQQWnd = FindQQWindow();
		HWND hFrontWnd = GetForegroundWindow(); 

		if (hQQWnd != hFrontWnd)
		{
			if (!SetForegroundWindow(hQQWnd))
			{
				MessageBox(NULL, L"没有找到QQ窗口", NULL, NULL);
				break;
			}
		}
		if (errorTimes == 0)
		{
			PressKey(VK_TAB);
			PressKey(VK_TAB);
		}
		PressKey(VK_DOWN);
		PressKey(VK_RETURN);

		HWND hCurFrontWnd = GetForegroundWindow();
		if (hCurFrontWnd == hQQWnd)  //
		{
			++errorTimes;
			continue;
		}

		errorTimes = 0;
		SendMsg();
	}
}

//找到QQ窗口
HWND QQmessage::FindQQWindow()
{
	HWND hWnd = FindWindow(L"TXGuiFoundation",L"QQ");  //Find  Window //获取QQ的窗口!!!
	
	//辅助工具就是这么做的
	return hWnd;
}

//模拟按键
void QQmessage::PressKey(BYTE vkey)
{
	keybd_event(vkey, 0, 0, 0);  //按下(0)和弹起(KEYEVENTF_KEYUP)
	Sleep(100);
	keybd_event(vkey, 0, KEYEVENTF_KEYUP, 0);  //敲击TAB
	Sleep(100);
}

//发送消息  16GU盘
void QQmessage::SendMsg()
{
	//粘贴  +  发送
	keybd_event(VK_CONTROL, 0, 0, 0);  //按下(0)和弹起(KEYEVENTF_KEYUP)
	Sleep(100);
	keybd_event(0x56, 0, 0, 0);  //按下(0)和弹起(KEYEVENTF_KEYUP)
	Sleep(100);

	keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);  //敲击TAB
	Sleep(100);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);  //敲击TAB
	Sleep(100); //你好 鲜花刷起来!

	//发送
	PressKey(VK_RETURN);
	PressKey(VK_ESCAPE);
}

//添加文本到剪贴板
void QQmessage::AddTextToClipboard()
{
	//1.把文本拷贝到全局变量!  
	int memLen = m_msg.GetLength() * sizeof(wchar_t) + 2;

	HANDLE hGloBal = GlobalAlloc(GHND,memLen);   //malloc  calloc  relloc 

	void* memAddr = GlobalLock(hGloBal);

	ZeroMemory(memAddr, memLen);

	memcpy(memAddr, (const void*)m_msg.GetBuffer(), memLen);

	GlobalUnlock(hGloBal);

	//操作剪贴板!  怎么把大象装进冰箱!
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hGloBal);
	CloseClipboard();
}





