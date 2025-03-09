/* 2025.02.10 �ΐ�q�� �t�@�C���쐬 */
#include "GimmickDisappear.h"

// �R���X�g���N�^
GimmickDisappear::GimmickDisappear() : PlatformBase()
{
	/* �f�[�^���X�g */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));
		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Object/DisappearFloor/DisappearFloor");
	}

	//�v���C���[�̏����擾
	this->pPlayer = ObjectList->GetCharacterPlayer();

	//�M�~�b�N�̏��Ŏ���
	this->iDisappearTime = GIMMICK_DISAPPEAR_TIME;

	//�M�~�b�N�e�N�X�`���ύX�J�E���g
	this->iTextureFirstChangeCount = GIMMICK_TEXTURE_CHANGE_FIRST_COUNT;

	//�M�~�b�N�e�N�X�`���ύX�J�E���g
	this->iTextureSecondChangeCount = GIMMICK_TEXTURE_CHANGE_SECOND_COUNT;

	// �e�N�X�`���̓ǂݍ���
	this->textureOrangeHandle = LoadGraph("resource/ModelData/Gimmick/Orange.png");

	// �e�N�X�`���̓ǂݍ���
	this->textureRedHandle = LoadGraph("resource/ModelData/Gimmick/aka.png");
}

// �f�X�g���N�^
GimmickDisappear::~GimmickDisappear()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

//�M�~�b�N�̏���
void GimmickDisappear::ProcessGimmick()
{
	//�v���C���[�̍��W���擾
	VECTOR playerPos = pPlayer->vecGetPosition();

	//�v���C���[���M�~�b�N�̏�ɏ���Ă��邩�m�F
	if (playerPos.x > this->vecPosition.x - 50 && playerPos.x < this->vecPosition.x + 50 &&
		playerPos.y > this->vecPosition.y - 50 && playerPos.y < this->vecPosition.y + 50 &&
		playerPos.z > this->vecPosition.z - 50 && playerPos.z < this->vecPosition.z + 50)
	{
		//�v���C���[���M�~�b�N�̏�ɏ���Ă���ꍇ
		/* �G�t�F�N�g�ǉ� */

		/*�����G�t�F�N�g�𐶐� */
		this->pEffectSine = new EffectManualDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		this->pEffectSine->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_g_mine_sine/FX_g_mine_sine")));

		/* �G�t�F�N�g�̍��W�ݒ� */
		this->pEffectSine->SetPosition(this->vecPosition);

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		this->pEffectSine->SetRotation(this->vecRotation);

		/* �G�t�F�N�g�̏����� */
		this->pEffectSine->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(this->pEffectSine);
		}
		//�e�N�X�`���̕ύX�J�E���g�����炷
		iTextureFirstChangeCount--;

		//�e�N�X�`���̕ύX�J�E���g��0�ȉ��ɂȂ������m�F
		if (iTextureFirstChangeCount <= 0)
		{
			//�e�N�X�`���̕ύX�J�E���g��0�ȉ��ɂȂ����ꍇ
			// 0�Ԃ̃e�N�X�`�����I�����W�e�N�X�`���ɕύX
			MV1SetTextureGraphHandle(iModelHandle, 0, textureOrangeHandle, true);

			//�Z�J���h�e�N�X�`���̕ύX�J�E���g�����炷
			iTextureSecondChangeCount--;

			//�Z�J���h�e�N�X�`���̕ύX�J�E���g��0�ȉ��ɂȂ������m�F
			if (iTextureSecondChangeCount <= 0)
		{
				//�Z�J���h�e�N�X�`���̕ύX�J�E���g��0�ȉ��ɂȂ����ꍇ

				//�M�~�b�N�̏��Ŏ��ԃJ�E���g�𑝂₷
			iDisappearTimeCount++;

				// 0�Ԃ̃e�N�X�`����ԃe�N�X�`���ɕύX
				MV1SetTextureGraphHandle(iModelHandle, 0, textureRedHandle, true);
			
				//PlayMovieToGraph(textureHandle); // �Đ��J�n

				//�M�~�b�N�̏��Ŏ��ԃJ�E���g����萔�ɂȂ������m�F
			if (iDisappearTimeCount == GIMMICK_DISAPPEAR_TIME)
			{
				//�M�~�b�N�̏��Ŏ��ԃJ�E���g����萔�ɂȂ����ꍇ
				//�Đ��I��
				//	PauseMovieToGraph(textureHandle);
				
				//�M�~�b�N�����ł�����
				this->SetDeleteFlg(true);
			}
		}
	}
}
}

// �X�V
void GimmickDisappear::Update()
{
	//�M�~�b�N�̏���
	ProcessGimmick();
}
