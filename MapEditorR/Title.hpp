#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"
#include <fstream>
#include <sstream>



// �^�C�g���ł̃V�[��
enum class STEPNUMBER
{
	backGround, chip, file, fileExc, nextScene
};


/*
�^�C�g��
*/
class Title : public BaseScene
{
private:
	/// �^�C�g���Ɋւ���---------------------------------------------------

	// �X�e�b�v����
	STEPNUMBER stepNowNum;


	/// �}�b�v�G�f�B�^�Ɋւ���---------------------------------------------

	// �}�b�v�`�b�v�f��
	std::vector<int>* vp_mapChip;

	// �������ރt�@�C���̃p�X
	std::string* p_filePath;

	// ���}�b�v�̍쐬
	void CreateMap(const bool t_fileCSV);

	// �w�i�摜
	int* p_backGround;


public:
	// �R���X�g���N�^(�}�b�v�`�b�v�f�ނƏ������݃t�@�C���̃p�X���󂯎��
	Title(std::vector<int>& t_mapChip, std::string& t_filePath, int& t_backGround);

	// �f�X�g���N�^
	~Title() {}


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;

	// �h���b�O�A���h�h���b�v����}�b�v�`�b�v�f�ނ̒ǉ�
	void AddDragAndDrop(char t_path[]) override;
};

