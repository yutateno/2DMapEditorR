#include "Input.hpp"

//////////////////////////////////////////////キーボード////////////////////////////////////////////////////
KeyData::KeyData()
{

}

KeyData::~KeyData()
{

}

int KeyData::key[256];
char KeyData::tmpKey[256];

void KeyData::UpDate()
{
	KeyData::tmpKey[256];			// 現在のキーの入力状態を格納する
	GetHitKeyStateAll(KeyData::tmpKey);	// 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++)
	{
		// i番のキーコードに対応するキーが押されていたら
		if (KeyData::tmpKey[i] != 0)
		{
			KeyData::key[i]++;   // 加算
		}
		// キーが離された瞬間
		else if (KeyData::key[i] > 0)
		{
			KeyData::key[i] = -1; // -1にする
		}
		// それ以外
		else
		{
			KeyData::key[i] = 0; // 0にする
		}
	}
}

bool KeyData::CheckEnd()
{
	return KeyData::key[KEY_INPUT_ESCAPE] <= 0;
}

int KeyData::Get(int KeyCode)
{
	return KeyData::key[KeyCode];
}


//////////////////////////////////////////////マウス関連////////////////////////////////////////////////////

MouseData::MouseData()
{

}

MouseData::~MouseData()
{

}

int MouseData::m_Mouse[3];
int MouseData::MouseInput;

void MouseData::Mouse_UpDate() {
	MouseInput = GetMouseInput();    //マウスの押した状態取得
	for (int i = 0; i < 3; i++) {
		if ((MouseInput & 1 << i) != 0) {
			m_Mouse[i]++;   //押されていたらカウントアップ
		}
		else {
			m_Mouse[i] = 0; //押されてなかったら0
		}
	}
}

int MouseData::GetClick(int MouseCode) {
	return m_Mouse[MouseCode];
}

//////////////////////////////////////////////マウスホイール関連////////////////////////////////////////////////////
MouseWheelData::MouseWheelData()
{

}

MouseWheelData::~MouseWheelData()
{

}

int MouseWheelData::m_MouseWheel;
int MouseWheelData::old_MouseWheel;

void MouseWheelData::MouseWheel_Update() {
	old_MouseWheel = m_MouseWheel;
	if (old_MouseWheel - m_MouseWheel > 0) {
		m_MouseWheel++;
	}
	else if (old_MouseWheel - m_MouseWheel < 0) {
		m_MouseWheel--;
	}
	else {
		m_MouseWheel = 0;
	}
}

int MouseWheelData::GetMouseWheel(int MouseWheelCode) {
	return m_MouseWheel += MouseWheelCode;
}