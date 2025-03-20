/* 2025.02.11 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "PublicInclude.h"
#include "EditDefine.h"

/* �G�f�B�b�g��ʗp�̍\���̂�萔�̐錾���s�� */

/* �I�����ڂ̎�� */
static const int	SELECT_TYPE_NONE		= -1;	// �I�����ږ���
static const int	SELECT_TYPE_KEEP_EDIT	= 0;	// �L�[�v���̃G�f�B�b�g
static const int	SELECT_TYPE_NEW_EDIT	= 1;	// �V�K�̃G�f�B�b�g
static const int	SELECT_TYPE_DELETE_EDIT	= 2;	// �폜
static const int	SELECT_TYPE_NOW_EDIT	= 3;	// ���݂̃G�f�B�b�g
static const int	SELECT_TYPE_NEXT		= 4;	// ����
static const int	SELECT_TYPE_MAX			= 5;	// �I�����ڂ̎�ނ̑���

/* �I�����ڂ̔ԍ� */
static const int	SELECT_ITEM_KEEP			= 0;	// �L�[�v���̃G�f�B�b�g
static const int	SELECT_ITEM_NEW_EDIT_START	= 1;	// �V�K�̃G�f�B�b�g(��������)
static const int	SELECT_ITEM_NEW_EDIT_END	= 5;	// �V�K�̃G�f�B�b�g(�����܂�)
static const int	SELECT_ITEM_DELETE			= 6;	// �폜
static const int	SELECT_ITEM_NOW_EDIT_START	= 7;	// ���݂̃G�f�B�b�g(��������)
static const int	SELECT_ITEM_NOW_EDIT_END	= 11;	// ���݂̃G�f�B�b�g(�����܂�)
static const int	SELECT_ITEM_NEXT			= 12;	// ����
static const int	SELECT_ITEM_MAX				= 13;	// �I�����ڂ̑���

/* �I�����ڂ̏�� */
static const int	SELECT_STATUS_NONE				= -1;	// ��Ԗ���
static const int	SELECT_STATUS_POSSIBLE_SET		= 0;	// �Z�b�g�\
static const int	SELECT_STATUS_POSSIBLE_UPGRADE	= 1;	// �����\
static const int	SELECT_STATUS_INTERCHANGEABLE	= 2;	// �����\
static const int	SELECT_STATUS_IMPOSSIBLE		= 3;	// �I��s��
static const int	SELECT_STATUS_MAX				= 4;	// �I�����ڂ̏�Ԃ̑���

/* �����N�ɉ������V�K�G�f�B�b�g�� */
static const int	NEW_EDIT_NO_RANK_S				= 5;	// �V�K�G�f�B�b�g��(S�����N��)
static const int	NEW_EDIT_NO_RANK_A				= 5;	// �V�K�G�f�B�b�g��(A�����N��)
static const int	NEW_EDIT_NO_RANK_B				= 4;	// �V�K�G�f�B�b�g��(B�����N��)
static const int	NEW_EDIT_NO_RANK_C				= 3;	// �V�K�G�f�B�b�g��(C�����N��)
static const int	NEW_EDIT_NO_RANK_D				= 3;	// �V�K�G�f�B�b�g��(D�����N��)


/* �I�����ڂ̊Ǘ��p�\���� */
struct EDIT_SELECT_ITEM
{
	EDIT_DATA*		pstEditData;		// �G�f�B�b�g���
	int				iSelectItemType;	// �I�����ڂ̎��
	st2DPosition	stDrawPos;			// �`�ʍ��W
	int				iSelectStatus;		// �I�����
};

/* �G�f�B�b�g���I�p�̍\���� */
struct EDIT_LOTTERY
{
	int			iEffect;		// �G�f�B�b�g�̌���
	int			iRank;			// �G�f�B�b�g�̃����N
	int			iIncidenceRate;	// �o����
	int			iCost;			// ���i
	std::string	aText;			// �e�L�X�g
};
