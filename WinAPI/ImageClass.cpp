#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
	
	//MAGNI :  WINSIZE_X/512   //magnification

#pragma region BG
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
	IMAGEMANAGER->addImage("abyss9BG", "Resources/Images/MApToll/abyss9BG.bmp", 0, 0, 256 * MAGNI, 192 * MAGNI, MGT);

	IMAGEMANAGER->addImage("Å×¸Ê", "Resources/testMap.bmp", 0, 0, 1280,960, MGT);
	IMAGEMANAGER->addImage("¸Ê2", "Resources/testMap2.bmp", 0, 0, 720*10, 720*10, MGT);

#pragma region Player
	IMAGEMANAGER->addImage("p_attacked", "Resources/Images/Player/p_attacked.bmp", 0, 0, 24 * MAGNI, 37 * MAGNI, MGT);
	IMAGEMANAGER->addImage("p_down", "Resources/Images/Player/p_down.bmp", 0, 0, 32 * MAGNI, 29 * MAGNI, MGT);

	IMAGEMANAGER->addFrameImage("p_att_ax_6", "Resources/Images/Player/p_att_ax_6.bmp", 48 * MAGNI, 38 * MAGNI, 2, 1, MGT);
	IMAGEMANAGER->addFrameImage("p_run_6", "Resources/Images/Player/p_run_6.bmp", 80 * MAGNI, 37 * MAGNI, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("p_run_7", "Resources/Images/Player/p_run_7.bmp", 104 * MAGNI, 72 * MAGNI, 4, 2, MGT);
	IMAGEMANAGER->addFrameImage("p_run_9", "Resources/Images/Player/p_run_9.bmp", 124 * MAGNI, 76 * MAGNI, 4, 2, MGT);
	IMAGEMANAGER->addFrameImage("p_run_11", "Resources/Images/Player/p_run_9.bmp", 108 * MAGNI, 82 * MAGNI, 4, 2, MGT);
	IMAGEMANAGER->addFrameImage("p_run_12", "Resources/Images/Player/p_run_12.bmp", 80 * MAGNI, 42 * MAGNI, 4, 1, MGT);

	IMAGEMANAGER->addImage("p_idle_6", "Resources/Images/Player/p_idle_6.bmp", 0,0,24 * MAGNI, 46 * MAGNI, MGT);


#pragma endregion

#pragma region object
	IMAGEMANAGER->addFrameImage("dropItem", "Resources/Images/Object/dropItem.bmp", 150 * MAGNI, 22 * MAGNI, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("Equipment_icon", "Resources/Images/Object/Equipment_icon.bmp", 160 * MAGNI, 52 * MAGNI, 6, 2, MGT);
	IMAGEMANAGER->addFrameImage("Inven_icon", "Resources/Images/Object/Inven_icon.bmp", 352 * MAGNI, 96 * MAGNI, 11, 3, MGT);

	IMAGEMANAGER->addFrameImage("monsterDie", "Resources/Images/Object/monsterDie.bmp", 160 * MAGNI, 32 * MAGNI, 5, 1, MGT);


#pragma endregion

#pragma region UI	


	
	IMAGEMANAGER->addImage("titleButton", "Resources/Images/Object/titleButton.bmp", RSCENTER_X, CENTER_Y, 98 * MAGNI, 30 * MAGNI, MGT);
	IMAGEMANAGER->addImage("nextButton", "Resources/Images/Object/nextButton.bmp", RSCENTER_X, CENTER_Y, 72 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("ynButton", "Resources/Images/Object/YesNoButton.bmp",   RSCENTER_X, CENTER_Y, 56 * MAGNI, 20 * MAGNI, MGT);
	IMAGEMANAGER->addImage("ynButton1", "Resources/Images/Object/YesNoButton1.bmp", RSCENTER_X, CENTER_Y, 56 * MAGNI, 20 * MAGNI, MGT);
	IMAGEMANAGER->addImage("ynButton2", "Resources/Images/Object/YesNoButton2.bmp", RSCENTER_X, CENTER_Y, 56 * MAGNI, 20 * MAGNI, MGT);

	IMAGEMANAGER->addImage("newGame", "Resources/Images/Object/newGame.bmp", 0, 0, 58 * MAGNI, 12 * MAGNI, MGT);
	IMAGEMANAGER->addImage("newGame0", "Resources/Images/Object/newGame0.bmp", 0, 0, 58 * MAGNI, 12 * MAGNI, MGT);

	// ÀÛÀº ÇÁ·¹ÀÓ ÀÌ¹ÌÁö¶ó ÂÉ°³°í ·»´õÇÒ¶§ *ºñÀ² Àû¿ë
	IMAGEMANAGER->addFrameImage("Num_0", "Resources/Images/Object/Num_0.bmp",		  0, 0, 70 , 8  , 10, 1, MGT);
	IMAGEMANAGER->addFrameImage("Num_R", "Resources/Images/Object/Num_R.bmp",		  0, 0, 90 , 10 , 10, 1, MGT);
	IMAGEMANAGER->addFrameImage("Num_G", "Resources/Images/Object/Num_G.bmp",		  0, 0, 90 , 10 , 10, 1, MGT);
	IMAGEMANAGER->addFrameImage("Num_B", "Resources/Images/Object/Num_B.bmp",		  0, 0, 90 , 10 , 10, 1, MGT);
	IMAGEMANAGER->addFrameImage("Num_store", "Resources/Images/Object/Num_store.bmp", 0, 0, 90 , 10 , 10, 1, MGT);
	//IMAGEMANAGER->addFrameImage("Num_UI", "Resources/Images/Object/Num_UI.bmp",		  0, 0, 99 , 10 , 11, 1, MGT); //99 * MAGNI, 10 * MAGNI
	IMAGEMANAGER->addFrameImage("Num_UI", "Resources/Images/Object/Num_UI2.bmp", 0, 0, 297, 30, 11, 1, MGT); //99 * MAGNI, 10 * MAGNI

	IMAGEMANAGER->addImage("abyss1", "Resources/Images/Object/abyss1.bmp", 0, 0, 144 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("abyss2", "Resources/Images/Object/abyss2.bmp", 0, 0, 144 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("abyss3", "Resources/Images/Object/abyss3.bmp", 0, 0, 144 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("stage1", "Resources/Images/Object/stage1.bmp", 0, 0, 144 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("stage2", "Resources/Images/Object/stage2.bmp", 0, 0, 144 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("stage3", "Resources/Images/Object/stage3.bmp", 0, 0, 144 * MAGNI, 48 * MAGNI, MGT);




	IMAGEMANAGER->addFrameImage("skill_att_Icon", "Resources/Images/Object/skill_att_Icon.bmp", 0, 0, 297 * MAGNI, 99 * MAGNI, 9, 3, MGT);
	IMAGEMANAGER->addFrameImage("skill_utill_Icon", "Resources/Images/Object/skill_utill_Icon.bmp", 0, 0, 256 * MAGNI, 32 * MAGNI, 8, 1, MGT);
	IMAGEMANAGER->addFrameImage("store_icon", "Resources/Images/Object/store_icon.bmp", 0, 0, 240 * MAGNI, 20 * MAGNI, 15, 2, MGT);


	//IMAGEMANAGER->addImage("hp", "Resources/Images/Object/hp.bmp", 0, 0, 1 * MAGNI, 4 * MAGNI, MGT);
	IMAGEMANAGER->addImage("HPBar", "Resources/Images/Object/HPBar.bmp", 65, 12, 92 * MAGNI, 26 * MAGNI, MGT);
	//IMAGEMANAGER->addImage("sp", "Resources/Images/Object/hp.bmp", 0, 0, 1 * MAGNI, 4 * MAGNI, MGT);
	IMAGEMANAGER->addImage("SPBar", "Resources/Images/Object/SPBar.bmp", 360 ,12, 92 * MAGNI, 26 * MAGNI, MGT);
	IMAGEMANAGER->addImage("Item_select", "Resources/Images/Object/Item_select.bmp", 0, 0, 40 * MAGNI, 40 * MAGNI, MGT);
	IMAGEMANAGER->addImage("tap_1", "Resources/Images/Object/tap_1.bmp", 0, 0, 27 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("tap_2", "Resources/Images/Object/tap_2.bmp", 0, 0, 27 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("tap_3", "Resources/Images/Object/tap_3.bmp", 0, 0, 27 * MAGNI, 48 * MAGNI, MGT);
	IMAGEMANAGER->addImage("UI_pathInfo", "Resources/Images/Object/UI_pathInfo.bmp", 0, 0, 21 * MAGNI, 21 * MAGNI, MGT);
	IMAGEMANAGER->addImage("LvUp", "Resources/Images/Object/LvUp.bmp", 0, 0, 83 * MAGNI, 11 * MAGNI, MGT);

	IMAGEMANAGER->addImage("map_abyss", "Resources/Images/Object/map_abyss.bmp", 0, 0, 37 * MAGNI, 10 * MAGNI, MGT);
	IMAGEMANAGER->addImage("map_stage", "Resources/Images/Object/map_stage.bmp", 0, 0, 37 * MAGNI, 10 * MAGNI, MGT);
	IMAGEMANAGER->addFrameImage("map_sumnail", "Resources/Images/Object/map_sumnail.bmp", 0, 0, 37 * MAGNI, 10 * MAGNI, 8, 1, MGT);
	IMAGEMANAGER->addFrameImage("map_path", "Resources/Images/Object/map_path.bmp", 0, 0, 170 * MAGNI, 10 * MAGNI, 17, 1, MGT);
	IMAGEMANAGER->addFrameImage("map_point", "Resources/Images/Object/map_point.bmp", 0, 0, 40 * MAGNI, 10 * MAGNI, 4, 1, MGT);




#pragma endregion

#pragma region MapTool

	// ¸ÊÅø 
	IMAGEMANAGER->addFrameImage("abyss_tile1", "Resources/Images/MapTool/abyss1.bmp", 0, 0, 256*3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile2", "Resources/Images/MapTool/abyss2.bmp", 0, 0, 256 * 3, 184 * 3, 32, 23, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile3", "Resources/Images/MapTool/abyss3.bmp", 0, 0, 256 * 3, 184 * 3, 32, 23, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile4", "Resources/Images/MapTool/abyss4.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile5", "Resources/Images/MapTool/abyss5.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile6", "Resources/Images/MapTool/abyss6.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile7", "Resources/Images/MapTool/abyss7.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile8", "Resources/Images/MapTool/abyss8.bmp", 0, 0, 256 * 3, 192 * 3, 32, 24, MGT);
	IMAGEMANAGER->addFrameImage("abyss_tile9", "Resources/Images/MapTool/abyss9.bmp", 0, 0, 256 * 3, 47  * 3, 6, 24, MGT);

	IMAGEMANAGER->addImage("mbg", "Resources/Images/MapTool/mbg.bmp", 0, 0, 320,720, MGT);
	IMAGEMANAGER->addImage("loadB", "Resources/Images/MapTool/loadB.bmp", 0,0,100,50, MGT);
	IMAGEMANAGER->addImage("saveB", "Resources/Images/MapTool/saveB.bmp", 0, 0, 100, 50, MGT);
	IMAGEMANAGER->addImage("wallB", "Resources/Images/MapTool/wallB.bmp", 0, 0, 100, 50, MGT);
	IMAGEMANAGER->addImage("plusB", "Resources/Images/MapTool/plusB.bmp", 0, 0, 50, 50, MGT);
	IMAGEMANAGER->addImage("minusB", "Resources/Images/MapTool/minusB.bmp", 0, 0, 50, 50, MGT);


	


#pragma endregion
	return S_OK;
}

ImageClass::ImageClass()
{
}

ImageClass::~ImageClass()
{
}
