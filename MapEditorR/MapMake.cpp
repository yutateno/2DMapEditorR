#include "MapMake.hpp"

using namespace std;

MapMake::MapMake(int data) {
	this->data = data;
	gr_selectmode = LoadGraph("media\\selectback.png");

	gr_bg_saba = LoadGraph("media\\砂漠マップ.png");
	gr_bg_sise = LoadGraph("media\\施設マップ.png");
	gr_bg_sinri = LoadGraph("media\\森林マップ.png");

	gr_wall[0] = LoadGraph("media\\kabe.png");
	gr_wall[1] = LoadGraph("media\\player1.png");
	gr_wall[2] = LoadGraph("media\\player2.png");
	gr_wall[3] = LoadGraph("media\\player3.png");
	gr_wall[4] = LoadGraph("media\\player4.png");
	gr_wall[8] = LoadGraph("media\\capsule.png");
	gr_wall[9] = LoadGraph("media\\rock.png");

	gr_selectchip = LoadGraph("media\\select.png");
	gr_select = gr_wall[0];

	selectflag = false;
	selectareaflag = false;

	mousex = 0;
	mousey = 0;
	selectx = 0;
	selecty = 0;
	scrollx = 0;
	scrolly = 0;
	limitx = 0;
	limity = 0;

	selectchip = "10";
	savecount = 0;

	LoadMapData(data);
}

MapMake::~MapMake() {
	DeleteGraph(gr_selectmode);
	DeleteGraph(gr_bg_saba);
	DeleteGraph(gr_bg_sise);
	DeleteGraph(gr_bg_sinri);
	DeleteGraph(gr_selectchip);
	DeleteGraph(gr_select);
	for (int i = 0; i != 10; ++i)
	{
		DeleteGraph(gr_wall[i]);
	}
}

void MapMake::Update() {
	Process();
	Draw();
}

