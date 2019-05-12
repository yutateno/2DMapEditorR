#include "Title.hpp"



Title::Title()
{

}



Title::~Title()
{

}



void Title::Draw()
{
	DrawBox(100, 60, 540, 120, GetColor(255, 0, 0), true);
	DrawBox(100, 180, 540, 240, GetColor(255, 0, 0), true);
	DrawBox(100, 300, 540, 360, GetColor(255, 0, 0), true);
}


void Title::Process()
{
	if (KeyData::Get(KEY_INPUT_0) == 1) BASICPARAM::e_nowScene = ESceneNumber::MAPEDITOR;
}
