//#pragma once
//
///*
//大本
//*/
//
///// インクルードファイル--------------------------------------------------------
//#include "DxLib.h"
//#include <vector>
//
//
///// 色んな所で使いそうなもの----------------------------------------------------
//
//// シーンの動き
//enum class ESceneNumber
//{
//	TITLE, MAPEDITOR
//};
//
//
//namespace BASICPARAM
//{
//	// 直前のシーン
//	extern ESceneNumber e_preScene;
//
//	// 今のシーン
//	extern ESceneNumber e_nowScene;
//
//	// 画像IDの番号
//}
//
//
///// マクロ-------------------------------------------------------------------------------------
//
//// ポインタ用解放マクロ
//template<typename T>
//constexpr void POINTER_RELEASE(T p) { if(p!=nullptr) {delete p; (p)=nullptr; } }
//
//// 2D関連画像解放マクロ
//template<typename T>
//constexpr void  GRAPHIC_RELEASE(T p) { if(p!=-1) { DeleteGraph(p); (p)=-1; } }
//
