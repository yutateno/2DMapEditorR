#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"
#include <fstream>
#include <sstream>



// シーン
enum class STEPNUMBER
{
	chip, file, fileExc, nextScene
};


/*
タイトル
*/
class Title : public BaseScene
{
private:
	// マップチップ素材
	std::vector<int>* vp_mapChip;

	// ステップ項数
	STEPNUMBER stepNowNum;

	// 書き込むファイルのパス
	std::string* p_filePath;

	// 適当なファイルを作成したときの仮マップ
	void CreateMap(const bool t_fileCSV);


public:
	Title(std::vector<int>& t_mapChip, std::string& t_filePath);
	~Title();


	void Draw() override;
	void Process() override;

	void AddDragAndDrop(char t_path[]) override;
};

