/* 2025.01.30 ��򕗏� �t�@�C���쐬 */

#pragma once

/* �T�E���h�Ǘ��̍\���̂�萔�̐錾���s�� */

/* BGM�֌W */
// BGM�ԍ�
static  const int	BGM_STAGE		= 0;	// �X�e�[�W
static  const int	BGM_TITLE		= 1;	// �^�C�g��
static  const int	BGM_HOME		= 2;	// �z�[��
static  const int	BGM_MAX			= 3;	// BGM����

// BGM����
static const std::string BGM_NAME[BGM_MAX] =
{
    "BGM_Stage",    // �X�e�[�W
    "BGM_Title",    // �^�C�g��
    "BGM_Home"      // �z�[��
};

/* SE�֌W */
// SE�ԍ�(�V�X�e���֌W)
static  const int   SE_SYSTEM_MOVECURSOR        = 0;    // �J�[�\���ړ�
static  const int   SE_SYSTEM_DICISION          = 1;    // ����
static  const int   SE_SYSTEM_CANCEL            = 2;    // �L�����Z��
// SE�ԍ�(�v���C���[�֌W)
static  const int   SE_PLAYER_WALK              = 3;    // ����
static  const int   SE_PLAYER_RUN               = 4;    // ����
static  const int   SE_PLAYER_RUN_SP            = 5;    // �����_�b�V��
static  const int   SE_PLAYER_JUMP              = 6;    // �W�����v
static  const int   SE_PLAYER_LANDING           = 7;    // ���n
static  const int   SE_PLAYER_KUNAI_GET         = 8;    // �N�i�C����
static  const int   SE_PLAYER_KUNAI             = 9;    // �N�i�C����
static  const int   SE_PLAYER_DODGE             = 10;   // ���
static  const int   SE_PLAYER_ABSORB            = 11;   // �U���z��
static  const int   SE_PLAYER_NIAI              = 12;   // �ʏ틏���U��
static  const int   SE_PLAYER_DOWN              = 13;   // �|���
static  const int   SE_PLAYER_DAMAGE            = 14;   // ��_���[�W
static  const int   SE_PLAYER_CHARGE            = 15;   // ���ߋ����`���[�W
static  const int   SE_PLAYER_CHARGE_COMPLETE   = 16;   // ���ߋ����`���[�W����
static  const int   SE_PLAYER_SPIAI             = 17;   // ���ߋ����U��
// SE�ԍ�(�G�l�~�[�֌W)
static  const int   SE_ENEMY_IKURA_ATTACK       = 18;   // ������U��
static  const int   SE_ENEMY_BEAM_CHARGE        = 19;   // �r�[���`���[�W
static  const int   SE_ENEMY_BEAM_SHOT          = 20;   // �r�[���V���b�g
static  const int   SE_ENEMY_DAMAGE             = 21;   // ���j

static  const int   SE_MAX                      = 22;   // SE����

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
    "SE_Beam_Charge",               // �r�[���`���[�W
	"SE_Beam_Shot",                 // �r�[���V���b�g
    "SE_Enemy_Damage"               // ���j
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