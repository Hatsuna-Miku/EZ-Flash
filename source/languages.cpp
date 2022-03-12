#include "../includes/languages.h"

namespace languages
{
	std::string pageindicator(unsigned short language, uint8_t currentpage, uint8_t allpage)
	{
		switch (language)
		{
		case LANG_CHINESE:
			return "��" + std::string(1, char(currentpage + 48)) + "ҳ����" + std::string(1, char(allpage + 48)) + "ҳ";
			break;
			/*
		case LANG_RUSSIAN:
		*/
		case LANG_ENGLISH:
			return "Page " + std::string(1, char(currentpage + 48)) + " of " + std::string(1, char(allpage + 48));
			break;
			/*
		case LANG_JAPANESE:
			*/
		default:
			return "��" + std::string(1, char(currentpage + 48)) + "ҳ����" + std::string(1, char(allpage + 48)) + "ҳ";
			break;
		}
	}
	STR loadstring(unsigned short language)
	{
		STR strings;
		switch (language)
		{
		case LANG_CHINESE:
			strings.serlist_serlist = "�����б�:";
			strings.serlist_menunotice = "��1~9ѡ��,��rˢ��,��q������һ����";
			strings.getinet_fetchingfilelist = "���ڴӷ�������ȡ�̼��б�����";
			strings.inetfile_filelist = "�̼��б�";
			strings.inetfile_notice = "��1~9ѡ��,��rˢ��,[]��ҳ,��q������һ����";
			strings.menu_menu = "�˵���";
			strings.menu_menunotice = "ѡ��ѡ�";
			strings.menu_option_download = "����";
			strings.menu_option_settings = "����";
			strings.menu_option_flash = "ˢ��";
			strings.menu_option_quit = "�˳�";
			strings.menu_option_download_description = "���������ع̼�";
			strings.menu_option_settings_description = "�����������";
			strings.menu_option_flash_description = "�����й̼����豸ˢ��";
			strings.menu_option_quit_description = "�˳�����";
			strings.flash_notice = "��ʾ��������ʼˢ����";
			strings.flash_optionnotice = "�Ƿ����ˢ��һ����(y/n),��q�˳�����";
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
			*/
			
		case LANG_ENGLISH:
			strings.serlist_serlist = "COM list:";
			strings.serlist_menunotice = "Press 1~9 to select, press r to refresh, press q to return to the previous level:";
			strings.getinet_fetchingfilelist = "Fetching file list...";
			strings.inetfile_filelist = "File list:";
			strings.inetfile_notice = "Press 1~9 to select, press r to refresh, [] turn the page, press q to return to the previous level:";
			strings.menu_menu = "Menu:";
			strings.menu_menunotice = "Press 1~9 to select��";
			strings.menu_option_download = "Downloads";
			strings.menu_option_settings = "Settings";
			strings.menu_option_flash = "Flash";
			strings.menu_option_quit = "Quit";
			strings.menu_option_download_description = "Download firm from the server";
			strings.menu_option_settings_description = "Change settings";
			strings.menu_option_flash_description = "Flash the devices with local firm file";
			strings.menu_option_quit_description = "Recycle the gabages and quit";
			strings.flash_notice = "Notice:flashing is about to start,";
			strings.flash_optionnotice = "Do you want to continue flashing the next one? (y/n), press q to exit";
			break;
			
			/*
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
			strings.serlist_serlist = "�����б�:";
			strings.serlist_menunotice = "��1~9ѡ��,��rˢ��,��q������һ����";
			strings.getinet_fetchingfilelist = "���ڴӷ�������ȡ�̼��б�����";
			strings.inetfile_filelist = "�̼��б�";
			strings.inetfile_notice = "��1~9ѡ��,��rˢ��,[]��ҳ,��q������һ����";
			strings.menu_menu = "�˵���";
			strings.menu_menunotice = "ѡ��ѡ�";
			strings.menu_option_download = "����";
			strings.menu_option_settings = "����";
			strings.menu_option_flash = "ˢ��";
			strings.menu_option_quit = "�˳�";
			strings.menu_option_download_description = "���������ع̼�";
			strings.menu_option_settings_description = "�����������";
			strings.menu_option_flash_description = "�����й̼����豸ˢ��";
			strings.menu_option_quit_description = "�˳�����";
			strings.flash_notice = "��ʾ��������ʼˢ����";
			strings.flash_optionnotice = "�Ƿ����ˢ��һ����(y/n),��q�˳�����";
			break;
		}
		return strings;
	}
}