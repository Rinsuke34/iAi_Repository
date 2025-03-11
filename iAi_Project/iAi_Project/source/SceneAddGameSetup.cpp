/* 2025.02.27 �t�@�C���쐬 ��򕗏� */

#include <vector>
#include <iostream>
#include "SceneAddGameSetup.h"

/* �V�[��"�Q�[��"�ǉ��Z�b�g�A�b�v�̒�` */
// �R���X�g���N�^
SceneAddSceneGameSetup::SceneAddSceneGameSetup() : SceneBase("AddSceneGameSetup", 10, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�G�t�F�N�g���\�[�X�Ǘ�"��ǉ� */
		this->EffectList = dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));
	}

	/* �S�G�t�F�N�g�̎��O�ǂݍ��� */
	PreloadAllEffects();
}

// �v�Z
void SceneAddSceneGameSetup::Process()
{
	/* ���s�V�[���폜�t���O��L���� */
	gpSceneServer->SetDeleteCurrentSceneFlg(true);

	/* �V�[��"�Q�[��"��ǉ� */
	gpSceneServer->AddSceneReservation(new SceneGame());
}

// �S�G�t�F�N�g�̎��O�ǂݍ���
void SceneAddSceneGameSetup::PreloadAllEffects()
{
	/* �G�t�F�N�g�t�@�C���ɕۑ����ꂽ�S�ẴG�t�F�N�g�����[�h���� */
	// ��Effekseer�̃G�t�F�N�g�͔񓯊��ǂݍ��݂ɑΉ����Ă��Ȃ����߁A�񓯊��ǂݍ��݂͍s��Ȃ�

	/* �G�t�F�N�g�t�H���_(resource/EffectData)���̑S�Ẵt�H���_�����擾����z�� */
	std::vector<std::string> aEffectFolderName;

	/* �擾�����t�@�C���̏���ۑ�����ϐ� */
	WIN32_FIND_DATA findFileData;

	/* �t�H���_�����p�̃n���h�� */
	HANDLE hFindFile = FindFirstFile("resource/EffectData\\*", &findFileData);

	/* �t�H���_�����݂���Ȃ�A�t�H���_�����擾���� */
	while (hFindFile != INVALID_HANDLE_VALUE)
	{
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			/* �t�H���_����std::string�^�ɕϊ� */
			std::string folderName = findFileData.cFileName;

			/* �t�@�C���ł͂Ȃ����m�F("."���邢��".."�������Ă���Ȃ�t�@�C���Ɣ���) */
			if (folderName != "." && folderName != "..")
			{
				// �t�@�C���ł͂Ȃ��ꍇ(�t�H���_�̏ꍇ)
				/* �t�H���_����z��ɒǉ� */
				aEffectFolderName.push_back(findFileData.cFileName);
			}
		}

		/* ���̃t�@�C�������� */
		if (FindNextFile(hFindFile, &findFileData) == false)
		{
			// �t�@�C����������Ȃ������ꍇ
			/* �t�@�C�������I�� */
			break;
		}
	}

	/* �����n���h������� */
	FindClose(hFindFile);

	/* �ǂݍ��񂾃G�t�F�N�g�t�H���_�ɑΉ������G�t�F�N�g��ǂݍ��� */
	for (auto& effectFolderName : aEffectFolderName)
	{
		/* �G�t�F�N�g��ǂݍ��� */
		this->EffectList->LoadEffect(effectFolderName + "/" + effectFolderName);
	}
}
