#include "Manager.hpp"



/*
メイン部分
*/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
	// ログを出力させる
	SetOutApplicationLogValidFlag(TRUE);
#elif NDEBUG
	// ログを出力させない
	SetOutApplicationLogValidFlag(FALSE);
#endif

	SetWindowText("MapEditorR");		// window名の変更
	ChangeWindowMode(TRUE);				// ウィンドウモードに変更


	SetGraphMode(1280, 760, 32);			// 画面サイズ設定

	// DxLibの初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	
	SetAlwaysRunFlag(TRUE);				// 裏画面でも常にアクティブに変更
	SetDrawScreen(DX_SCREEN_BACK);		// 裏画面描画

	SetDragFileValidFlag(TRUE);			// ドラッグアンドドロップの有効化


	// ツール本体の初期化
	Manager manager = Manager();


	// メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && KeyData::CheckEnd() && !manager.GetEnd())
	{
		KeyData::UpDate();						// キーボードの更新
		MouseData::UpDate();				// マウスの更新
		MouseWheelData::Update();	// マウスホイールの更新

		// 本体の更新
		manager.Update();

		// ドラッグアンドドロップが行われたとき
		if (GetDragFileNum() > 0)
		{
			char filePath[MAX_PATH];				// ファイルのパスを所持する仮置き変数

			GetDragFilePath(filePath);				// ドラッグアンドドロップのパスを取得

			manager.GetAddDragAndDrop(filePath);	// ドラッグアンドドロップのパスを渡す
		}
	}

	// 本体の削除
	manager.~Manager();

	// 後片付け
	InitGraph();
	DxLib_End();

	// プロジェクト終了
	return 0;
}