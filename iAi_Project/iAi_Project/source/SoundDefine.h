/* 2025.01.30 ��򕗏� �t�@�C���쐬 */

#pragma once

/* �T�E���h�Ǘ��̍\���̂�萔�̐錾���s�� */

/* BGM�֌W */
// BGM�ԍ�
static  const int	BGM_TITLE		    = 0;	// �^�C�g��
static  const int	BGM_HOME		    = 1;	// �z�[��
static  const int   BGM_CONVERSATION_0  = 2;    // ��b0
static  const int   BGM_CONVERSATION_1  = 3;    // ��b1
static  const int   BGM_CONVERSATION_2  = 4;    // ��b2
static  const int   BGM_CONVERSATION_3  = 5;    // ��b3
static  const int   BGM_CONVERSATION_4  = 6;    // ��b4
static  const int   BGM_CONVERSATION_5  = 7;    // ��b5(�G���f�B���O)
static  const int   BGM_STAGE_0         = 8;    // �X�e�[�W0(1_1 �` 1_3)
static  const int   BGM_STAGE_1         = 9;    // �X�e�[�W1(2_1 �` 2_3)
static  const int   BGM_STAGE_2         = 10;   // �X�e�[�W2(3_1 �` 3_2)
static  const int   BGM_STAGE_3         = 11;   // �X�e�[�W3(3_3)
static  const int   BGM_EDIT            = 12;   // �G�f�B�b�g 
static  const int	BGM_MAX			    = 13;	// BGM����

// BGM����
static const std::string BGM_NAME[BGM_MAX] =
{
    "Title/BGM_Title",                  // �^�C�g��
    "Home/BGM_Home" ,                   // �z�[��
    "Conversation/BGM_Conv_0",          // ��b0
    "Conversation/BGM_Conv_1",          // ��b1
    "Conversation/BGM_Conv_2",          // ��b2
    "Conversation/BGM_Conv_3",          // ��b3
	"Conversation/BGM_Conv_4",          // ��b4
    "Conversation/BGM_Conv_5_Ending",   // ��b5(�G���f�B���O)
    "Stage/BGM_Stage_1-1_1-3",          // �X�e�[�W0(1_1 �` 1_3)
    "Stage/BGM_Stage_2-1_2-3",          // �X�e�[�W1(2_1 �` 2_3)
    "Stage/BGM_Stage_3-1_3-2",          // �X�e�[�W2(3_1 �` 3_2)
    "Stage/BGM_Stage_3-3",              // �X�e�[�W3(3_3)
    "Edit/BGM_Edit"                     // �G�f�B�b�g
};

/* SE�֌W */
// SE�̏��p�\����
struct SE_INFO
{
	std::string     aSeName;    // SE��
	int             iSeType;    // SE�̎��(FALSE:�ʏ� / TRUE:3D�T�E���h)
};

// 3D�T�E���h����������͈�
static  const float SE_3D_SOUND_RADIUS          = 5000.f;

// SE�ԍ�(�V�X�e���֌W)
static  const int   SE_SYSTEM_MOVECURSOR        = 0;    // �J�[�\���ړ�
static  const int   SE_SYSTEM_DICISION          = 1;    // ����
static  const int   SE_SYSTEM_CANCEL            = 2;    // �L�����Z��
static  const int   SE_SYSTEM_BEEP              = 3;    // ���s
static  const int   SE_SYSTEM_POSEMENU          = 4;    // �|�[�Y���j���[
static  const int   SE_SYSTEM_STAGECLEAR        = 5;    // �X�e�[�W�N���A
static  const int   SE_SYSTEM_RESULT_COUNT      = 6;    // ���U���g�J�E���g
static  const int   SE_SYSTEM_RESULT_RANK_SMALL = 7;    // ���U���g���]��
static  const int   SE_SYSTEM_RESULT_RANK_BIG   = 8;    // ���U���g��]��
static  const int   SE_SYSTEM_CONV_DICISION     = 9;    // ��b�V�[������

