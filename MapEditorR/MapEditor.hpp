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

	// �}�b�v�`�b�v�I����ʂ̕\��
	bool selectMapChipWindow;

	// �}�b�v�`�b�v�̃T�C�Y�𒲂ׂ�
	int mapChipSizeX, mapChipSizeY;

	// �}�b�v�`�b�v�̈��`�悷��
	void MapChipDraw(const int t_areaX, const int t_areaY, const int t_chipID);


public:
	MapEditor(std::vector<int>& t_mapChip, std::string& t_filePath);
	~MapEditor();


	void Draw() override;
	void Process() override;
	void AddDragAndDrop(char t_path[]) override {}
};

