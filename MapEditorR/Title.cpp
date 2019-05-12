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

	// �t�@�C�������
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

			DrawFormatString(0, 240, GetColor(255, 255, 255), "�S���̑f�ނ���ꂽ���ʓ��Ńz�C�[���N���b�N���Ă��������B\n��蒼���ꍇ�͉E�N���b�N");
			DrawFormatString(0, 240, GetColor(0, 0, 255), "�@�@�@�@�@�@�@�@�@�@�@�@�@�@�z�C�[���N���b�N");
			DrawFormatString(0, 240, GetColor(0, 255, 0), "\n�@�@�@�@�@�@�@�E�N���b�N");
		}
		else
		{
			DrawFormatString(0, 0, GetColor(255, 255, 255), "�}�b�v�`�b�v�Ƃ��Ĉ��������摜��ID���Ƀh���b�O�A���h�h���b�v���Ă��������B");
		}
		break;


	case STEPNUMBER::file:
		for (int i = 0, n = static_cast<int>(vp_mapChip->size()); i != n; ++i)
		{
			DrawGraph(i * 15, 0, vp_mapChip->at(i), true);
		}
		DrawFormatString(0, 240, GetColor(255, 255, 255), "�ǂݍ��ރt�@�C��������ꍇ�͂�����h���b�O�A���h�h���b�v���Ă��������B\n�����ꍇ�͂��̂܂܃z�C�[���N���b�N���Ă��������B");
		DrawFormatString(0, 240, GetColor(0, 255, 0), "\n�@�@�@�@�@�@�@�@�@�z�C�[���N���b�N");
		break;


	case STEPNUMBER::fileExc:
		for (int i = 0, n = static_cast<int>(vp_mapChip->size()); i != n; ++i)
		{
			DrawGraph(i * 15, 0, vp_mapChip->at(i), true);
		}
		DrawFormatString(0, 240, GetColor(255, 255, 255), "�������ރt�@�C���̌`����.csv�Ȃ�z�C�[���N���b�N���Ă��������B\n.txt�Ȃ�E�N���b�N");
		DrawFormatString(0, 240, GetColor(0, 255, 0), "�@�@�@�@�@�@�@�@�@�@�@�@�@�@    �z�C�[���N���b�N");
		DrawFormatString(0, 240, GetColor(0, 0, 255), "\n�@�@    �E�N���b�N");
		break;


	case STEPNUMBER::nextScene:
		for (int i = 0, n = static_cast<int>(vp_mapChip->size()); i != n; ++i)
		{
			DrawGraph(i * 15, 0, vp_mapChip->at(i), true);
		}
		DrawFormatString(0, 120, GetColor(255, 255, 255), "%s", p_filePath->c_str());
		DrawFormatString(0, 240, GetColor(255, 255, 255), "�}�b�v�G�f�B�^��ʂɐi�ޏꍇ�̓z�C�[���N���b�N���Ă��������B\n�ŏ������蒼���ꍇ�͋N�����Ȃ����B\n�t�@�C�������蒼���ꍇ�͉E�N���b�N�B");
		DrawFormatString(0, 240, GetColor(0, 255, 0), "�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�z�C�[���N���b�N");
		DrawFormatString(0, 240, GetColor(0, 0, 255), "\n\n�@�@�@�@�@�@�@�@�@�@�@�@�@�E�N���b�N�B");
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
