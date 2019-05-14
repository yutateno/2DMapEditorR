#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"
#include <fstream>
#include <sstream>



// タイトルでのシーン
enum class STEPNUMBER
{
	backGround, chip, file, fileExc, nextScene
};


/*
タイトル
*/
class Title : public BaseScene
{
private:
	/// タイトルに関する---------------------------------------------------

	// ステップ項数
	STEPNUMBER stepNowNum;


	/// マップエディタに関する---------------------------------------------

	// マップチップ素材
	std::vector<int>* vp_mapChip;

	// 書き込むファイルのパス
	std::string* p_filePath;

	// 仮マップの作成
	void CreateMap(const bool t_fileCSV);

	// 背景画像
	int* p_backGround;


public:
	// コンストラクタ(マップチップ素材と書き込みファイルのパスを受け取る
	Title(std::vector<int>& t_mapChip, std::string& t_filePath, int& t_backGround);

	// デストラクタ
	~Title() {}


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;

	// ドラッグアンドドロップからマップチップ素材の追加
	void AddDragAndDrop(char t_path[]) override;
};

