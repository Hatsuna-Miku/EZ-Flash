#include "../includes/FSM.h"

std::vector<std::string> createfilelist;
/*
* 函数
*/
char* FSM::wideCharToMultiByte(const wchar_t* pWCStrKey)
{
    //第一次调用确认转换后单字节字符串的长度，用于开辟空间
    int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
    char* pCStrKey = new char[pSize + 1];
    //第二次调用将双字节字符串转换成单字节字符串
    WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
    pCStrKey[pSize] = '\0';
    return pCStrKey;

    //如果想要转换成string，直接赋值即可
    //string pKey = pCStrKey;
}

LPCWSTR FSM::stringToLPCWSTR(std::string orig)
{
    size_t origsize = orig.length() + 1;
    size_t convertedChars = 0;
    wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1) + 4);
    mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
    return wcstring;
}

std::vector<fsm::serialDev> FSM::getComPortList()
{
    HKEY hKey;
    wchar_t w_portName[256], w_commName[256];
    std::vector <fsm::serialDev> retval;
    fsm::serialDev device;
    //打开串口注册表对应的键值  
    if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Hardware\\DeviceMap\\SerialComm"), NULL, KEY_READ, &hKey))
    {
        int i = 0;
        int mm = 0;
        DWORD  dwLong, dwSize;
        while (TRUE)
        {
            dwLong = dwSize = sizeof(w_portName);
            //枚举串口
            if (ERROR_NO_MORE_ITEMS == ::RegEnumValue(hKey, i, w_portName, &dwLong, NULL, NULL, (PUCHAR)w_commName, &dwSize))
            {
                break;
            }
            device.comm = wideCharToMultiByte(w_commName);
            device.portName = wideCharToMultiByte(w_portName);
            retval.push_back(device);
            i++;
        }
        //关闭注册表
        RegCloseKey(hKey);
    }
    else
    {
        //MessageBox(NULL, L"您的计算机的注册表上没有HKEY_LOCAL_MACHINE:Hardware\\DeviceMap\\SerialComm项", L"警告", MB_OK);
    }
    //返回串口
    return retval;
}


int FSM::downloadFile(std::string url, std::string filename)
{

    DeleteFileW(stringToLPCWSTR(filename));
    //std::cout << "downloading: " << url << " as: " << filename << std::endl;
    DeleteUrlCacheEntryW(stringToLPCWSTR(url));
    HRESULT ret = URLDownloadToFileW( // 从网络上下载数据到本地文件
        nullptr,                  // 在这里，写 nullptr 就行
        stringToLPCWSTR(url), // 在这里写上网址
        stringToLPCWSTR(filename),            // 文件名写在这
        0,                        // 写 0 就对了
        nullptr                   // 也是，在这里写 nullptr 就行
    );
    createfilelist.push_back(filename);

    if (ret != S_OK)
        //std::cout << "fail" << std::endl;
        return -1;
    //std::cout << "OK" << std::endl;
    return 0;
}


int FSM::exeCmd(fsm::flashconf Config)
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

std::vector<fsm::optiontype> FSM::listCom(std::vector<fsm::serialDev> comlist)
{
    std::vector<fsm::optiontype> entrylist;
    std::cout << strings.serlist_serlist << std::endl;
    int j = 1;
    for (auto i : comlist)
    {
        std::cout << j << '\t';
        std::cout << i.comm << '\t';
        std::cout << i.portName << std::endl;
        entrylist.push_back({ fsm::INCLUDE,0,char(j + 48) });
        j++;
    }
    entrylist.push_back({ fsm::INCLUDE,0,'r' });
    entrylist.push_back({ fsm::INCLUDE,0,'q' });
    std::cout << strings.serlist_menunotice << std::endl;
    return entrylist;
}

fsm::devicefwinfo FSM::parseConfigLine(std::string line)
{
    fsm::devicefwinfo info;
    std::istringstream pieces(line);
    pieces >> info.model;
    pieces >> info.version;
    pieces >> info.url;
    pieces >> info.description;
    pieces >> info.notice;
    return info;
}

