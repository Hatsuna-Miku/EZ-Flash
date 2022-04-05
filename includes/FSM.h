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
#include "languages.h"

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

    struct settingtype
    {
        unsigned short language;
        std::string flashspeed;
    };

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
    languages::STR strings;
    char option;
    std::string flashnotice;
    fsm::settingtype settings;
    int dbgflag;
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
    /*
    * 函数
    */
    char* wideCharToMultiByte(const wchar_t* pWCStrKey);
    LPCWSTR stringToLPCWSTR(std::string orig);
    std::vector<fsm::serialDev> getComPortList();
    int downloadFile(std::string url, std::string filename);
    int exeCmd(fsm::flashconf Config);
    std::vector<fsm::optiontype> listCom(std::vector<fsm::serialDev> comlist);
    fsm::devicefwinfo parseConfigLine(std::string line);
    std::vector<fsm::devicefwinfo> parseConfig();
    inline void getUpdateConfig();
    int releaseExe();
    std::vector<fsm::optiontype> listFirmwareInfo(std::vector<fsm::devicefwinfo> fwlist, fsm::cursortype cursor);
    int getKbdLoop();
    void cleanFile();
    int getOption(int setting);//过时的函数
    char getOption(std::vector<fsm::optiontype> options);
    std::vector<fsm::optiontype> listMenu(std::vector<fsm::menuoption> menulist);
    void printInfo();
    int readSettings();
    int writeSettings();
};
