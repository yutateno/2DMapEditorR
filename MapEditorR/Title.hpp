#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"
#include <fstream>
#include <sstream>



// �V�[��
enum class STEPNUMBER
{
	chip, file, fileExc, nextScene
};


/*
�^�C�g��
*/
class Title : public BaseScene
{
private:
	// �}�b�v�`�b�v�f��
	std::vector<int>* vp_mapChip;

	// �X�e�b�v����
	STEPNUMBER stepNowNum;

	// �������ރt�@�C���̃p�X
	std::string* p_filePath;

	// �K���ȃt�@�C�����쐬�����Ƃ��̉��}�b�v
	void CreateMap(const bool t_fileCSV);


public:
	Title(std::vector<int>& t_mapChip, std::string& t_filePath);
	~Title();


	void Draw() override;
	void Process() override;

	void AddDragAndDrop(char t_path[]) override;
};

