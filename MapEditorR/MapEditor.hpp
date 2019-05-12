#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"



/*
マップエディター
*/
class MapEditor : public BaseScene
{
private:
	// マップチップ素材
	std::vector<int> *vp_mapChip;


public:
	MapEditor(std::vector<int> &t_mapChip);
	~MapEditor();


	void Draw() override;
	void Process() override;
	void AddMapChip(char t_path[]) override {}
};

