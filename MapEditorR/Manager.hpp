#pragma once
#include "BaseScene.hpp"

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


public:
	// �R���X�g���N�^
	Manager();

	// �f�X�g���N�^
	~Manager();


	// ���C���v���Z�X
	void Update();
};
