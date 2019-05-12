#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"



/*
タイトル
*/
class Title : public BaseScene
{
private:
	// マップチップ素材
	std::vector<int> *vp_mapChip;

public:
	Title(std::vector<int> &t_mapChip);
	~Title();


	void Draw() override;
	void Process() override;

	void AddMapChip(char t_path[]) override
	{
		vp_mapChip->push_back(LoadGraph(t_path));
	}
};

