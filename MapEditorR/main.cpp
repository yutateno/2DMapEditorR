#include "Manager.hpp"



/*
���C������
*/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
	// ���O���o�͂�����
	SetOutApplicationLogValidFlag(TRUE);
#elif NDEBUG
	// ���O���o�͂����Ȃ�
	SetOutApplicationLogValidFlag(FALSE);
#endif

	SetWindowText("MapEditorR");		// window���̕ύX
	ChangeWindowMode(TRUE);				// �E�B���h�E���[�h�ɕύX


	SetGraphMode(1280, 760, 32);			// ��ʃT�C�Y�ݒ�

	// DxLib�̏�����
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	
	SetAlwaysRunFlag(TRUE);				// ����ʂł���ɃA�N�e�B�u�ɕύX
	SetDrawScreen(DX_SCREEN_BACK);		// ����ʕ`��

	SetDragFileValidFlag(TRUE);			// �h���b�O�A���h�h���b�v�̗L����


	// �c�[���{�̂̏�����
	Manager manager = Manager();


	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && KeyData::CheckEnd() && !manager.GetEnd())
	{
		KeyData::UpDate();						// �L�[�{�[�h�̍X�V
		MouseData::UpDate();				// �}�E�X�̍X�V
		MouseWheelData::Update();	// �}�E�X�z�C�[���̍X�V

		// �{�̂̍X�V
		manager.Update();

		// �h���b�O�A���h�h���b�v���s��ꂽ�Ƃ�
		if (GetDragFileNum() > 0)
		{
			char filePath[MAX_PATH];				// �t�@�C���̃p�X���������鉼�u���ϐ�

			GetDragFilePath(filePath);				// �h���b�O�A���h�h���b�v�̃p�X���擾

			manager.GetAddDragAndDrop(filePath);	// �h���b�O�A���h�h���b�v�̃p�X��n��
		}
	}

	// �{�̂̍폜
	manager.~Manager();

	// ��Еt��
	InitGraph();
	DxLib_End();

	// �v���W�F�N�g�I��
	return 0;
}