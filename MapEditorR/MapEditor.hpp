#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"
#include <fstream>
#include <sstream>




enum class EChipSelectAreaX : unsigned int
{
	mapRightAddFirst = 20, mapRightAddEnd = 60, mapUnderAddFirst = 80, mapUnderAddEnd = 120
	, mapRightDelFirst = 140, mapRightDelEnd = 180 , mapUnderDelFirst = 200, mapUnderDelEnd = 240
};


enum class EChipSelectAreaY : unsigned int
{
	oneAreaFirst = 20, oneAreaEnd = 60 , secondAreaFirst = 80 , secondAreaEnd = 120, thirdAreaFirst = 140, thirdAreaEnd = 180
	, fourthAreaFirst = 200, fourthAreaEnd = 240
};


/*
�}�b�v�G�f�B�^�[
*/
class MapEditor : public BaseScene
{
private:
	/// �}�b�v�`�b�v�f�ނɊւ���----------------------------------

	// �}�b�v�`�b�v�f��
	std::vector<int>* vp_mapChip;

	// �}�b�v�`�b�v�I����ʂ̕\��
	bool selectMapChipWindow;

	// �}�b�v�`�b�v�̃T�C�Y�𒲂ׂ�
	int mapChipSizeX, mapChipSizeY;

	// �}�b�v�`�b�v�̈��`�悷��
	void MapChipDraw(const int t_areaX, const int t_areaY, const int t_chipID);

	// �w�i�摜
	int* p_backGround;


	/// �t�@�C���Ɋւ���------------------------------------------

	// �������ރt�@�C���p�X
	std::string* p_filePath;

	// �}�b�v�`�b�vID�͓񌅂��ǂ���
	bool chipDoubleDigitID;

	// .csv���ǂ���
	bool readFileCSV;

	// �ǂݍ��񂾃t�@�C������ID�擾
	std::vector<std::vector<std::string>> vv_mapdata;

	// �t�@�C���ǂݍ���
	void LoadMap();

	// �t�@�C����������
	void SaveMap();

	// �Z�[�u���������ǂ���
	bool saveEndFlag;

	// �Z�[�u�����̕\���J�E���g
	int saveEndViewCount;


	/// �}�E�X�Ɋւ���-------------------------------------------

	// �}�E�X�̈ʒu
	int mouseX, mouseY;


public:
	// �R���X�g���N�^(�}�b�v�`�b�v�f�ނƃt�@�C���p�X���󂯂Ƃ�
	MapEditor(std::vector<int>& t_mapChip, std::string& t_filePath, int& t_backGround);

	// �f�X�g���N�^
	~MapEditor();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;

	// �h���b�O�A���h�h���b�v�ɂ��ǉ�
	void AddDragAndDrop(char t_path[]) override {}
};

