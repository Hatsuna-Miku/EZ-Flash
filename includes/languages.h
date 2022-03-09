#pragma once
#include <string>
#include "defines.h"
#include <windows.h>

namespace languages
{
	struct STR
	{
		std::string serlist_serlist,
			serlist_menunotice,
			getinet_fetchingfilelist,
			inetfile_filelist,
			inetfile_notice,
			menu_menu,
			menu_menunotice,
			menu_option_download,
			menu_option_settings,
			menu_option_flash,
			menu_option_quit,
			menu_option_download_description,
			menu_option_settings_description,
			menu_option_flash_description,
			menu_option_quit_description,
			flash_notice,
			flash_optionnotice;
	};
	std::string pageindicator(unsigned short language, uint8_t currentpage, uint8_t allpage);
	STR loadstring(unsigned short language);
}