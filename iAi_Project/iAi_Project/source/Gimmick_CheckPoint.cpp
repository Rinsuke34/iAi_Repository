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

	/* �摜�擾 */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �ʏ펞(��A�N�e�B�u��)�̔����F */
		this->piGrHandle_NormalRight = ImageList->piGetImage("SpawnPoint/NormalRight");

		/* �A�N�e�B�u���̔����F */
		this->piGrHandle_ActiveRight = ImageList->piGetImage("SpawnPoint/ActiveRight");
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

		/* �����t���[�����A�N�e�B�u���̔����F�ɐݒ肷�� */
		MV1SetTextureGraphHandle(this->iModelHandle, this->aiLightFrameNo[0], *this->piGrHandle_ActiveRight, true);
	}
	else
	{
		// �X�^�[�g�n�_�łȂ��ꍇ
		/* ��A�N�e�B�u��Ԃɐݒ肷�� */
		this->bActiveFlg = false;

		/* �����t���[����ʏ펞�̔����F�ɐݒ肷�� */
		MV1SetTextureGraphHandle(this->iModelHandle, this->aiLightFrameNo[0], *this->piGrHandle_NormalRight, true);
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

			/* �����t���[�����A�N�e�B�u���̔����F�ɐݒ肷�� */
			MV1SetTextureGraphHandle(this->iModelHandle, this->aiLightFrameNo[0], *this->piGrHandle_ActiveRight, true);
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
