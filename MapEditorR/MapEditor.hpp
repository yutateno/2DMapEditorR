#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"
#include <fstream>
#include <sstream>




enum class EChipSelectAreaX : unsigned int
{
	oneFirst = 20, oneEnd = 60, secondFirst = 80, secondEnd = 120, thirdFirst = 140, thirdEnd = 180
	, fourthFirst = 200, fourthEnd = 240, fifthFirst = 260, fifthEnd = 300
};


enum class EChipSelectAreaY : unsigned int
{
	oneFirst = 20, oneEnd = 60 , secondFirst = 80 , secondEnd = 120, thirdFirst = 140, thirdEnd = 180
	, fourthFirst = 200, fourthEnd = 240, fifthFirst = 260, fifthEnd = 300, sixthFirst = 320, sixthEnd = 360
	, seventhFirst = 380, seventhEnd = 420, eighthFirst = 440, eighthEnd = 480, ninthFirst = 500, ninthEnd = 540
	, tenthFirst = 560, tenthEnd = 600
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

	// �}�b�v�`�b�v��̈ʒu
	int chipSelectAreaX, chipSelectAreaY;

	// �I�����Ă���}�b�v�`�b�vID
	int mouseSelectChipID;

	// �w��̃}�b�v�`�b�vID���폜
	void DeleteChip();

	// �w��̃}�b�v�`�b�vID��ݒ�
	void SettingChip();


	/// �����֐��Ɋւ���----------------------------------------
	
	// �}�b�v�`�b�v�̑I����ʕ`��
	void MapChipSelectDraw();

	// �}�b�v�`�b�v�̑I����ʃv���Z�X
	void MapChipSelectProcess();


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

