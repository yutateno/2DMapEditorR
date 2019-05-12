#include "MapEditor.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::LoadMap()
{
	int readCount = 0;

	std::ifstream readFile(p_filePath->c_str());

	std::string readLine = "";

	readFileCSV = (p_filePath->find(".csv") != -1);

	// ファイル読み込み失敗
	if ((p_filePath->find(".csv") == -1) && (p_filePath->find(".txt") == -1))
	{
		endFlag = true;
		return;
	}

	if (readFileCSV)
	{
		while (getline(readFile, readLine))
		{
			std::string token;
			std::istringstream stream(readLine);
			int tempReadCount = readCount + 1;
			vv_mapdata.resize(tempReadCount);

			while (std::getline(stream, token, ','))
			{
				vv_mapdata[readCount].push_back(token);
			}
			readCount++;
		}
	}
	else
	{
		while (std::getline(readFile, readLine))
		{
			int tempReadCount = readCount + 1;
			vv_mapdata.resize(tempReadCount);

			for (int i = 0, n = static_cast<int>(readLine.length()); i < n; chipDoubleDigitID ? i += 2 : ++i)
			{
				vv_mapdata[readCount].push_back(readLine.substr(i, chipDoubleDigitID ? 2 : 1));
			}

			readCount++;
		}
	}


	// ファイルを閉じる
	readFile.close();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::SaveMap()
{
	std::ofstream saveFile(p_filePath->c_str());

	// ファイル読み込み失敗
	if (saveFile.fail())
	{
		endFlag = true;
		return;
	}

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
void MapEditor::MapChipDraw(const int t_areaX, const int t_areaY, const int t_chipID)
{
	if (vp_mapChip->size() <= t_chipID)
	{
		DrawBox(t_areaY * mapChipSizeY, t_areaX * mapChipSizeX, (t_areaY + 1) * mapChipSizeY, (t_areaX + 1) * mapChipSizeX, GetColor(50, 50, 50), true);
	}
	else
	{
		DrawGraph(t_areaY * mapChipSizeY, t_areaX * mapChipSizeX, vp_mapChip->at(t_chipID), false);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
MapEditor::MapEditor(std::vector<int>& t_mapChip, std::string& t_filePath)
{
	endFlag = false;

	vp_mapChip = &t_mapChip;

	p_filePath = &t_filePath;

	mouseX = 0;
	mouseY = 0;

	chipDoubleDigitID = (vp_mapChip->size() >= 11);

	readFileCSV = false;

	vv_mapdata.clear();

	LoadMap();

	selectMapChipWindow = false;

	GetGraphSize(vp_mapChip->at(0), &mapChipSizeX, &mapChipSizeY);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
MapEditor::~MapEditor()
{
	vv_mapdata.shrink_to_fit();
	vv_mapdata.clear();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::Draw()
{
	for (int i = 0, n = static_cast<int>(vv_mapdata.size()); i != n; ++i)
	{
		for (int j = 0, m = static_cast<int>(vv_mapdata[i].size()); j != m; ++j)
		{
			MapChipDraw(i, j, stoi(vv_mapdata[i][j]));
		}
	}

	if (selectMapChipWindow)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 190);
		DrawBox(0, 0, 640, 480, GetColor(125, 125, 125), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	
	DrawBox(0, 480, 640, 520, GetColor(0, 0, 0), true);
	DrawFormatString(0, 500, GetColor(255, 255, 255), "ホイールクリックでセーブ。左または右Ctrlでマップチップ選択画面");
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::Process()
{
	GetMousePoint(&mouseX, &mouseY);


	if (MouseData::GetClick(2) == 1)
	{
		SaveMap();
	}


	if (KeyData::Get(KEY_INPUT_LCONTROL) == 1 || KeyData::Get(KEY_INPUT_RCONTROL) == 1)
	{
		selectMapChipWindow = !selectMapChipWindow;
	}
}
