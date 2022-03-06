#include "../includes/FSM.h"

void FSM::Advance()
{
	if (!eventQueue.empty())
	{
		switch (eventQueue.front())
		{
		case fsm::ONSTARTUP:
			break;
		case fsm::ONINITED:
			break;
		case fsm::GETINTFILE:
			break;
		case fsm::ONSETTING:
			break;
		case fsm::ONDOWNLOAD:
			break;
		case fsm::ONCONFIGURE:
			break;
		case fsm::ONFLASH:
			break;
		case fsm::ONSELECT:
			break;
		case fsm::ONEXIT:
			break;
		case fsm::RET_MENU:
			break;
		case fsm::RET_INETFILE:
			break;
		case fsm::RET_SETTING:
			break;
		case fsm::RET_CONFIGURE:
			break;
		}
	}
}

void FSM::OnStartup()
{
	fsmState = fsm::STARTUP;
	fsm::printInfo();
	atexit(fsm::cleanFile);
	menulist.push_back({"���ع̼�","���������ع̼�" });
	menulist.push_back({ "����","�����������" });
	menulist.push_back({ "��ʼˢ��","�����й̼����豸ˢ��" });
	menulist.push_back({ "�˳�","�˳�����" });
	eventQueue.push(fsm::ONINITED);
}

void FSM::OnInited()
{
	fsmState = fsm::MENU;
}

void FSM::OnMenu()
{
	std::cout << "���������������[���������������[     ���������������[�����[      �����������[ ���������������[�����[  �����[" << std::endl
		<< "�����X�T�T�T�T�a�^�T�T�������X�a     �����X�T�T�T�T�a�����U     �����X�T�T�����[�����X�T�T�T�T�a�����U  �����U" << std::endl
		<< "�����������[    �������X�a�����������[�����������[  �����U     ���������������U���������������[���������������U" << std::endl
		<< "�����X�T�T�a   �������X�a �^�T�T�T�T�a�����X�T�T�a  �����U     �����X�T�T�����U�^�T�T�T�T�����U�����X�T�T�����U" << std::endl
		<< "���������������[���������������[     �����U     ���������������[�����U  �����U���������������U�����U  �����U" << std::endl
		<< "�^�T�T�T�T�T�T�a�^�T�T�T�T�T�T�a     �^�T�a     �^�T�T�T�T�T�T�a�^�T�a  �^�T�a�^�T�T�T�T�T�T�a�^�T�a  �^�T�a" << std::endl << std::endl;
	fsm::listMenu(menulist);

	fsmState = fsm::MENU;
}

void FSM::GetInetFile()
{
	fsmState = fsm::INETFILE;
}

void FSM::OnSetting()
{
	fsmState = fsm::SETTING;
}

void FSM::OnDownload()
{
	fsmState = fsm::DOWNLOAD;
}

void FSM::OnConfigure()
{
	fsmState = fsm::CONFIGURE;
}

void FSM::OnFlash()
{
	fsmState = fsm::FLASH;
}

void FSM::OnSelect()
{
	fsmState = fsm::SELECT;
}

void FSM::OnExit()
{
	fsmState = fsm::EXIT;
}

void FSM::RetMenu()
{
	fsmState = fsm::MENU;
}

void FSM::RetInetfile()
{
	fsmState = fsm::INETFILE;
}

void FSM::RetSetting()
{
	fsmState = fsm::SETTING;
}

void FSM::RetConfigure()
{
	fsmState = fsm::CONFIGURE;
}
