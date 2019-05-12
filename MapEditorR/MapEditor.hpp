#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"



/*
�}�b�v�G�f�B�^�[
*/
class MapEditor : public BaseScene
{
private:
	// �}�b�v�`�b�v�f��
	std::vector<int> *vp_mapChip;


public:
	MapEditor(std::vector<int> &t_mapChip);
	~MapEditor();


	void Draw() override;
	void Process() override;
	void AddMapChip(char t_path[]) override {}
};

