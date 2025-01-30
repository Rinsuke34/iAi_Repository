/* 2025.01.30 ��򕗏� �t�@�C���쐬 */

#pragma once

/* �T�E���h�Ǘ��̍\���̂�萔�̐錾���s�� */

/* BGM�֌W */
// BGM�ԍ�
const int	BGM_STAGE		= 0;	// �X�e�[�W
const int	BGM_TITLE		= 1;	// �^�C�g��
const int	BGM_HOME		= 2;	// �z�[��
const int	BGM_MAX			= 3;	// BGM����

// BGM����
static const std::string BGM_NAME[BGM_MAX] =
{
    "BGM_Stage",    // �X�e�[�W
    "BGM_Title",    // �^�C�g��
    "BGM_Home"      // �z�[��
};

/* SE�֌W */
// SE�ԍ�(�V�X�e���֌W)
const int   SE_SYSTEM_MOVECURSOR        = 0;    // �J�[�\���ړ�
const int   SE_SYSTEM_DICISION          = 1;    // ����
const int   SE_SYSTEM_CANCEL            = 2;    // �L�����Z��
// SE�ԍ�(�v���C���[�֌W)
const int   SE_PLAYER_WALK              = 3;    // ����
const int   SE_PLAYER_RUN               = 4;    // ����
const int   SE_PLAYER_RUN_SP            = 5;    // �����_�b�V��
const int   SE_PLAYER_JUMP              = 6;    // �W�����v
const int   SE_PLAYER_LANDING           = 7;    // ���n
const int   SE_PLAYER_KUNAI_GET         = 8;    // �N�i�C����
const int   SE_PLAYER_KUNAI             = 9;    // �N�i�C����
const int   SE_PLAYER_DODGE             = 10;   // ���
const int   SE_PLAYER_ABSORB            = 11;   // �U���z��
const int   SE_PLAYER_NIAI              = 12;   // �ʏ틏���U��
const int   SE_PLAYER_DOWN              = 13;   // �|���
const int   SE_PLAYER_DAMAGE            = 14;   // ��_���[�W
const int   SE_PLAYER_CHARGE            = 15;   // ���ߋ����`���[�W
const int   SE_PLAYER_CHARGE_COMPLETE   = 16;   // ���ߋ����`���[�W����
const int   SE_PLAYER_SPIAI             = 17;   // ���ߋ����U��
// SE�ԍ�(�G�l�~�[�֌W)
const int   SE_ENEMY_IKURA_ATTACK       = 18;   // ������U��
const int   SE_ENEMY_BEAM_ATTACK        = 19;   // �r�[���U��
const int   SE_ENEMY_DAMAGE             = 20;   // ���j

const int   SE_MAX                      = 21;   // SE����

// SE����
static const std::string SE_NAME[SE_MAX] =
{
    // �V�X�e���֌W
    "SE_Movecursor",                // �J�[�\���ړ�
    "SE_Decision",                  // ����
    "SE_Cancel",                    // �L�����Z��
    // �v���C���[�֌W
    "SE_Player_Walk",               // ����
    "SE_Player_Run",                // ����
    "SE_Player_SPRun",              // �����_�b�V��
    "SE_Player_Jump",               // �W�����v
    "SE_Player_Landing",            // ���n
    "SE_Player_Getkunai",           // �N�i�C����
    "SE_Player_Kunai",              // �N�i�C����
    "SE_Player_Dodge",              // ���
    "SE_Player_Absorb",             // �U���z��
    "SE_Player_Niai",               // �ʏ틏���U��
    "SE_Player_Down",               // �|���
    "SE_Player_Damage",             // ��_���[�W
    "SE_Player_Charge",             // ���ߋ����`���[�W
    "SE_Player_ChargeComplete",     // ���ߋ����`���[�W����
    "SE_Player_SPiai",              // ���ߋ����U��
    // �G�l�~�[�֌W
    "SE_Ikura_Attack",              // ������U��
    "SE_Beam_Attack",               // �r�[���U��
    "SE_Enemy_Damage"               // ���j
};
