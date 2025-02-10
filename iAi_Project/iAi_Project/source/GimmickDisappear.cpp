/* 2025.02.10 �ΐ�q�� �t�@�C���쐬 */
#include "GimmickDisappear.h"

// �R���X�g���N�^
GimmickDisappear::GimmickDisappear() : PlatformBasic()
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
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/cube");
	}
	this->pPlayer = ObjectList->GetCharacterPlayer();

	//�M�~�b�N�̏��Ŏ���
	this->iDisappearTime = GIMMICK_DISAPPEAR_TIME;

	//�M�~�b�N�e�N�X�`���ύX�J�E���g
	this->iTextureChangeCount = GIMMICK_TEXTURE_CHANGE_COUNT;

	this->textureHandle = LoadGraph("resource/ModelData/Gimmick/�{��.mp4");
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
		//180�t���[����ɃM�~�b�N�����ł�����
		iTextureChangeCount--;
		if (iTextureChangeCount <= 0)
		{
			iDisappearTimeCount++;
			PlayMovieToGraph(textureHandle); // �Đ��J�n

			// �V�����e�N�X�`����ݒ�
			MV1SetTextureGraphHandle(iModelHandle, 0, textureHandle, true);
			
			if (iDisappearTimeCount == GIMMICK_DISAPPEAR_TIME)
			{
				//�Đ��I��
				PauseMovieToGraph(textureHandle);
				
				//�M�~�b�N�����ł�����
				this->SetDeleteFlg(true);
			}
		}
	}
}

// �X�V
void GimmickDisappear::Update()
{
	ProcessGimmick();
}
