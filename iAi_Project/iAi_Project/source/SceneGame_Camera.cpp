/* 2024.01.02 ��򕗏� �t�@�C���ǉ� */

#include "SceneGame_Camera.h"

/* �V�[���u�Q�[�� - �J�����v�̐錾 */

// �R���X�g���N�^
SceneGame_Camera::SceneGame_Camera() : SceneBase("Game_Camera", 1, false)
{
	/* �񓯊��ǂݍ��݂�L�������� */
	SetUseASyncLoadFlag(true);

	/* "�I�u�W�F�N�g�Ǘ�"���擾 */
	this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	/* "�v���C���[���"���擾 */
	this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

	/* �񓯊��ǂݍ��݂𖳌������� */
	SetUseASyncLoadFlag(false);
}

// �f�X�g���N�^
SceneGame_Camera::~SceneGame_Camera()
{

}

// �v�Z
void SceneGame_Camera::Process()
{
	/* 3D��{�ݒ� */
	{
		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);
		SetUseBackCulling(TRUE);
	}
	
	/* �v���C���[���W�擾 */
	VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();	

	/* �J���������_�ݒ� */
	VECTOR vecCameraTarget = VAdd(vecPlayerPos, VGet(0, 100, 0));
	this->PlayerStatusList->SetCameraTarget(vecCameraTarget);

	/* ���_�ύX�ɕK�v�ȃf�[�^�擾 */
	float fCameraAngleX				= this->PlayerStatusList->fGetCameraAngleX();			// X����]��
	float fCameraAngleY				= this->PlayerStatusList->fGetCameraAngleY();			// Y����]��
	float fCameraRotationalSpeed	= this->PlayerStatusList->fGetCameraRotationalSpeed();	// ��]���x

	/* ���͂���J������]�ʂ��擾 */
	/* �}�E�X */
	{
		fCameraAngleX += gstKeyboardInputData.iMouseMoveX * fCameraRotationalSpeed;
		fCameraAngleY += gstKeyboardInputData.iMouseMoveY * fCameraRotationalSpeed;
	}
	
	/* �R���g���[���[ */
	{
		float fCameraSensitivity = 0.1f;	// �J�������x

		fCameraAngleX += fCameraSensitivity * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_RIGHT]);
		fCameraAngleY += fCameraSensitivity * PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_RIGHT]);
	}

	/* Y���̉�]�p�x���� */
	{
		float fAngleLimitUp		= this->PlayerStatusList->fGetCameraAngleLimitUp();		// ������̐����p�x
		float fAngleLimitDown	= this->PlayerStatusList->fGetCameraAngleLimitDown();	// �������̐����p�x

		if (fCameraAngleY > fAngleLimitUp)		{ fCameraAngleY = fAngleLimitUp; }		// ������̐����p�x�𒴂����琧���p�x�ɐݒ�
		if (fCameraAngleY < fAngleLimitDown)	{ fCameraAngleY = fAngleLimitDown; }	// �������̐����p�x�𒴂����琧���p�x�ɐݒ�
	}

	/* ��]�ʂ��X�V */
	{
		this->PlayerStatusList->SetCameraAngleX(fCameraAngleX);
		this->PlayerStatusList->SetCameraAngleY(fCameraAngleY);
	}

	/* �J�������W�ݒ� */
	{
		float fRadius	= this->PlayerStatusList->fGetCameraRadius();				// �����_����̋���
		float fCameraX	= fRadius * +cosf(fCameraAngleX)	+ vecCameraTarget.x;	// X���W
		float fCameraY	= fRadius * -sinf(fCameraAngleY)	+ vecCameraTarget.y;	// Y���W
		float fCameraZ	= fRadius * +sinf(fCameraAngleX)	+ vecCameraTarget.z;	// Z���W

		this->PlayerStatusList->SetCameraPosition(VGet(fCameraX, fCameraY, fCameraZ));
	}

	/* �J�����ݒ� */
	{
		SetCameraPositionAndTargetAndUpVec(this->PlayerStatusList->vecGetCameraPosition(), this->PlayerStatusList->vecGetCameraTarget(), this->PlayerStatusList->vecGetCameraUp());
	}
}

// �`��
void SceneGame_Camera::Draw()
{
	/* �e�X�g�p */
	VECTOR vecTest;

	// �J�����̏�����擾
	vecTest = this->PlayerStatusList->vecGetCameraUp();
	DrawFormatString(800, 16 * 0, GetColor(255, 255, 255), "�J��������� X:%f, Y:%f, Z:%f", vecTest.x, vecTest.y, vecTest.z);

	// �J�����̍��W�擾
	vecTest = this->PlayerStatusList->vecGetCameraPosition();
	DrawFormatString(800, 16 * 1, GetColor(255, 255, 255), "�J�������W X:%f, Y:%f, Z:%f", vecTest.x, vecTest.y, vecTest.z);

	// �J�����̒����_�擾
	vecTest = this->PlayerStatusList->vecGetCameraTarget();
	DrawFormatString(800, 16 * 2, GetColor(255, 255, 255), "�J���������_ X:%f, Y:%f, Z:%f", vecTest.x, vecTest.y, vecTest.z);

	// �J�����̒��S�_����̋����擾
	DrawFormatString(800, 16 * 3, GetColor(255, 255, 255), "���S����̋���:%f", this->PlayerStatusList->fGetCameraRadius());

	// �J������X����]�ʎ擾
	DrawFormatString(800, 16 * 4, GetColor(255, 255, 255), "�J������X����]��:%f", this->PlayerStatusList->fGetCameraAngleX());

	// �J������Y����]�ʎ擾
	DrawFormatString(800, 16 * 5, GetColor(255, 255, 255), "�J������Y����]��:%f", this->PlayerStatusList->fGetCameraAngleY());

	// �J�����̉�]���x�擾
	DrawFormatString(800, 16 * 6, GetColor(255, 255, 255), "�J�����̉�]���x:%f", this->PlayerStatusList->fGetCameraRotationalSpeed());

	// �}�E�X�ړ���
	DrawFormatString(800, 16 * 7, GetColor(255, 255, 255), "�}�E�X�ړ���X:%d", gstKeyboardInputData.iMouseMoveX);
	DrawFormatString(800, 16 * 8, GetColor(255, 255, 255), "�}�E�X�ړ���Y:%d", gstKeyboardInputData.iMouseMoveY);


	/* �����_���W�擾 */
	VECTOR vecTargetPos = this->PlayerStatusList->vecGetCameraTarget();

	/* ���_���S�`�� */
	DrawLine3D(VAdd(vecTargetPos, VGet(-50, 0, 0)), VAdd(vecTargetPos, VGet(50, 0, 0)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(vecTargetPos, VGet(0, -50, 0)), VAdd(vecTargetPos, VGet(0, 50, 0)), GetColor(0, 255, 0));
	DrawLine3D(VAdd(vecTargetPos, VGet(0, 0, -50)), VAdd(vecTargetPos, VGet(0, 0, 50)), GetColor(0, 0, 255));

	/* ���_���S�`�� */
	DrawLine3D(VGet(-50, 0, 0), VGet(50, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -50, 0), VGet(0, 50, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -50), VGet(0, 0, 50), GetColor(0, 0, 255));
}
