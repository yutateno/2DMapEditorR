#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"



/*
�^�C�g��
*/
class Title : public BaseScene
{
private:
	// �}�b�v�`�b�v�f��
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

