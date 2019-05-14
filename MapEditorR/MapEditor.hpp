#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"
#include <fstream>
#include <sstream>




enum class EChipSelectAreaX : unsigned int
{
	oneFirst = 20, oneEnd = 60, secondFirst = 80, secondEnd = 120, thirdFirst = 140, thirdEnd = 180
	, fourthFirst = 200, fourthEnd = 240, fifthFirst = 260, fifthEnd = 300
};


enum class EChipSelectAreaY : unsigned int
{
	oneFirst = 20, oneEnd = 60 , secondFirst = 80 , secondEnd = 120, thirdFirst = 140, thirdEnd = 180
	, fourthFirst = 200, fourthEnd = 240, fifthFirst = 260, fifthEnd = 300, sixthFirst = 320, sixthEnd = 360
	, seventhFirst = 380, seventhEnd = 420, eighthFirst = 440, eighthEnd = 480, ninthFirst = 500, ninthEnd = 540
	, tenthFirst = 560, tenthEnd = 600
};


/*
マップエディター
*/
class MapEditor : public BaseScene
{
private:
	/// マップチップ素材に関する----------------------------------

	// マップチップ素材
	std::vector<int>* vp_mapChip;

	// マップチップ選択画面の表示
	bool selectMapChipWindow;

	// マップチップのサイズを調べる
	int mapChipSizeX, mapChipSizeY;

	// マップチップの一つを描画する
	void MapChipDraw(const int t_areaX, const int t_areaY, const int t_chipID);

	// 背景画像
	int* p_backGround;


	/// ファイルに関する------------------------------------------

	// 書き込むファイルパス
	std::string* p_filePath;

	// マップチップIDは二桁かどうか
	bool chipDoubleDigitID;

	// .csvかどうか
	bool readFileCSV;

	// 読み込んだファイルからID取得
	std::vector<std::vector<std::string>> vv_mapdata;

	// ファイル読み込む
	void LoadMap();

	// ファイル書き込む
	void SaveMap();

	// セーブをしたかどうか
	bool saveEndFlag;

	// セーブ完了の表示カウント
	int saveEndViewCount;


	/// マウスに関する-------------------------------------------

	// マウスの位置
	int mouseX, mouseY;

	// マップチップ上の位置
	int chipSelectAreaX, chipSelectAreaY;

	// 選択しているマップチップID
	int mouseSelectChipID;

	// 指定のマップチップIDを削除
	void DeleteChip();

	// 指定のマップチップIDを設定
	void SettingChip();


	/// 内部関数に関する----------------------------------------
	
	// マップチップの選択画面描画
	void MapChipSelectDraw();

	// マップチップの選択画面プロセス
	void MapChipSelectProcess();


public:
	// コンストラクタ(マップチップ素材とファイルパスを受けとる
	MapEditor(std::vector<int>& t_mapChip, std::string& t_filePath, int& t_backGround);

	// デストラクタ
	~MapEditor();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;

	// ドラッグアンドドロップによる追加
	void AddDragAndDrop(char t_path[]) override {}
};

