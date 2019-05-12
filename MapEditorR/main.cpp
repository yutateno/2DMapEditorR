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
	DxLib_Init();
	SetGraphMode(640, 480, 32);
	SetDrawScreen(DX_SCREEN_BACK);


	Manager manager = Manager();


	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && KeyData::CheckEnd())
	{
		KeyData::UpDate();
		MouseData::Mouse_UpDate();
		MouseWheelData::MouseWheel_Update();

		manager.Update();
	}

	manager.~Manager();

	InitGraph();
	DxLib_End();
	return 0;
}