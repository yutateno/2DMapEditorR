#include "MapEditor.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::MapChipDraw(const int t_areaX, const int t_areaY, const int t_chipID)
{
	// �}�b�v�`�b�v�f�ނɂȂ�ID�ԍ��̎�
	if (vp_mapChip->size() <= t_chipID)
	{
		DrawBox(t_areaY * mapChipSizeY, t_areaX * mapChipSizeX, (t_areaY + 1) * mapChipSizeY, (t_areaX + 1) * mapChipSizeX, GetColor(50, 50, 50), true);
	}
	// �}�b�v�`�b�v�f�ނ�ID������Ƃ�
	else
	{
		DrawGraph(t_areaY * mapChipSizeY, t_areaX * mapChipSizeX, vp_mapChip->at(t_chipID), false);
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::LoadMap()
{
	// �s�m�F�p�ϐ�
	int readCount = 0;

	// �t�@�C����ǂݍ���
	std::ifstream readFile(p_filePath->c_str());

	// �s���擾����
	std::string readLine = "";

	// CSV�t�@�C�����ǂ����m�F����
	readFileCSV = (p_filePath->find(".csv") != -1);


	// �t�@�C���ǂݍ��ݎ��s
	if ((p_filePath->find(".csv") == -1) && (p_filePath->find(".txt") == -1))
	{
		// �����I��������
		endFlag = true;
		return;
	}


	// CSV�t�@�C����������
	if (readFileCSV)
	{
		// �s���m�F
		while (getline(readFile, readLine))
		{
			std::string token;
			std::istringstream stream(readLine);

			// �}�b�v�f�[�^���߂ɍ쐬
			int tempReadCount = readCount + 1;
			vv_mapdata.resize(tempReadCount);

			// [,]�܂Ŋm�F
			while (std::getline(stream, token, ','))
			{
				// �}�b�v�f�[�^�ɒǉ�
				vv_mapdata[readCount].push_back(token);
			}

			// �s�����Z
			readCount++;
		}
	}
	// TXT�t�@�C����������
	else
	{
		// �s�m�F
		while (std::getline(readFile, readLine))
		{
			// �}�b�v�f�[�^���߂ɍ쐬
			int tempReadCount = readCount + 1;
			vv_mapdata.resize(tempReadCount);

			// 1���܂���2�����m�F
			for (int i = 0, n = static_cast<int>(readLine.length()); i < n; chipDoubleDigitID ? i += 2 : ++i)
			{
				// �}�b�v�f�[�^�ɒǉ�
				vv_mapdata[readCount].push_back(readLine.substr(i, chipDoubleDigitID ? 2 : 1));
			}

			// �s�����Z
			readCount++;
		}
	}


	// �t�@�C�������
	readFile.close();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::SaveMap()
{
	// �t�@�C����ǂݍ���
	std::ofstream saveFile(p_filePath->c_str());


	// �t�@�C���ǂݍ��ݎ��s
	if (saveFile.fail())
	{
		// �����I��������
		endFlag = true;
		return;
	}

	
	// CSV�t�@�C����������
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
	// TXT�t�@�C����������
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


	// �t�@�C�������
	saveFile.close();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
MapEditor::MapEditor(std::vector<int>& t_mapChip, std::string& t_filePath)
{
	// �����I���t���b�O������
	endFlag = false;

	// �}�b�v�`�b�v�f�ނ����L����
	vp_mapChip = &t_mapChip;

	// �t�@�C���p�X�����L����
	p_filePath = &t_filePath;

	// �}�E�X���W��������
	mouseX = 0;
	mouseY = 0;

	// �}�b�v�`�b�vID���񌅂��ǂ����ŏ���������
	chipDoubleDigitID = (vp_mapChip->size() >= 11);

	// �ǂݍ��݃t�@�C���̊g���q��TXT�f�[�^�Ɖ��肵�ď���������
	readFileCSV = false;

	// �}�b�v�f�[�^������������
	vv_mapdata.clear();

	// �}�b�v�t�@�C����ǂݍ���Ń}�b�v�f�[�^�ɏ�������
	LoadMap();

	// �}�b�v�`�b�v�I����ʃt���b�O�̏�����
	selectMapChipWindow = false;

	// �}�b�v�`�b�v�f�ނ�0�Ԗڂ̃T�C�Y���擾���ă}�b�v�`�b�v�S���̃T�C�Y�Ɖ��肷��
	GetGraphSize(vp_mapChip->at(0), &mapChipSizeX, &mapChipSizeY);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
MapEditor::~MapEditor()
{
	// �}�b�v�f�[�^���폜����
	vv_mapdata.shrink_to_fit();
	vv_mapdata.clear();
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::Draw()
{
	// �}�b�v�f�[�^����}�b�v�`�b�v��z�u�������̂�`�悷��
	for (int i = 0, n = static_cast<int>(vv_mapdata.size()); i != n; ++i)
	{
		for (int j = 0, m = static_cast<int>(vv_mapdata[i].size()); j != m; ++j)
		{
			MapChipDraw(i, j, stoi(vv_mapdata[i][j]));
		}
	}


	// �}�b�v�`�b�v�I����ʂ̕`�������Ƃ�
	if (selectMapChipWindow)
	{
		// �������Ƃ��ă}�b�v�`�b�v�I����ʂ�`�悷��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 190);
		DrawBox(0, 0, 640, 480, GetColor(125, 125, 125), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	
	// ���ɐ�����\������
	DrawBox(0, 480, 640, 520, GetColor(0, 0, 0), true);
	DrawFormatString(0, 500, GetColor(255, 255, 255), "�z�C�[���N���b�N�ŃZ�[�u�B���܂��͉ECtrl�Ń}�b�v�`�b�v�I�����");
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::Process()
{
	// �}�E�X�̈ʒu���擾����
	GetMousePoint(&mouseX, &mouseY);


	// �}�E�X�z�C�[�����N���b�N���ꂽ��
	if (MouseData::GetClick(2) == 1)
	{
		// �}�b�v�f�[�^����t�@�C���ɏ�������
		SaveMap();
	}


	// ���܂��͉E�R���g���[���������ꂽ��
	if (KeyData::Get(KEY_INPUT_LCONTROL) == 1 || KeyData::Get(KEY_INPUT_RCONTROL) == 1)
	{
		// �}�b�v�`�b�v�I����ʂ̃t���b�O�𒼑O�̋t�ɂ���
		selectMapChipWindow = !selectMapChipWindow;
	}
}
