#pragma once

game_dlftbls = [
[0, 0, 0, 0, 0, 0, first_game_init, first_game_cleanup, 0, 0, 0, 0xE4],
[0, 0, 0, 0, 0, 0, select_init, select_cleanup, 0, 0, 0, 0x240],
[0, 0, 0, 0, 0, 0, play_init, play_cleanup, 0, 0, 0, 0x25A0],
[0, 0, 0, 0, 0, 0, second_game_init, second_game_cleanup, 0, 0, 0, 0xE4],
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, trademark_init, trademark_cleanup, 0, 0, 0, 0x25A78],
[0, 0, 0, 0, 0, 0, player_select_init, player_select_cleanup, 0, 0, 0, 0x288],
[0, 0, 0, 0, 0, 0, save_menu_init, save_menu_cleanup, 0, 0, 0, 0x230],
[0, 0, 0, 0, 0, 0, famicom_emu_init, famicom_emu_cleanup, 0, 0, 0, 0xE4],
[0, 0, 0, 0, 0, 0, prenmi_init, prenmi_cleanup, 0, 0, 0, 0xEC],
[0, 0, 0, 0, 0, 0, reload_data_init, reload_data_cleanup, 0, 0, 0, 0xCC18]
]