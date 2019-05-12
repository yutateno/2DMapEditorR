#pragma once
#include <vector>
#include <string>



// シーンの動き
enum class ESceneNumber
{
	TITLE, MAPEDITOR
};



// 全体で必要な変数
namespace BASICPARAM
{
	// 直前のシーン
	extern ESceneNumber e_preScene;

	// 現在のシーン
	extern ESceneNumber e_nowScene;
}


/*
ムーブの大本
*/
class BaseScene
{
protected:
	// 強制終了フラッグ
	bool endFlag;


public:
	// 描画
	virtual void Draw() = 0;

	// プロセス
	virtual void Process() = 0;


	// マップチップの追加
	virtual void AddDragAndDrop(char t_path[]) = 0;


	// 強制的に終了させる
	bool GetEnd() { return endFlag; }
};

