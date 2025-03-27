/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#include "AppFrame.h"
#include "VariableDefine.h"

/* �V�[�� */
#include "SceneLoad.h"
#include "SceneTitle.h"
#include "SceneLogo.h"

/* �f�[�^���X�g */
#include "DataList_Input.h"
#include "DataList_Sound.h"
#include "DataList_Model.h"
#include "DataList_Image.h"
#include "DataList_Effect.h"
#include "DataList_StageStatus.h"
#include "DataList_Option.h"

/* AppFrame�Ŏg�p����֐��̒�` */

// �V�[���̐ݒ�
namespace SCENE_SET
{
	// �Q�[���N�����̃V�[�����Z�b�g
	void	SetFastScene()
	{
		/* ���[�h��ʒǉ��t���O��L���� */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* �^�C�g���V�[����ǉ� */
		gpSceneServer->AddSceneReservation(new SceneTitle());

		/* ���S�V�[����ǉ� */
		gpSceneServer->AddSceneReservation(new SceneLogo());
	}

	// ���[�h�V�[�����Z�b�g
	void	SetLoadScene()
	{
		/* ���[�h�V�[����ǉ� */
		gpSceneServer->AddSceneReservation(new SceneLoad());
	}
}

// ������
namespace PROJECT_INIT
{
	// �v���W�F�N�g����������
	void	Init()
	{
		/* �f�[�^���X�g�쐬 */
		{
			/* �f�[�^���X�g�T�[�o�[��"�v���C���[���͊Ǘ�"��ǉ� */
			gpDataListServer->AddDataList(new DataList_Input());

			/* �f�[�^���X�g�T�[�o�[��"3D���f���Ǘ�"��ǉ� */
			gpDataListServer->AddDataList(new DataList_Model());

			/* �f�[�^���X�g�T�[�o�[��"�摜���\�[�X�Ǘ�"��ǉ� */
			gpDataListServer->AddDataList(new DataList_Image());

			/* �f�[�^���X�g�T�[�o�[��"�G�t�F�N�g���\�[�X�Ǘ�"��ǉ� */
			gpDataListServer->AddDataList(new DataList_Effect());

			/* �f�[�^���X�g�T�[�o�[��"�X�e�[�W��ԊǗ�"��ǉ� */
			gpDataListServer->AddDataList(new DataList_StageStatus());

			/* �f�[�^���X�g�T�[�o�[��"�I�v�V�����ݒ�Ǘ�"��ǉ� */
			gpDataListServer->AddDataList(new DataList_Option());

			/* �f�[�^���X�g�T�[�o�[��"�T�E���h�Ǘ�"��ǉ� */
			// ���T�E���h�Ǘ��ł́A�I�v�V�����ݒ�Ǘ����擾���邽�߁A�I�v�V�����ݒ�Ǘ�����ɒǉ�����
			gpDataListServer->AddDataList(new DataList_Sound());
		}
	
		/* �f�[�^���X�g�擾 */
		{
			/* ���ǉ�����"�v���C���[���͊Ǘ�"���擾 */
			gpDataList_Input = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));

			/* ���ǉ�����"�T�E���h�Ǘ�"���擾 */
			gpDataList_Sound = dynamic_cast<DataList_Sound*>(gpDataListServer->GetDataList("DataList_Sound"));
		}

		/* �t�H���g�ݒ� */
		{
			/* �t�H���g�n���h�����擾(�}�L�i�X/�ʏ�T�C�Y) */
			giFontHandle_Small					= LoadFontDataToHandle("resource/FontData/Makinas-4-Flat.dft", 0);

			/* �t�H���g�n���h�����擾(�}�L�i�X/���T�C�Y) */
			giFontHandle_Medium					= CreateFontToHandle(NULL, 60, 9, DX_FONTTYPE_ANTIALIASING, -1, giFontHandle_Small);

			/* �t�H���g�n���h�����擾(�}�L�i�X/��T�C�Y) */
			giFontHandle_Large					= CreateFontToHandle(NULL, 90, 9, DX_FONTTYPE_ANTIALIASING, -1, giFontHandle_Small);

			/* �t�H���g�n���h�����擾(�̂Ƃ����/�Z���t�e�L�X�g�p) */
			giFontHandle_NotoSerifJP_Medium		= LoadFontDataToHandle("resource/FontData/NotoSerifJP-Medium.dft", 0);

			/* �t�H���g�n���h�����擾(�̂Ƃ����/�l�[���^�O�A�I�v�V�����p) */
			giFontHandle_NotoSerifJP_SemiBold	= LoadFontDataToHandle("resource/FontData/NotoSerifJP-SemiBold.dft", 0);
		}
	}
}
