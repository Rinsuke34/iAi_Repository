/* 2025.03.27 ��򕗏� �t�@�C���쐬 */

#include "Gimmick_TutorialDraw.h"

/* �`���[�g���A���`�ʒn�_�N���X�̒�` */
// �R���X�g���N�^
Gimmick_TutorialDraw::Gimmick_TutorialDraw() : PlatformBase()
{
	/* �f�[�^���X�g���擾 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* ������ */
	this->iDrawTutorialNo = 0;	// �`�ʂ���`���[�g���A���ԍ�
}

// ������
void Gimmick_TutorialDraw::Initialization()
{
	/* �R���W�������Z�b�g */
	this->stCollisionSqhere.vecSqhere		= this->vecPosition;
	this->stCollisionSqhere.fSqhereRadius	= 800.0f * this->vecScale.x;
}

// �X�V
void Gimmick_TutorialDraw::Update()
{
	/* �v���C���[���擾 */
	CharacterBase* pPlayer = this->ObjectList->GetCharacterPlayer();

	/* �v���C���[�Ƃ̐ڐG���� */
	if (pPlayer->HitCheck(this->stCollisionSqhere) == true)
	{
		// �ڐG���Ă���ꍇ
		/* �V�[��"UI(�`���[�g���A��)"���쐬 */
		SceneUi_Tutorial* pSceneUi_Tutorial = new SceneUi_Tutorial();
		gpSceneServer->AddSceneReservation(pSceneUi_Tutorial);

		/* �`���[�g���A���ԍ���ݒ肷�� */
		pSceneUi_Tutorial->SetTutorialNo(this->iDrawTutorialNo);

		/* ���������������s���� */
		pSceneUi_Tutorial->Initialization();

		/* �폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
	}
}

// �����蔻��`��
void Gimmick_TutorialDraw::CollisionDraw()
{
	/* �����蔻���`�� */
	int iColor = GetColor(255, 0, 0);
	DrawSphere3D(this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.fSqhereRadius, 16, iColor, iColor, FALSE);
}
