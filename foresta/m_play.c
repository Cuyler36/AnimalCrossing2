#include "m_play.h"

/*
810D503C .text
810D503C Game_play_Reset_destiny
810D5094 event_title_flag_on
810D50B8 event_title_flag_off
810D50E0 Game_play_camera_proc
810D5114 Game_play_fbdemo_wipe_destroy
810D515C Game_play_fbdemo_wipe_create_sub
810D51FC Game_play_fbdemo_wipe_create
810D5230 Game_play_fbdemo_wipe_init
810D5310 Game_play_fbdemo_fade_in_move_end
810D5364 Game_play_fbdemo_fade_out_start_emu_move_end
810D5384 Game_play_fbdemo_fade_out_game_end_move_end
810D53A8 Game_play_change_scene_move_end
810D53F0 Game_play_fbdemo_wipe_move
810D56FC Game_play_fbdemo_wipe_proc
810D5754 game_play_set_fog
810D5794 Game_play_fbdemo_proc
810D5820 play_cleanup
810D594C VR_Box_ct*/
void play_init(uint32_t* class_p) {
	game_resize_hyral(class_p, 0xFFFC1800);
	*(uint8_t*)0x8129689C = 0;
	mFI_ChangeClimate_ForEventNotice();
	mTM_time_init();
	sAdo_Set_ongenpos_refuse_fg(0);
	event_title_flag_on();
	mTD_rtc_set();
	mTM_set_season();
	mPlib_Clear_controller_data_for_title_demo();
	mSM_submenu_ovlptr_init(class_p);
	mDemo_Init(class_p);
	mEv_init((uint32_t*)(class_p + 0x204C));
	initView((uint32_t*)(class_p + 0x1A70), *(uint32_t*)class_p);
	CollisionCheck_ct(class_p, (uint32_t*)(class_p + 0x22C8));
	mCoBG_InitMoveBgData();
	mCoBG_InitBlockBgCheckMode();
	mCoBG_InitDecalCircle();
	*(uint8_t*)(class_p + 0x1F44) = -1;
	uint32_t* ptr = (uint32_t *)0x812670A8;
	Gameplay_Scene_Read((int16_t)*ptr;
}
/*810D5C04 Game_play_move_fbdemo_not_move
810D5D58 Game_play_move
810D5F04 setupFog
810D5F54 setupViewer
810D5F7C setupViewMatrix
810D6054 copy_efb_to_texture_dl
810D60CC getP_prbuf
810D60D8 capture_display_data
810D6200 makeBumpTexture
810D6510 draw_version
810D65A0 Game_play_draw
810D66C8 play_main
810D6864 Gameplay_Scene_Init
810D68D4 mPl_SceneNo2SoundRoomType
810D6918 Gameplay_Scene_Read
*/