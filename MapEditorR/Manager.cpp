#include "Manager.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Manager::SceneChange()
{
	// 今のシーン
	switch (BASICPARAM::e_nowScene)
	{
		// タイトル
	case ESceneNumber::TITLE:
		POINTER_RELEASE(p_baseMove);
		p_baseMove = new Title(v_mapChip, filePath);
		break;


		// マップエディター
	case ESceneNumber::MAPEDITOR:
		POINTER_RELEASE(p_baseMove);
		p_baseMove = new MapEditor(v_mapChip, filePath);


	default:
		break;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Manager::Manager()
{
	// 初期化
	BASICPARAM::e_preScene = ESceneNumber::TITLE;
	BASICPARAM::e_nowScene = ESceneNumber::TITLE;


	// 画像ファイル
	v_mapChip.clear();

	
	// 書き込むファイル
	filePath = "";


	// メモリの初期化
	p_baseMove = nullptr;
	p_baseMove = new Title(v_mapChip, filePath);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Manager::~Manager()
{
	POINTER_RELEASE(p_baseMove);


	if (v_mapChip.size() != 0)
	{
		for (size_t i = 0, n = v_mapChip.size(); i != n; ++i)
		{
			GRAPHIC_RELEASE(v_mapChip[i]);
		}
		v_mapChip.shrink_to_fit();
		v_mapChip.clear();
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Manager::Update()
{
	// 今のシーンと直前のシーンが同じ
	if (BASICPARAM::e_nowScene == BASICPARAM::e_preScene)
	{
		// ゲームに関する
		p_baseMove->Draw();


		// ゲームに関する
		p_baseMove->Process();
	}
	// シーンを移行するように指定されたら
	else
	{
		// シーンを変える
		SceneChange();


		// 直前のシーンと今のシーンを同じにする
		BASICPARAM::e_preScene = BASICPARAM::e_nowScene;
	}
}
