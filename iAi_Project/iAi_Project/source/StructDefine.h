/* 2024.01.03 ��򕗏� �t�@�C���쐬 */

#pragma once

/* �O���Q�� */
// ��AppFrame�Œ�`����Ă��Ȃ��N���X���g�p����ꍇ�A�z�Q�Ƒ΍�Ɏ��{����B
class EnemyBasic;

/* �v���W�F�N�g�Ŏg�p����\���̂̐錾 */

// �w��ӏ��ƃG�l�~�[�̋�������p�̍\����
struct NearEnemy
{
	EnemyBasic* pEnemy;		// �G�l�~�[�̃|�C���^
	float fDistance;		// ��ʒ��S����̋���(�y�ʉ��̂��ߍ��W�̍��̓��)
};