// SE�ԍ�(�v���C���[�֌W)
static  const int   SE_PLAYER_RUN               = 10;    // ����
static  const int   SE_PLAYER_JUMP              = 11;   // �W�����v
static  const int   SE_PLAYER_LANDING           = 12;   // ���n
static  const int   SE_PLAYER_KUNAI_GET         = 13;   // �N�i�C����
static  const int   SE_PLAYER_KUNAI             = 14;   // �N�i�C����
static  const int   SE_PLAYER_DODGE             = 15;   // ���
static  const int   SE_PLAYER_ABSORB            = 16;   // �U���z��
static  const int   SE_PLAYER_NIAI              = 17;   // �ʏ틏���U��
static  const int   SE_PLAYER_SLASH_HIT         = 18;   // �U���q�b�g��
static  const int   SE_PLAYER_DOWN              = 19;   // �|���
static  const int   SE_PLAYER_DAMAGE            = 20;   // ��_���[�W
static  const int   SE_PLAYER_DAMAGE_ELEC       = 21;   // ��_���[�W�r���r��
static  const int   SE_PLAYER_CHARGE            = 22;   // ���ߋ����`���[�W
static  const int   SE_PLAYER_CHARGE_COMPLETE   = 23;   // ���ߋ����`���[�W����
static  const int   SE_PLAYER_CHARGE_HOLD       = 24;   // ���߃`���[�W�z�[���h
static  const int   SE_PLAYER_SPIAI             = 25;   // ���ߋ����U��
static  const int   SE_PLAYER_GET_BLOOD         = 26;   // �u���b�h�擾
static  const int   SE_PLAYER_SPIAI_ELEC        = 27;   // ���ߋ������d

// SE�ԍ�(�G�l�~�[�֌W)
static  const int   SE_ENEMY_IKURA_ATTACK       = 28;   // �m�[�}���U����
static  const int   SE_ENEMY_DAMAGE             = 29;   // ���j��
static  const int   SE_ENEMY_BEAM_CHARGE        = 30;   // �r�[���`���[�W��
static  const int   SE_ENEMY_BEAM_SHOT          = 31;   // �r�[�����ˉ�
static  const int   SE_ENEMY_WARNING            = 32;   // �U���\����
static  const int   SE_ENEMY_MISSILE_SHOT       = 33;   // �~�T�C�����ˉ�
static  const int   SE_ENEMY_MISSILE_HIT        = 34;   // �~�T�C�����ˉ�
static  const int   SE_ENEMY_MISSILE_EXPLOSION  = 35;   // �~�T�C�����e�r���r����
static  const int   SE_ENEMY_WARNING_EXPLOSION  = 36;   // �����\����
static  const int   SE_ENEMY_RUN                = 37;   // �����L���L����
// SE�ԍ�(�I�u�W�F�N�g�֌W)
static  const int   SE_GIMMIC_JUMPEXPLP         = 38;   // �����W�����v
static  const int   SE_RESPAWN_ACTIVATE         = 39;   // ���X�|�[���n�_�N��
static  const int   SE_GOAL_SHUTTER             = 40;   // �S�[�����o(�V���b�^�[��)
static  const int   SE_GOAL_SHINE               = 41;   // �S�[�����o(�����ӂ��)
static  const int   SE_GOAL                     = 42;   // �S�[���������鉹

static  const int   SE_MAX                      = 43;   // SE����

