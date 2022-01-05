#include "defines.h"
#include <afx.h>
#include <afxinet.h>
#include <stdio.h> 
#include "stdlib.h"
#include <string>
#include "stdio.h"
#include <vector>
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

std::vector<std::string> createfilelist;

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
    wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1)+4);
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


int downloadFile(std::string url,std::string filename)
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
    while (1) {
        if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
            return _getch();//使用_getch()函数获取按下的键值
        }
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
    
void printInfo()
{
    std::cout << "ETFlasher " << TOOL_VERSION << " By " << AUTHUR << '\t' << URL << std::endl << std::endl;
}


int main()
{
    flashconf flashConfig;
    std::string cmdstr;
    std::vector<serialDev> seriallist;
    int option1, option2, option3;
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //system("pause");
    printInfo();
    atexit(cleanFile);
    getUpdateConfig();
    std::vector<devicefwinfo> fwlist = parseConfig();
    do
    {
        system("cls");
        printInfo();
        getUpdateConfig();
        std::vector<devicefwinfo> fwlist = parseConfig();
        listFirmwareInfo(fwlist);
        std::cout << "需要下载哪个型号的固件？（1~8选择，按0刷新,按9退出）" << std::endl;
        option1 = getOption(GET_NUMKEY) - 1;
    } while (option1 == -1);
    if (option1 == 8)
    {
        return 0;
    }
    downloadFile(fwlist[option1].url, "FIRMWARE_" + fwlist[option1].model + ".bin");
    releaseExe();
    do
    {
        flashConfig.filename = "FIRMWARE_" + fwlist[option1].model + ".bin";
        do
        {
            system("cls");
            seriallist = listCom();
            std::cout << "需要对哪个串口进行刷机？（1~9选择，按0刷新,按9退出）" << std::endl;
            option2 = getOption(GET_NUMKEY) - 1;
        } while (option2 == -1);
        if (option2 == 8)
        {
            return 0;
        }
        std::cout << std::endl;
        SetConsoleTextAttribute(hOut, 207);
        std::cout << "提示：即将开始刷机，" << fwlist[option1].notice << std::endl << std::endl;
        SetConsoleTextAttribute(hOut, 15);
        system("pause");
        flashConfig.port = seriallist[option2].comm;
        exeCmd(flashConfig);
        std::cout << "是否继续刷下一个？(y/n)" << std::endl;
        option3 = getOption(GET_YESORNO);
    } while (option3 == 'y');
    return 0;
}
