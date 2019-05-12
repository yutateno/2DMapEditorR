#include "Manager.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Manager::SceneChange()
{
	// ���̃V�[��
	switch (BASICPARAM::e_nowScene)
	{
		// �^�C�g��
	case ESceneNumber::TITLE:
		POINTER_RELEASE(p_baseMove);
		p_baseMove = new Title(v_mapChip, filePath);
		break;


		// �}�b�v�G�f�B�^�[
	case ESceneNumber::MAPEDITOR:
		POINTER_RELEASE(p_baseMove);
		p_baseMove = new MapEditor(v_mapChip, filePath);


	default:
		break;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Manager::Manager()
{
	// ������
	BASICPARAM::e_preScene = ESceneNumber::TITLE;
	BASICPARAM::e_nowScene = ESceneNumber::TITLE;


	// �摜�t�@�C��
	v_mapChip.clear();

	
	// �������ރt�@�C��
	filePath = "";


	// �������̏�����
	p_baseMove = nullptr;
	p_baseMove = new Title(v_mapChip, filePath);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Manager::~Manager()
{
	POINTER_RELEASE(p_baseMove);


	if (v_mapChip.size() != 0)
	{
		for (size_t i = 0, n = v_mapChip.size(); i != n; ++i)
		{
			GRAPHIC_RELEASE(v_mapChip[i]);
		}
		v_mapChip.shrink_to_fit();
		v_mapChip.clear();
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
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
