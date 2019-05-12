//#include "Manager.hpp"
//
//
//
///// --------------------------------------------------------------------------------------------------
//void Manager::SceneChange()
//{
//	// 今のシーン
//	switch (BASICPARAM::e_nowScene)
//	{
//		// タイトル
//	case ESceneNumber::TITLE:
//		POINTER_RELEASE(p_baseMove);
//		for (int i = 0; i != std::extent<decltype(tempMap), 0>::value; ++i)
//		{
//			tempMap[i] = map[i];
//		}
//		p_baseMove = new Title(tempMap);
//		p_baseMove->SetScene(BASICPARAM::e_nowScene);
//		break;
//
//
//		// ゲーム
//	case ESceneNumber::GAME:
//		POINTER_RELEASE(p_baseMove);
//		for (int i = 0; i != std::extent<decltype(tempMap), 0>::value; ++i)
//		{
//			tempMap[i] = map[i];
//		}
//		p_baseMove = new Game(tempMap);
//		p_baseMove->SetScene(BASICPARAM::e_nowScene);
//		break;
//
//
//		// エンディング
//	case ESceneNumber::END:
//		POINTER_RELEASE(p_baseMove);
//		for (int i = 0; i != std::extent<decltype(map), 0>::value; ++i)
//		{
//			for (int j = 0; j != std::extent<decltype(map), 1>::value; ++j)
//			{
//				map[i][j] = -1;
//			}
//		}
//		p_baseMove = new End();
//		p_baseMove->SetScene(BASICPARAM::e_nowScene);
//
//
//	default:
//		break;
//	}
//}
//
//
//
///// --------------------------------------------------------------------------------------------------
//Manager::Manager()
//{
//	// 初期化
//	BASICPARAM::e_preScene = ESceneNumber::TITLE;
//	BASICPARAM::e_nowScene = ESceneNumber::TITLE;
//
//
//	// マップ初期化
//	for (int i = 0; i != std::extent<decltype(map), 0>::value; ++i)
//	{
//		for (int j = 0; j != std::extent<decltype(map), 1>::value; ++j)
//		{
//			map[i][j] = -1;
//		}
//	}
//	map[0][0] = static_cast<int>(MAPStep::Start);
//	map[std::extent<decltype(map), 0>::value - 1][std::extent<decltype(map), 1>::value - 1] = static_cast<int>(MAPStep::Goal);
//	for (int i = 0; i != std::extent<decltype(tempMap), 0>::value; ++i)
//	{
//		tempMap[i] = map[i];
//	}
//
//
//	// メモリの初期化
//	p_baseMove = nullptr;
//	p_baseMove = new Title(tempMap);
//
//
//	// ゲームに関する
//	gameEnd = false;
//}
//
//
//
///// --------------------------------------------------------------------------------------------------
//Manager::~Manager()
//{
//	POINTER_RELEASE(p_baseMove);
//}
//
//
//
///// --------------------------------------------------------------------------------------------------
//void Manager::Update()
//{
//	// 今のシーンと直前のシーンが同じ
//	if (BASICPARAM::e_nowScene == BASICPARAM::e_preScene)
//	{
//		// ゲームに関する
//		p_baseMove->Draw();
//
//
//		// ゲームに関する
//		p_baseMove->Process();
//
//
//		// 直前のシーンと今のシーンを同じにする
//		BASICPARAM::e_nowScene = p_baseMove->GetScene();
//	}
//	// シーンを移行するように指定されたら
//	else
//	{
//		// シーンを変える
//		SceneChange();
//
//
//		// 直前のシーンと今のシーンを同じにする
//		BASICPARAM::e_preScene = BASICPARAM::e_nowScene;
//	}
//}