#pragma once



// シーンの動き
enum class ESceneNumber
{
	TITLE, MAPEDITOR
};


namespace BASICPARAM
{
	// 直前のシーン
	extern ESceneNumber e_preScene;

	// 今のシーン
	extern ESceneNumber e_nowScene;
}


/*
ムーブの大本
*/
class BaseScene
{
public:
	// 描画
	virtual void Draw() = 0;

	// プロセス
	virtual void Process() = 0;
};

