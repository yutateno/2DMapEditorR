#include "MapMake.hpp"

using namespace std;

MapMake::MapMake(int data) {
	this->data = data;
	gr_selectmode = LoadGraph("media\\selectback.png");

	gr_bg_saba = LoadGraph("media\\�����}�b�v.png");
	gr_bg_sise = LoadGraph("media\\�{�݃}�b�v.png");
	gr_bg_sinri = LoadGraph("media\\�X�у}�b�v.png");

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

	//�Z���N�g�G���A�\����\��
	if (KeyData::Get(KEY_INPUT_LCONTROL) == 1) {
		//�Ȃɂ��Ȃ��Ƃ�
		if (selectflag == false && selectareaflag == false) {
			selectflag = true;
			selectareaflag = false;
		}
		//�E�ɕ\�����Ă�Ƃ�
		else if (selectflag == true && selectareaflag == true) {
			selectflag = true;
			selectareaflag = true;
		}
		//���ɕ\�����Ă�Ƃ�
		else if (selectflag == true && selectareaflag == false) {
			selectflag = false;
			selectareaflag = false;
		}
	}
	if (KeyData::Get(KEY_INPUT_RCONTROL) == 1) {
		//�Ȃɂ��Ȃ��Ƃ�
		if (selectflag == false && selectareaflag == false) {
			selectflag = true;
			selectareaflag = true;
		}
		//���ɕ\�����Ă�Ƃ�
		else if (selectflag == true && selectareaflag == false) {
			selectflag = true;
			selectareaflag = false;
		}
		//�E�ɕ\�����Ă�Ƃ�
		else if (selectflag == true && selectareaflag == true) {
			selectflag = false;
			selectareaflag = false;
		}
	}

	//�Z�[�u���@
	if (selectflag == true) {
		if (KeyData::Get(KEY_INPUT_S) == 1) {
			SaveMapData();
		}
	}
	//�X�N���[��
	//��
	if (KeyData::Get(KEY_INPUT_UP) > 0) {
		scrolly += 16;
	}
	//��
	if (KeyData::Get(KEY_INPUT_DOWN) > 0) {
		scrolly -= 16;
	}
	//��
	if (KeyData::Get(KEY_INPUT_LEFT) > 0) {
		scrollx += 16;
	}
	//�E
	if (KeyData::Get(KEY_INPUT_RIGHT) > 0) {
		scrollx -= 16;
	}

	//��}�E�X�z�C�[��
	if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) > 1) {
		scrolly += 64;
	}
	else if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) == 1) {
		scrolly += 32;
	}
	//���}�E�X�z�C�[��
	else if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) < -1) {
		scrolly -= 64;
	}
	else if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) == -1) {
		scrolly -= 32;
	}

	//�X�N���[���C��
	limitx = (mapdata[0].size() * -32) + 640;
	limity = (mapdata.size() * -32) + 480;

	//����E
	if (scrolly > 0) {
		scrolly = 0;
	}
	//�����E
	else if (scrolly < limity) {
		scrolly = limity;
	}
	//�����E
	if (scrollx > 0) {
		scrollx = 0;
	}
	//�E���E
	else if (scrollx < limitx) {
		scrollx = limitx;
	}

	//�}�E�X�̂���`�b�v�̍��W���擾
	selectx = (int)((mousex - scrollx) / 32);
	selecty = (int)((mousey - scrolly) / 32);

	//���N���b�N
	if (MouseData::GetClick(0) > 0) {
		//�|�C���^���}�b�v���y�}�b�v�`�b�v�z�u�z
		if (selectflag == false) {	//�}�b�v�`�b�v�ύX��ʂ��o�ĂȂ��Ƃ�
			PutChip();	//�`�b�v��u��
		}
		//�Z���N�g�G���A������
		else {
			//�Z���N�g�G���A�ȊO�`�b�v�ύX�\
			if ((mousex > 222 || mousey > 240) && selectareaflag == false) {
				PutChip();
			}
			else if ((mousex < 418 || mousey > 240) && selectareaflag == true) {
				PutChip();
			}

			//�P�s��
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
			//�Q�s��
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
	//�E�N���b�N�Ń`�b�v������
	if (MouseData::GetClick(1) > 0) {
		//�Z���N�g�G���A�Ȃ�
		if (selectflag == false) {
			DeleteChip();
		}
		//����
		else {
			if ((mousex > 222 || mousey > 240) && selectareaflag == false) {
				DeleteChip();
			}
			else if ((mousex < 418 || mousey > 240) && selectareaflag == true) {
				DeleteChip();
			}
		}
	}

	//�Z�[�u
	if (savecount > 0) {
		savecount--;
	}

	//�Z�[�u���I��
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

	// �}�b�v�`�b�v
	for (int i = 0, n = mapdata.size(); i < n; i++) {
		for (int j = 0, m = mapdata[i].size(); j < m; j++) {
			// ��ʓ��Ȃ�`��
			if (j * 32 + scrollx >= -32 && j * 32 + scrollx <= 640 &&
				i * 32 + scrolly >= -32 && i * 32 + scrolly <= 480) {
				//stoi �ŕ����𐔒l�ɕϊ�
				switch ((int)(stoi(mapdata[i][j]) * 0.1)) {
				case 0:	//00
					break;

				case 1:	//��
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
				//�}�E�X�̂���ʒu
				if (j == selectx && i == selecty) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
					DrawChip(i, j, gr_select);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
			}
		}
	}
	// �Z���N�g�G���A
	if (selectflag == true) {
		// �g
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
	// �Z�[�u�R�����g
	if (savecount > 0) {
		DrawString(280, 240, "�Z�[�u���܂���", GetColor(0, 0, 255));
	}
}

// �}�b�v�`�b�v�`��
void MapMake::DrawChip(int i, int j, int gr) {
	DrawGraph(j * 32 + scrollx, i * 32 + scrolly, gr, true);
}

// �}�b�v�`�b�v��u��
void MapMake::PutChip() {
	mapdata[selecty][selectx] = selectchip;
}

// �}�b�v�`�b�v������
void MapMake::DeleteChip() {
	mapdata[selecty][selectx] = "00";
}

void MapMake::LoadMapData(int data) {

	read_count = 0;
	switch (data)
	{
	case 0:
		read_file.open("Map\\����.txt");		// �t�@�C���I�[�v��
		break;
	case 1:
		read_file.open("Map\\�{��.txt");		// �t�@�C���I�[�v��
		break;
	case 2:
		read_file.open("Map\\�X��.txt");		// �t�@�C���I�[�v��
		break;
	default:
		break;
	}

	if (read_file.fail()) {	// �t�@�C���ǂݍ��ݎ��s
		DxLib_End();
	}
	else {
		// �ǂݍ��ݐ���
		while (getline(read_file, read_line)) {	// ��s���ǂݍ���

			mapdata.resize(read_count + 1);
			for (int i = 0, n = read_line.length(); i < n; i += 2) {
				mapdata[read_count].push_back(read_line.substr(i, 2));
			}
			read_count++;	// ���̍s��
		}
	}
	// �t�@�C�������
	read_file.close();
}


void MapMake::SaveMapData() {

	write_file.open("Map\\Map.txt");		// �t�@�C���I�[�v��

	if (write_file.fail()) {	// �t�@�C���ǂݍ��ݎ��s
		DxLib_End();
	}
	else {
		// �ǂݍ��ݐ���
		for (int i = 0, n = mapdata.size(); i < n; i++) {
			for (int j = 0, m = mapdata[i].size(); j < m; j++) {
				write_file << mapdata[i][j];
			}
			write_file << endl;
		}
		savecount = 30;
	}

	// �t�@�C�������
	write_file.close();
}