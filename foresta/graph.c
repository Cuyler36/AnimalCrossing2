#include "graph.h"

/*
80E8468C .text
80E8468C graph_setup_double_buffer
80E84854 game_get_next_game_dlf_no
80E84968 game_get_next_game_dlftbl*/

void graph_ct(uint32_t* graph_class) {
	bzero(graph_class, 0x380);
	*(uint32_t*)(graph_class+0x350) = 0;
	*(uint8_t*)(graph_class+0x363) = 0;
	*(int16_t*)(debug_mode+0x116) &= -3; //???
	*(int16_t*)(debug_mode+0x116) &= -2; //???
	zurumode_init();
	*(uint8_t*)(graph_class+0x360) = 1; //step 1?
}

void graph_dt(uint32_t* graph_class) {
	*(uint8_t*)(graph_class+0x360) = 0x15; //step 0x15?
	zurumode_cleanup();
}
/*
80E84A48 graph_task_set00
80E84B20 graph_draw_finish
80E84D7C do_soft_reset
80E84DD0 reset_check
80E84E14 graph_main*/

void graph_proc(void) {
	uint32_t curr_dlftbl[12] = game_dlftbls[0];
	uint32_t dlf_no = 0;
	
	graph_ct(graph_class);
	while (curr_dlftbl) { //double check
		game_class_p = malloc(curr_dlftbl[11]); //0xE4, etc
		bzero(game_class_p, curr_dlftbl[11]);
		*(uint8_t*)(graph_class+0x360) = 2; //step?
		game_ct(game_class_p, curr_dlftbl[6], graph_class, dlf_no);
		*(uint8_t*)(graph_class+0x360) = 3;
		emu64_refresh();
		while (game_is_doing(game_class_p)) {
			if (dvderr_draw()) {
				if (OSGetResetSwitchState())
					__osResetSwitchPressed = 1;
				else
					if (__osResetSwitchPressed)
						osShutdownStart(2);
			} else
				graph_main(graph_class, game_class_p);
		}
		curr_dlftbl = game_get_next_game_dlftbl(game_class_p); //TODO: make this return right type
		dlf_no = game_get_next_game_dlf_no(game_class_p);
		*(uint8_t*)(graph_class+0x360) = 0x12;
		*(uint8_t*)(graph_class+0x360) = 0x13; //???
		game_dt(game_class_p);
		*(uint8_t*)(graph_class+0x360) = 0x14;
		free(game_class_p);
		game_class_p = 0; //and loop
	}
	graph_dt(graph_class);
}
