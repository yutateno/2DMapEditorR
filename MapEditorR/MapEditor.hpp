#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"
#include <fstream>
#include <sstream>



/*
マップエディター
*/
class MapEditor : public BaseScene
{
private:
	// マップチップ素材
	std::vector<int> *vp_mapChip;

	// 書き込むファイルパス
	std::string* p_filePath;

	// IDは二桁かどうか
	bool chipDoubleDigitID;

	// .csvかどうか
	bool readFileCSV;

	// 読み込んだファイルからID取得
	std::vector<std::vector<std::string>> vv_mapdata;

	// ファイル読み込む
	void LoadMap();

	// ファイル書き込む
	void SaveMap();

	// マウスの位置
	int mouseX, mouseY;


public:
	MapEditor(std::vector<int>& t_mapChip, std::string& t_filePath);
	~MapEditor();


	void Draw() override;
	void Process() override;
	void AddDragAndDrop(char t_path[]) override {}
};

