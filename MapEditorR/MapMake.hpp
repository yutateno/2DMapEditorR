#pragma once
#include "DxLib.h"
#include "Input.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class MapMake {

private:
	//画像
	//種類画面
	int gr_selectmode;
	//背景
	int gr_bg_saba;
	int gr_bg_sise;
	int gr_bg_sinri;
	//背景壁
	int gr_wall[10];

	//その他操作
	int gr_selectchip;
	int gr_select;

	int data;

	// セレクトエリア
	bool selectflag;		//あるかどうか
	bool selectareaflag;	//位置　0:左　1:右

	string selectchip;		// 選択中のマップチップ

	int mousex;		// マウスの座標
	int mousey;
	int selectx;	// 選択中の座標
	int selecty;
	int scrollx;	// スクロール
	int scrolly;
	int limitx;		// 右限
	int limity;		// 下限

	vector<vector<string>> mapdata;

	// ファイル読み込み用
	ifstream read_file;		// 読み込むファイル
	string read_line;		// 読み込んだ行（1行）
	int read_count;			// ノード読み込み用（何行目を読み込んでいるか）

							// ファイル書き込み用
	ofstream write_file;	// 書き込むファイル
	int savecount;		// セーブ表示

	void LoadMapData(int data);

public:
	MapMake(int data);
	~MapMake();

	void Update();
	void Process();
	void Draw();

	void DrawChip(int i, int j, int gr);	// チップ描画
	void PutChip();	// 選択中のチップを置く
	void DeleteChip();	// マップチップを消す

	void SaveMapData();
};