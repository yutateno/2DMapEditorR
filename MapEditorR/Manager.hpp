#pragma once
#include "BaseScene.hpp"

#include "Title.hpp"
#include "MapEditor.hpp"



/*
ゲームの大本
*/
class Manager
{
private:
	/// 各シーンに関する-----------------------------------------------------

	// シーンの基底クラス
	BaseScene* p_baseMove;

	// シーンを切り替える
	void SceneChange();


public:
	// コンストラクタ
	Manager();

	// デストラクタ
	~Manager();


	// メインプロセス
	void Update();
};
