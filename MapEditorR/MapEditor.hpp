#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"
#include <fstream>
#include <sstream>



/*
�}�b�v�G�f�B�^�[
*/
class MapEditor : public BaseScene
{
private:
	// �}�b�v�`�b�v�f��
	std::vector<int> *vp_mapChip;

	// �������ރt�@�C���p�X
	std::string* p_filePath;

	// ID�͓񌅂��ǂ���
	bool chipDoubleDigitID;

	// .csv���ǂ���
	bool readFileCSV;

	// �ǂݍ��񂾃t�@�C������ID�擾
	std::vector<std::vector<std::string>> vv_mapdata;

	// �t�@�C���ǂݍ���
	void LoadMap();

	// �t�@�C����������
	void SaveMap();

	// �}�E�X�̈ʒu
	int mouseX, mouseY;


public:
	MapEditor(std::vector<int>& t_mapChip, std::string& t_filePath);
	~MapEditor();


	void Draw() override;
	void Process() override;
	void AddDragAndDrop(char t_path[]) override {}
};

