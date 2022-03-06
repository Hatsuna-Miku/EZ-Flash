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
	menulist.push_back({"下载固件","从网络下载固件" });
	menulist.push_back({ "设置","更改软件设置" });
	menulist.push_back({ "开始刷机","用已有固件对设备刷机" });
	menulist.push_back({ "退出","退出程序" });
	eventQueue.push(fsm::ONINITED);
}

void FSM::OnInited()
{
	fsmState = fsm::MENU;
}

void FSM::OnMenu()
{
	std::cout << "███████╗███████╗     ███████╗██╗      █████╗ ███████╗██╗  ██╗" << std::endl
		<< "██╔════╝╚══███╔╝     ██╔════╝██║     ██╔══██╗██╔════╝██║  ██║" << std::endl
		<< "█████╗    ███╔╝█████╗█████╗  ██║     ███████║███████╗███████║" << std::endl
		<< "██╔══╝   ███╔╝ ╚════╝██╔══╝  ██║     ██╔══██║╚════██║██╔══██║" << std::endl
		<< "███████╗███████╗     ██║     ███████╗██║  ██║███████║██║  ██║" << std::endl
		<< "╚══════╝╚══════╝     ╚═╝     ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝" << std::endl << std::endl;
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
