#include "Title.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::CreateMap(const bool t_fileCSV)
{
	// �t�@�C���𐶐��y�ъJ��
	std::ofstream saveFile(p_filePath->c_str());

	// CSV�t�@�C����I������Ă�����
	if (t_fileCSV)
	{
		for (int i = 0; i != 2; ++i)
		{
			saveFile << "1,1,1,1" << std::endl;
		}
	}
	// TXT�t�@�C����I������Ă�����
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
	// �����I���t���b�O������
	endFlag = false;

	// �}�b�v�`�b�v�f�ނ����L����
	vp_mapChip = &t_mapChip;

	// ���݂̃V�[��������������
	stepNowNum = STEPNUMBER::chip;

	// �t�@�C���̃p�X�����L����
	p_filePath = &t_filePath;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Title::Draw()
{
	// �}�b�v�`�b�v�f�ނ������тɕ`�悷��
	for (int i = 0, n = static_cast<int>(vp_mapChip->size()); i != n; ++i)
	{
		DrawGraph(i * 15, 0, vp_mapChip->at(i), true);
	}


	// �V�[���ŕ`�悷����e��ύX����
	switch (stepNowNum)
	{

	// �}�b�v�`�b�v�f�ނ�ǉ����Ă��炤
	case STEPNUMBER::chip:

		// ��ł��}�b�v�`�b�v�f�ނ��h���b�O�A���h�h���b�v���Ă�����
		if (vp_mapChip->size() != 0)
		{
			// ������\������
			DrawFormatString(0, 240, GetColor(255, 255, 255), "�S���̑f�ނ���ꂽ���ʓ��Ńz�C�[���N���b�N���Ă��������B\n��蒼���ꍇ�͉E�N���b�N");
			DrawFormatString(0, 240, GetColor(0, 0, 255), "�@�@�@�@�@�@�@�@�@�@�@�@�@�@�z�C�[���N���b�N");
			DrawFormatString(0, 240, GetColor(0, 255, 0), "\n�@�@�@�@�@�@�@�E�N���b�N");
		}

		// �܂��}�b�v�`�b�v�f�ނ��h���b�O�A���h�h���b�v���Ă��Ȃ�������
		else
		{
			DrawFormatString(0, 0, GetColor(255, 255, 255), "�}�b�v�`�b�v�Ƃ��Ĉ��������摜��ID���Ƀh���b�O�A���h�h���b�v���Ă��������B");
		}

		break;


	// �}�b�v�̃t�@�C����ǉ����Ă��炤
	case STEPNUMBER::file:

		// ������\������
		DrawFormatString(0, 240, GetColor(255, 255, 255), "�ǂݍ��ރt�@�C��������ꍇ�͂�����h���b�O�A���h�h���b�v���Ă��������B\n�����ꍇ�͂��̂܂܃z�C�[���N���b�N���Ă��������B");
		DrawFormatString(0, 240, GetColor(0, 255, 0), "\n�@�@�@�@�@�@�@�@�@�z�C�[���N���b�N");

		break;


	// �}�b�v�̃t�@�C���𐶐�����ۂ̊g���q�����߂Ă��炤
	case STEPNUMBER::fileExc:

		// ������\������
		DrawFormatString(0, 240, GetColor(255, 255, 255), "�������ރt�@�C���̌`����.csv�Ȃ�z�C�[���N���b�N���Ă��������B\n.txt�Ȃ�E�N���b�N");
		DrawFormatString(0, 240, GetColor(0, 255, 0), "�@�@�@�@�@�@�@�@�@�@�@�@�@�@    �z�C�[���N���b�N");
		DrawFormatString(0, 240, GetColor(0, 0, 255), "\n�@�@    �E�N���b�N");

		break;


	// �}�b�v�G�f�B�^�Ɉڍs���邩�m�F����
	case STEPNUMBER::nextScene:

		// ������\������
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
	// �e�V�[���̍s��
	switch (stepNowNum)
	{

	// �}�b�v�`�b�v�f�ނ�ǉ����Ă��炤
	case STEPNUMBER::chip:

		// �}�E�X�z�C�[�����N���b�N���ꂽ��
		if (MouseData::GetClick(2) == 1)
		{
			// �V�[�����t�@�C���̒ǉ��Ɉړ�����
			stepNowNum = STEPNUMBER::file;
		}

		// �E�N���b�N���ꂽ��
		if (MouseData::GetClick(1) == 1)
		{
			// �ǉ������}�b�v�`�b�v�f�ނ�S���폜����
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


	// �}�b�v�̃t�@�C����ǉ����Ă��炤
	case STEPNUMBER::file:

		// �t�@�C�����ǉ�����Ă��Ȃ��Ƃ�
		if (p_filePath->empty())
		{
			// �}�E�X�z�C�[�����N���b�N���ꂽ��
			if (MouseData::GetClick(2) == 1)
			{
				// �}�b�v�t�@�C���𐶐�����ۂ̊g���q�����߂�V�[���ֈڍs
				stepNowNum = STEPNUMBER::fileExc;
			}
		}
		// �t�@�C�����ǉ����ꂽ��
		else
		{
			// �}�b�v�G�f�B�^�ֈڍs���邩�m�F����V�[���ֈڍs
			stepNowNum = STEPNUMBER::nextScene;
		}

		break;


	// �}�b�v�̃t�@�C���𐶐�����ۂ̊g���q�����߂Ă��炤
	case STEPNUMBER::fileExc:

		// �}�E�X�z�C�[�����N���b�N���ꂽ��
		if (MouseData::GetClick(2) == 1)
		{
			// �g���qCSV�Ƃ��ăt�@�C�����쐬����
			*p_filePath = "Map\\Save.csv";
			CreateMap(true);

			// �}�b�v�G�f�B�^�ֈڍs���邩�m�F����V�[���ֈڍs
			stepNowNum = STEPNUMBER::nextScene;
		}

		// �E�N���b�N���ꂽ��
		if (MouseData::GetClick(1) == 1)
		{
			// �g���qTXT�Ƃ��ăt�@�C�����쐬����
			*p_filePath = "Map\\Save.txt";
			CreateMap(false);

			// �}�b�v�G�f�B�^�ֈڍs���邩�m�F����V�[���ֈڍs
			stepNowNum = STEPNUMBER::nextScene;
		}

		break;


	// �}�b�v�G�f�B�^�Ɉڍs���邩�m�F����
	case STEPNUMBER::nextScene:

		// �}�E�X�z�C�[�����N���b�N���ꂽ��
		if (MouseData::GetClick(2) == 1)
		{
			// �V�[�����}�b�v�G�f�B�^�Ɉڍs����
			BASICPARAM::e_nowScene = ESceneNumber::MAPEDITOR;
		}

		// �E�N���b�N���ꂽ��
		if (MouseData::GetClick(1) == 1)
		{
			// �t�@�C���̃p�X������������
			*p_filePath = "";

			// �t�@�C���̒ǉ��V�[���ɖ߂�
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
	// ���݂̃V�[���Ńh���b�O�A���h�h���b�v�̏�����ύX
	switch (stepNowNum)
	{

	// �}�b�v�`�b�v�f�ނ̎�
	case STEPNUMBER::chip:

		// �}�b�v�`�b�v�f�ނ�ǂݍ���
		vp_mapChip->push_back(LoadGraph(t_path));

		break;

		
	// �t�@�C���̒ǉ��̎�
	case STEPNUMBER::file:

		// �t�@�C���̃p�X���擾����
		*p_filePath = t_path;

		break;


	default:
		break;
	}
}
