#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
	//MAGNI :  WINSIZE_X/512   //magnification
#pragma region BG
	// 맵 이미지 
	IMAGEMANAGER->addImage("map_stage11", "Resources/Images/Map/map_stage11.bmp", 0, 0, 1038 * 3, 1025 * 3, MGT);
	IMAGEMANAGER->addImage("map_stage11_top", "Resources/Images/Map/map_stage11_top.bmp", 0, 0, 1038 * 3, 1025 * 3, MGT);
	IMAGEMANAGER->addImage("map_stage11_pixel", "Resources/Images/Map/map_stage11_pixel.bmp", 0, 0, 1038 * 3, 1025 * 3, MGT);
	IMAGEMANAGER->addImage("map_stage14", "Resources/Images/Map/map_stage14.bmp", 0, 0, 2628,2123, MGT);
	IMAGEMANAGER->addImage("map_stage14_pixel", "Resources/Images/Map/map_stage14_pixel.bmp", 0, 0, 2628, 2123, MGT);

	IMAGEMANAGER->addImage("black", "Resources/Images/BackGround/black.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("title", "Resources/Images/BackGround/title.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("save", "Resources/Images/BackGround/save.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("main", "Resources/Images/BackGround/main.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("abyss", "Resources/Images/BackGround/abyss.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("pub", "Resources/Images/BackGround/pub.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("pub2", "Resources/Images/BackGround/pub2.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("pub3", "Resources/Images/BackGround/pub3.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("pub4", "Resources/Images/BackGround/pub4.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("pub5", "Resources/Images/BackGround/pub5.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("store", "Resources/Images/BackGround/store.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("store2", "Resources/Images/BackGround/store2.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("store3", "Resources/Images/BackGround/store3.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("store4", "Resources/Images/BackGround/store4.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("store5", "Resources/Images/BackGround/store5.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("tutorial", "Resources/Images/BackGround/tutorial.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("castle", "Resources/Images/BackGround/castle_1.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("castle2", "Resources/Images/BackGround/castle_2.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("square", "Resources/Images/BackGround/square/square.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("square_boxTop", "Resources/Images/BackGround/square/square_boxTop.bmp", 254 * MAGNI, 68 * MAGNI, MGT);
	IMAGEMANAGER->addImage("square_boxBottom", "Resources/Images/BackGround/square/square_boxBottom.bmp", 254 * MAGNI, 68 * MAGNI, MGT);
	IMAGEMANAGER->addImage("tomi", "Resources/Images/BackGround/square/NPC_tomi.bmp",		158 * MAGNI, 178 * MAGNI, MGT);
	IMAGEMANAGER->addImage("doble", "Resources/Images/BackGround/square/NPC_doble.bmp",		158 * MAGNI, 178 * MAGNI, MGT);
	IMAGEMANAGER->addImage("lasmeda", "Resources/Images/BackGround/square/NPC_lasmeda.bmp", 158 * MAGNI, 178 * MAGNI, MGT);
	IMAGEMANAGER->addImage("daisy_0", "Resources/Images/BackGround/square/NPC_daisy_0.bmp", 158 * MAGNI, 178 * MAGNI, MGT);
	IMAGEMANAGER->addImage("daisy_1", "Resources/Images/BackGround/square/NPC_daisy_1.bmp", 158 * MAGNI, 178 * MAGNI, MGT);
	IMAGEMANAGER->addImage("daisy_2", "Resources/Images/BackGround/square/NPC_daisy_2.bmp", 158 * MAGNI, 178 * MAGNI, MGT);
	IMAGEMANAGER->addImage("fiena_0", "Resources/Images/BackGround/square/NPC_fiena_0.bmp", 158 * MAGNI, 178 * MAGNI, MGT);
	IMAGEMANAGER->addImage("fiena_2", "Resources/Images/BackGround/square/NPC_fiena_2.bmp", 158 * MAGNI, 178 * MAGNI, MGT);
	IMAGEMANAGER->addImage("gamel_0", "Resources/Images/BackGround/square/NPC_gamel_0.bmp", 158 * MAGNI, 178 * MAGNI, MGT);
	IMAGEMANAGER->addImage("gamel_1", "Resources/Images/BackGround/square/NPC_gamel_1.bmp", 158 * MAGNI, 178 * MAGNI, MGT);

	// In Abyss, Right Screen Menu
	IMAGEMANAGER->addImage("sub_inven", "Resources/Images/BackGround/sub_inven.bmp", CENTER_X,0,256 * MAGNI, 192 * MAGNI, MGT);
	IMAGEMANAGER->addImage("sub_stat", "Resources/Images/BackGround/sub_stat.bmp", CENTER_X, 0, 256 * MAGNI, 192 * MAGNI, MGT);
	IMAGEMANAGER->addImage("sub_map", "Resources/Images/BackGround/sub_map.bmp", CENTER_X, 0, 256 * MAGNI, 192 * MAGNI, MGT);
	IMAGEMANAGER->addImage("sub_skill", "Resources/Images/BackGround/sub_skill.bmp", CENTER_X, 0, 256 * MAGNI, 192 * MAGNI, MGT);

#pragma endregion

#pragma region Player

	IMAGEMANAGER->addImage("p_shadow", "Resources/Images/Player/p_shadow.bmp", 18 * MAGNI, 8 * MAGNI, MGT);
	IMAGEMANAGER->addFrameImage("p_down", "Resources/Images/Player/p_down.bmp", 30 * MAGNI, 100 * MAGNI, 1, 2, MGT);
	IMAGEMANAGER->addFrameImage("p_def", "Resources/Images/Player/p_def.bmp", 30 * MAGNI, 100 * MAGNI, 1 , 2, MGT);
	IMAGEMANAGER->addFrameImage("p_idle_oneHand", "Resources/Images/Player/p_idle_oneHand.bmp", 30 * MAGNI, 400 * MAGNI, 1, 8, MGT);
	IMAGEMANAGER->addFrameImage("p_idle_twoHand", "Resources/Images/Player/p_idle_twoHand.bmp", 30 * MAGNI, 400 * MAGNI, 1, 8, MGT);
	IMAGEMANAGER->addFrameImage("p_move", "Resources/Images/Player/p_move.bmp", 120 * MAGNI, 400 * MAGNI, 4,8, MGT);
	IMAGEMANAGER->addFrameImage("p_oneHandCombo", "Resources/Images/Player/p_oneHandCombo.bmp", 60 * MAGNI, 400 * MAGNI, 6, 8, MGT);
	IMAGEMANAGER->addFrameImage("p_twoHandCombo", "Resources/Images/Player/p_twoHandCombo.bmp", 60 * MAGNI, 400 * MAGNI, 4, 8, MGT);
	IMAGEMANAGER->addFrameImage("p_skill_soulCapture", "Resources/Images/Player/p_skill_soulCapture.bmp", 90 * MAGNI, 400 * MAGNI, 3, 8, MGT);
	IMAGEMANAGER->addFrameImage("p_oneHandCombo_01", "Resources/Images/Player/p_oneHandCombo_01.bmp", 60 * MAGNI, 400 * MAGNI, 2, 8, MGT);
	IMAGEMANAGER->addFrameImage("p_oneHandCombo_02", "Resources/Images/Player/p_oneHandCombo_02.bmp", 60 * MAGNI, 400 * MAGNI, 2, 8, MGT);
	IMAGEMANAGER->addFrameImage("p_oneHandCombo_03", "Resources/Images/Player/p_oneHandCombo_03.bmp", 60 * MAGNI, 400 * MAGNI, 2, 8, MGT);
	IMAGEMANAGER->addFrameImage("p_twoHandCombo_01", "Resources/Images/Player/p_twoHandCombo_01.bmp", 60 * MAGNI, 400 * MAGNI, 2, 8, MGT);
	IMAGEMANAGER->addFrameImage("p_twoHandCombo_02", "Resources/Images/Player/p_twoHandCombo_02.bmp", 60 * MAGNI, 400 * MAGNI, 2, 8, MGT);

	IMAGEMANAGER->addImage("p_face", "Resources/Images/Player/p_face.bmp", 0,0,40* MAGNI, 40 * MAGNI, MGT);

	
#pragma endregion

#pragma region enemy
	IMAGEMANAGER->addFrameImage("Dionaea_attack", "Resources/Images/Monster/Dionaea_attack.bmp", 96 * MAGNI, 240 * MAGNI, 2, 4, MGT);
	IMAGEMANAGER->addFrameImage("Dionaea_def", "Resources/Images/Monster/Dionaea_def.bmp", 48 * MAGNI, 120 * MAGNI, 1, 2, MGT);
	IMAGEMANAGER->addFrameImage("Dionaea_idle", "Resources/Images/Monster/Dionaea_idle.bmp", 48 * MAGNI, 240 * MAGNI, 1, 4, MGT);
	IMAGEMANAGER->addFrameImage("Dionaea_move", "Resources/Images/Monster/Dionaea_move.bmp", 96 * MAGNI, 240 * MAGNI, 2, 4, MGT);
	
	IMAGEMANAGER->addFrameImage("evilEye_attack", "Resources/Images/Monster/evilEye_attack.bmp", 84 * MAGNI, 160 * MAGNI, 2, 4, MGT);
	IMAGEMANAGER->addFrameImage("evilEye_def", "Resources/Images/Monster/evilEye_def.bmp", 42 * MAGNI, 80 * MAGNI, 1, 2, MGT);
	IMAGEMANAGER->addFrameImage("evilEye_idle", "Resources/Images/Monster/evilEye_idle.bmp", 42 * MAGNI, 160 * MAGNI, 1, 4, MGT);
	IMAGEMANAGER->addFrameImage("evilEye_move", "Resources/Images/Monster/evilEye_move.bmp", 84 * MAGNI, 160 * MAGNI, 2, 4, MGT);
	
	IMAGEMANAGER->addFrameImage("Kobold_attack", "Resources/Images/Monster/Kobold_attack.bmp", 84 * MAGNI, 168 * MAGNI, 2, 4, MGT);
	IMAGEMANAGER->addFrameImage("Kobold_def", "Resources/Images/Monster/Kobold_def.bmp", 40 * MAGNI, 84 * MAGNI, 1, 2, MGT);
	IMAGEMANAGER->addFrameImage("Kobold_idle", "Resources/Images/Monster/Kobold_idle.bmp", 40 * MAGNI, 168 * MAGNI, 1, 4, MGT);
	IMAGEMANAGER->addFrameImage("Kobold_move", "Resources/Images/Monster/Kobold_move.bmp", 80 * MAGNI, 168 * MAGNI, 2, 4, MGT);
	IMAGEMANAGER->addFrameImage("Kobold_skill", "Resources/Images/Monster/Kobold_skill.bmp", 88 * MAGNI, 168 * MAGNI, 2, 4, MGT);

	IMAGEMANAGER->addFrameImage("mino_attack", "Resources/Images/Monster/Boss/mino_attack.bmp", 392 * MAGNI, 472 * MAGNI, 2, 4, MGT);
	IMAGEMANAGER->addFrameImage("mino_skill",  "Resources/Images/Monster/Boss/mino_skill.bmp", 150 * MAGNI, 88 * MAGNI, 1, 1, MGT);
	IMAGEMANAGER->addFrameImage("mino_idle",   "Resources/Images/Monster/Boss/mino_idle.bmp", 196 * MAGNI, 472 * MAGNI, 1, 4, MGT);
	IMAGEMANAGER->addFrameImage("mino_move",   "Resources/Images/Monster/Boss/mino_move.bmp", 392 * MAGNI, 472 * MAGNI, 2, 4, MGT);

#pragma endregion

#pragma region effect

	IMAGEMANAGER->addImage("eff_AttUp",	                "Resources/Images/Effect/eff_AttUp.bmp", 130, 70, MGT);
	IMAGEMANAGER->addImage("eff_AttDown",               "Resources/Images/Effect/eff_AttDown.bmp", 130, 70, MGT);
	IMAGEMANAGER->addImage("eff_AttLeft",               "Resources/Images/Effect/eff_AttLeft.bmp", 70, 130, MGT);
	IMAGEMANAGER->addImage("eff_AttLeftDown",           "Resources/Images/Effect/eff_AttLeftDown.bmp", 100, 90, MGT);
	IMAGEMANAGER->addImage("eff_AttLeftUp",             "Resources/Images/Effect/eff_AttLeftUp.bmp", 100, 90, MGT);
	IMAGEMANAGER->addImage("eff_AttRight",              "Resources/Images/Effect/eff_AttRight.bmp", 70, 130, MGT);
	IMAGEMANAGER->addImage("eff_AttRightDown",          "Resources/Images/Effect/eff_AttRightDown.bmp", 100, 90, MGT);
	IMAGEMANAGER->addImage("eff_AttRightUp",            "Resources/Images/Effect/eff_AttRightUp.bmp", 100, 90, MGT);
	IMAGEMANAGER->addFrameImage("eff_collision",        "Resources/Images/Effect/eff_collision.bmp", 525, 385, 5, 4, MGT);
	IMAGEMANAGER->addFrameImage("eff_Collision2",		"Resources/Images/Effect/eff_Collision2.bmp", 210, 98, 2, 1, MGT);
												        
												        
												        
	IMAGEMANAGER->addImage("eff_bossAttUp",             "Resources/Images/Effect/eff_bossAttUp.bmp", 278, 108, MGT);
	IMAGEMANAGER->addImage("eff_bossAttDown",			"Resources/Images/Effect/eff_bossAttDown.bmp", 278, 108, MGT);
	IMAGEMANAGER->addImage("eff_bossAttLeft",			"Resources/Images/Effect/eff_bossAttLeft.bmp", 108, 278, MGT);
	IMAGEMANAGER->addImage("eff_bossAttRight",          "Resources/Images/Effect/eff_bossAttRight.bmp", 108, 278, MGT);
	IMAGEMANAGER->addFrameImage("monsterDie",           "Resources/Images/Effect/monsterDie.bmp", 160 * MAGNI, 32 * MAGNI, 5, 1, MGT);
	IMAGEMANAGER->addFrameImage("bossDie",	            "Resources/Images/Effect/BossDie.bmp", 160 * MAGNI, 30 * MAGNI, 5, 1, MGT);

#pragma endregion


#pragma region object

	IMAGEMANAGER->addImage("map_gate", "Resources/Images/Map/map_obj_gate.bmp", 0, 0, 120,50, MGT);
	IMAGEMANAGER->addImage("map_wood1", "Resources/Images/Map/map_obj_wood1.bmp", 0, 0, 85 * 3, 96 * 3, MGT);
	IMAGEMANAGER->addImage("map_wood2", "Resources/Images/Map/map_obj_wood2.bmp", 0, 0, 126 * 3, 190 * 3, MGT);
	IMAGEMANAGER->addImage("map_rock", "Resources/Images/Map/map_obj_rock.bmp", 0, 0, 32 * 3, 45 * 3, MGT);
	IMAGEMANAGER->addImage("map_stone", "Resources/Images/Map/map_obj_stone.bmp", 0, 0, 22 * 3, 46 * 3, MGT);

	IMAGEMANAGER->addFrameImage("dropItem", "Resources/Images/Object/dropItem.bmp", 150 * MAGNI, 22 * MAGNI, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("Equipment_icon", "Resources/Images/Object/Equipment_icon.bmp", 160 * MAGNI, 52 * MAGNI, 6, 2, MGT);
	IMAGEMANAGER->addFrameImage("Inven_icon", "Resources/Images/Object/Inven_icon.bmp", 352 * MAGNI, 96 * MAGNI, 11, 3, MGT);


	IMAGEMANAGER->addFrameImage("weapon_sword", "Resources/Images/Object/weapon_sword.bmp", 600 * MAGNI, 25 * MAGNI, 25, 1, MGT);
	IMAGEMANAGER->addFrameImage("weapon_ax", "Resources/Images/Object/weapon_ax.bmp", 675 * MAGNI, 50 * MAGNI, 27, 2, MGT);
	IMAGEMANAGER->addFrameImage("weapon_spear", "Resources/Images/Object/weapon_spear.bmp", 832 * MAGNI, 75 * MAGNI, 16, 1, MGT);
	IMAGEMANAGER->addFrameImage("weapon_none", "Resources/Images/Object/weapon_none.bmp", 25 * MAGNI, 25 * MAGNI, 1, 1, MGT);
	IMAGEMANAGER->addFrameImage("none", "Resources/Images/Object/none.bmp", 25 * MAGNI, 25 * MAGNI, 1, 1, MGT);
	IMAGEMANAGER->addImage("none2", "Resources/Images/Object/none.bmp", 25 * MAGNI, 25 * MAGNI,MGT);




#pragma endregion

#pragma region UI	
	
	IMAGEMANAGER->addImage("titleButton", "Resources/Images/Object/titleButton.bmp", RSCENTER_X, CENTER_Y, 98 * MAGNI, 30 * MAGNI, MGT);
	IMAGEMANAGER->addImage("nextButton", "Resources/Images/Object/nextButton.bmp", RSCENTER_X, CENTER_Y, 72 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("ynButton", "Resources/Images/Object/YesNoButton.bmp",   RSCENTER_X, CENTER_Y, 56 * MAGNI, 20 * MAGNI, MGT);
	IMAGEMANAGER->addImage("ynButton1", "Resources/Images/Object/YesNoButton1.bmp", RSCENTER_X, CENTER_Y, 56 * MAGNI, 20 * MAGNI, MGT);
	IMAGEMANAGER->addImage("ynButton2", "Resources/Images/Object/YesNoButton2.bmp", RSCENTER_X, CENTER_Y, 56 * MAGNI, 20 * MAGNI, MGT);
	IMAGEMANAGER->addFrameImage("upDownButton", "Resources/Images/Object/upDownButton.bmp", RSCENTER_X, 0, 62 * MAGNI, 62 * MAGNI, MGT);

	IMAGEMANAGER->addImage("newGame", "Resources/Images/Object/newGame.bmp", 0, 0, 58 * MAGNI, 12 * MAGNI, MGT);
	IMAGEMANAGER->addImage("newGame0", "Resources/Images/Object/newGame0.bmp", 0, 0, 58 * MAGNI, 12 * MAGNI, MGT);

	// 작은 프레임 이미지라 쪼개고 렌더할때 *비율 적용
	IMAGEMANAGER->addFrameImage("Num_0", "Resources/Images/Object/Num_0.bmp",		  0, 0, 70 , 8  , 10, 1, MGT);
	IMAGEMANAGER->addFrameImage("Num_R", "Resources/Images/Object/Num_R.bmp",		  0, 0, 90 , 10 , 10, 1, MGT);
	IMAGEMANAGER->addFrameImage("Num_G", "Resources/Images/Object/Num_G.bmp",		  0, 0, 90 , 10 , 10, 1, MGT);
	IMAGEMANAGER->addFrameImage("Num_B", "Resources/Images/Object/Num_B.bmp",		  0, 0, 90 , 10 , 10, 1, MGT);
	IMAGEMANAGER->addFrameImage("Num_W", "Resources/Images/Object/Num_W.bmp",		  0, 0, 90 , 10 , 10, 1, MGT);
	IMAGEMANAGER->addFrameImage("Num_W2", "Resources/Images/Object/Num_W2.bmp",		  0, 0, 243 , 27 , 10, 1, MGT);
	IMAGEMANAGER->addFrameImage("Num_UI", "Resources/Images/Object/Num_UI2.bmp",      0, 0, 297 , 30 , 11, 1, MGT); //99 * MAGNI, 10 * MAGNI
	IMAGEMANAGER->addFrameImage("Num_UI2", "Resources/Images/Object/Num_UI.bmp",	  0, 0, 198 , 20 , 11, 1, MGT); //99 * MAGNI, 10 * MAGNI

	IMAGEMANAGER->addImage("abyss1", "Resources/Images/Object/abyss1.bmp", 0, 0, 144 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("abyss2", "Resources/Images/Object/abyss2.bmp", 0, 0, 144 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("abyss3", "Resources/Images/Object/abyss3.bmp", 0, 0, 144 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("stage1", "Resources/Images/Object/stage1.bmp", 0, 0, 144 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("stage2", "Resources/Images/Object/stage2.bmp", 0, 0, 144 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("stage3", "Resources/Images/Object/stage3.bmp", 0, 0, 144 * MAGNI, 48 * MAGNI, MGT);

	IMAGEMANAGER->addFrameImage("skill_atk_Icon", "Resources/Images/Object/skill_atk_Icon.bmp", 0, 0, 297 * MAGNI, 99 * MAGNI, 9, 3, MGT);
	IMAGEMANAGER->addFrameImage("skill_utill_Icon", "Resources/Images/Object/skill_utill_Icon.bmp", 0, 0, 256 * MAGNI, 32 * MAGNI, 8, 1, MGT);
	IMAGEMANAGER->addFrameImage("store_icon", "Resources/Images/Object/store_icon.bmp", 0, 0, 240 * MAGNI, 20 * MAGNI, 15, 2, MGT);


	//IMAGEMANAGER->addImage("hp", "Resources/Images/Object/hp.bmp", 0, 0, 1 * MAGNI, 4 * MAGNI, MGT);
	IMAGEMANAGER->addImage("HPBar", "Resources/Images/Object/HPBar.bmp", 65, 12, 92 * MAGNI, 26 * MAGNI, MGT);
	//IMAGEMANAGER->addImage("sp", "Resources/Images/Object/hp.bmp", 0, 0, 1 * MAGNI, 4 * MAGNI, MGT);
	IMAGEMANAGER->addImage("SPBar", "Resources/Images/Object/SPBar.bmp", 360 ,12, 92 * MAGNI, 26 * MAGNI, MGT);
	
	//IMAGEMANAGER->addImage("bossHp", "Resources/Images/Object/hpBoss.bmp", 0, 0, 2 * MAGNI, 20 * MAGNI, MGT);
	//IMAGEMANAGER->addImage("bossHpBg", "Resources/Images/Object/hpBackBoss.bmp", 0, 0, 2 * MAGNI, 20 * MAGNI, MGT);

	
	
	IMAGEMANAGER->addImage("Item_select", "Resources/Images/Object/Item_select.bmp", 0, 0, 40 * MAGNI, 40 * MAGNI, MGT);
	IMAGEMANAGER->addImage("tap_1", "Resources/Images/Object/tap_1.bmp", 0, 0, 27 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("tap_2", "Resources/Images/Object/tap_2.bmp", 0, 0, 27 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("tap_3", "Resources/Images/Object/tap_3.bmp", 0, 0, 27 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("enterStage", "Resources/Images/Object/enterStage.bmp", 0, 0, 49 * MAGNI, 11 * MAGNI, MGT);
	IMAGEMANAGER->addImage("LvUp", "Resources/Images/Object/LvUp.bmp", 0, 0, 83 * MAGNI, 11 * MAGNI, MGT);
	IMAGEMANAGER->addImage("UI_pathInfo", "Resources/Images/Object/UI_pathInfo.bmp", 0, 0, 21 * MAGNI, 21 * MAGNI, MGT);
	IMAGEMANAGER->addFrameImage("UI_path", "Resources/Images/Object/UI_path.bmp", 0, 0, 160 * 3, 10 * 3, 16,1, MGT);
	IMAGEMANAGER->addFrameImage("UI_point", "Resources/Images/Object/map_point.bmp", 0, 0, 40 * 3, 10 * 3, 4, 1, MGT);

	IMAGEMANAGER->addImage("map_abyss", "Resources/Images/Object/map_abyss.bmp", 0, 0, 37 * MAGNI, 10 * MAGNI, MGT);
	IMAGEMANAGER->addImage("map_stage", "Resources/Images/Object/map_stage.bmp", 0, 0, 37 * MAGNI, 10 * MAGNI, MGT);
	IMAGEMANAGER->addFrameImage("map_thumbnail", "Resources/Images/Object/map_thumbnail.bmp", 0, 0, 512 * MAGNI, 64 * MAGNI, 8, 1, MGT);
	IMAGEMANAGER->addFrameImage("map_path", "Resources/Images/Object/map_path.bmp", 0, 0, 160 * MAGNI, 10 * MAGNI, 16, 1, MGT);
	IMAGEMANAGER->addFrameImage("map_point", "Resources/Images/Object/map_point.bmp", 0, 0, 40 * MAGNI, 10 * MAGNI, 4, 1, MGT);





#pragma endregion

#pragma region MapTool

	// 맵툴 
	IMAGEMANAGER->addFrameImage("abyss_tile1", "Resources/Images/MapTool/abyss1.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile2", "Resources/Images/MapTool/abyss2.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile3", "Resources/Images/MapTool/abyss3.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile4", "Resources/Images/MapTool/abyss4.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile5", "Resources/Images/MapTool/abyss5.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile6", "Resources/Images/MapTool/abyss6.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile7", "Resources/Images/MapTool/abyss7.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile8", "Resources/Images/MapTool/abyss8.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile9", "Resources/Images/MapTool/abyss9.bmp", 0, 0, 256 * 3, 47  * 3, 6, 24, MGT);

	IMAGEMANAGER->addFrameImage("abyss_tile11", "Resources/Images/MapTool/abyss11.bmp", 0, 0, 3328,2496, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile22", "Resources/Images/MapTool/abyss22.bmp", 0, 0, 3328,2496, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile33", "Resources/Images/MapTool/abyss33.bmp", 0, 0, 3328,2496, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile44", "Resources/Images/MapTool/abyss44.bmp", 0, 0, 3328,2496, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile55", "Resources/Images/MapTool/abyss55.bmp", 0, 0, 3328,2496, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile66", "Resources/Images/MapTool/abyss66.bmp", 0, 0, 3328,2496, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile77", "Resources/Images/MapTool/abyss77.bmp", 0, 0, 3328,2496, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile88", "Resources/Images/MapTool/abyss88.bmp", 0, 0, 3328,2496, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile99", "Resources/Images/MapTool/abyss99.bmp", 0, 0, 3328 ,611, 6, 24, MGT);


	IMAGEMANAGER->addImage("mBG", "Resources/Images/MapTool/bg.bmp", 0, 0, 1280, 720, MGT);
	IMAGEMANAGER->addImage("mbg", "Resources/Images/MapTool/mbg.bmp", 0, 0, 320,720, MGT);
	IMAGEMANAGER->addImage("abyss9BG", "Resources/Images/MApToll/abyss9BG.bmp", 0, 0, 256 * MAGNI, 192 * MAGNI, MGT);

	IMAGEMANAGER->addImage("tileSetB", "Resources/Images/MapTool/tileSetB.bmp", 0, 0, 100, 50, MGT);
	IMAGEMANAGER->addImage("wallB", "Resources/Images/MapTool/wallB.bmp", 0, 0, 100, 50, MGT);
	IMAGEMANAGER->addImage("fillB", "Resources/Images/MapTool/fillB.bmp", 0, 0, 100, 50, MGT);
	IMAGEMANAGER->addImage("undoB", "Resources/Images/MapTool/undoB.bmp", 0, 0, 100, 50, MGT);
	IMAGEMANAGER->addImage("plusB", "Resources/Images/MapTool/plusB.bmp", 0, 0, 50, 50, MGT);
	IMAGEMANAGER->addImage("minusB", "Resources/Images/MapTool/minusB.bmp", 0, 0, 50, 50, MGT);
	IMAGEMANAGER->addImage("loadB", "Resources/Images/MapTool/loadB.bmp", 0,0,100,50, MGT);
	IMAGEMANAGER->addImage("saveB", "Resources/Images/MapTool/saveB.bmp", 0, 0, 100, 50, MGT);

	// 선택 타일 표시
	IMAGEMANAGER->addImage("tileS", "Resources/Images/MapTool/tileSlot.bmp", 0, 0, 24, 24, MGT);


#pragma endregion
	return S_OK;
}

ImageClass::ImageClass()
{
}

ImageClass::~ImageClass()
{
}
