#include "Input.hpp"



//////////////////////////////////////////////キーボード////////////////////////////////////////////////////

int KeyData::key[256];
char KeyData::tmpKey[256];


/// ------------------------------------------------------------------------------------------------------------
void KeyData::UpDate()
{
	GetHitKeyStateAll(KeyData::tmpKey);	// 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		// i番のキーコードに対応するキーが押されていたら
		if (KeyData::tmpKey[i] != 0)
		{
			KeyData::key[i]++;
		}
		// キーが離された瞬間
		else if (KeyData::key[i] > 0)
		{
			KeyData::key[i] = -1;
		}
		// アクションがない
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



//////////////////////////////////////////////マウス関連////////////////////////////////////////////////////

int MouseData::mouse[3];
int MouseData::mouseInput;



/// ------------------------------------------------------------------------------------------------------------
void MouseData::UpDate()
{
	mouseInput = GetMouseInput();		//マウスの押した状態取得

	for (int i = 0; i < 3; i++)
	{
		//押されていたら
		if ((mouseInput & 1 << i) != 0)
		{
			mouse[i]++;
		}
		//押されてなかったら
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



//////////////////////////////////////////////マウスホイール関連////////////////////////////////////////////////////

int MouseWheelData::mouseWheel;
int MouseWheelData::oldMouseWheel;



/// ------------------------------------------------------------------------------------------------------------
void MouseWheelData::Update()
{
	oldMouseWheel = mouseWheel;

	// 上にホイールが動いたら
	if (oldMouseWheel - mouseWheel > 0)
	{
		mouseWheel++;
	}
	// 下にホイールが動いたら
	else if (oldMouseWheel - mouseWheel < 0)
	{
		mouseWheel--;
	}
	// 何もしていないとき
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