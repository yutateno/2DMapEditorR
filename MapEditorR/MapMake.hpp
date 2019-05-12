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
	//�摜
	//��މ��
	int gr_selectmode;
	//�w�i
	int gr_bg_saba;
	int gr_bg_sise;
	int gr_bg_sinri;
	//�w�i��
	int gr_wall[10];

	//���̑�����
	int gr_selectchip;
	int gr_select;

	int data;

	// �Z���N�g�G���A
	bool selectflag;		//���邩�ǂ���
	bool selectareaflag;	//�ʒu�@0:���@1:�E

	string selectchip;		// �I�𒆂̃}�b�v�`�b�v

	int mousex;		// �}�E�X�̍��W
	int mousey;
	int selectx;	// �I�𒆂̍��W
	int selecty;
	int scrollx;	// �X�N���[��
	int scrolly;
	int limitx;		// �E��
	int limity;		// ����

	vector<vector<string>> mapdata;

	// �t�@�C���ǂݍ��ݗp
	ifstream read_file;		// �ǂݍ��ރt�@�C��
	string read_line;		// �ǂݍ��񂾍s�i1�s�j
	int read_count;			// �m�[�h�ǂݍ��ݗp�i���s�ڂ�ǂݍ���ł��邩�j

							// �t�@�C���������ݗp
	ofstream write_file;	// �������ރt�@�C��
	int savecount;		// �Z�[�u�\��

	void LoadMapData(int data);

public:
	MapMake(int data);
	~MapMake();

	void Update();
	void Process();
	void Draw();

	void DrawChip(int i, int j, int gr);	// �`�b�v�`��
	void PutChip();	// �I�𒆂̃`�b�v��u��
	void DeleteChip();	// �}�b�v�`�b�v������

	void SaveMapData();
};