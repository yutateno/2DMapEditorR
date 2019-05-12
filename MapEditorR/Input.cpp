#include "Input.hpp"



//////////////////////////////////////////////�L�[�{�[�h////////////////////////////////////////////////////

int KeyData::key[256];
char KeyData::tmpKey[256];


/// ------------------------------------------------------------------------------------------------------------
void KeyData::UpDate()
{
	GetHitKeyStateAll(KeyData::tmpKey);	// �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < 256; i++)
	{
		// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
		if (KeyData::tmpKey[i] != 0)
		{
			KeyData::key[i]++;
		}
		// �L�[�������ꂽ�u��
		else if (KeyData::key[i] > 0)
		{
			KeyData::key[i] = -1;
		}
		// �A�N�V�������Ȃ�
		else
		{
			KeyData::key[i] = 0;
		}
	}
}



/// ------------------------------------------------------------------------------------------------------------
bool KeyData::CheckEnd()
{
	return KeyData::key[KEY_INPUT_ESCAPE] <= 0;
}



/// ------------------------------------------------------------------------------------------------------------
int KeyData::Get(int t_keyCode)
{
	return KeyData::key[t_keyCode];
}



//////////////////////////////////////////////�}�E�X�֘A////////////////////////////////////////////////////

int MouseData::mouse[3];
int MouseData::mouseInput;



/// ------------------------------------------------------------------------------------------------------------
void MouseData::UpDate()
{
	mouseInput = GetMouseInput();		//�}�E�X�̉�������Ԏ擾

	for (int i = 0; i < 3; i++)
	{
		//������Ă�����
		if ((mouseInput & 1 << i) != 0)
		{
			mouse[i]++;
		}
		//������ĂȂ�������
		else
		{
			mouse[i] = 0;
		}
	}
}



/// ------------------------------------------------------------------------------------------------------------
int MouseData::GetClick(int t_mouseCode)
{
	return mouse[t_mouseCode];
}



//////////////////////////////////////////////�}�E�X�z�C�[���֘A////////////////////////////////////////////////////

int MouseWheelData::mouseWheel;
int MouseWheelData::oldMouseWheel;



/// ------------------------------------------------------------------------------------------------------------
void MouseWheelData::Update()
{
	oldMouseWheel = mouseWheel;

	// ��Ƀz�C�[������������
	if (oldMouseWheel - mouseWheel > 0)
	{
		mouseWheel++;
	}
	// ���Ƀz�C�[������������
	else if (oldMouseWheel - mouseWheel < 0)
	{
		mouseWheel--;
	}
	// �������Ă��Ȃ��Ƃ�
	else 
	{
		mouseWheel = 0;
	}
}



/// ------------------------------------------------------------------------------------------------------------
int MouseWheelData::GetMouseWheel(int t_mouseWheelCode)
{
	return mouseWheel += t_mouseWheelCode;
}