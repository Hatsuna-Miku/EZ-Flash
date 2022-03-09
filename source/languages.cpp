#include "../includes/languages.h"

namespace languages
{
	std::string pageindecator(unsigned short language, uint8_t currentpage, uint8_t allpage)
	{
		switch (language)
		{
		case LANG_CHINESE:
			return "��" + std::string(1, char(currentpage + 48)) + "ҳ����" + std::string(1, char(allpage + 48)) + "ҳ";
			break;
			/*
		case LANG_RUSSIAN:
		case LANG_ENGLISH:
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