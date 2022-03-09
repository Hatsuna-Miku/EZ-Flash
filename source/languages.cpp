#include "../includes/languages.h"

namespace languages
{
	std::string pageindecator(unsigned short language, uint8_t currentpage, uint8_t allpage)
	{
		switch (language)
		{
		case LANG_CHINESE:
			return "第" + std::string(1, char(currentpage + 48)) + "页，共" + std::string(1, char(allpage + 48)) + "页";
			break;
			/*
		case LANG_RUSSIAN:
		case LANG_ENGLISH:
		case LANG_JAPANESE:
			*/
		default:
			return "第" + std::string(1, char(currentpage + 48)) + "页，共" + std::string(1, char(allpage + 48)) + "页";
			break;
		}
	}
	STR loadstring(unsigned short language)
	{
		STR strings;
		switch (language)
		{
		case LANG_CHINESE:
			strings.serlist_serlist = "串口列表:";
			strings.serlist_menunotice = "按1~9选择,按r刷新,按q返回上一级：";
			strings.getinet_fetchingfilelist = "正在从服务器获取固件列表。。。";
			strings.inetfile_filelist = "固件列表：";
			strings.inetfile_notice = "按1~9选择,按r刷新,[]翻页,按q返回上一级：";
			strings.menu_menu = "菜单：";
			strings.menu_menunotice = "选择选项：";
			strings.menu_option_download = "下载";
			strings.menu_option_settings = "设置";
			strings.menu_option_flash = "刷机";
			strings.menu_option_quit = "退出";
			strings.menu_option_download_description = "从网络下载固件";
			strings.menu_option_settings_description = "更改软件设置";
			strings.menu_option_flash_description = "用已有固件对设备刷机";
			strings.menu_option_quit_description = "退出程序";
			strings.flash_notice = "提示：即将开始刷机，";
			strings.flash_optionnotice = "是否继续刷下一个？(y/n),按q退出程序";
			break;
			/*
		case LANG_RUSSIAN:
			strings.serlist_serlist =
			strings.serlist_menunotice =
			strings.getinet_fetchingfilelist =
			strings.inetfile_filelist =
			strings.inetfile_notice =
			strings.menu_menu =
			strings.menu_menunotice =
			strings.menu_option_download =
			strings.menu_option_settings =
			strings.menu_option_flash =
			strings.menu_option_quit =
			strings.menu_option_download_description =
			strings.menu_option_settings_description =
			strings.menu_option_flash_description =
			strings.menu_option_quit_description =
			strings.flash_notice =
			strings.flash_optionnotice =
			break;
		case LANG_ENGLISH:
			strings.serlist_serlist =
			strings.serlist_menunotice =
			strings.getinet_fetchingfilelist =
			strings.inetfile_filelist =
			strings.inetfile_notice =
			strings.menu_menu =
			strings.menu_menunotice =
			strings.menu_option_download =
			strings.menu_option_settings =
			strings.menu_option_flash =
			strings.menu_option_quit =
			strings.menu_option_download_description =
			strings.menu_option_settings_description =
			strings.menu_option_flash_description =
			strings.menu_option_quit_description =
			strings.flash_notice =
			strings.flash_optionnotice =
			break;
		case LANG_JAPANESE:
			strings.serlist_serlist =
			strings.serlist_menunotice =
			strings.getinet_fetchingfilelist =
			strings.inetfile_filelist =
			strings.inetfile_notice =
			strings.menu_menu =
			strings.menu_menunotice =
			strings.menu_option_download =
			strings.menu_option_settings =
			strings.menu_option_flash =
			strings.menu_option_quit =
			strings.menu_option_download_description =
			strings.menu_option_settings_description =
			strings.menu_option_flash_description =
			strings.menu_option_quit_description =
			strings.flash_notice =
			strings.flash_optionnotice =
			break;
			*/
		default:
			strings.serlist_serlist = "串口列表:";
			strings.serlist_menunotice = "按1~9选择,按r刷新,按q返回上一级：";
			strings.getinet_fetchingfilelist = "正在从服务器获取固件列表。。。";
			strings.inetfile_filelist = "固件列表：";
			strings.inetfile_notice = "按1~9选择,按r刷新,[]翻页,按q返回上一级：";
			strings.menu_menu = "菜单：";
			strings.menu_menunotice = "选择选项：";
			strings.menu_option_download = "下载";
			strings.menu_option_settings = "设置";
			strings.menu_option_flash = "刷机";
			strings.menu_option_quit = "退出";
			strings.menu_option_download_description = "从网络下载固件";
			strings.menu_option_settings_description = "更改软件设置";
			strings.menu_option_flash_description = "用已有固件对设备刷机";
			strings.menu_option_quit_description = "退出程序";
			strings.flash_notice = "提示：即将开始刷机，";
			strings.flash_optionnotice = "是否继续刷下一个？(y/n),按q退出程序";
			break;
		}
		return strings;
	}
}