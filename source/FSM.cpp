#include "../includes/FSM.h"

namespace fsm
{

    std::vector<std::string> createfilelist;
    /*
    * ����
    */
    char* wideCharToMultiByte(const wchar_t* pWCStrKey)
    {
        //��һ�ε���ȷ��ת�����ֽ��ַ����ĳ��ȣ����ڿ��ٿռ�
        int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
        char* pCStrKey = new char[pSize + 1];
        //�ڶ��ε��ý�˫�ֽ��ַ���ת���ɵ��ֽ��ַ���
        WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
        pCStrKey[pSize] = '\0';
        return pCStrKey;

        //�����Ҫת����string��ֱ�Ӹ�ֵ����
        //string pKey = pCStrKey;
    }

    LPCWSTR stringToLPCWSTR(std::string orig)
    {
        size_t origsize = orig.length() + 1;
        size_t convertedChars = 0;
        wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1) + 4);
        mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
        return wcstring;
    }

    std::vector<serialDev> getComPortList()
    {
        HKEY hKey;
        wchar_t w_portName[256], w_commName[256];
        std::vector <serialDev> retval;
        serialDev device;
        //�򿪴���ע����Ӧ�ļ�ֵ  
        if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Hardware\\DeviceMap\\SerialComm"), NULL, KEY_READ, &hKey))
        {
            int i = 0;
            int mm = 0;
            DWORD  dwLong, dwSize;
            while (TRUE)
            {
                dwLong = dwSize = sizeof(w_portName);
                //ö�ٴ���
                if (ERROR_NO_MORE_ITEMS == ::RegEnumValue(hKey, i, w_portName, &dwLong, NULL, NULL, (PUCHAR)w_commName, &dwSize))
                {
                    break;
                }
                device.comm = wideCharToMultiByte(w_commName);
                device.portName = wideCharToMultiByte(w_portName);
                retval.push_back(device);
                i++;
            }
            //�ر�ע���
            RegCloseKey(hKey);
        }
        else
        {
            //MessageBox(NULL, L"���ļ������ע�����û��HKEY_LOCAL_MACHINE:Hardware\\DeviceMap\\SerialComm��", L"����", MB_OK);
        }
        //���ش���
        return retval;
    }


    int downloadFile(std::string url, std::string filename)
    {

        DeleteFileW(stringToLPCWSTR(filename));
        //std::cout << "downloading: " << url << " as: " << filename << std::endl;
        DeleteUrlCacheEntryW(stringToLPCWSTR(url));
        HRESULT ret = URLDownloadToFileW( // ���������������ݵ������ļ�
            nullptr,                  // �����д nullptr ����
            stringToLPCWSTR(url), // ������д����ַ
            stringToLPCWSTR(filename),            // �ļ���д����
            0,                        // д 0 �Ͷ���
            nullptr                   // Ҳ�ǣ�������д nullptr ����
        );
        createfilelist.push_back(filename);

        if (ret != S_OK)
            //std::cout << "fail" << std::endl;
            return -1;
        //std::cout << "OK" << std::endl;
        return 0;
    }


    int exeCmd(flashconf Config)
    {
        FILE* fp;
        char buf[255] = { 0 };
        std::string cmd, toolname;
        toolname = wideCharToMultiByte(ESPTOOL_NAME);
        cmd = toolname + " --port " + Config.port + " --chip esp8266 --baud 921600 --before default_reset  --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size 4MB 0x0 " + Config.filename;
        //std::cout << cmd << std::endl;
        if ((fp = _popen(const_cast<char*>(cmd.c_str()), "r")) == NULL) {
            perror("Fail to popen\n");
            exit(1);
        }
        while (fgets(buf, 255, fp) != NULL) {
            printf("%s", buf);
        }
        _pclose(fp);
        return 0;
    }

    std::vector<optiontype> listCom(std::vector<serialDev> comlist)
    {
        std::vector<optiontype> entrylist;
        std::cout << "�����б�:" << std::endl;
        int j = 1;
        for (auto i : comlist)
        {
            std::cout << j << '\t';
            std::cout << i.comm << '\t';
            std::cout << i.portName << std::endl;
            entrylist.push_back({ INCLUDE,0,char(j + 48) });
            j++;
        }
        entrylist.push_back({ INCLUDE,0,'r' });
        entrylist.push_back({ INCLUDE,0,'q' });
        std::cout << "��1~9ѡ��,��rˢ��,��q������һ����" << std::endl;
        return entrylist;
    }

    devicefwinfo parseConfigLine(std::string line)
    {
        devicefwinfo info;
        std::istringstream pieces(line);
        pieces >> info.model;
        pieces >> info.version;
        pieces >> info.url;
        pieces >> info.description;
        pieces >> info.notice;
        return info;
    }

    std::vector<devicefwinfo> parseConfig()
    {
        std::string fileline;
        std::fstream configfile(DEVICE_UPDATE_CONF);
        std::vector<devicefwinfo> devicelist;
        if (!configfile.is_open())
        {
            //return -1;
        }
        while (getline(configfile, fileline))
        {
            devicelist.push_back(parseConfigLine(fileline));
        }
        return devicelist;
    }

    inline void getUpdateConfig()
    {
        std::cout << "���ڴӷ�������ȡ�̼��б�����" << std::endl;
        downloadFile(DEVICE_UPDATE_CONF_URL, DEVICE_UPDATE_CONF);
        /*
        while (!downloadFile(DEVICE_UPDATE_CONF_URL, DEVICE_UPDATE_CONF))
        {
            std::cout << "." << std::endl;
        };*/
    }

    int releaseExe()
    {
        //������������
        CReleaseDLL releasehelper;
        bool blRes;
        remove(wideCharToMultiByte(const_cast<wchar_t*>(ESPTOOL_NAME)));
        blRes = releasehelper.FreeResFile(IDR_EXECUTABLE2, L"EXECUTABLE", ESPTOOL_NAME);
        createfilelist.push_back(wideCharToMultiByte(const_cast<wchar_t*>(ESPTOOL_NAME)));
        if (blRes)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }

    std::vector<optiontype> listFirmwareInfo(std::vector<devicefwinfo> fwlist)
    {
        std::vector<optiontype> entrylist;
        std::cout << "�̼��б�" << std::endl;
        int j = 1;
        for (auto i : fwlist)
        {
            std::cout << j << '\t';
            std::cout << i.model << "\t";
            std::cout << i.version << "\t";
            std::cout << i.description << std::endl;
            entrylist.push_back({ INCLUDE,0,char(j + 48) });
            j++;
        }
        entrylist.push_back({ INCLUDE,0,'r' });
        entrylist.push_back({ INCLUDE,0,'q' });
        std::cout << "��1~9ѡ��,��rˢ��,��q������һ����" << std::endl;
        return entrylist;
    }

    int getKbdLoop()
    {
        while (!_kbhit())
        {
            return _getch();
        }
    }


    void cleanFile()
    {
        for (auto i : createfilelist)
        {
            std::remove(const_cast<char*>(i.c_str()));
        }
    }

    int getOption(int setting)//��ʱ�ĺ���
    {
        int ch;
        while (1)
        {
            ch = getKbdLoop();
            if (setting == GET_NUMKEY)
            {
                if (ch >= '0' || ch <= '9')
                {
                    return ch - '0';
                }
            }
            else if (setting == GET_CHARKEY)
            {
                if (ch >= 'a' || ch <= 'z')
                {
                    return ch - 'a';
                }
            }
            else if (setting == GET_YESORNO)
            {
                if (ch == 'y' || ch <= 'n')
                {
                    return ch;
                }
            }
        }
    }

    char getOption(std::vector<optiontype> options)
    {
        int ch;
        bool isfunctionkey = 0;
        bool inaggregate = 0;//ָʾ�Ƿ��ڴ�����
        optiontype leftedge;
        std::vector<optiontype> excludes;
        while (1)//����δ������ѭ��
        {
            ch = getKbdLoop();//��ȡ����
            //std::cout << ch << std::endl;
            if (ch == 0x00 || ch == 0xE0)//�жϰ��µ��Ƿ�Ϊ���ܼ�
            {
                isfunctionkey = 1;
                ch = getKbdLoop();//���ܼ�����λ�ȡ
                //std::cout << ch << std::endl;
            }
            for (auto i : options)//����ѡ���б�
            {
                if (isfunctionkey == i.isfunctionkey)//�簴�����ͺ���Ŀ���Ͳ�һ����ֱ������
                {
                    switch (i.aggregatetype)
                    {
                    case INCLUDE:
                        if (ch == i.value)
                        {
                            return ch;
                        }
                        break;
                    case EXCLUDE:
                        if (inaggregate)
                        {
                            excludes.push_back(i);
                        }
                        break;
                    case MORE_THAN:
                        if (ch > i.value)
                        {
                            inaggregate = 1;
                            leftedge = i;
                        }
                        break;
                    case LESS_THAN:
                        if (inaggregate)
                        {
                            if (ch < i.value)
                            {
                                bool pass = 0;
                                switch (leftedge.aggregatetype)
                                {
                                case MORE_THAN:
                                    if (ch > leftedge.value)
                                    {
                                        pass = 1;
                                    }
                                    break;
                                case NOT_LESS_THAN:
                                    if (ch >= leftedge.value)
                                    {
                                        pass = 1;
                                    }
                                    break;
                                }
                                if (pass)
                                {
                                    for (auto j : excludes)
                                    {
                                        if (j.value == ch)
                                        {
                                            pass = 0;
                                            break;
                                        }
                                    }
                                }
                                if (pass)
                                {
                                    return ch;
                                }
                                inaggregate = 0;
                                excludes.clear();
                            }
                        }
                        break;
                    case NOT_LESS_THAN:
                        if (ch >= i.value)
                        {
                            inaggregate = 1;
                            leftedge = i;
                        }
                        break;
                    case NOT_MORE_THAN:
                        if (inaggregate)
                        {
                            if (ch <= i.value)
                            {
                                bool pass = 0;
                                switch (leftedge.aggregatetype)
                                {
                                case MORE_THAN:
                                    if (ch > leftedge.value)
                                    {
                                        pass = 1;
                                    }
                                    break;
                                case NOT_LESS_THAN:
                                    if (ch >= leftedge.value)
                                    {
                                        pass = 1;
                                    }
                                    break;
                                }
                                if (pass)
                                {
                                    for (auto j : excludes)
                                    {
                                        if (j.value == ch)
                                        {
                                            pass = 0;
                                            break;
                                        }
                                    }
                                }
                                if (pass)
                                {
                                    return ch;
                                }
                                inaggregate = 0;
                                excludes.clear();
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

    void printInfo()
    {
        std::cout << "ETFlasher " << TOOL_VERSION << " By " << AUTHUR << '\t' << URL << std::endl << std::endl;
    }
    std::vector<optiontype> listMenu(std::vector<menuoption> menulist)
    {
        std::vector<optiontype> optionlist;
        std::cout << "�˵���" << std::endl;
        for (auto i : menulist)
        {
            std::cout << i.key << '\t';
            std::cout << i.name << "\t";
            std::cout << i.description << std::endl;
            optionlist.push_back({ INCLUDE,0,i.key });
        }
        std::cout << "ѡ��ѡ�" << std::endl;
        return optionlist;
    }
}

int FSM::Advance()
{
	bool shutdownSignal = 0;
	if (!eventQueue.empty())
	{
		switch (eventQueue.front())
		{
		case fsm::ONSTARTUP:
			OnStartup();
			break;
		case fsm::ONINITED:
			OnInited();
			break;
		case fsm::ONMENU:
			OnMenu();
			break;
		case fsm::GETINTFILE:
			GetInetFile();
			break;
		case fsm::ONSETTING:
			OnSetting();
			break;
		case fsm::ONDOWNLOAD:
			OnDownload();
			break;
		case fsm::ONCONFIGURE:
			OnConfigure();
			break;
		case fsm::ONFLASH:
			OnFlash();
			break;
		case fsm::ONSELECT:
			OnSelect();
			break;
		case fsm::ONEXIT:
			OnExit();
			shutdownSignal = 1;
			break;
		case fsm::RET_MENU:
			RetMenu();
			break;
		case fsm::RET_INETFILE:
			RetInetfile();
			break;
		case fsm::RET_SETTING:
			RetSetting();
			break;
		case fsm::RET_CONFIGURE:
			RetConfigure();
			break;
        case fsm::RET_FLASH:
            RetFlash();
            break;
		}
        eventQueue.pop();
		if (shutdownSignal)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

void FSM::OnStartup()
{
	fsmState = fsm::STARTUP;
	fsm::printInfo();
	atexit(fsm::cleanFile);
    menulist.clear();
	menulist.push_back({ '1',"����","���������ع̼�" });
	menulist.push_back({ '2',"����","�����������" });
	menulist.push_back({ '3',"ˢ��","�����й̼����豸ˢ��" });
	menulist.push_back({ 'q',"�˳�","�˳�����" });
	eventQueue.push(fsm::ONINITED);
}

void FSM::OnInited()
{
	fsmState = fsm::INITED;
	eventQueue.push(fsm::ONMENU);
}

void FSM::OnMenu()
{
	fsmState = fsm::MENU;
	optionlist.clear();
	system("cls");
	fsm::printInfo();
	std::cout << "���������������[���������������[     ���������������[�����[      �����������[ ���������������[�����[  �����[" << std::endl
		<< "�����X�T�T�T�T�a�^�T�T�������X�a     �����X�T�T�T�T�a�����U     �����X�T�T�����[�����X�T�T�T�T�a�����U  �����U" << std::endl
		<< "�����������[    �������X�a�����������[�����������[  �����U     ���������������U���������������[���������������U" << std::endl
		<< "�����X�T�T�a   �������X�a �^�T�T�T�T�a�����X�T�T�a  �����U     �����X�T�T�����U�^�T�T�T�T�����U�����X�T�T�����U" << std::endl
		<< "���������������[���������������[     �����U     ���������������[�����U  �����U���������������U�����U  �����U" << std::endl
		<< "�^�T�T�T�T�T�T�a�^�T�T�T�T�T�T�a     �^�T�a     �^�T�T�T�T�T�T�a�^�T�a  �^�T�a�^�T�T�T�T�T�T�a�^�T�a  �^�T�a" << std::endl << std::endl;
	optionlist = fsm::listMenu(menulist);
	eventQueue.push(fsm::ONSELECT);
	eventQueue.push(fsm::RET_MENU);
}

void FSM::GetInetFile()
{
	fsmState = fsm::INETFILE;
	system("cls");
	optionlist.clear();
	fsm::getUpdateConfig();
	fwlist = fsm::parseConfig();
	optionlist = fsm::listFirmwareInfo(fwlist);
	eventQueue.push(fsm::ONSELECT);
	eventQueue.push(fsm::RET_INETFILE);
}

void FSM::OnSetting()
{
	fsmState = fsm::SETTING;
	eventQueue.push(fsm::ONMENU);
}

void FSM::OnDownload()
{
	fsmState = fsm::DOWNLOAD;
	fsm::downloadFile(fwlist[option - 49].url, "FIRMWARE_" + fwlist[option - 49].model + ".bin");
	flashConfig.filename = "FIRMWARE_" + fwlist[option - 49].model + ".bin";
    flashnotice = fwlist[option - 49].notice;
	eventQueue.push(fsm::GETINTFILE);
}

void FSM::OnConfigure()
{
	fsmState = fsm::CONFIGURE;
	system("cls");
	optionlist.clear();
	seriallist = fsm::getComPortList();
	optionlist = fsm::listCom(seriallist);
	eventQueue.push(fsm::ONSELECT);
	eventQueue.push(fsm::RET_CONFIGURE);
}

void FSM::OnFlash()
{
	fsmState = fsm::FLASH;
	std::cout << std::endl;
	SetConsoleTextAttribute(hOut, 207);
	std::cout << "��ʾ��������ʼˢ����" << flashnotice << std::endl << std::endl;
	SetConsoleTextAttribute(hOut, 15);
	system("pause");
	exeCmd(flashConfig);
	optionlist.clear();
	optionlist.push_back({ fsm::INCLUDE,0,'y' });
	optionlist.push_back({ fsm::INCLUDE,0,'n' });
	optionlist.push_back({ fsm::INCLUDE,0,'q' });
	std::cout << "�Ƿ����ˢ��һ����(y/n),��q�˳�����" << std::endl;
	eventQueue.push(fsm::ONSELECT);
	eventQueue.push(fsm::RET_FLASH);
}

void FSM::OnSelect()
{
	fsmState = fsm::SELECT;
	option = fsm::getOption(optionlist);
}

void FSM::OnExit()
{
	fsmState = fsm::EXIT;
}

void FSM::RetMenu()
{
	fsmState = fsm::MENU;
	switch (option)
	{
	case '1':
		eventQueue.push(fsm::GETINTFILE);
		break;
	case '2':
		eventQueue.push(fsm::ONSETTING);
		break;
	case '3':
		fsm::releaseExe();
		eventQueue.push(fsm::ONCONFIGURE);
		break;
	case 'q':
		eventQueue.push(fsm::ONEXIT);
		break;
	}
}

void FSM::RetInetfile()
{
	fsmState = fsm::INETFILE;
	switch (option)
	{
	case 'r':
		eventQueue.push(fsm::GETINTFILE);
		break;
	case 'q':
		eventQueue.push(fsm::ONMENU);
		break;
	default:
		eventQueue.push(fsm::ONDOWNLOAD);
		break;
	}
}

void FSM::RetSetting()
{
	fsmState = fsm::SETTING;
	eventQueue.push(fsm::ONSETTING);
}

void FSM::RetConfigure()
{
	fsmState = fsm::CONFIGURE;
	switch (option)
	{
	case 'r':
		eventQueue.push(fsm::ONCONFIGURE);
		break;
	case 'q':
		eventQueue.push(fsm::ONMENU);
		break;
	default:
		flashConfig.port = seriallist[option - 49].comm;
		eventQueue.push(fsm::ONFLASH);
		break;
	}
}

void FSM::RetFlash()
{
	fsmState = fsm::CONFIGURE;
	switch (option)
	{
	case 'y':
		eventQueue.push(fsm::ONCONFIGURE);
		break;
	case 'n':
		eventQueue.push(fsm::ONMENU);
		break;
	case 'q':
		eventQueue.push(fsm::ONEXIT);
		break;
	}
}
