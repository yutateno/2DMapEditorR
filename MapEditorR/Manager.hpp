#pragma once
#include "BaseScene.hpp"
#include <vector>

#include "Title.hpp"
#include "MapEditor.hpp"



/*
�Q�[���̑�{
*/
class Manager
{
private:
	/// �e�V�[���Ɋւ���-----------------------------------------------------

	// �V�[���̊��N���X
	BaseScene* p_baseMove;

	// �V�[����؂�ւ���
	void SceneChange();


	// �}�b�v�`�b�v�f��
	std::vector<int> v_mapChip;


public:
	// �R���X�g���N�^
	Manager();

	// �f�X�g���N�^
	~Manager();


	// ���C���v���Z�X
	void Update();


	// �f�ގ󂯎��
	void GetAddMapChipPath(char t_path[])
	{
		p_baseMove->AddMapChip(t_path);
	}
};
