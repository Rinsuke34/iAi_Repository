/* 2025.03.16 ��򕗏� �t�@�C���쐬 */

#include "Gimmick_CheckPoint.h"

/* ���ԃ|�C���g�N���X�̒�` */
// �R���X�g���N�^
Gimmick_CheckPoint::Gimmick_CheckPoint() : PlatformBase()
{
	/* �f�[�^���X�g���擾 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/CheckPoint/CheckPoint");
	}

	/* ������ */
	this->bActiveFlg		= false;
	this->bStartPositionFlg = false;
}

// ������
void Gimmick_CheckPoint::Initialization()
{
	PlatformBase::Initialization();

	/* �R���W�������Z�b�g */
	this->stCollisionSqhere.vecSqhere		= this->vecPosition;
	this->stCollisionSqhere.fSqhereRadius	= 200.0f;

	/* �X�^�[�g�n�_�ł��邩�m�F */
	if (this->bStartPositionFlg == true)
	{
		// �X�^�[�g�n�_�ł���ꍇ
		/* �A�N�e�B�u��Ԃɐݒ肷�� */
		this->bActiveFlg = true;
	}
	else
	{
		// �X�^�[�g�n�_�łȂ��ꍇ
		/* ��A�N�e�B�u��Ԃɐݒ肷�� */
		this->bActiveFlg = false;
	}
}

// �X�V
void Gimmick_CheckPoint::Update()
{
	/* �A�N�e�B�u��ԂłȂ����m�F */
	if (this->bActiveFlg == false)
	{
		// �A�N�e�B�u��ԂłȂ��ꍇ
		/* �v���C���[���擾 */
		CharacterBase* pPlayer = this->ObjectList->GetCharacterPlayer();

		/* �v���C���[�Ƃ̐ڐG���� */
		if (pPlayer->HitCheck(this->stCollisionSqhere) == true)
		{
			// �ڐG���Ă���ꍇ
			/* �A�N�e�B�u��Ԃɐݒ肷�� */
			this->bActiveFlg = true;
		}
	}
}

// ���Z�b�g����
void Gimmick_CheckPoint::Reset()
{
	/* ���̃I�u�W�F�N�g�̏��������������s���� */
	Initialization();
}

// �����`��
void Gimmick_CheckPoint::BloomDraw()
{
	/* �A�N�e�B�u��Ԃł��邩�m�F */
	if (this->bActiveFlg == true)
	{
		// �A�N�e�B�u��Ԃł���ꍇ
		/* �����`�� */
		// ���F�ŕ`��
		{
			/* �t���[�������擾 */
			int iBackUpFrames = MV1GetFrameNum(this->iModelHandle);

			/* ���̐F��ۑ� */
			std::vector<COLOR_F> vecOriginalDifColor(iBackUpFrames);
			std::vector<COLOR_F> vecOriginalSpcColor(iBackUpFrames);
			std::vector<COLOR_F> vecOriginalEmiColor(iBackUpFrames);
			std::vector<COLOR_F> vecOriginalAmbColor(iBackUpFrames);

			for (int i = 0; i < iBackUpFrames; i++)
			{
				/* �t���[���̐F���擾 */
				vecOriginalDifColor[i] = MV1GetFrameDifColorScale(this->iModelHandle, i);
				vecOriginalSpcColor[i] = MV1GetFrameSpcColorScale(this->iModelHandle, i);
				vecOriginalEmiColor[i] = MV1GetFrameEmiColorScale(this->iModelHandle, i);
				vecOriginalAmbColor[i] = MV1GetFrameAmbColorScale(this->iModelHandle, i);
			}

			/* �^�[�Q�b�g�ȊO�̐F�����ɐݒ� */
			for (int i = 0; i < iBackUpFrames; i++)
			{
				/* �����t���[���ł͂Ȃ����m�F */
				if (std::find(aiLightFrameNo.begin(), aiLightFrameNo.end(), i) != aiLightFrameNo.end() == false)
				{
					// �����t���[���ł͂Ȃ��ꍇ
					/* �t���[���̐F�����F�ɐݒ� */
					MV1SetFrameDifColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
					MV1SetFrameSpcColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
					MV1SetFrameEmiColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
					MV1SetFrameAmbColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
				}
				else
				{
					// �����t���[���ł���ꍇ
					/* �t���[���̐F��F�ɐݒ� */
					MV1SetFrameDifColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 1.f, 1.f));
				}
			}

			/* ���f���`�� */
			MV1DrawModel(this->iModelHandle);

			/* ���̐F�ɖ߂� */
			for (int i = 0; i < iBackUpFrames; i++)
			{
				/* �t���[���̐F�����̐F�ɐݒ� */
				MV1SetFrameDifColorScale(this->iModelHandle, i, vecOriginalDifColor[i]);
				MV1SetFrameSpcColorScale(this->iModelHandle, i, vecOriginalSpcColor[i]);
				MV1SetFrameEmiColorScale(this->iModelHandle, i, vecOriginalEmiColor[i]);
				MV1SetFrameAmbColorScale(this->iModelHandle, i, vecOriginalAmbColor[i]);
			}
		}
	}
	else
	{
		// �A�N�e�B�u��ԂłȂ��ꍇ
		/* �����`�� */
		// ���f�t�H���g�̐F(��)�ŕ`��
		PlatformBase::BloomDraw();
	}
}

// �����蔻��`��
void Gimmick_CheckPoint::CollisionDraw()
{
	/* �����蔻���`�� */
	int iColor = GetColor(255, 0, 0);
	DrawSphere3D(this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.fSqhereRadius, 16, iColor, iColor, FALSE);
}
