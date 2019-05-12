#include "MapEditor.hpp"



MapEditor::MapEditor(std::vector<int>& t_mapChip)
{
	vp_mapChip = &t_mapChip;
}



MapEditor::~MapEditor()
{
}



void MapEditor::Draw()
{
	if (vp_mapChip->size() != 0)
	{
		for (int i = 0, n = static_cast<int>(vp_mapChip->size()); i != n; ++i)
		{
			DrawGraph(i * 15, 0, vp_mapChip->at(i), true);
		}
	}
}



void MapEditor::Process()
{
	if (KeyData::Get(KEY_INPUT_1) == 1) BASICPARAM::e_nowScene = ESceneNumber::TITLE;
}
