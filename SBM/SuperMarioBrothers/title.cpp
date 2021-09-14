#include"title.h"
#include"DxLib.h"


int background, name, world, wonum, time , top;
int score[15];
int uicoin[4];
int i;
int a;
int count = 0;

void Title_Init(void) {
	background = LoadGraph("images/title.png");
	name = LoadGraph("images/name_mario.png");
	world = LoadGraph("images/world.png");
	wonum = LoadGraph("images/1-.png");
	time = LoadGraph("images/time.png");
	top = LoadGraph("images/top.png");

	Title_ImgLoad();
}
void Title_Update(void) {
	count++;
}
void Title_Draw(void) {
	DrawGraph(0, 0, background, TRUE);
	DrawGraph(80, 32, name, TRUE);
	for (i = 0; i < 6; i++)
	{
		DrawGraph(80 + i * 16, 48, score[0], TRUE);
	}
	Title_Coinanime();
	DrawGraph(256, 48, score[11], TRUE);
	for (i = 0; i < 2; i++)
	{
		DrawGraph(272 + i * 16, 48, score[0], TRUE);
	}
	DrawGraph(384, 32, world, TRUE);
	DrawGraph(400, 48, wonum, TRUE);
	DrawGraph(432, 48, score[1], TRUE);
	DrawGraph(512, 32, time, TRUE);
	for (i = 0; i < 3; i++)
	{
		DrawGraph(528 + i * 16, 48, score[0], TRUE);
	}
	DrawGraph(240, 368, top, TRUE);
	for (i = 0; i < 6; i++)
	{
		DrawGraph(320 + i * 16, 368, score[0], TRUE);
	}
}
int Title_ImgLoad(void) {
	if (LoadDivGraph("images/num.png", 15, 15, 1, 16, 16, score) == -1) {
		return -1;
	}
	if (LoadDivGraph("images/uicoin.png", 4, 4, 1, 16, 16, uicoin) == -1) {
		return -1;
	}
}

void Title_Coinanime(void) {
	static int img_nm = 0;
	DrawGraph(240, 48, uicoin[img_nm], TRUE);
	if (count % 15 == 0) {
		img_nm++;
		if (img_nm > 3) {
			img_nm = 0;
		}
	}
	
	if (count > 60) {
		count = 0;
	}
	
}