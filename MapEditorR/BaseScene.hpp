#pragma once
#include <vector>
#include <string>



// �V�[���̓���
enum class ESceneNumber
{
	TITLE, MAPEDITOR
};



// �S�̂ŕK�v�ȕϐ�
namespace BASICPARAM
{
	// ���O�̃V�[��
	extern ESceneNumber e_preScene;

	// ���݂̃V�[��
	extern ESceneNumber e_nowScene;
}


/*
���[�u�̑�{
*/
class BaseScene
{
protected:
	// �����I���t���b�O
	bool endFlag;


public:
	// �`��
	virtual void Draw() = 0;

	// �v���Z�X
	virtual void Process() = 0;


	// �}�b�v�`�b�v�̒ǉ�
	virtual void AddDragAndDrop(char t_path[]) = 0;


	// �����I�ɏI��������
	bool GetEnd() { return endFlag; }
};

