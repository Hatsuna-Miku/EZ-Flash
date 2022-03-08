#pragma once
#include <windows.h>

#define MAX_DLL_PATH 1024
//�����������λ��DLL�����У��Ͷ�������ĺ꣬����ע�͵�
//#define _USER_RELEASEDLL_

//�ͷ�DLL������
class CReleaseDLL
{
public:
	CReleaseDLL();
	~CReleaseDLL();
	/*
	*function:�ͷ�DLL�ļ���������
	*[IN]:
	m_lResourceID:��Դ��ID
	m_strResourceType:��Դ����
	m_strReleasePath:��Ҫ�ͷŵ��ļ�����
	*[OUT]:
	�ͷųɹ�������TRUE�����򷵻�FALSE
	*/
	bool FreeResFile(unsigned long m_lResourceID, const wchar_t* m_strResourceType, const wchar_t* m_strFileName);
private:
	/*
	*function:��ȡģ��Ļ�ַ
	*[IN]:
	*[OUT]:
	���ػ�ȡ�Ļ�ַ
	*/
	HMODULE GetSelfModuleHandle();
private:
	//ģ���ַ
	HMODULE m_hModule;
	//����ǰĿ¼
	wchar_t m_filePath[MAX_DLL_PATH];
};