#include "../includes/languages.h"

namespace languages
{
	std::string pageindicator(unsigned short language, uint8_t currentpage, uint8_t allpage)
	{
		switch (language)
		{
		case LANG_CHINESE:
			return "第" + std::string(1, char(currentpage + 48)) + "页，共" + std::string(1, char(allpage + 48)) + "页";
			break;
		case LANG_RUSSIAN:
			return "Страница " + std::string(1, char(currentpage + 48)) + "из" + std::string(1, char(allpage + 48));
		case LANG_ENGLISH:
			return "Page " + std::string(1, char(currentpage + 48)) + " of " + std::string(1, char(allpage + 48));
			break;
		case LANG_JAPANESE:
			return "ページ" + std::string(1, char(currentpage + 48)) + " の " + std::string(1, char(allpage + 48));
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
		case LANG_RUSSIAN:
			strings.serlist_serlist = "Список последовательных портов:";
			strings.serlist_menunotice = "Нажмите 1 ~ 9 для выбора, нажмите r для обновления, нажмите q, чтобы вернуться к предыдущему уровню:";
			strings.getinet_fetchingfilelist = "Получение списка встроенного ПО с сервера...";
			strings.inetfile_filelist = "Список прошивок:";
			strings.inetfile_notice = "Нажмите 1 ~ 9 для выбора, нажмите r для обновления, [] переверните страницу, нажмите q, чтобы вернуться на предыдущий уровень:";
			strings.menu_menu = "меню:";
			strings.menu_menunotice = "Выберите вариант:";
			strings.menu_option_download = "Загружать";
			strings.menu_option_settings = "Устанавливать";
			strings.menu_option_flash = "Чистящая машина";
			strings.menu_option_quit = "покидать";
			strings.menu_option_download_description = "Загрузка прошивки из сети";
			strings.menu_option_settings_description = "Изменение настроек программного обеспечения";
			strings.menu_option_flash_description = "Прошивка устройства с существующей прошивкой";
			strings.menu_option_quit_description = "Выйдите из программы";
			strings.flash_notice = "Совет: Мигание вот-вот начнется,";
			strings.flash_optionnotice = "Вы хотите продолжить чистку следующего? (y/n), нажмите q, чтобы выйти из программы";
			break;
			
		case LANG_ENGLISH:
			strings.serlist_serlist = "COM list:";
			strings.serlist_menunotice = "Press 1~9 to select, press r to refresh, press q to return to the previous level:";
			strings.getinet_fetchingfilelist = "Fetching file list...";
			strings.inetfile_filelist = "File list:";
			strings.inetfile_notice = "Press 1~9 to select, press r to refresh, [] turn the page, press q to return to the previous level:";
			strings.menu_menu = "Menu:";
			strings.menu_menunotice = "Press 1~9 to select：";
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
			strings.serlist_serlist = "シリアル リスト";
			strings.serlist_menunotice = "1 ~ 9 を押して選択し、r を押して更新し、q キーを押して上位レベルに戻ります。";
			strings.getinet_fetchingfilelist = "サーバーからファームウェアの一覧を取得しています。。。";
			strings.inetfile_filelist = "ファームウェアのリスト:";
			strings.inetfile_notice = "1 ~ 9 を押して選択し、r を押して更新し、[] をクリックしてページをめくり、q キーを押して 1 つ上のレベルに戻ります:";
			strings.menu_menu = "メニュー:";
			strings.menu_menunotice = "オプションを選択:";
			strings.menu_option_download = "ダウンロードします";
			strings.menu_option_settings = "設定します";
			strings.menu_option_flash = "ブラシマシン";
			strings.menu_option_quit = "終了します";
			strings.menu_option_download_description = "ネットワークからファームウェアをダウンロードします";
			strings.menu_option_settings_description = "ソフトウェア設定を変更します";
			strings.menu_option_flash_description = "既存のファームウェアを使用して、デバイスをブラシします";
			strings.menu_option_quit_description = "プログラムを終了します";
			strings.flash_notice = "ヒント:ブラシマシンを開始する予定、";
			strings.flash_optionnotice = "次のブラシを続行しますか? (y/n)を押してプログラムを終了します";
			break;;

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