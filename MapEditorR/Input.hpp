#pragma once
#include "DxLib.h"



// �L�[�{�[�h�̓��͏��
class KeyData
{
private:
	static int key[256];		// �L�[�̓��͏�Ԋi�[�p�ϐ�
	static char tmpKey[256];	// ���݂̃L�[�̓��͏�Ԃ��i�[����

public:
	static void UpDate();			// �L�[���͂̏�ԍX�V
	static int Get(int t_keyCode);	// �L�[���͏�Ԏ擾
	static bool CheckEnd();			// �����I��
};



// �}�E�X���͏��
class MouseData
{
private:
	static int mouse[3];			// �}�E�X�̓��͏�Ԋi�[�p�ϐ�
	static int mouseInput;			// ���݂̃}�E�X�̓��͏�Ԃ��i�[����

public:
	static void UpDate();					//�}�E�X�̃N���b�N�̏�Ԃ��X�V����
	static int GetClick(int t_mouseCode);	//�}�E�X�̃N���b�N�̏�Ԃ�Ԃ�
};



// �}�E�X�z�C�[�����͏��
class MouseWheelData
{
private:
	static int mouseWheel;			// ���݂̃z�C�[���ʒu���i�[����ϐ�
	static int oldMouseWheel;		// ���O�̃z�C�[���ʒu���i�[����ϐ�

public:
	static void Update();							//�}�E�X�̃z�C�[���̏�Ԃ��X�V
	static int GetMouseWheel(int t_mouseWheelCode);	//�}�E�X�z�C�[���̏�Ԃ�Ԃ�
};