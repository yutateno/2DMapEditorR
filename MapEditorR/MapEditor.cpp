#include "MapEditor.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::MapChipDraw(const int t_areaX, const int t_areaY, const int t_chipID)
{
	// �}�b�v�`�b�v�f�ނɂȂ�ID�ԍ��̎�
	if (vp_mapChip->size() > t_chipID)
	{
		DrawGraph(t_areaY * mapChipSizeY, t_areaX * mapChipSizeX, vp_mapChip->at(t_chipID), true);
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


	// �Z�[�u������\��������
	saveEndFlag = true;
	saveEndViewCount = 255;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
MapEditor::MapEditor(std::vector<int>& t_mapChip, std::string& t_filePath, int& t_backGround)
{
	// �����I���t���b�O������
	endFlag = false;

	// �}�b�v�`�b�v�f�ނ����L����
	vp_mapChip = &t_mapChip;

	// �t�@�C���p�X�����L����
	p_filePath = &t_filePath;

	// �w�i�摜�����L����
	p_backGround = &t_backGround;

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

	// �Z�[�u���Ă���t���b�O�̏�����
	saveEndFlag = false;

	// �Z�[�u�����̃J�E���g������
	saveEndViewCount = 0;
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
	// �w�i�摜��`�悷��
	if (*p_backGround != -1)
	{
		DrawGraph(0, 0, *p_backGround, false);
	}


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
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 225);
		DrawBox(0, 0, 320, 720, GetColor(125, 125, 125), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


		// ���ڂɂ���
		{
			const int yFirst = static_cast<int>(EChipSelectAreaY::oneAreaFirst);
			const int yEnd = static_cast<int>(EChipSelectAreaY::oneAreaEnd);


			// �E���ǉ�
			DrawBox(static_cast<int>(EChipSelectAreaX::mapRightAddFirst), yFirst
				, static_cast<int>(EChipSelectAreaX::mapRightAddEnd), yEnd, GetColor(255, 255, 255), true);
			DrawBox(static_cast<int>(EChipSelectAreaX::mapRightAddEnd) - 10, yFirst
				, static_cast<int>(EChipSelectAreaX::mapRightAddEnd), yEnd, GetColor(0, 255, 0), true);


			// ����s�ǉ�
			DrawBox(static_cast<int>(EChipSelectAreaX::mapUnderAddFirst), yFirst
				, static_cast<int>(EChipSelectAreaX::mapUnderAddEnd), yEnd, GetColor(255, 255, 255), true);
			DrawBox(static_cast<int>(EChipSelectAreaX::mapUnderAddFirst), yFirst - 10
				, static_cast<int>(EChipSelectAreaX::mapUnderAddEnd), yEnd, GetColor(0, 255, 0), true);


			// �E���폜
			DrawBox(static_cast<int>(EChipSelectAreaX::mapRightDelFirst), yFirst
				, static_cast<int>(EChipSelectAreaX::mapRightDelEnd), yEnd, GetColor(255, 255, 255), true);
			DrawBox(static_cast<int>(EChipSelectAreaX::mapRightDelEnd) - 10, yFirst
				, static_cast<int>(EChipSelectAreaX::mapRightDelEnd), yEnd, GetColor(255, 0, 0), true);


			// ����s�폜
			DrawBox(static_cast<int>(EChipSelectAreaX::mapUnderDelFirst), yFirst
				, static_cast<int>(EChipSelectAreaX::mapUnderDelEnd), yEnd, GetColor(255, 255, 255), true);
			DrawBox(static_cast<int>(EChipSelectAreaX::mapUnderDelFirst), yFirst - 10
				, static_cast<int>(EChipSelectAreaX::mapUnderDelEnd), yEnd, GetColor(255, 0, 0), true);
		}
	}

	
	// ���ɐ�����\������
	DrawBox(0, 720, 1280, 760, GetColor(0, 0, 0), true);
	DrawFormatString(0, 730, GetColor(255, 255, 255), "�z�C�[���N���b�N�ŃZ�[�u�B���܂��͉ECtrl�Ń}�b�v�`�b�v�I����ʁB���}�b�v�T�C�Y: %d x %d", vv_mapdata[0].size(), vv_mapdata.size());


	// �Z�[�u�̕\��
	if (saveEndFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, saveEndViewCount);
		DrawFormatString(0, 730, GetColor(255, 0, 0), "�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@    �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@         �@�Z�[�u���܂����B");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	// �}�E�X�̈ʒu��\��
	DrawFormatString(mouseX, mouseY, GetColor(255, 255, 255), "%dx%d", mouseX, mouseY);
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


	// �Z�[�u�����̕\�������Ă���Ƃ�
	if (saveEndFlag)
	{
		// ���߂�Z�����Ă���
		if ((saveEndViewCount -= 3) <= 0)
		{
			// �Z�[�u�����̕\��������
			saveEndFlag = false;
		}
	}


	// ���܂��͉E�R���g���[���������ꂽ��
	if (KeyData::Get(KEY_INPUT_LCONTROL) == 1 || KeyData::Get(KEY_INPUT_RCONTROL) == 1)
	{
		// �}�b�v�`�b�v�I����ʂ̃t���b�O�𒼑O�̋t�ɂ���
		selectMapChipWindow = !selectMapChipWindow;
	}


	// �}�b�v�`�b�v�I����ʂ��\������Ă�����
	if (selectMapChipWindow)
	{
		// ���N���b�N���ꂽ��
		if (MouseData::GetClick(0) == 1)
		{
			// ��s�ڂ̎�
			if (mouseY > static_cast<int>(EChipSelectAreaY::oneAreaFirst) && mouseY < static_cast<int>(EChipSelectAreaY::oneAreaEnd))
			{
				// �u�E����ǉ�����v��I��
				if (mouseX > static_cast<int>(EChipSelectAreaX::mapRightAddFirst) && mouseX < static_cast<int>(EChipSelectAreaX::mapRightAddEnd))
				{
					std::string str = chipDoubleDigitID ? "00" : "0";
					for (size_t i = 0, n = vv_mapdata.size(); i != n; ++i) 
					{
						vv_mapdata[i].push_back(str);
					}
				}
				

				// �u����s��ǉ�����v��I��
				if (mouseX > static_cast<int>(EChipSelectAreaX::mapUnderAddFirst) && mouseX < static_cast<int>(EChipSelectAreaX::mapUnderAddEnd))
				{
					vv_mapdata.push_back(vv_mapdata.back());
				}


				// �u�E�����폜����v��I��
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


				// �u����s���폜����v��I��
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
	// �}�b�v�`�b�v�I����ʂ��\������Ă��Ȃ�������
	else
	{

	}
}
