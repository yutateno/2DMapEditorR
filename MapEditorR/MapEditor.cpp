#include "MapEditor.hpp"



MapEditor::MapEditor()
{
}



MapEditor::~MapEditor()
{
}



void MapEditor::Draw()
{
	printfDx("MapEditor\n");
}



void MapEditor::Process()
{
	if (KeyData::Get(KEY_INPUT_1) == 1) BASICPARAM::e_nowScene = ESceneNumber::TITLE;
}
