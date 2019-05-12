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


	// マップチップ素材
	std::vector<int> v_mapChip;

	// 書き込むファイル
	std::string filePath;


public:
	// コンストラクタ
	Manager();

	// デストラクタ
	~Manager();


	// メインプロセス
	void Update();


	// 素材受け取り
	void GetAddDragAndDrop(char t_path[])
	{
		p_baseMove->AddDragAndDrop(t_path);
	}
};
