#pragma once



/*
大本
*/


/// マクロ-------------------------------------------------------------------------------------

// ポインタ用解放マクロ
#define POINTER_RELEASE(p)	\
{	\
	if (p != nullptr)	\
	{	\
		delete p;	\
		p = nullptr;	\
	}	\
}	\

// 2D関連画像解放マクロ
#define GRAPHIC_RELEASE(p)	\
{	\
	if (p != -1)	\
	{	\
		DeleteGraph(p);	\
		p = -1;	\
	}	\
}	\