// SE����
static const SE_INFO SE_NAME[SE_MAX] =
{
    // �V�X�e���֌W
    { "System/SE_Movecursor_ver2",       FALSE },     // �J�[�\���ړ�
    { "System/SE_Player_Niai",           FALSE },     // ����
    { "System/SE_Cancel",                FALSE },     // �L�����Z��
    { "System/SE_Beep",                  FALSE },     // ���s
    { "System/SE_PoseMenu",              FALSE },     // �|�[�Y���j���[
    { "System/SE_StageClear",            FALSE },     // �X�e�[�W�N���A
    { "System/SE_Result_Count",          FALSE },     // ���U���g�J�E���g
    { "System/SE_Result_Rank_Small",     FALSE },     // ���U���g���]��
    { "System/SE_Result_Rank_Big",       FALSE },     // ���U���g��]��
    { "System/SE_Conv_Button",           FALSE },     // ��b�V�[������
    // �v���C���[�֌W
    { "Player/SE_Player_Run_ver2",       FALSE },     // ����
    { "Player/SE_Player_Jump_ver2",      FALSE },     // �W�����v
    { "Player/SE_Player_Landing",	     FALSE },     // ���n
    { "Player/SE_Player_Getkunai",       FALSE },     // �N�i�C����
    { "Player/SE_Kunai_ver2",            FALSE },     // �N�i�C����
    { "Player/SE_Player_Dodge_ver2",     FALSE },	  // ���
    { "Player/SE_Player_Absorb",         FALSE },     // �U���z��
    { "Player/SE_Player_Niai",           FALSE },     // �ʏ틏��
    { "Player/SE_Slash_Hit",             FALSE },     // �U���q�b�g��
    { "Player/SE_Player_Down",           FALSE },     // �|���
    { "Player/SE_Player_Damagehit",      FALSE },     // ��_���[�W
    { "Player/SE_Player_Damage_Elec",    FALSE },     // ��_���[�W�r���r��
    { "Player/SE_Player_Charge_ver2",    FALSE },     // ���ߍU���`���[�W��
    { "Player/SE_Player_ChargeComplete", FALSE },     // ���ߍU���`���[�W������
    { "Player/SE_Player_Charge_Hold",    FALSE },     // ���߃`���[�W�z�[���h
    { "Player/SE_Player_SPiai",          FALSE },     // ���ߍU����
    { "Player/SE_Player_GetBlood",       FALSE },     // �u���b�h�擾
    { "Player/SE_Player_SPiaiElec",	     FALSE },	  // ���ߍU�����d
    // �G�l�~�[�֌W
    { "Enemy/SE_Ikura_Attack",           TRUE },      // �m�[�}���U����
    { "Enemy/SE_Enemy_Dmage",            TRUE },      // ���j��
    { "Enemy/SE_Beam_Charge",            TRUE },      // �r�[���`���[�W��
    { "Enemy/SE_Beam_Shot",              TRUE },      // �r�[�����ˉ�
    { "Enemy/SE_Warning",                TRUE },      // �U���\����
    { "Enemy/SE_Missile_shot",           TRUE },      // �~�T�C�����ˉ�
    { "Enemy/SE_Missile_hit",            TRUE },      // �~�T�C�����e��
    { "Enemy/SE_Missile_elec",           TRUE },      // �~�T�C�����e�r���r����
    { "Enemy/SE_Warning_Jibaku",         TRUE },      // �����\����
    { "Enemy/SE_Nige_Shining",           TRUE },      // �����L���L����
    // �I�u�W�F�N�g�֌W
    { "Object/SE_Gimmic_JumpExplo",      TRUE },      // �����W�����v��
    { "Object/SE_RespownActivate",       TRUE },      // ���X�|�[���n�_�N��
    { "Object/SE_Goal_Shutter",          FALSE},      // �S�[�����o(�V���b�^�[��)
    { "Object/SE_Goal_Shine",            TRUE },      // �S�[�����o(�����ӂ��)
    { "Object/SE_Goal",                  TRUE }       // �S�[���������鉹
};

/* �{�C�X�֘A */
// �{�C�X�^�C�v
static  const int   VOICE_TYPE_PLAYER   = 0;    // �v���C���[
static  const int   VOICE_TYPE_DOCTOR   = 1;    // ���m(�T�G�W�}�L���E�R)
static  const int   VOICE_TYPE_MAX      = 2;    // �{�C�X�^�C�v����

