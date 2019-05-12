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

			for (int i = 0, n = static_cast<int>(readLine.length()); i < n; ++i)
			{
				vv_mapdata[readCount].push_back(readLine.substr(i, 1));
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
	if (vp_mapChip->size() != 0)
	{
		for (int i = 0, n = static_cast<int>(vp_mapChip->size()); i != n; ++i)
		{
			DrawGraph(i * 15, 0, vp_mapChip->at(i), true);
		}
	}

	for (int i = 0, n = static_cast<int>(vv_mapdata.size()); i != n; ++i)
	{
		for (int j = 0, m = static_cast<int>(vv_mapdata[i].size()); j != m; ++j)
		{
			DrawFormatString(j * 5, 240 + i * 5, GetColor(255, 255, 255), "%d", stoi(vv_mapdata[i][j]));
		}
	}

	DrawFormatString(0, 120, GetColor(255, 255, 255), "%s", p_filePath->c_str());
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::Process()
{
	GetMousePoint(&mouseX, &mouseY);


	if (MouseData::GetClick(0) == 1)
	{
		SaveMap();
	}


	if (KeyData::Get(KEY_INPUT_1) == 1) BASICPARAM::e_nowScene = ESceneNumber::TITLE;
}
