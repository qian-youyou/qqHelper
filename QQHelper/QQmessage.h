#pragma once
class QQmessage
{
public:
	QQmessage();
	~QQmessage();

	//������ 
	static QQmessage *Instance()
	{
		static QQmessage object;
		
		return &object;
	}

	//��ں���
	void Start(const wchar_t *msg);

private:
	//��ʼ�߳�
	static unsigned int WINAPI RunThreadproc(void* param);
	
	//����������
	void SendAll();

	//�ҵ�QQ����
	HWND FindQQWindow();

	//ģ�ⰴ��
	void PressKey(BYTE vkey);

	//������Ϣ
	void SendMsg();

	//����ı���������
	void AddTextToClipboard();

private:
	CString m_msg;
};