// �{�C�X�ԍ�(����)
static  const int   VOICE_TITLE_CALL                        = 0;    // �^�C�g���R�[��(����)
static  const int   VOICE_GAMEOVER                          = 1;    // �Q�[���I�[�o�[(����)
static  const int   VOICE_RETRY                             = 2;    // ���g���C(����)
// �{�C�X�ԍ�(�v���C���[)
static  const int   VOICE_PLAYER_CONVERSATION_CONSENT_1     = 3;    // ��b(�v���C���[/����1)
static  const int   VOICE_PLAYER_CONVERSATION_CONSENT_2     = 4;    // ��b(�v���C���[/����2)
static  const int   VOICE_PLAYER_CONVERSATION_CONSENT_3     = 5;    // ��b(�v���C���[/����3)
static  const int   VOICE_PLAYER_CONVERSATION_CONSENT_4     = 6;    // ��b(�v���C���[/����4)
static  const int   VOICE_PLAYER_CONVERSATION_CONSENT_5     = 7;    // ��b(�v���C���[/����5)
static  const int   VOICE_PLAYER_ACTION                     = 8;    // �A�N�V����(�v���C���[)
static  const int   VOICE_PLAYER_STRONG_MELEE               = 9;    // ���U��(�v���C���[)
static  const int   VOICE_PLAYER_KILL_ENEMY                 = 10;   // �G���j(�v���C���[)
static  const int   VOICE_PLAYER_DAMAGE                     = 11;   // �_���[�W(�v���C���[)
static  const int   VOICE_PLAYER_STAGECLEAR                 = 12;   // �X�e�[�W�N���A(�v���C���[)
static  const int   VOICE_PLAYER_PROJECTILE                 = 13;   // �������U��(�v���C���[)
// �{�C�X�ԍ�(���m)
static  const int   VOICE_DOCTOR_CONVERSATION_WELLWELL      = 14;   // ��b(���m/�����)
static  const int   VOICE_DOCTOR_CONVERSATION_SO            = 15;   // ��b(���m/�����)
static  const int   VOICE_DOCTOR_PRAISE                     = 16;   // �܎^(���m)
static  const int   VOICE_DOCTOR_RESULT_S                   = 17;   // ����S(���m)
static  const int   VOICE_DOCTOR_RESULT_A                   = 18;   // ����A(���m)
static  const int   VOICE_DOCTOR_RESULT_BC                  = 19;   // ����BC(���m)
static  const int   VOICE_DOCTOR_RESULT_D                   = 20;   // ����D(���m)
static  const int   VOICE_DOCTOR_CONVERSATION_CONSENT       = 21;   // ��b(���m/����)
static  const int   VOICE_DOCTOR_CONVERSATION_BYTHEWAY      = 22;   // ��b(���m/�Ƃ����)
static  const int   VOICE_DOCTOR_CONVERSATION_THAT_1        = 23;   // ��b(���m/�����1)
static  const int   VOICE_DOCTOR_CONVERSATION_THAT_2        = 24;   // ��b(���m/�����2)

static  const int   VOICE_MAX                               = 54;   // �{�C�X����(�ꕔ�d������)

// �{�C�X���z��p�\����
struct VOICE_INFO
{
	int         iVoiceType;     // �{�C�X�^�C�v
	int         iVoiceNo;       // �{�C�X�ԍ�
	std::string aVoiceName;     // �t�@�C����
};

// �{�C�X�n���h���Ǘ��p�\����
struct VOICE_HANDLE_INFO
{
	int         iVoiceHandle;   // �{�C�X�n���h��
	int         iVoiceType;     // �{�C�X�^�C�v
	int         iVoiceNo;       // �{�C�X�ԍ�
};

// �t�@�C������(�{�C�X�^�C�v)
static const std::string VOICE_TYPE_NAME[VOICE_TYPE_MAX] =
{
    "Player",   // �v���C���[
    "Doctor"    // ���m
};

