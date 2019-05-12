#pragma once



// �V�[���̓���
enum class ESceneNumber
{
	TITLE, MAPEDITOR
};


namespace BASICPARAM
{
	// ���O�̃V�[��
	extern ESceneNumber e_preScene;

	// ���̃V�[��
	extern ESceneNumber e_nowScene;
}


/*
���[�u�̑�{
*/
class BaseScene
{
public:
	// �`��
	virtual void Draw() = 0;

	// �v���Z�X
	virtual void Process() = 0;
};

