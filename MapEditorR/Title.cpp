#include "Title.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::CreateMap(const bool t_fileCSV)
{
	// ファイルを生成及び開く
	std::ofstream saveFile(p_filePath->c_str());

	// CSVファイルを選択されていたら
	if (t_fileCSV)
	{
		for (int i = 0; i != 2; ++i)
		{
			saveFile << "1,1,1,1" << std::endl;
		}
	}
	// TXTファイルを選択されていたら
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
	// 強制終了フラッグを下す
	endFlag = false;

	// マップチップ素材を共有する
	vp_mapChip = &t_mapChip;

	// 現在のシーンを初期化する
	stepNowNum = STEPNUMBER::chip;

	// ファイルのパスを共有する
	p_filePath = &t_filePath;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::Draw()
{
	// マップチップ素材を横並びに描画する
	for (int i = 0, n = static_cast<int>(vp_mapChip->size()); i != n; ++i)
	{
		DrawGraph(i * 15, 0, vp_mapChip->at(i), true);
	}


	// シーンで描画する内容を変更する
	switch (stepNowNum)
	{

	// マップチップ素材を追加してもらう
	case STEPNUMBER::chip:

		// 一つでもマップチップ素材をドラッグアンドドロップしていたら
		if (vp_mapChip->size() != 0)
		{
			// 説明を表示する
			DrawFormatString(0, 240, GetColor(255, 255, 255), "全部の素材を入れたら画面内でホイールクリックしてください。\nやり直す場合は右クリック");
			DrawFormatString(0, 240, GetColor(0, 0, 255), "　　　　　　　　　　　　　　ホイールクリック");
			DrawFormatString(0, 240, GetColor(0, 255, 0), "\n　　　　　　　右クリック");
		}

		// まだマップチップ素材をドラッグアンドドロップしていなかったら
		else
		{
			DrawFormatString(0, 0, GetColor(255, 255, 255), "マップチップとして扱いたい画像をID順にドラッグアンドドロップしてください。");
		}

		break;


	// マップのファイルを追加してもらう
	case STEPNUMBER::file:

		// 説明を表示する
		DrawFormatString(0, 240, GetColor(255, 255, 255), "読み込むファイルがある場合はそれをドラッグアンドドロップしてください。\n無い場合はそのままホイールクリックしてください。");
		DrawFormatString(0, 240, GetColor(0, 255, 0), "\n　　　　　　　　　ホイールクリック");

		break;


	// マップのファイルを生成する際の拡張子を決めてもらう
	case STEPNUMBER::fileExc:

		// 説明を表示する
		DrawFormatString(0, 240, GetColor(255, 255, 255), "書き込むファイルの形式が.csvならホイールクリックしてください。\n.txtなら右クリック");
		DrawFormatString(0, 240, GetColor(0, 255, 0), "　　　　　　　　　　　　　　    ホイールクリック");
		DrawFormatString(0, 240, GetColor(0, 0, 255), "\n　　    右クリック");

		break;


	// マップエディタに移行するか確認する
	case STEPNUMBER::nextScene:

		// 説明を表示する
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
	// 各シーンの行動
	switch (stepNowNum)
	{

	// マップチップ素材を追加してもらう
	case STEPNUMBER::chip:

		// マウスホイールがクリックされたら
		if (MouseData::GetClick(2) == 1)
		{
			// シーンをファイルの追加に移動する
			stepNowNum = STEPNUMBER::file;
		}

		// 右クリックされたら
		if (MouseData::GetClick(1) == 1)
		{
			// 追加したマップチップ素材を全部削除する
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


	// マップのファイルを追加してもらう
	case STEPNUMBER::file:

		// ファイルが追加されていないとき
		if (p_filePath->empty())
		{
			// マウスホイールがクリックされたら
			if (MouseData::GetClick(2) == 1)
			{
				// マップファイルを生成する際の拡張子を決めるシーンへ移行
				stepNowNum = STEPNUMBER::fileExc;
			}
		}
		// ファイルが追加されたら
		else
		{
			// マップエディタへ移行するか確認するシーンへ移行
			stepNowNum = STEPNUMBER::nextScene;
		}

		break;


	// マップのファイルを生成する際の拡張子を決めてもらう
	case STEPNUMBER::fileExc:

		// マウスホイールがクリックされたら
		if (MouseData::GetClick(2) == 1)
		{
			// 拡張子CSVとしてファイルを作成する
			*p_filePath = "Map\\Save.csv";
			CreateMap(true);

			// マップエディタへ移行するか確認するシーンへ移行
			stepNowNum = STEPNUMBER::nextScene;
		}

		// 右クリックされたら
		if (MouseData::GetClick(1) == 1)
		{
			// 拡張子TXTとしてファイルを作成する
			*p_filePath = "Map\\Save.txt";
			CreateMap(false);

			// マップエディタへ移行するか確認するシーンへ移行
			stepNowNum = STEPNUMBER::nextScene;
		}

		break;


	// マップエディタに移行するか確認する
	case STEPNUMBER::nextScene:

		// マウスホイールがクリックされたら
		if (MouseData::GetClick(2) == 1)
		{
			// シーンをマップエディタに移行する
			BASICPARAM::e_nowScene = ESceneNumber::MAPEDITOR;
		}

		// 右クリックされたら
		if (MouseData::GetClick(1) == 1)
		{
			// ファイルのパスを初期化する
			*p_filePath = "";

			// ファイルの追加シーンに戻る
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
	// 現在のシーンでドラッグアンドドロップの処理を変更
	switch (stepNowNum)
	{

	// マップチップ素材の時
	case STEPNUMBER::chip:

		// マップチップ素材を読み込む
		vp_mapChip->push_back(LoadGraph(t_path));

		break;

		
	// ファイルの追加の時
	case STEPNUMBER::file:

		// ファイルのパスを取得する
		*p_filePath = t_path;

		break;


	default:
		break;
	}
}
