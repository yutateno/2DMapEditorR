#include "Title.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::CreateMap(const bool t_fileCSV)
{
	std::ofstream saveFile(p_filePath->c_str());

	if (t_fileCSV)
	{
		for (int i = 0; i != 2; ++i)
		{
			saveFile << "1,1,1,1" << std::endl;
		}
	}
	else
	{
		for (int i = 0; i != 2; ++i)
		{
			saveFile << "1111" << std::endl;
		}
	}

	// ファイルを閉じる
	saveFile.close();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Title::Title(std::vector<int>& t_mapChip, std::string& t_filePath)
{
	endFlag = false;

	vp_mapChip = &t_mapChip;

	stepNowNum = STEPNUMBER::chip;

	p_filePath = &t_filePath;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Title::~Title()
{

}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::Draw()
{
	switch (stepNowNum)
	{
	case STEPNUMBER::chip:
		if (vp_mapChip->size() != 0)
		{
			for (int i = 0, n = static_cast<int>(vp_mapChip->size()); i != n; ++i)
			{
				DrawGraph(i * 15, 0, vp_mapChip->at(i), true);
			}

			DrawFormatString(0, 240, GetColor(255, 255, 255), "全部の素材を入れたら画面内でホイールクリックしてください。\nやり直す場合は右クリック");
			DrawFormatString(0, 240, GetColor(0, 0, 255), "　　　　　　　　　　　　　　ホイールクリック");
			DrawFormatString(0, 240, GetColor(0, 255, 0), "\n　　　　　　　右クリック");
		}
		else
		{
			DrawFormatString(0, 0, GetColor(255, 255, 255), "マップチップとして扱いたい画像をID順にドラッグアンドドロップしてください。");
		}
		break;


	case STEPNUMBER::file:
		for (int i = 0, n = static_cast<int>(vp_mapChip->size()); i != n; ++i)
		{
			DrawGraph(i * 15, 0, vp_mapChip->at(i), true);
		}
		DrawFormatString(0, 240, GetColor(255, 255, 255), "読み込むファイルがある場合はそれをドラッグアンドドロップしてください。\n無い場合はそのままホイールクリックしてください。");
		DrawFormatString(0, 240, GetColor(0, 255, 0), "\n　　　　　　　　　ホイールクリック");
		break;


	case STEPNUMBER::fileExc:
		for (int i = 0, n = static_cast<int>(vp_mapChip->size()); i != n; ++i)
		{
			DrawGraph(i * 15, 0, vp_mapChip->at(i), true);
		}
		DrawFormatString(0, 240, GetColor(255, 255, 255), "書き込むファイルの形式が.csvならホイールクリックしてください。\n.txtなら右クリック");
		DrawFormatString(0, 240, GetColor(0, 255, 0), "　　　　　　　　　　　　　　    ホイールクリック");
		DrawFormatString(0, 240, GetColor(0, 0, 255), "\n　　    右クリック");
		break;


	case STEPNUMBER::nextScene:
		for (int i = 0, n = static_cast<int>(vp_mapChip->size()); i != n; ++i)
		{
			DrawGraph(i * 15, 0, vp_mapChip->at(i), true);
		}
		DrawFormatString(0, 120, GetColor(255, 255, 255), "%s", p_filePath->c_str());
		DrawFormatString(0, 240, GetColor(255, 255, 255), "マップエディタ画面に進む場合はホイールクリックしてください。\n最初からやり直す場合は起動しなおす。\nファイルからやり直す場合は右クリック。");
		DrawFormatString(0, 240, GetColor(0, 255, 0), "　　　　　　　　　　　　　　　ホイールクリック");
		DrawFormatString(0, 240, GetColor(0, 0, 255), "\n\n　　　　　　　　　　　　　右クリック。");
		break;


	default:
		break;
	}
}


/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::Process()
{
	switch (stepNowNum)
	{
	case STEPNUMBER::chip:
		if (MouseData::GetClick(2) == 1)
		{
			stepNowNum = STEPNUMBER::file;
		}
		if (MouseData::GetClick(1) == 1)
		{
			if (vp_mapChip->size() != 0)
			{
				for (size_t i = 0, n = vp_mapChip->size(); i != n; ++i)
				{
					GRAPHIC_RELEASE(vp_mapChip->at(i));
				}
				vp_mapChip->shrink_to_fit();
				vp_mapChip->clear();
			}
		}
		break;


	case STEPNUMBER::file:
		if (p_filePath->empty())
		{
			if (MouseData::GetClick(2) == 1)
			{
				stepNowNum = STEPNUMBER::fileExc;
			}
		}
		else
		{
			stepNowNum = STEPNUMBER::nextScene;
		}
		break;


	case STEPNUMBER::fileExc:
		if (MouseData::GetClick(2) == 1)
		{
			*p_filePath = "Map\\Save.csv";
			CreateMap(true);
			stepNowNum = STEPNUMBER::nextScene;
		}
		if (MouseData::GetClick(1) == 1)
		{
			*p_filePath = "Map\\Save.txt";
			CreateMap(false);
			stepNowNum = STEPNUMBER::nextScene;
		}
		break;


	case STEPNUMBER::nextScene:
		if (MouseData::GetClick(2) == 1)
		{
			BASICPARAM::e_nowScene = ESceneNumber::MAPEDITOR;
		}
		if (MouseData::GetClick(1) == 1)
		{
			*p_filePath = "";
			stepNowNum = STEPNUMBER::file;
		}
		break;


	default:
		break;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::AddDragAndDrop(char t_path[])
{
	switch (stepNowNum)
	{
	case STEPNUMBER::chip:
		vp_mapChip->push_back(LoadGraph(t_path));
		break;

		
	case STEPNUMBER::file:
		*p_filePath = t_path;
		break;


	default:
		break;
	}
}
