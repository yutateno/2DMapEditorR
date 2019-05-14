#include "MapEditor.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MapEditor::MapChipDraw(const int t_areaX, const int t_areaY, const int t_chipID)
{
	// �}�b�v�`�b�v�f�ނɂ���ID�ԍ��̎�
	const int temp = t_chipID - 1;
	if (temp >= 0)
	{
		if (vp_mapChip->size() > temp)
		{
			DrawGraph(t_areaX, t_areaY, vp_mapChip->at(temp), true);
		}
		// �}�b�v�`�b�v�f�ނɂȂ�ID�ԍ��̎�
		else
		{
			DrawBox(t_areaX, t_areaY, t_areaX + mapChipSizeX, t_areaY + mapChipSizeY, GetColor(50, 50, 50), true);
		}
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

	// �I�����Ă���}�b�v�`�b�vID�̏�����
	mouseSelectChipID = 0;
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
			MapChipDraw(j * mapChipSizeX, i * mapChipSizeX, stoi(vv_mapdata[i][j]));
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
			const int yFirst = static_cast<int>(EChipSelectAreaY::oneFirst);
			const int yEnd = static_cast<int>(EChipSelectAreaY::oneEnd);


			// �E���ǉ�
			DrawBox(static_cast<int>(EChipSelectAreaX::oneFirst)	, yFirst, static_cast<int>(EChipSelectAreaX::oneEnd), yEnd, GetColor(255, 255, 255), true);
			DrawBox(static_cast<int>(EChipSelectAreaX::oneEnd) - 10	, yFirst, static_cast<int>(EChipSelectAreaX::oneEnd), yEnd, GetColor(0, 255, 0), true);


			// ����s�ǉ�
			DrawBox(static_cast<int>(EChipSelectAreaX::secondFirst), yFirst		, static_cast<int>(EChipSelectAreaX::secondEnd), yEnd, GetColor(255, 255, 255), true);
			DrawBox(static_cast<int>(EChipSelectAreaX::secondFirst), yEnd - 10, static_cast<int>(EChipSelectAreaX::secondEnd), yEnd, GetColor(0, 255, 0), true);


			// �E���폜
			DrawBox(static_cast<int>(EChipSelectAreaX::thirdFirst)		, yFirst, static_cast<int>(EChipSelectAreaX::thirdEnd), yEnd, GetColor(255, 255, 255), true);
			DrawBox(static_cast<int>(EChipSelectAreaX::thirdEnd) - 10	, yFirst, static_cast<int>(EChipSelectAreaX::thirdEnd), yEnd, GetColor(255, 0, 0), true);


			// ����s�폜
			DrawBox(static_cast<int>(EChipSelectAreaX::fourthFirst), yFirst		, static_cast<int>(EChipSelectAreaX::fourthEnd), yEnd, GetColor(255, 255, 255), true);
			DrawBox(static_cast<int>(EChipSelectAreaX::fourthFirst), yEnd - 10, static_cast<int>(EChipSelectAreaX::fourthEnd), yEnd, GetColor(255, 0, 0), true);
		}


		// ���ڈȍ~�ɂ���
		{
			int i = 0;		// ���s�ڂ����ׂ�

			for (EChipSelectAreaY areaY : {EChipSelectAreaY::secondFirst, EChipSelectAreaY::thirdFirst, EChipSelectAreaY::fourthFirst
				, EChipSelectAreaY::fifthFirst, EChipSelectAreaY::sixthFirst, EChipSelectAreaY::seventhFirst, EChipSelectAreaY::eighthFirst
				, EChipSelectAreaY::ninthFirst, EChipSelectAreaY::tenthFirst})
			{
				int j = 0;		// ����ڂ����ׂ�

				for (EChipSelectAreaX areaX : {EChipSelectAreaX::oneFirst, EChipSelectAreaX::secondFirst, EChipSelectAreaX::thirdFirst
					, EChipSelectAreaX::fourthFirst, EChipSelectAreaX::fifthFirst})
				{
					// �}�b�v�`�b�v��`��
					MapChipDraw(static_cast<int>(areaX), static_cast<int>(areaY), (j + (i * 5)));

					// �}�b�v�`�b�vID��\��
					DrawFormatString(static_cast<int>(areaX), static_cast<int>(areaY), GetColor(255, 255, 255), "%d", j + (i * 5));

					j++;		// ����Z
				}
				i++;		// �s���Z
			}
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


	// �I�����Ă���}�b�v�`�b�vID��0�Ԗڂ���Ȃ�������
	if (mouseSelectChipID != 0)
	{
		// �}�E�X�őI�����Ă���`�b�v��\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
		MapChipDraw(mouseX, mouseY, mouseSelectChipID);
		DrawFormatString(mouseX + mapChipSizeX - 10, mouseY, GetColor(255, 255, 255), "%d", mouseSelectChipID);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
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
			if (mouseY > static_cast<int>(EChipSelectAreaY::oneFirst) && mouseY < static_cast<int>(EChipSelectAreaY::oneEnd))
			{
				// �u�E����ǉ�����v��I��
				if (mouseX > static_cast<int>(EChipSelectAreaX::oneFirst) && mouseX < static_cast<int>(EChipSelectAreaX::oneEnd))
				{
					// �ꌅ���ǂ����Œǉ�����ID��I��
					std::string str = chipDoubleDigitID ? "01" : "1";

					// �E�[�Ɉ��ǉ�
					for (size_t i = 0, n = vv_mapdata.size(); i != n; ++i) 
					{
						vv_mapdata[i].push_back(str);
					}
				}
				

				// �u����s��ǉ�����v��I��
				if (mouseX > static_cast<int>(EChipSelectAreaX::secondFirst) && mouseX < static_cast<int>(EChipSelectAreaX::secondEnd))
				{
					// ���[�Ɉ�s�ǉ�
					vv_mapdata.push_back(vv_mapdata.back());
				}


				// �u�E�����폜����v��I��
				if (mouseX > static_cast<int>(EChipSelectAreaX::thirdFirst) && mouseX < static_cast<int>(EChipSelectAreaX::thirdEnd))
				{
					// �S�ď����Ȃ��悤�ɂ���
					if (vv_mapdata[0].size() >= 2)
					{
						// �E�[�����폜
						for (size_t i = 0, n = vv_mapdata.size(); i != n; ++i)
						{
							vv_mapdata[i].pop_back();
						}
					}
				}


				// �u����s���폜����v��I��
				if (mouseX > static_cast<int>(EChipSelectAreaX::fourthFirst) && mouseX < static_cast<int>(EChipSelectAreaX::fourthEnd))
				{
					// �S�ď����Ȃ��悤�ɂ���
					if (vv_mapdata.size() >= 2)
					{
						// ���[�����폜
						vv_mapdata.pop_back();
					}
				}
			} /// if (mouseY > static_cast<int>(EChipSelectAreaY::oneFirst) && mouseY < static_cast<int>(EChipSelectAreaY::oneEnd))


			// ��s�ڈȍ~�̎�
			{
				int i = 0;		// ���s�ڂ�

				for (EChipSelectAreaY areaY : {EChipSelectAreaY::secondFirst, EChipSelectAreaY::thirdFirst, EChipSelectAreaY::fourthFirst
					, EChipSelectAreaY::fifthFirst, EChipSelectAreaY::sixthFirst, EChipSelectAreaY::seventhFirst, EChipSelectAreaY::eighthFirst
					, EChipSelectAreaY::ninthFirst, EChipSelectAreaY::tenthFirst})
				{
					int j = 0;		// ����ڂ�

					// Y���W�ɂă}�E�X�������Ă�����
					if (mouseY > static_cast<int>(areaY) && mouseY < static_cast<int>(areaY) + 40)
					{
						// �`�b�v��I��
						for (EChipSelectAreaX areaX : {EChipSelectAreaX::oneFirst, EChipSelectAreaX::secondFirst, EChipSelectAreaX::thirdFirst
							, EChipSelectAreaX::fourthFirst, EChipSelectAreaX::fifthFirst})
						{
							// X���W�ɂă}�E�X�������Ă�����
							if (mouseX > static_cast<int>(areaX) && mouseX < static_cast<int>(areaX) + 40)
							{
								// �}�E�X�I���}�b�v�`�b�vID��n��
								mouseSelectChipID = (j + (i * 5));
							}
							j++;		// ����Z
						}
					}
					i++;		// �s���Z
				}
			}
		} /// if (MouseData::GetClick(0) == 1)
	}
	// �}�b�v�`�b�v�I����ʂ��\������Ă��Ȃ�������
	else
	{

	}
}
