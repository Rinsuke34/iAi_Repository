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
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/DisappearFloor/DisappearFloor");
	}

	//�v���C���[�̏����擾
	this->pPlayer = ObjectList->GetCharacterPlayer();

	//�M�~�b�N�̏��Ŏ���
	this->iDisappearTime = GIMMICK_DISAPPEAR_TIME;

	//�M�~�b�N�e�N�X�`���ύX�J�E���g
	this->iTextureFirstChangeCount = GIMMICK_TEXTURE_CHANGE_FIRST_COUNT;

	//�M�~�b�N�e�N�X�`���ύX�J�E���g
	this->iTextureSecondChangeCount = GIMMICK_TEXTURE_CHANGE_SECOND_COUNT;

	//�M�~�b�N�̃X�|�[���J�E���g
	this->iSpawnCount = GIMMICK_SPAWN_COUNT;

	/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
	DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));
	// �e�N�X�`���̓ǂݍ���
	this->textureOrangeHandle = *ImageList->piGetImage("DisappearFloor/Orange");

	// �e�N�X�`���̓ǂݍ���
	this->textureRedHandle = *ImageList->piGetImage("DisappearFloor/Red");

	//���Ńt���O
	this->bDisappearFlg = false;
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

	////�v���C���[���M�~�b�N�̏�ɏ���Ă��邩�����f���̃t���[��0�Ԃ̍��W���擾���Ċm�F
	//VECTOR vecFramePos = MV1GetFramePosition(iModelHandle, 0);
	//if (playerPos.x >= vecFramePos.x - 200 && playerPos.x <= vecFramePos.x + 200 &&
	//	playerPos.y >= vecFramePos.y - 50 && playerPos.y <= vecFramePos.y + 55 &&
	//	playerPos.z >= vecFramePos.z - 300 && playerPos.z <= vecFramePos.z + 300)
		if (this->bRidePlayerFlg == true)
	{
		//�v���C���[���M�~�b�N�̏�ɏ���Ă���ꍇ
		//�e�N�X�`���̕ύX�J�E���g�����炷
		iTextureFirstChangeCount--;
;

		//�e�N�X�`���̕ύX�J�E���g��0�ȉ��ɂȂ������m�F
		if (iTextureFirstChangeCount <= 0)
		{
			//�e�N�X�`���̕ύX�J�E���g��0�ȉ��ɂȂ����ꍇ
			// 0�Ԃ̃e�N�X�`�����I�����W�e�N�X�`���ɕύX
			MV1SetTextureGraphHandle(iModelHandle, 0, textureOrangeHandle, true);
			MV1SetTextureGraphHandle(iModelHandle, 1, textureOrangeHandle, true);

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
				MV1SetTextureGraphHandle(iModelHandle, 1, textureRedHandle, true);
			

				//�M�~�b�N�̏��Ŏ��ԃJ�E���g����萔�ɂȂ������m�F
				if (iDisappearTimeCount == GIMMICK_DISAPPEAR_TIME)
				{
					//�M�~�b�N�̏��Ŏ��ԃJ�E���g����萔�ɂȂ����ꍇ
				
					this->bDisappearFlg = true;
				
					//�M�~�b�N������
					MV1SetVisible(this->iModelHandle, FALSE);

					//�R���W�������폜
					MV1TerminateCollInfo(this->iModelHandle, 0);

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
