#pragma once
#include "DxLib.h"



// キーボードの入力状態
class KeyData
{
private:
	static int key[256];		// キーの入力状態格納用変数
	static char tmpKey[256];	// 現在のキーの入力状態を格納する

public:
	static void UpDate();			// キー入力の状態更新
	static int Get(int t_keyCode);	// キー入力状態取得
	static bool CheckEnd();			// 強制終了
};



// マウス入力状態
class MouseData
{
private:
	static int mouse[3];			// マウスの入力状態格納用変数
	static int mouseInput;			// 現在のマウスの入力状態を格納する

public:
	static void UpDate();					//マウスのクリックの状態を更新する
	static int GetClick(int t_mouseCode);	//マウスのクリックの状態を返す
};



// マウスホイール入力状態
class MouseWheelData
{
private:
	static int mouseWheel;			// 現在のホイール位置を格納する変数
	static int oldMouseWheel;		// 直前のホイール位置を格納する変数

public:
	static void Update();							//マウスのホイールの状態を更新
	static int GetMouseWheel(int t_mouseWheelCode);	//マウスホイールの状態を返す
};