// �{�C�X���
const VOICE_INFO stVoice_Info[VOICE_MAX] =
{
    // �{�C�X�^�C�v,        �{�C�X�ԍ�,                             �t�@�C����
    { VOICE_TYPE_PLAYER,    VOICE_TITLE_CALL,                       "CV_P_Title1"       },      // �^�C�g���R�[��(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_TITLE_CALL,                       "CV_P_Title2"       },      // �^�C�g���R�[��(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_TITLE_CALL,                       "CV_P_Title3"       },      // �^�C�g���R�[��(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_CONVERSATION_CONSENT_1,    "CV_P_Understand01" },      // ��b(�v���C���[/����1)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_CONVERSATION_CONSENT_2,    "CV_P_Understand02" },      // ��b(�v���C���[/����2)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_CONVERSATION_CONSENT_3,    "CV_P_Understand03" },      // ��b(�v���C���[/����3)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_CONVERSATION_CONSENT_4,    "CV_P_Understand04" },      // ��b(�v���C���[/����4)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_CONVERSATION_CONSENT_5,    "CV_P_Understand05" },      // ��b(�v���C���[/����5)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_ACTION,                    "CV_P_Move01"       },      // �A�N�V����(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_ACTION,                    "CV_P_Move02"       },      // �A�N�V����(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_ACTION,                    "CV_P_Move03"       },      // �A�N�V����(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STRONG_MELEE,              "CV_P_ChargeIai1"   },      // ���U��(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STRONG_MELEE,              "CV_P_ChargeIai2"   },      // ���U��(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_KILL_ENEMY,                "CV_P_AttackEnd1"   },      // �G���j(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_KILL_ENEMY,                "CV_P_AttackEnd2"   },      // �G���j(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_KILL_ENEMY,                "CV_P_AttackEnd3"   },      // �G���j(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_KILL_ENEMY,                "CV_P_AttackEnd4"   },      // �G���j(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_KILL_ENEMY,                "CV_P_AttackEnd5"   },      // �G���j(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_DAMAGE,                    "CV_P_Damage"       },      // �_���[�W(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STAGECLEAR,                "CV_P_GameClear1"   },      // �X�e�[�W�N���A��(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STAGECLEAR,                "CV_P_GameClear2"   },      // �X�e�[�W�N���A��(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STAGECLEAR,                "CV_P_GameClear3"   },      // �X�e�[�W�N���A��(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STAGECLEAR,                "CV_P_GameClear4"   },      // �X�e�[�W�N���A��(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STAGECLEAR,                "CV_P_GameClear5"   },      // �X�e�[�W�N���A��(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_GAMEOVER,                         "CV_P_GameOver1"    },      // �Q�[���I�[�o�[(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_GAMEOVER,                         "CV_P_Gameover2"    },      // �Q�[���I�[�o�[(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_RETRY,                            "CV_P_Retry"        },      // ���g���C(�v���C���[)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_PROJECTILE,                "CV_P_Kunai"        },      // �Q�[���I�[�o�[(�v���C���[)
    { VOICE_TYPE_DOCTOR,    VOICE_TITLE_CALL,                       "CV_S_Title"        },      // �^�C�g���R�[��(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_CONVERSATION_WELLWELL,     "CV_S_Wellwell"     },      // ��b(���m/�����)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_CONVERSATION_SO,           "CV_S_So"           },      // ��b(���m/�����)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise1"      },      // �܎^(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise2"      },      // �܎^(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise3"      },      // �܎^(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise4"      },      // �܎^(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise5"      },      // �܎^(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise6"      },      // �܎^(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise7"      },      // �܎^(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise8"      },      // �܎^(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_S,                  "CV_S_Result_S1"    },      // ����S(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_S,                  "CV_S_Result_S2"    },      // ����S(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_S,                  "CV_S_Result_S3"    },      // ����S(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_S,                  "CV_S_Result_S4"    },      // ����S(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_A,                  "CV_S_Result_A"     },      // ����A(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_BC,                 "CV_S_Result_BC"    },      // ����BC(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_D,                  "CV_S_Result_D1"    },      // ����D(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_D,                  "CV_S_Result_D2"    },      // ����D(���m)
    { VOICE_TYPE_DOCTOR,    VOICE_GAMEOVER,                         "CV_S_Defeal1"      },      // �Q�[���I�[�o�[(����)
    { VOICE_TYPE_DOCTOR,    VOICE_GAMEOVER,                         "CV_S_Defeal2"      },      // �Q�[���I�[�o�[(����)
    { VOICE_TYPE_DOCTOR,    VOICE_RETRY,                            "CV_S_Retry"        },      // ���g���C(����)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_CONVERSATION_CONSENT,      "CV_S_Aa"           },      // ��b(���m/����)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_CONVERSATION_BYTHEWAY,     "CV_S_ByTheWay"     },      // ��b(���m/�Ƃ����)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_CONVERSATION_THAT_1,       "CV_S_That"         },      // ��b(���m/�����1)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_CONVERSATION_THAT_2,       "CV_S_That2"        },      // ��b(���m/�����2)
};