std::vector<fsm::devicefwinfo> FSM::parseConfig()
{
    std::string fileline;
    std::fstream configfile(DEVICE_UPDATE_CONF);
    std::vector<fsm::devicefwinfo> devicelist;
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

inline void FSM::getUpdateConfig()
{
    std::cout << strings.getinet_fetchingfilelist << std::endl;
    downloadFile(DEVICE_UPDATE_CONF_URL, DEVICE_UPDATE_CONF);
    /*
    while (!downloadFile(DEVICE_UPDATE_CONF_URL, DEVICE_UPDATE_CONF))
    {
        std::cout << "." << std::endl;
    };*/
}

int FSM::releaseExe()
{
    //定义操作类对象
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

std::vector<fsm::optiontype> FSM::listFirmwareInfo(std::vector<fsm::devicefwinfo> fwlist, fsm::cursortype cursor)
{
    std::vector<fsm::optiontype> entrylist;
    std::cout << strings.inetfile_filelist << std::endl;
    std::size_t i;
    for (i = (cursor.page - 1) * 9; (i < fwlist.size()) && i < (cursor.page * 9 - 1); i++)
    {
        if ((i % 9 + 1) == cursor.option)
        {
            //SetConsoleTextAttribute(cursor.hOut, 0xF0);
        }
        std::cout << i % 9 + 1 << '\t';
        std::cout << fwlist[i].model << "\t";
        std::cout << fwlist[i].version << "\t";
        std::cout << fwlist[i].description << std::endl;
        if ((i % 9 + 1) == cursor.option)
        {
            //SetConsoleTextAttribute(cursor.hOut, 0x0F);
        }
        entrylist.push_back({ fsm::INCLUDE,0,char(i % 9 + 49) });
    }
    std::cout << languages::pageindicator(lang, cursor.page, cursor.allpage) << std::endl;
    entrylist.push_back({ fsm::INCLUDE,0,'r' });
    entrylist.push_back({ fsm::INCLUDE,0,'q' });
    entrylist.push_back({ fsm::INCLUDE,0,'[' });
    entrylist.push_back({ fsm::INCLUDE,0,']' });
    std::cout << strings.inetfile_notice << std::endl;
    return entrylist;
}

int FSM::getKbdLoop()
{
    while (!_kbhit())
    {
        return _getch();
    }
}


void FSM::cleanFile()
{
    for (auto i : createfilelist)
    {
        std::remove(const_cast<char*>(i.c_str()));
    }
}

int FSM::getOption(int setting)//过时的函数
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

char FSM::getOption(std::vector<fsm::optiontype> options)
{
    int ch;
    bool isfunctionkey = 0;
    bool inaggregate = 0;//指示是否在处理集合
    fsm::optiontype leftedge;
    std::vector<fsm::optiontype> excludes;
    while (1)//假如未返回则循环
    {
        ch = getKbdLoop();//获取按键
        //std::cout << ch << std::endl;
        if (ch == 0x00 || ch == 0xE0)//判断按下的是否为功能键
        {
            isfunctionkey = 1;
            ch = getKbdLoop();//功能键须二次获取
            //std::cout << ch << std::endl;
        }
        for (auto i : options)//遍历选项列表
        {
            if (isfunctionkey == i.isfunctionkey)//如按键类型和条目类型不一样则直接跳过
            {
                switch (i.aggregatetype)
                {
                case fsm::INCLUDE:
                    if (ch == i.value)
                    {
                        return ch;
                    }
                    break;
                case fsm::EXCLUDE:
                    if (inaggregate)
                    {
                        excludes.push_back(i);
                    }
                    break;
                case fsm::MORE_THAN:
                    if (ch > i.value)
                    {
                        inaggregate = 1;
                        leftedge = i;
                    }
                    break;
                case fsm::LESS_THAN:
                    if (inaggregate)
                    {
                        if (ch < i.value)
                        {
                            bool pass = 0;
                            switch (leftedge.aggregatetype)
                            {
                            case fsm::MORE_THAN:
                                if (ch > leftedge.value)
                                {
                                    pass = 1;
                                }
                                break;
                            case fsm::NOT_LESS_THAN:
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
                case fsm::NOT_LESS_THAN:
                    if (ch >= i.value)
                    {
                        inaggregate = 1;
                        leftedge = i;
                    }
                    break;
                case fsm::NOT_MORE_THAN:
                    if (inaggregate)
                    {
                        if (ch <= i.value)
                        {
                            bool pass = 0;
                            switch (leftedge.aggregatetype)
                            {
                            case fsm::MORE_THAN:
                                if (ch > leftedge.value)
                                {
                                    pass = 1;
                                }
                                break;
                            case fsm::NOT_LESS_THAN:
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

void FSM::printInfo()
{
    std::cout << "ETFlasher " << TOOL_VERSION << " By " << AUTHUR << '\t' << URL << std::endl << std::endl;
}
std::vector<fsm::optiontype> FSM::listMenu(std::vector<fsm::menuoption> menulist)
{
    std::vector<fsm::optiontype> optionlist;
    std::cout << strings.menu_menu << std::endl;
    for (auto i : menulist)
    {
        std::cout << i.key << '\t';
        std::cout << i.name << "\t";
        std::cout << i.description << std::endl;
        optionlist.push_back({ fsm::INCLUDE,0,i.key });
    }
    std::cout << strings.menu_menunotice << std::endl;
    return optionlist;
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
        case fsm::GETINETFILE:
            GetInetFile();
            break;
        case fsm::ONINETFILE:
            OnInetFile();
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
	printInfo();
    LCID localeID = GetUserDefaultLCID();
    lang = localeID && 0xFF;
    strings = languages::loadstring(lang);
    menulist.clear();
	menulist.push_back({ '1',strings.menu_option_download,strings.menu_option_download_description });
	menulist.push_back({ '2',strings.menu_option_settings,strings.menu_option_settings_description });
	menulist.push_back({ '3',strings.menu_option_flash,strings.menu_option_flash_description });
	menulist.push_back({ 'q',strings.menu_option_quit,strings.menu_option_quit_description });
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
	printInfo();
	std::cout << "███████╗███████╗     ███████╗██╗      █████╗ ███████╗██╗  ██╗" << std::endl
		<< "██╔════╝╚══███╔╝     ██╔════╝██║     ██╔══██╗██╔════╝██║  ██║" << std::endl
		<< "█████╗    ███╔╝█████╗█████╗  ██║     ███████║███████╗███████║" << std::endl
		<< "██╔══╝   ███╔╝ ╚════╝██╔══╝  ██║     ██╔══██║╚════██║██╔══██║" << std::endl
		<< "███████╗███████╗     ██║     ███████╗██║  ██║███████║██║  ██║" << std::endl
		<< "╚══════╝╚══════╝     ╚═╝     ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝" << std::endl << std::endl;
	optionlist = listMenu(menulist);
	eventQueue.push(fsm::ONSELECT);
	eventQueue.push(fsm::RET_MENU);
}

void FSM::GetInetFile()
{
	fsmState = fsm::GETINET;
    system("cls");
	getUpdateConfig();
	fwlist = parseConfig();
    cursor.allpage = fwlist.size() / 9 + ((fwlist.size() % 9 != 0) ? 1 : 0);
    eventQueue.push(fsm::ONINETFILE);
}

void FSM::OnInetFile()
{
    fsmState = fsm::INETFILE;
    system("cls");
    optionlist.clear();
    optionlist = listFirmwareInfo(fwlist, cursor);
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
    int target = option - 49 + (cursor.page - 1) * 9;
	fsmState = fsm::DOWNLOAD;
	downloadFile(fwlist[target].url, "FIRMWARE_" + fwlist[target].model + ".bin");
	flashConfig.filename = "FIRMWARE_" + fwlist[target].model + ".bin";
    flashnotice = fwlist[target].notice;
	eventQueue.push(fsm::ONINETFILE);
}

void FSM::OnConfigure()
{
	fsmState = fsm::CONFIGURE;
	system("cls");
	optionlist.clear();
	seriallist = getComPortList();
	optionlist = listCom(seriallist);
	eventQueue.push(fsm::ONSELECT);
	eventQueue.push(fsm::RET_CONFIGURE);
}

void FSM::OnFlash()
{
	fsmState = fsm::FLASH;
	std::cout << std::endl;
	SetConsoleTextAttribute(hOut, 207);
	std::cout << strings.flash_notice << flashnotice << std::endl << std::endl;
	SetConsoleTextAttribute(hOut, 15);
	system("pause");
	exeCmd(flashConfig);
	optionlist.clear();
	optionlist.push_back({ fsm::INCLUDE,0,'y' });
	optionlist.push_back({ fsm::INCLUDE,0,'n' });
	optionlist.push_back({ fsm::INCLUDE,0,'q' });
	std::cout << strings.flash_optionnotice << std::endl;
	eventQueue.push(fsm::ONSELECT);
	eventQueue.push(fsm::RET_FLASH);
}

void FSM::OnSelect()
{
	fsmState = fsm::SELECT;
	option = getOption(optionlist);
}

void FSM::OnExit()
{
	fsmState = fsm::EXIT;
    cleanFile();
}

void FSM::RetMenu()
{
	fsmState = fsm::MENU;
	switch (option)
	{
	case '1':
		eventQueue.push(fsm::GETINETFILE);
		break;
	case '2':
		eventQueue.push(fsm::ONSETTING);
		break;
	case '3':
		releaseExe();
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
		eventQueue.push(fsm::GETINETFILE);
		break;
	case 'q':
		eventQueue.push(fsm::ONMENU);
		break;
    case '[':
        if (cursor.page > 1)
        {
            cursor.page = cursor.page - 1;
        }
        eventQueue.push(fsm::ONINETFILE);
        break;
    case ']':
        if (cursor.page < cursor.allpage)
        {
            cursor.page = cursor.page + 1;
        }
        eventQueue.push(fsm::ONINETFILE);
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
