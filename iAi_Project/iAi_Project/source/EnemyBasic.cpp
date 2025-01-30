/* 2025.01.27 ��򕗏� �t�@�C���쐬 */

#include "EnemyBasic.h"

/* �f�[�^���X�g */
// ���z�Q�Ƒ΍�ł����Œ�`����
#include "DataList_Object.h"

/* ��{�G�l�~�[�N���X�̒�` */

// �R���X�g���N�^
EnemyBasic::EnemyBasic() : EnemyBase()
{
	/* ������ */
	this->iPlayerLockOnType	= PLAYER_LOCKON_NONE;	// ���b�N�I������Ă��Ȃ���Ԃɂ���
	this->iCoreFrameNo		= -1;					// �R�A�t���[���ԍ���������
}

// �f�X�g���N�^
EnemyBasic::~EnemyBasic()
{
	/* �v���C���[�̃R���{�����Z���p�����ԃ��Z�b�g */
	{
		/* �f�[�^���X�g�擾 */
		DataList_Score* ScoreList = dynamic_cast<DataList_Score*>(gpDataListServer->GetDataList("DataList_Score"));

		/* �v���C���[�̃R���{�����Z */
		ScoreList->SetPlayerComboNowCount(ScoreList->iGetPlayerComboNowCount() + 1);

		/* �v���C���[�̃R���{�p�����ԃ��Z�b�g */
		ScoreList->SetPlayerComboDuration(PLAYER_COMBO_DURATION);
	}

	/* �����G�t�F�N�g���� */
	{
		/* ���Ԍo�߂ō폜�����G�t�F�N�g��ǉ� */
		EffectSelfDelete* AddEffect = new EffectSelfDelete();

		/* �G�t�F�N�g�ǂݍ��� */
		AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_die03")));

		/* �G�t�F�N�g�̍��W�ݒ� */
		AddEffect->SetPosition(this->vecPosition);

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		AddEffect->SetRotation(this->vecRotation);

		/* �G�t�F�N�g�̍폜�����܂ł̎��Ԃ�ݒ� */
		AddEffect->SetDeleteCount(30);

		/* �G�t�F�N�g�̏����� */
		AddEffect->Initialization();

		/* ���X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(AddEffect);
		}
	}
}

// �R�A�t���[���ԍ��擾
void EnemyBasic::LoadCoreFrameNo()
{
	/* �R�A�t���[���ԍ����擾 */
	this->iCoreFrameNo = MV1SearchFrame(this->iModelHandle, "Core");
}
