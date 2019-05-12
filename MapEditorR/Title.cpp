#include "Title.hpp"



Title::Title(std::vector<int>& t_mapChip)
{
	vp_mapChip = &t_mapChip;
}



Title::~Title()
{

}



void Title::Draw()
{
	DrawBox(100, 60, 540, 120, GetColor(255, 0, 0), true);
	DrawBox(100, 180, 540, 240, GetColor(255, 0, 0), true);
	DrawBox(100, 300, 540, 360, GetColor(255, 0, 0), true);

	if (vp_mapChip->size() != 0)
	{
		for (int i = 0, n = static_cast<int>(vp_mapChip->size()); i != n; ++i)
		{
			DrawGraph(i * 15, 0, vp_mapChip->at(i), true);
		}
	}
}


void Title::Process()
{
	if (KeyData::Get(KEY_INPUT_0) == 1) BASICPARAM::e_nowScene = ESceneNumber::MAPEDITOR;
}
