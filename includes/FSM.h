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

    enum STATES
    {
        STARTUP,
        INITED,
        MENU,
        SETTING,
        GETINET,
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
        ONMENU,
        GETINETFILE,
        ONINETFILE,
        ONSETTING,
        ONDOWNLOAD,
        ONCONFIGURE,
        ONFLASH,
        ONSELECT,
        ONEXIT,
        RET_MENU,
        RET_INETFILE,
        RET_SETTING,
        RET_CONFIGURE,
        RET_FLASH
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
        char key;
        std::string name, description;
    };

    struct optiontype
    {
        AGGREGATES aggregatetype;
        bool isfunctionkey;
        char value;
    };

    struct cursortype
    {
        HANDLE hOut;
        uint8_t page, option, allpage;
    };

    /*
    * 函数
    */
    char* wideCharToMultiByte(const wchar_t* pWCStrKey);
    LPCWSTR stringToLPCWSTR(std::string orig);
    std::vector<serialDev> getComPortList();
    int downloadFile(std::string url, std::string filename);
    int exeCmd(flashconf Config);
    std::vector<optiontype> listCom(std::vector<serialDev> comlist);
    devicefwinfo parseConfigLine(std::string line);
    std::vector<devicefwinfo> parseConfig();
    inline void getUpdateConfig();
    int releaseExe();
    std::vector<optiontype> listFirmwareInfo(std::vector<devicefwinfo> fwlist);
    int getKbdLoop();
    void cleanFile();
    int getOption(int setting);//过时的函数
    char getOption(std::vector<optiontype> options);
    void printInfo();
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
    std::vector<fsm::optiontype> optionlist;
    std::vector<fsm::devicefwinfo> fwlist;
    fsm::cursortype cursor;
    char option;
    std::string flashnotice;
public:
    FSM()
    {
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        eventQueue.push(fsm::ONSTARTUP);
        option = 0;
        cursor.hOut = hOut;
        cursor.page = 1;
        cursor.option = 1;
    }
    int Advance();
    void OnStartup();
    void OnInited();
    void OnMenu();
    void GetInetFile();
    void OnInetFile();
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
    void RetFlash();
};