void MapMake::Process() {
	GetMousePoint(&mousex, &mousey);

	//セレクトエリア表示非表示
	if (KeyData::Get(KEY_INPUT_LCONTROL) == 1) {
		//なにもないとき
		if (selectflag == false && selectareaflag == false) {
			selectflag = true;
			selectareaflag = false;
		}
		//右に表示してるとき
		else if (selectflag == true && selectareaflag == true) {
			selectflag = true;
			selectareaflag = true;
		}
		//左に表示してるとき
		else if (selectflag == true && selectareaflag == false) {
			selectflag = false;
			selectareaflag = false;
		}
	}
	if (KeyData::Get(KEY_INPUT_RCONTROL) == 1) {
		//なにもないとき
		if (selectflag == false && selectareaflag == false) {
			selectflag = true;
			selectareaflag = true;
		}
		//左に表示してるとき
		else if (selectflag == true && selectareaflag == false) {
			selectflag = true;
			selectareaflag = false;
		}
		//右に表示してるとき
		else if (selectflag == true && selectareaflag == true) {
			selectflag = false;
			selectareaflag = false;
		}
	}

	//セーブ方法
	if (selectflag == true) {
		if (KeyData::Get(KEY_INPUT_S) == 1) {
			SaveMapData();
		}
	}
	//スクロール
	//上
	if (KeyData::Get(KEY_INPUT_UP) > 0) {
		scrolly += 16;
	}
	//下
	if (KeyData::Get(KEY_INPUT_DOWN) > 0) {
		scrolly -= 16;
	}
	//左
	if (KeyData::Get(KEY_INPUT_LEFT) > 0) {
		scrollx += 16;
	}
	//右
	if (KeyData::Get(KEY_INPUT_RIGHT) > 0) {
		scrollx -= 16;
	}

	//上マウスホイール
	if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) > 1) {
		scrolly += 64;
	}
	else if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) == 1) {
		scrolly += 32;
	}
	//下マウスホイール
	else if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) < -1) {
		scrolly -= 64;
	}
	else if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) == -1) {
		scrolly -= 32;
	}

	//スクロール修正
	limitx = (mapdata[0].size() * -32) + 640;
	limity = (mapdata.size() * -32) + 480;

	//上限界
	if (scrolly > 0) {
		scrolly = 0;
	}
	//下限界
	else if (scrolly < limity) {
		scrolly = limity;
	}
	//左限界
	if (scrollx > 0) {
		scrollx = 0;
	}
	//右限界
	else if (scrollx < limitx) {
		scrollx = limitx;
	}

	//マウスのあるチップの座標を取得
	selectx = (int)((mousex - scrollx) / 32);
	selecty = (int)((mousey - scrolly) / 32);

	//左クリック
	if (MouseData::GetClick(0) > 0) {
		//ポインタがマップ内【マップチップ配置】
		if (selectflag == false) {	//マップチップ変更画面が出てないとき
			PutChip();	//チップを置く
		}
		//セレクトエリアがある
		else {
			//セレクトエリア以外チップ変更可能
			if ((mousex > 222 || mousey > 240) && selectareaflag == false) {
				PutChip();
			}
			else if ((mousex < 418 || mousey > 240) && selectareaflag == true) {
				PutChip();
			}

			//１行目
			if (mousey >= 42 && mousey <= 70) {
				if (mousex >= (14 + (selectareaflag * 418))
					&& mousex <= (42 + (selectareaflag * 418))) {
					selectchip = "10";
					gr_select = gr_wall[0];
				}
				else if (mousex >= (57 + (selectareaflag * 418))
					&& mousex <= (85 + (selectareaflag * 418))) {
					selectchip = "18";
					gr_select = gr_wall[1];
				}
				else if (mousex >= (99 + (selectareaflag * 418))
					&& mousex <= (127 + (selectareaflag * 418))) {
					selectchip = "19";
					gr_select = gr_wall[2];
				}
				else if (mousex >= (142 + (selectareaflag * 418))
					&& mousex <= (170 + (selectareaflag * 418))) {
					selectchip = "13";
					gr_select = gr_wall[3];
				}
				else if (mousex >= (184 + (selectareaflag * 418))
					&& mousex <= (212 + (selectareaflag * 418))) {
					selectchip = "14";
					gr_select = gr_wall[4];
				}
			}
			//２行目
			else if (mousey >= 85 && mousey <= 113) {
				if (mousex >= (14 + (selectareaflag * 418))
					&& mousex <= (42 + (selectareaflag * 418))) {
					selectchip = "11";
					gr_select = gr_wall[8];
				}
				else if (mousex >= (57 + (selectareaflag * 418))
					&& mousex <= (85 + (selectareaflag * 418))) {
					selectchip = "12";
					gr_select = gr_wall[9];
				}
			}
		}
	}
	//右クリックでチップを消す
	if (MouseData::GetClick(1) > 0) {
		//セレクトエリアなし
		if (selectflag == false) {
			DeleteChip();
		}
		//あり
		else {
			if ((mousex > 222 || mousey > 240) && selectareaflag == false) {
				DeleteChip();
			}
			else if ((mousex < 418 || mousey > 240) && selectareaflag == true) {
				DeleteChip();
			}
		}
	}

	//セーブ
	if (savecount > 0) {
		savecount--;
	}

	//セーブ兼終了
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		SaveMapData();
	}
}

