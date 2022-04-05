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
		case LANG_RUSSIAN:
			return "�����ѧߧڧ�� " + std::string(1, char(currentpage + 48)) + "�ڧ�" + std::string(1, char(allpage + 48));
		case LANG_ENGLISH:
			return "Page " + std::string(1, char(currentpage + 48)) + " of " + std::string(1, char(allpage + 48));
			break;
		case LANG_JAPANESE:
			return "�ک`��" + std::string(1, char(currentpage + 48)) + " �� " + std::string(1, char(allpage + 48));
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
		case LANG_RUSSIAN:
			strings.serlist_serlist = "����ڧ��� ����ݧ֧է�ӧѧ�֧ݧ�ߧ�� �������:";
			strings.serlist_menunotice = "���ѧاާڧ�� 1 ~ 9 �էݧ� �ӧ�ҧ���, �ߧѧاާڧ�� r �էݧ� ��ҧߧ�ӧݧ֧ߧڧ�, �ߧѧاާڧ�� q, ����ҧ� �ӧ֧�ߧ����� �� ���֧է�է��֧ާ� ����ӧߧ�:";
			strings.getinet_fetchingfilelist = "����ݧ��֧ߧڧ� ���ڧ�ܧ� �ӧ����֧ߧߧ�ԧ� ���� �� ��֧�ӧ֧��...";
			strings.inetfile_filelist = "����ڧ��� �����ڧӧ��:";
			strings.inetfile_notice = "���ѧاާڧ�� 1 ~ 9 �էݧ� �ӧ�ҧ���, �ߧѧاާڧ�� r �էݧ� ��ҧߧ�ӧݧ֧ߧڧ�, [] ��֧�֧ӧ֧�ߧڧ�� ����ѧߧڧ��, �ߧѧاާڧ�� q, ����ҧ� �ӧ֧�ߧ����� �ߧ� ���֧է�է��ڧ� ����ӧ֧ߧ�:";
			strings.menu_menu = "�ާ֧ߧ�:";
			strings.menu_menunotice = "����ҧ֧�ڧ�� �ӧѧ�ڧѧߧ�:";
			strings.menu_option_download = "���ѧԧ��اѧ��";
			strings.menu_option_settings = "�����ѧߧѧӧݧڧӧѧ��";
			strings.menu_option_flash = "���ڧ����ѧ� �ާѧ�ڧߧ�";
			strings.menu_option_quit = "���ܧڧէѧ��";
			strings.menu_option_download_description = "���ѧԧ��٧ܧ� �����ڧӧܧ� �ڧ� ��֧��";
			strings.menu_option_settings_description = "���٧ާ֧ߧ֧ߧڧ� �ߧѧ����֧� ����ԧ�ѧާާߧ�ԧ� ��ҧ֧��֧�֧ߧڧ�";
			strings.menu_option_flash_description = "������ڧӧܧ� ������ۧ��ӧ� �� ����֧��ӧ���֧� �����ڧӧܧ��";
			strings.menu_option_quit_description = "����ۧէڧ�� �ڧ� ����ԧ�ѧާާ�";
			strings.flash_notice = "����ӧ֧�: ���ڧԧѧߧڧ� �ӧ��-�ӧ�� �ߧѧ�ߧ֧���,";
			strings.flash_optionnotice = "���� ����ڧ�� ����է�ݧاڧ�� ��ڧ��ܧ� ��ݧ֧է���֧ԧ�? (y/n), �ߧѧاާڧ�� q, ����ҧ� �ӧ�ۧ�� �ڧ� ����ԧ�ѧާާ�";
			break;
			
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
			
		case LANG_JAPANESE:
			strings.serlist_serlist = "���ꥢ�� �ꥹ��";
			strings.serlist_menunotice = "1 ~ 9 ��Ѻ�����x�k����r ��Ѻ���Ƹ��¤���q ���`��Ѻ������λ��٥�ˑ���ޤ���";
			strings.getinet_fetchingfilelist = "���`�Щ`����ե��`�०������һ�E��ȡ�ä��Ƥ��ޤ�������";
			strings.inetfile_filelist = "�ե��`�०�����Υꥹ��:";
			strings.inetfile_notice = "1 ~ 9 ��Ѻ�����x�k����r ��Ѻ���Ƹ��¤���[] �򥯥�å����ƥک`����᤯�ꡢq ���`��Ѻ���� 1 ���ϤΥ�٥�ˑ���ޤ�:";
			strings.menu_menu = "��˥�`:";
			strings.menu_menunotice = "���ץ������x�k:";
			strings.menu_option_download = "�������`�ɤ��ޤ�";
			strings.menu_option_settings = "�O�����ޤ�";
			strings.menu_option_flash = "�֥饷�ޥ���";
			strings.menu_option_quit = "�K�ˤ��ޤ�";
			strings.menu_option_download_description = "�ͥåȥ�`������ե��`�०������������`�ɤ��ޤ�";
			strings.menu_option_settings_description = "���եȥ������O���������ޤ�";
			strings.menu_option_flash_description = "�ȴ�Υե��`�०������ʹ�ä��ơ��ǥХ�����֥饷���ޤ�";
			strings.menu_option_quit_description = "�ץ�����K�ˤ��ޤ�";
			strings.flash_notice = "�ҥ��:�֥饷�ޥ�����_ʼ�����趨��";
			strings.flash_optionnotice = "�ΤΥ֥饷��A�Ф��ޤ���? (y/n)��Ѻ���ƥץ�����K�ˤ��ޤ�";
			break;;

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