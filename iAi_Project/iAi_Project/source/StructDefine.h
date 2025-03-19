/* 2024.01.03 ��򕗏� �t�@�C���쐬 */

#pragma once

/* �O���Q�� */
// ��AppFrame�Œ�`����Ă��Ȃ��N���X���g�p����ꍇ�A�z�Q�Ƒ΍�Ɏ��{����B
class Enemy_Basic;

/* �v���W�F�N�g�Ŏg�p����\���̂̐錾 */

// ���W(2D��)
// ���ǐ�����̂��߁A���̂ɐ������g�p
struct st2DPosition
{
	int ix;
	int iy;
};

// �w��ӏ��ƃG�l�~�[�̋�������p�̍\����
struct NearEnemy
{
	Enemy_Basic* pEnemy;		// �G�l�~�[�̃|�C���^
	float fDistance;		// ��ʒ��S����̋���(�y�ʉ��̂��ߍ��W�̍��̓��)
};

// ��b�p�[�g�p�̃e�L�X�g�f�[�^
struct TEXT_DATA
{
	std::string	aText;				// ����
	int			iFocusCharacter;	// �����G����O�Ɏ����Ă���L�����N�^�[(0:�ǂ���������Ă��Ȃ� / 1:�� / 2:�E / 3:���� )
	int			iLeftCharactorCg;	// ���̃L�����N�^�[�̗����GNo
	int			iRightCharactorCg;	// �E�̃L�����N�^�[�̗����GNo
	int			iSpeed;				// �`�ʑ��x
	int			iVoiceNo;			// �{�C�X�ԍ�
};