void MapMake::Draw() {
	switch (data)
	{
	case 0:
		DrawGraph(scrollx, scrolly, gr_bg_saba, false);
		break;
	case 1:
		DrawGraph(scrollx, scrolly, gr_bg_sise, false);
		break;
	case 2:
		DrawGraph(scrollx, scrolly, gr_bg_sinri, false);
		break;
	default:
		break;
	}

	// マップチップ
	for (int i = 0, n = mapdata.size(); i < n; i++) {
		for (int j = 0, m = mapdata[i].size(); j < m; j++) {
			// 画面内なら描画
			if (j * 32 + scrollx >= -32 && j * 32 + scrollx <= 640 &&
				i * 32 + scrolly >= -32 && i * 32 + scrolly <= 480) {
				//stoi で文字を数値に変換
				switch ((int)(stoi(mapdata[i][j]) * 0.1)) {
				case 0:	//00
					break;

				case 1:	//壁
					switch (stoi(mapdata[i][j]) % 10) {
					case 0:	//10
						DrawChip(i, j, gr_wall[0]);
						break;

					case 8:	//11
						DrawChip(i, j, gr_wall[1]);
						break;

					case 9:	//12
						DrawChip(i, j, gr_wall[2]);
						break;

					case 3:	//13
						DrawChip(i, j, gr_wall[3]);
						break;

					case 4:	//14
						DrawChip(i, j, gr_wall[4]);
						break;

					case 1:	//18
						DrawChip(i, j, gr_wall[8]);
						break;

					case 2:
						DrawChip(i, j, gr_wall[9]);
						break;

					default:
						break;
					}
					break;
				default:
					break;
				}
				//マウスのいる位置
				if (j == selectx && i == selecty) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
					DrawChip(i, j, gr_select);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
			}
		}
	}
	// セレクトエリア
	if (selectflag == true) {
		// 枠
		DrawGraph((0 + (selectareaflag * 418)), 0, gr_selectmode, false);

		DrawGraph((14 + (selectareaflag * 418)), 42, gr_wall[0], true);
		if (selectchip == "10") DrawGraph((4 + (selectareaflag * 418)), 32, gr_selectchip, true);
		DrawGraph((57 + (selectareaflag * 418)), 42, gr_wall[1], true);
		if (selectchip == "18") DrawGraph((47 + (selectareaflag * 418)), 32, gr_selectchip, true);
		DrawGraph((99 + (selectareaflag * 418)), 42, gr_wall[2], true);
		if (selectchip == "19") DrawGraph((89 + (selectareaflag * 418)), 32, gr_selectchip, true);
		DrawGraph((142 + (selectareaflag * 418)), 42, gr_wall[3], true);
		if (selectchip == "13") DrawGraph((132 + (selectareaflag * 418)), 32, gr_selectchip, true);
		DrawGraph((184 + (selectareaflag * 418)), 42, gr_wall[4], true);
		if (selectchip == "14") DrawGraph((174 + (selectareaflag * 418)), 32, gr_selectchip, true);
		DrawGraph((14 + (selectareaflag * 418)), 85, gr_wall[8], true);
		if (selectchip == "11") DrawGraph((4 + (selectareaflag * 418)), 75, gr_selectchip, true);
		DrawGraph((57 + (selectareaflag * 418)), 85, gr_wall[9], true);
		if (selectchip == "12") DrawGraph((47 + (selectareaflag * 418)), 75, gr_selectchip, true);
	}
	// セーブコメント
	if (savecount > 0) {
		DrawString(280, 240, "セーブしました", GetColor(0, 0, 255));
	}
}

// マップチップ描画
void MapMake::DrawChip(int i, int j, int gr) {
	DrawGraph(j * 32 + scrollx, i * 32 + scrolly, gr, true);
}

// マップチップを置く
void MapMake::PutChip() {
	mapdata[selecty][selectx] = selectchip;
}

// マップチップを消す
void MapMake::DeleteChip() {
	mapdata[selecty][selectx] = "00";
}

void MapMake::LoadMapData(int data) {

	read_count = 0;
	switch (data)
	{
	case 0:
		read_file.open("Map\\砂漠.txt");		// ファイルオープン
		break;
	case 1:
		read_file.open("Map\\施設.txt");		// ファイルオープン
		break;
	case 2:
		read_file.open("Map\\森林.txt");		// ファイルオープン
		break;
	default:
		break;
	}

	if (read_file.fail()) {	// ファイル読み込み失敗
		DxLib_End();
	}
	else {
		// 読み込み成功
		while (getline(read_file, read_line)) {	// 一行ずつ読み込み

			mapdata.resize(read_count + 1);
			for (int i = 0, n = read_line.length(); i < n; i += 2) {
				mapdata[read_count].push_back(read_line.substr(i, 2));
			}
			read_count++;	// 次の行に
		}
	}
	// ファイルを閉じる
	read_file.close();
}


void MapMake::SaveMapData() {

	write_file.open("Map\\Map.txt");		// ファイルオープン

	if (write_file.fail()) {	// ファイル読み込み失敗
		DxLib_End();
	}
	else {
		// 読み込み成功
		for (int i = 0, n = mapdata.size(); i < n; i++) {
			for (int j = 0, m = mapdata[i].size(); j < m; j++) {
				write_file << mapdata[i][j];
			}
			write_file << endl;
		}
		savecount = 30;
	}

	// ファイルを閉じる
	write_file.close();
}