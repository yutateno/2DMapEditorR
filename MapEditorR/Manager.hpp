#pragma once
#include "BaseScene.hpp"
#include <vector>

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


	// マップチップ素材
	std::vector<int> v_mapChip;


public:
	// コンストラクタ
	Manager();

	// デストラクタ
	~Manager();


	// メインプロセス
	void Update();


	// 素材受け取り
	void GetAddMapChipPath(char t_path[])
	{
		p_baseMove->AddMapChip(t_path);
	}
};
