#pragma once
#include "defines.h"
#include <afx.h>
#include <afxinet.h>
#include <stdio.h> 
#include "stdlib.h"
#include <string>
#include "stdio.h"
#include <vector>
#include <queue>
#include <atlbase.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "resource.h"
#include "releaseHelper.h"
#include <conio.h>
#include <urlmon.h>

#pragma comment(lib,"urlmon.lib")

#define CONFIG_PATH 

namespace fsm
{
    /*
* 一些数据类型
*/
    std::vector<std::string> createfilelist;

    enum STATES
    {
        STARTUP,
        MENU,
        SETTING,
        INETFILE,
        DOWNLOAD,
        CONFIGURE,
        FLASH,
        SELECT,
        EXIT
    };

    enum EVENTS
    {
        ONSTARTUP,
        ONINITED,
        GETINTFILE,
        ONSETTING,
        ONDOWNLOAD,
        ONCONFIGURE,
        ONFLASH,
        ONSELECT,
        ONEXIT,
        RET_MENU,
        RET_INETFILE,
        RET_SETTING,
        RET_CONFIGURE
    };

    enum AGGREGATES
    {
        INCLUDE,
        EXCLUDE,
        MORE_THAN,
        LESS_THAN,
        NOT_LESS_THAN,
        NOT_MORE_THAN
    };

    struct serialDev
    {
        std::string comm;
        std::string portName;
    };

    struct devicefwinfo
    {
        std::string model, version, url, description, notice;
        //int ver_num;
    };

    struct flashconf
    {
        std::string port, filename;
    };

    struct menuoption
    {
        std::string name, description;
    };

    struct optiontype
    {
        AGGREGATES aggregatetype;
        bool isfunctionkey;
        char value;
    };

    /*
    * 函数
    */
    char* wideCharToMultiByte(const wchar_t* pWCStrKey)
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


    int downloadFile(std::string url, std::string filename)
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

    std::vector<serialDev> listCom()
    {
        std::vector<serialDev> comlist;
        comlist = getComPortList();
        std::cout << "串口列表" << std::endl;
        int j = 1;
        for (auto i : comlist)
        {
            std::cout << j << '\t';
            std::cout << i.comm << '\t';
            std::cout << i.portName << std::endl;
            j++;
        }
        std::cout << std::endl;
        return comlist;
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
        std::cout << "正在从服务器获取固件列表。。。" << std::endl;
        downloadFile(DEVICE_UPDATE_CONF_URL, DEVICE_UPDATE_CONF);
        /*
        while (!downloadFile(DEVICE_UPDATE_CONF_URL, DEVICE_UPDATE_CONF))
        {
            std::cout << "." << std::endl;
        };*/
    }

    int releaseExe()
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

    int listFirmwareInfo(std::vector<devicefwinfo> fwlist)
    {
        std::cout << "固件列表：" << std::endl;
        int j = 1;
        for (auto i : fwlist)
        {
            std::cout << j << '\t';
            std::cout << i.model << "\t";
            std::cout << i.version << "\t";
            std::cout << i.description << std::endl;
            j++;
        }
        std::cout << std::endl;
        return 0;
    }

    int getKbdLoop()
    {
        while (!kbhit())
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

    int getOption(int setting)
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
        bool inaggregate = 0;//指示是否在处理集合
        optiontype leftedge;
        std::vector<optiontype> excludes;
        while (1)
        {
            ch = getKbdLoop();
            if (ch == 0x00 || ch == 0xE0)
            {
                isfunctionkey = 1;
                ch == getKbdLoop();
            }
            for (auto i : options)
            {
                if (isfunctionkey == i.isfunctionkey)
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
                                    if (ch > i.value)
                                    {
                                        pass = 1;
                                    }
                                    break;
                                case NOT_LESS_THAN:
                                    if (ch >= i.value)
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
                                break;
                            }
                        }
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
                                    if (ch > i.value)
                                    {
                                        pass = 1;
                                    }break;
                                case NOT_LESS_THAN:
                                    if (ch >= i.value)
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
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    void printInfo()
    {
        std::cout << "ETFlasher " << TOOL_VERSION << " By " << AUTHUR << '\t' << URL << std::endl << std::endl;
    }
    void listMenu(std::vector<menuoption> menulist)
    {
        std::cout << "请选择操作：" << std::endl;
        int j = 1;
        for (auto i : menulist)
        {
            std::cout << j << '\t';
            std::cout << i.name << "\t";
            std::cout << i.description << "\t";
            j++;
        }
        std::cout << std::endl;
    }
}

/*
* 类
*/

class FSM
{
private:
    fsm::flashconf flashConfig;
    std::string cmdstr;
    std::vector<fsm::menuoption> menulist;
    std::vector<fsm::serialDev> seriallist;
    HANDLE hOut;
    fsm::STATES fsmState;
    std::queue <fsm::EVENTS> eventQueue;
public:
    FSM()
    {
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        eventQueue.push(fsm::ONSTARTUP);
    }
    void Advance();
    void OnStartup();
    void OnInited();
    void OnMenu();
    void GetInetFile();
    void OnSetting();
    void OnDownload();
    void OnConfigure();
    void OnFlash();
    void OnSelect();
    void OnExit();
    void RetMenu();
    void RetInetfile();
    void RetSetting();
    void RetConfigure();
};
