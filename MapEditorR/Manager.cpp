#include "Manager.hpp"



/// --------------------------------------------------------------------------------------------------
void Manager::SceneChange()
{
	// ���̃V�[��
	switch (BASICPARAM::e_nowScene)
	{
		// �^�C�g��
	case ESceneNumber::TITLE:
		POINTER_RELEASE(p_baseMove);
		p_baseMove = new Title();
		break;


		// �}�b�v�G�f�B�^�[
	case ESceneNumber::MAPEDITOR:
		POINTER_RELEASE(p_baseMove);
		p_baseMove = new MapEditor();


	default:
		break;
	}
}



/// --------------------------------------------------------------------------------------------------
Manager::Manager()
{
	// ������
	BASICPARAM::e_preScene = ESceneNumber::TITLE;
	BASICPARAM::e_nowScene = ESceneNumber::TITLE;


	// �������̏�����
	p_baseMove = nullptr;
	p_baseMove = new Title();
}



/// --------------------------------------------------------------------------------------------------
Manager::~Manager()
{
	POINTER_RELEASE(p_baseMove);
}



/// --------------------------------------------------------------------------------------------------
void Manager::Update()
{
	// ���̃V�[���ƒ��O�̃V�[��������
	if (BASICPARAM::e_nowScene == BASICPARAM::e_preScene)
	{
		// �Q�[���Ɋւ���
		p_baseMove->Draw();


		// �Q�[���Ɋւ���
		p_baseMove->Process();
	}
	// �V�[�����ڍs����悤�Ɏw�肳�ꂽ��
	else
	{
		// �V�[����ς���
		SceneChange();


		// ���O�̃V�[���ƍ��̃V�[���𓯂��ɂ���
		BASICPARAM::e_preScene = BASICPARAM::e_nowScene;
	}
}