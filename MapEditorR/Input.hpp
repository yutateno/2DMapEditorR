#pragma once
#include "DxLib.h"

// キーボードの入力状態
class KeyData
{
private:
	static int key[256];	// キーの入力状態格納用変数
	static char tmpKey[256];	// 現在のキーの入力状態を格納する

public:
	KeyData();
	~KeyData();

	static void UpDate();	// キー入力の状態更新
	static int Get(int KeyCode);	// キー入力状態取得
	static bool CheckEnd();	// 強制終了
};


class MouseData
{
private:
	static int m_Mouse[3];
	static int MouseInput;

public:
	MouseData();
	~MouseData();

	static void Mouse_UpDate(); //マウスのクリックの状態を更新する
	static int GetClick(int MouseCode); //マウスのクリックの状態を返す
};


class MouseWheelData
{
private:
	static int m_MouseWheel;
	static int old_MouseWheel;

public:
	MouseWheelData();
	~MouseWheelData();

	static void MouseWheel_Update(); //マウスのホイールの状態を更新
	static int GetMouseWheel(int MouseWheelCode); //マウスホイールの状態を返す
};