#include "MapEditor.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::MapChipDraw(const int t_areaX, const int t_areaY, const int t_chipID)
{
	// マップチップ素材にないID番号の時
	if (vp_mapChip->size() > t_chipID)
	{
		DrawGraph(t_areaY * mapChipSizeY, t_areaX * mapChipSizeX, vp_mapChip->at(t_chipID), true);
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


	// セーブ完了を表示させる
	saveEndFlag = true;
	saveEndViewCount = 255;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
MapEditor::MapEditor(std::vector<int>& t_mapChip, std::string& t_filePath, int& t_backGround)
{
	// 強制終了フラッグを下す
	endFlag = false;

	// マップチップ素材を共有する
	vp_mapChip = &t_mapChip;

	// ファイルパスを共有する
	p_filePath = &t_filePath;

	// 背景画像を共有する
	p_backGround = &t_backGround;

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

	// セーブしているフラッグの初期化
	saveEndFlag = false;

	// セーブ完了のカウント初期化
	saveEndViewCount = 0;
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
	// 背景画像を描画する
	if (*p_backGround != -1)
	{
		DrawGraph(0, 0, *p_backGround, false);
	}


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
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 225);
		DrawBox(0, 0, 320, 720, GetColor(125, 125, 125), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		// 一列目について
		{
			const int yFirst = static_cast<int>(EChipSelectAreaY::oneAreaFirst);
			const int yEnd = static_cast<int>(EChipSelectAreaY::oneAreaEnd);


			// 右一列追加
			DrawBox(static_cast<int>(EChipSelectAreaX::mapRightAddFirst), yFirst
				, static_cast<int>(EChipSelectAreaX::mapRightAddEnd), yEnd, GetColor(255, 255, 255), true);
			DrawBox(static_cast<int>(EChipSelectAreaX::mapRightAddEnd) - 10, yFirst
				, static_cast<int>(EChipSelectAreaX::mapRightAddEnd), yEnd, GetColor(0, 255, 0), true);


			// 下一行追加
			DrawBox(static_cast<int>(EChipSelectAreaX::mapUnderAddFirst), yFirst
				, static_cast<int>(EChipSelectAreaX::mapUnderAddEnd), yEnd, GetColor(255, 255, 255), true);
			DrawBox(static_cast<int>(EChipSelectAreaX::mapUnderAddFirst), yFirst - 10
				, static_cast<int>(EChipSelectAreaX::mapUnderAddEnd), yEnd, GetColor(0, 255, 0), true);


			// 右一列削除
			DrawBox(static_cast<int>(EChipSelectAreaX::mapRightDelFirst), yFirst
				, static_cast<int>(EChipSelectAreaX::mapRightDelEnd), yEnd, GetColor(255, 255, 255), true);
			DrawBox(static_cast<int>(EChipSelectAreaX::mapRightDelEnd) - 10, yFirst
				, static_cast<int>(EChipSelectAreaX::mapRightDelEnd), yEnd, GetColor(255, 0, 0), true);


			// 下一行削除
			DrawBox(static_cast<int>(EChipSelectAreaX::mapUnderDelFirst), yFirst
				, static_cast<int>(EChipSelectAreaX::mapUnderDelEnd), yEnd, GetColor(255, 255, 255), true);
			DrawBox(static_cast<int>(EChipSelectAreaX::mapUnderDelFirst), yFirst - 10
				, static_cast<int>(EChipSelectAreaX::mapUnderDelEnd), yEnd, GetColor(255, 0, 0), true);
		}
	}

	
	// 下に説明を表示する
	DrawBox(0, 720, 1280, 760, GetColor(0, 0, 0), true);
	DrawFormatString(0, 730, GetColor(255, 255, 255), "ホイールクリックでセーブ。左または右Ctrlでマップチップ選択画面。現マップサイズ: %d x %d", vv_mapdata[0].size(), vv_mapdata.size());


	// セーブの表示
	if (saveEndFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, saveEndViewCount);
		DrawFormatString(0, 730, GetColor(255, 0, 0), "　　　　　　　　　　　　　　　　　　    　　　　　　　　　　　　　　　　　　　         　セーブしました。");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	// マウスの位置を表示
	DrawFormatString(mouseX, mouseY, GetColor(255, 255, 255), "%dx%d", mouseX, mouseY);
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


	// セーブ官僚の表示をしているとき
	if (saveEndFlag)
	{
		// 透過を濃くしていく
		if ((saveEndViewCount -= 3) <= 0)
		{
			// セーブ完了の表示を消す
			saveEndFlag = false;
		}
	}


	// 左または右コントロールが押されたら
	if (KeyData::Get(KEY_INPUT_LCONTROL) == 1 || KeyData::Get(KEY_INPUT_RCONTROL) == 1)
	{
		// マップチップ選択画面のフラッグを直前の逆にする
		selectMapChipWindow = !selectMapChipWindow;
	}


	// マップチップ選択画面が表示されていたら
	if (selectMapChipWindow)
	{
		// 左クリックされたら
		if (MouseData::GetClick(0) == 1)
		{
			// 一行目の時
			if (mouseY > static_cast<int>(EChipSelectAreaY::oneAreaFirst) && mouseY < static_cast<int>(EChipSelectAreaY::oneAreaEnd))
			{
				// 「右一列を追加する」を選択
				if (mouseX > static_cast<int>(EChipSelectAreaX::mapRightAddFirst) && mouseX < static_cast<int>(EChipSelectAreaX::mapRightAddEnd))
				{
					std::string str = chipDoubleDigitID ? "00" : "0";
					for (size_t i = 0, n = vv_mapdata.size(); i != n; ++i) 
					{
						vv_mapdata[i].push_back(str);
					}
				}
				

				// 「下一行を追加する」を選択
				if (mouseX > static_cast<int>(EChipSelectAreaX::mapUnderAddFirst) && mouseX < static_cast<int>(EChipSelectAreaX::mapUnderAddEnd))
				{
					vv_mapdata.push_back(vv_mapdata.back());
				}


				// 「右一列を削除する」を選択
				if (mouseX > static_cast<int>(EChipSelectAreaX::mapRightDelFirst) && mouseX < static_cast<int>(EChipSelectAreaX::mapRightDelEnd))
				{
					if (vv_mapdata[0].size() >= 2)
					{
						for (size_t i = 0, n = vv_mapdata.size(); i != n; ++i)
						{
							vv_mapdata[i].pop_back();
						}
					}
				}


				// 「下一行を削除する」を選択
				if (mouseX > static_cast<int>(EChipSelectAreaX::mapUnderDelFirst) && mouseX < static_cast<int>(EChipSelectAreaX::mapUnderDelEnd))
				{
					if (vv_mapdata.size() >= 2)
					{
						vv_mapdata.pop_back();
					}
				}
			}
		}
	}
	// マップチップ選択画面が表示されていなかったら
	else
	{

	}
}
