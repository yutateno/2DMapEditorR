#include "Manager.hpp"



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);
#endif

	SetWindowText("MapEditorR");
	ChangeWindowMode(TRUE);
	SetGraphMode(640, 480, 32);
	DxLib_Init();
	SetAlwaysRunFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	SetDragFileValidFlag(TRUE);


	Manager manager = Manager();


	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && KeyData::CheckEnd())
	{
		KeyData::UpDate();
		MouseData::Mouse_UpDate();
		MouseWheelData::MouseWheel_Update();

		manager.Update();

		if (GetDragFileNum() > 0)
		{
			char filePath[MAX_PATH];

			// �h���b�O���h���b�v���ꂽ�t�@�C���̃p�X���擾����
			GetDragFilePath(filePath);

			// �h���b�O���h���b�v���ꂽ�t�@�C�����摜�Ƃ��ēǂݍ���
			manager.GetAddMapChipPath(filePath);
		}
	}

	manager.~Manager();

	InitGraph();
	DxLib_End();
	return 0;
}