#include "../includes/FSM.h"

int main()
{
    FSM ServiceFSM;


    /*
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
    */
    return 0;
}
