#include "stdafx.h"
#include "QQmessage.h"


QQmessage::QQmessage()
{
}


QQmessage::~QQmessage()
{
}

//��ں���
void QQmessage::Start(const wchar_t *msg)
{
	m_msg = CString(msg); //������ı�

	_beginthreadex(NULL, 0, QQmessage::RunThreadproc, NULL, 0, NULL);
}

//��ʼ�߳�
unsigned int QQmessage::RunThreadproc(void* param)
{
	QQmessage::Instance()->SendAll();
	return 0;
}

//����������
void QQmessage::SendAll()
{
	int errorTimes = 0;  //�򿪶Ի������Ĵ���!
	//��text���Ƶ�������
	AddTextToClipboard();

	//��������. ����Ŀ����.
	while (errorTimes<= 4)
	{
		HWND hQQWnd = FindQQWindow();
		HWND hFrontWnd = GetForegroundWindow(); 

		if (hQQWnd != hFrontWnd)
		{
			if (!SetForegroundWindow(hQQWnd))
			{
				MessageBox(NULL, L"û���ҵ�QQ����", NULL, NULL);
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

//�ҵ�QQ����
HWND QQmessage::FindQQWindow()
{
	HWND hWnd = FindWindow(L"TXGuiFoundation",L"QQ");  //Find  Window //��ȡQQ�Ĵ���!!!
	
	//�������߾�����ô����
	return hWnd;
}

//ģ�ⰴ��
void QQmessage::PressKey(BYTE vkey)
{
	keybd_event(vkey, 0, 0, 0);  //����(0)�͵���(KEYEVENTF_KEYUP)
	Sleep(100);
	keybd_event(vkey, 0, KEYEVENTF_KEYUP, 0);  //�û�TAB
	Sleep(100);
}

//������Ϣ  16GU��
void QQmessage::SendMsg()
{
	//ճ��  +  ����
	keybd_event(VK_CONTROL, 0, 0, 0);  //����(0)�͵���(KEYEVENTF_KEYUP)
	Sleep(100);
	keybd_event(0x56, 0, 0, 0);  //����(0)�͵���(KEYEVENTF_KEYUP)
	Sleep(100);

	keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);  //�û�TAB
	Sleep(100);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);  //�û�TAB
	Sleep(100); //��� �ʻ�ˢ����!

	//����
	PressKey(VK_RETURN);
	PressKey(VK_ESCAPE);
}

//����ı���������
void QQmessage::AddTextToClipboard()
{
	//1.���ı�������ȫ�ֱ���!  
	int memLen = m_msg.GetLength() * sizeof(wchar_t) + 2;

	HANDLE hGloBal = GlobalAlloc(GHND,memLen);   //malloc  calloc  relloc 

	void* memAddr = GlobalLock(hGloBal);

	ZeroMemory(memAddr, memLen);

	memcpy(memAddr, (const void*)m_msg.GetBuffer(), memLen);

	GlobalUnlock(hGloBal);

	//����������!  ��ô�Ѵ���װ������!
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hGloBal);
	CloseClipboard();
}





