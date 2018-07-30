#pragma once

/*
800D1940 .rodata
800D1940 SEQ_TABLE
800D1C40 SE_FLOOR_DATA
800D1CF2 SE_ROOM_INS_DATA
800D1D14 SE_ROOM_INS_RANDOM_OFFSET
800D1D36 SHIIN2BOIN
800D1D8C TRGPRIO
800D1E0C sou_trg_se_init
800D1E2C sou_voice_se_init
800D1E50 sou_lev_se_init
800D1E64 sou_lev_ongen_data_init
800D1E78 sou_ongen_entry_init
800D1E88 sou_se_fade_init
800F4F00 .data
800F4F00 OCTAVETABLE
800F4F30 BGM_MUTE_TABLE_FINE
800F4F60 BGM_MUTE_TABLE_SNOW
800F4F90 BGM_MUTE_TABLE_SAKURA
800F4FC0 BGM_MUTE_TABLE_MUSEUM
800F4FE0 NIN_SEQ
800F5040 NIN_BANK
800F58C0 NIN_WAVE
800F5B00 str_800F5B00
800F5B20 str_800F5B20
800F5B48 str_800F5B48
800F5B70 str_800F5B70
800F5BBC str_800F5BBC
801122E0 .bss
801122E0 sou_ls_stack
80112310 sou_trg_se
801123D0 sou_voice_se
80112418 sou_lev_se
80112490 sou_lev_ongen_data
801124E0 sou_ongen_entry
80112800 sou_room_ins
80112990 sou_se_fade
80112A60 audiomemory
801A2A60 SOU_FIR_STATE_COPY
80291760 .sdata
80291760 BGM_MUTE_PRIVATE_ISLAND
80291762 sou_now_bgm_handle
80291764 SOU_ONGEN_AREA1
80291768 SOU_ONGEN_AREA2
8029176C sou_md_bgm_boost_pasent
80291FE8 .sbss
80291FE8 bootsound_ptr
80291FEC bootsound_size
80291FF0 sou_now_spec
80291FF4 sou_scene_mode
80291FF5 sou_chime_status
80291FF8 fatalErrorCallback
80291FFC sou_last_kokoro_counter
80291FFD sou_game_frame_counter
80291FFE sou_kokoro_toguru
80292000 sou_last_sys_trg_num
80292002 sou_sub_game_flag
80292004 sou_kazaguruma_speed
80292008 sou_fuusha_speed
8029200C sou_NeosBootCheck_ok
8029200D sou_walk_flag
8029200E sou_last_walk_l
8029200F sou_last_walk_r
80292010 sou_player_dash
80292014 sou_player_speed
80292018 sou_voice_se_toguru
80292019 sou_message_speed
8029201A sou_message_status
8029201B sou_last_voice
8029201C sou_voice_effect
8029201D sou_voice_effect_counter
8029201E sou_pause_flag
8029201F sou_metranome_counter
80292020 sou_last_perio
80292022 sou_last_uchiwa
80292024 sou_out_mode
80292025 sou_voice_mode
80292026 sou_kiteki_random
80292028 sou_kiteki_counter
8029202C sou_camera2ground
80292030 sou_now_boin
80292031 sou_now_voice_seq
80292032 sou_nobasu_count
80292034 sou_now_bgm_num
80292038 sou_bgm_vol_move_target
8029203C sou_bgm_vol_move_delta
80292040 sou_bgm1_vol_now
80292044 sou_bgm2_vol_now
80292048 sou_bgm_vol_move_time
8029204A sou_bgm_vol_move_counter
8029204C sou_kisha_angle
80292050 sou_kisha_distance
80292054 sou_kisha_angle2
80292058 sou_kisha_distance2
8029205C sou_kisha_status
8029205E sou_shu_count
80292060 sou_tonton_count
80292062 sou_voice_type
80292063 sou_SE_SENTAKU_KETTEI_timer
80292064 sou_SE_ami_hit_water_timer
80292065 sou_tenki
80292066 sou_now_bgm_fadeout
80292067 sou_se_handle_ready
80292068 sou_voice_handle_ready
80292069 sou_bgm_call_buffer
8029206A sou_bgm_call_buffer_u16
8029206C sou_bgm_call_buffer_fadetime
8029206E sou_ongenpos_kill_countdown
80292070 sou_chime_volume
80292074 sou_filter_status
80292075 sou_room_type
80292076 sou_museum_type
80292077 sou_meisou_status
80292078 sou_internal_filter_status
80292079 sou_se_fadeout_flag
8029207A sou_voice_sad_toguru
8029207B sou_last_voice_toguru
8029207C sou_voice_se_skip
8029207D sou_num2_request
8029207E sou_Na_VoiceSeCounter
8029207F sou_2flameCounter
80292080 sou_num2_animal_id
80292082 sou_num2_scale
80292083 sou_last_num
80292084 sou_last_num2
80292085 sou_num_org
80292086 sou_num2_org
80292087 sou_num3_org
80292088 sou_PrivateIslandStatus
80292089 sou_sys_lev
80292090 SOU_FIR_STATE
80292094 init
80292098 init_00
80292AE0 .sdata2
80292AE0 sou_ls_stack_init
80292AE8 sou_sys_lev_init
80292AEC sou_room_ins_init
80292AF4 str_80292AF4
80292AF8 str_80292AF8
80292AFC str_80292AFC
80292B00 str_80292B00
80292B04 str_80292B04
80292B08 str_80292B08
80292B10 str_80292B10
80292B18 str_80292B18
80292B1C str_80292B1C
80292B20 str_80292B20
80292B24 str_80292B24
80292B28 str_80292B28
80292B2C str_80292B2C
80292B30 str_80292B30
80292B34 str_80292B34
80292B38 str_80292B38
80292B40 str_80292B40
80292B44 str_80292B44
80292B48 str_80292B48
80292B4C str_80292B4C
80292B50 str_80292B50
80292B54 str_80292B54
80292B58 str_80292B58
80292B5C str_80292B5C
80292B60 str_80292B60
80292B64 str_80292B64
80292B68 str_80292B68
80292B6C str_80292B6C
80292B70 str_80292B70
80292B74 str_80292B74
80292B78 str_80292B78
80292B7C str_80292B7C
80292B80 str_80292B80
80292B84 str_80292B84
80292B88 str_80292B88
80292B8C str_80292B8C
80292B90 str_80292B90
80292B94 str_80292B94
80292B98 str_80292B98
80292B9C str_80292B9C
80292BA0 str_80292BA0
80292BA4 str_80292BA4
80292BA8 str_80292BA8
80292BAC str_80292BAC
80292BB0 str_80292BB0
80292BB4 str_80292BB4
80292BB8 str_80292BB8
80292BBC str_80292BBC
80292BC0 str_80292BC0
80292BC4 str_80292BC4
80292BC8 str_80292BC8
80292BCC str_80292BCC
80292BD0 str_80292BD0
80292BD4 str_80292BD4
80292BD8 str_80292BD8
80292BDC str_80292BDC
*/