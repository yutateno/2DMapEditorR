#include "MapEditor.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::MapChipDraw(const int t_areaX, const int t_areaY, const int t_chipID)
{
	// マップチップ素材にないID番号の時
	if (vp_mapChip->size() <= t_chipID)
	{
		DrawBox(t_areaY * mapChipSizeY, t_areaX * mapChipSizeX, (t_areaY + 1) * mapChipSizeY, (t_areaX + 1) * mapChipSizeX, GetColor(50, 50, 50), true);
	}
	// マップチップ素材のIDがあるとき
	else
	{
		DrawGraph(t_areaY * mapChipSizeY, t_areaX * mapChipSizeX, vp_mapChip->at(t_chipID), false);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::LoadMap()
{
	// 行確認用変数
	int readCount = 0;

	// ファイルを読み込む
	std::ifstream readFile(p_filePath->c_str());

	// 行を取得する
	std::string readLine = "";

	// CSVファイルかどうか確認する
	readFileCSV = (p_filePath->find(".csv") != -1);


	// ファイル読み込み失敗
	if ((p_filePath->find(".csv") == -1) && (p_filePath->find(".txt") == -1))
	{
		// 強制終了させる
		endFlag = true;
		return;
	}


	// CSVファイルだった時
	if (readFileCSV)
	{
		// 行ずつ確認
		while (getline(readFile, readLine))
		{
			std::string token;
			std::istringstream stream(readLine);

			// マップデータ多めに作成
			int tempReadCount = readCount + 1;
			vv_mapdata.resize(tempReadCount);

			// [,]まで確認
			while (std::getline(stream, token, ','))
			{
				// マップデータに追加
				vv_mapdata[readCount].push_back(token);
			}

			// 行を加算
			readCount++;
		}
	}
	// TXTファイルだった時
	else
	{
		// 行確認
		while (std::getline(readFile, readLine))
		{
			// マップデータ多めに作成
			int tempReadCount = readCount + 1;
			vv_mapdata.resize(tempReadCount);

			// 1字または2次ずつ確認
			for (int i = 0, n = static_cast<int>(readLine.length()); i < n; chipDoubleDigitID ? i += 2 : ++i)
			{
				// マップデータに追加
				vv_mapdata[readCount].push_back(readLine.substr(i, chipDoubleDigitID ? 2 : 1));
			}

			// 行を加算
			readCount++;
		}
	}


	// ファイルを閉じる
	readFile.close();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::SaveMap()
{
	// ファイルを読み込む
	std::ofstream saveFile(p_filePath->c_str());


	// ファイル読み込み失敗
	if (saveFile.fail())
	{
		// 強制終了させる
		endFlag = true;
		return;
	}

	
	// CSVファイルだった時
	if (readFileCSV)
	{
		for (int i = 0, n = static_cast<int>(vv_mapdata.size()); i != n; ++i)
		{
			for (int j = 0, m = static_cast<int>(vv_mapdata[i].size()); j != m; ++j)
			{
				saveFile << vv_mapdata[i][j];
				if (m != j + 1)
				{
					saveFile << ",";
				}
			}
			saveFile << std::endl;
		}
	}
	// TXTファイルだった時
	else
	{
		for (int i = 0, n = static_cast<int>(vv_mapdata.size()); i != n; ++i)
		{
			for (int j = 0, m = static_cast<int>(vv_mapdata[i].size()); j != m; ++j)
			{
				saveFile << vv_mapdata[i][j];
			}
			saveFile << std::endl;
		}
	}


	// ファイルを閉じる
	saveFile.close();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
MapEditor::MapEditor(std::vector<int>& t_mapChip, std::string& t_filePath)
{
	// 強制終了フラッグを下す
	endFlag = false;

	// マップチップ素材を共有する
	vp_mapChip = &t_mapChip;

	// ファイルパスを共有する
	p_filePath = &t_filePath;

	// マウス座標を初期化
	mouseX = 0;
	mouseY = 0;

	// マップチップIDが二桁かどうかで初期化する
	chipDoubleDigitID = (vp_mapChip->size() >= 11);

	// 読み込みファイルの拡張子をTXTデータと仮定して初期化する
	readFileCSV = false;

	// マップデータを初期化する
	vv_mapdata.clear();

	// マップファイルを読み込んでマップデータに書き込む
	LoadMap();

	// マップチップ選択画面フラッグの初期化
	selectMapChipWindow = false;

	// マップチップ素材の0番目のサイズを取得してマップチップ全部のサイズと仮定する
	GetGraphSize(vp_mapChip->at(0), &mapChipSizeX, &mapChipSizeY);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
MapEditor::~MapEditor()
{
	// マップデータを削除する
	vv_mapdata.shrink_to_fit();
	vv_mapdata.clear();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::Draw()
{
	// マップデータからマップチップを配置したものを描画する
	for (int i = 0, n = static_cast<int>(vv_mapdata.size()); i != n; ++i)
	{
		for (int j = 0, m = static_cast<int>(vv_mapdata[i].size()); j != m; ++j)
		{
			MapChipDraw(i, j, stoi(vv_mapdata[i][j]));
		}
	}


	// マップチップ選択画面の描画をするとき
	if (selectMapChipWindow)
	{
		// 半透明としてマップチップ選択画面を描画する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 190);
		DrawBox(0, 0, 640, 480, GetColor(125, 125, 125), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	
	// 下に説明を表示する
	DrawBox(0, 480, 640, 520, GetColor(0, 0, 0), true);
	DrawFormatString(0, 500, GetColor(255, 255, 255), "ホイールクリックでセーブ。左または右Ctrlでマップチップ選択画面");
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::Process()
{
	// マウスの位置を取得する
	GetMousePoint(&mouseX, &mouseY);


	// マウスホイールがクリックされたら
	if (MouseData::GetClick(2) == 1)
	{
		// マップデータからファイルに書き込む
		SaveMap();
	}


	// 左または右コントロールが押されたら
	if (KeyData::Get(KEY_INPUT_LCONTROL) == 1 || KeyData::Get(KEY_INPUT_RCONTROL) == 1)
	{
		// マップチップ選択画面のフラッグを直前の逆にする
		selectMapChipWindow = !selectMapChipWindow;
	}
}
