/* 2025.01.16 �t�@�C���쐬 ��򕗏� */

#include "SceneStage.h"

/* �I�u�W�F�N�g */
// ��������(�������肷��\������)
// �v���C���[
#include "CharacterPlayer.h"
// �G�l�~�[
#include "EnemyNormal.h"
#include "EnemyEscape.h"
#include "EnemyGoalObject.h"
#include "EnemyNormal.h"
#include "EnemyMissile.h"
#include "EnemyBeam.h"
#include "Enemy_Explosion.h"
// �v���b�g�t�H�[��
#include "PlatformBasic.h"
// �X�J�C�X�t�B�A
#include "SkySqhereBasic.h"
// �M�~�b�N
#include "GimmickDisappear.h"
#include "Gimmick_ForcedJump_Spawn.h"
#include "Screen.h"
#include "LargeScreen.h"
#include "Gimmick_FallJudgment.h"
// ��
#include "FallFog.h"


/* �X�e�[�W�N���X�̒�`(�}�b�v�ǂݍ��ݕ���) */

// �}�b�v�f�[�^�̃��[�h
void SceneStage::LoadMapData()
{
	/* ���݂̃X�e�[�W�ԍ����擾 */
	int iStageNo = this->StageStatusList->iGetNowStageNo();

	/* �}�b�v�����擾 */
	std::string MapName = STAGE_NAME[iStageNo];

	/* �������A�|�C���g���̏����� */
	StageStatusList->RecoveryPointList_Initialization();

	/* �}�b�v�f�[�^�̓ǂݍ��� */
	{
		/* �ǂݍ��݂����}�b�v�f�[�^�̃p�X�ݒ� */
		// ���t�@�C�����ƃX�e�[�W������v����悤�ɂ���
		std::string Path = "resource/MapData/";
		std::string Format = MapName + ".json";
		std::ifstream file(Path + Format);

		/* Json�t�@�C���ǂݍ��� */
		nlohmann::json json;
		file >> json;

		/* �v���b�g�t�H�[��(�`�ʃI�u�W�F�N�g)�ǂݍ��� */
		{
			/* Json�t�@�C������ǂݍ��� */
			std::string Type = "/Object";
			std::string GetName = MapName + Type;
			nlohmann::json stage = json.at(GetName);

			for (auto& data : stage)
			{
				/* "�I�u�W�F�N�g�Ǘ�"�Ƀv���b�g�t�H�[����ǉ� */
				PlatformBase* pPlatform = new PlatformBase();
				this->ObjectList->SetPlatform(pPlatform);

				/* ���f�� */
				std::string	name;
				data.at("objectName").get_to(name);
				std::string Path = "Object/" + name + "/" + name;
				pPlatform->SetModelHandle(this->ModelList->iGetModel(Path));

				/* ���W */
				VECTOR vecPos;
				// �ǂݍ���
				data.at("translate").at("x").get_to(vecPos.x);
				data.at("translate").at("z").get_to(vecPos.y);
				data.at("translate").at("y").get_to(vecPos.z);
				// Z���W���]
				vecPos.z *= -1;
				// �ݒ�
				pPlatform->SetPosition(vecPos);

				/* ��]�� */
				VECTOR vecRot;
				// �ǂݍ���
				data.at("rotate").at("x").get_to(vecRot.x);
				data.at("rotate").at("z").get_to(vecRot.y);
				data.at("rotate").at("y").get_to(vecRot.z);
				// degree -> radian�ϊ�
				vecRot.x = DEG2RAD(vecRot.x);
				vecRot.y = DEG2RAD(vecRot.y);
				vecRot.z = DEG2RAD(vecRot.z);
				// X���̉�]�����𔽓]
				vecRot.x *= -1;
				// �ݒ�
				pPlatform->SetRotation(vecRot);

				/* �g�嗦 */
				VECTOR vecScale;
				// �ǂݍ���
				data.at("scale").at("x").get_to(vecScale.x);
				data.at("scale").at("z").get_to(vecScale.y);
				data.at("scale").at("y").get_to(vecScale.z);
				// �ݒ�
				pPlatform->SetScale(vecScale);
			}
		}

		/* �}�[�J�[�ǂݍ��� */
		{
			/* Json�t�@�C������ǂݍ��� */
			std::string Type = "/Marker";
			std::string GetName = MapName + Type;
			nlohmann::json stage = json.at(GetName);

			for (auto& data : stage)
			{
				/* �}�[�J�[���擾 */
				std::string	name;
				data.at("objectName").get_to(name);

				/* ���W���擾 */
				VECTOR vecPos;
				// �ǂݍ���
				data.at("translate").at("x").get_to(vecPos.x);
				data.at("translate").at("z").get_to(vecPos.y);
				data.at("translate").at("y").get_to(vecPos.z);
				// Z���W���]
				vecPos.z *= -1;

				/* ��]�ʂ��擾 */
				VECTOR vecRot;
				// �ǂݍ���
				data.at("rotate").at("x").get_to(vecRot.x);
				data.at("rotate").at("z").get_to(vecRot.y);
				data.at("rotate").at("y").get_to(vecRot.z);
				// degree -> radian�ϊ�
				vecRot.x = DEG2RAD(vecRot.x);
				vecRot.y = DEG2RAD(vecRot.y);
				vecRot.z = DEG2RAD(vecRot.z);
				// X���̉�]�����𔽓]
				vecRot.x *= -1;

				/* �g�嗦 */
				VECTOR vecScale;
				// �ǂݍ���
				data.at("scale").at("x").get_to(vecScale.x);
				data.at("scale").at("z").get_to(vecScale.y);
				data.at("scale").at("y").get_to(vecScale.z);

				/* �}�[�J�[�^�C�v�m�F */
				if (name == "Marker_Player_Start")
				{
					// �v���C���[�X�^�[�g�n�_�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�Ƀv���C���[��ǉ� */
					CharacterPlayer* pPlayer = new CharacterPlayer();
					ObjectList->SetCharacterPlayer(pPlayer);

					/* ���W�ݒ� */
					pPlayer->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					pPlayer->SetRotation(vecRot);
				}
				else if (name == "Marker_Goal_Object")
				{
					// �S�[���n�_�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃS�[���I�u�W�F�N�g��ǉ� */
					EnemyBasic* pGoal = new EnemyGoalObject();
					ObjectList->SetEnemy(pGoal);

					/* ���W�ݒ� */
					pGoal->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					pGoal->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Beam")
				{
					// �G�l�~�[(�r�[��)�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃG�l�~�[(�r�[��)��ǉ� */
					BeamEnemy* AddEnemy = new BeamEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* ���W�ݒ� */
					AddEnemy->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Escape")
				{
					// �G�l�~�[(����)�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃG�l�~�[(����)��ǉ� */
					EscapeEnemy* AddEnemy = new EscapeEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* ���W�ݒ� */
					AddEnemy->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Explosion")
				{
					// �G�l�~�[(����)�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃG�l�~�[(����)��ǉ� */
					ExplosionEnemy* AddEnemy = new ExplosionEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* ���W�ݒ� */
					AddEnemy->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Missile")
				{
					// �G�l�~�[(�~�T�C��)�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃG�l�~�[(�~�T�C��)��ǉ� */
					MissileEnemy* AddEnemy = new MissileEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* ���W�ݒ� */
					AddEnemy->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Normal")
				{
					// �G�l�~�[(�ʏ�)�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃG�l�~�[(�ʏ�)��ǉ� */
					NormalEnemy* AddEnemy = new NormalEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* ���W�ݒ� */
					AddEnemy->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Gimmick_Jump")
				{
					// �M�~�b�N(�����W�����v)�̏ꍇ
					PlatformBasic* pAddGimick = new Gimmick_ForcedJump_Spawn();
					ObjectList->SetPlatform(pAddGimick);

					/* ���W�ݒ� */
					pAddGimick->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					pAddGimick->SetRotation(vecRot);
				}
				else if (name == "Marker_Camera_Position_Start")
				{
					// �J�����ʒu(�X�^�[�g)�̏ꍇ
					/* ���W�ݒ�(�J�������W) */
					StageStatusList->SetCameraPosition(vecPos);				// �J�����̍��W�ݒ�(���ݒn�_)
					StageStatusList->SetCameraPosition_Start(vecPos);		// �J�����̍��W�ݒ�(�ړ��O�n�_)
					StageStatusList->SetCameraPosition_Target(vecPos);		// �J�����̍��W�ݒ�(�ړ���n�_)

					/* ���W�ݒ�(�Œ���W(�J�n�n�_)) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_START].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_START].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosA")
				{
					// �J�����ʒu(�|�W�V����A)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����A) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_A].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_A].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosB")
				{
					// �J�����ʒu(�|�W�V����B)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����B) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_B].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_B].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosC")
				{
					// �J�����ʒu(�|�W�V����C)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����C) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_C].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_C].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosD")
				{
					// �J�����ʒu(�|�W�V����D)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����D) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_D].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_D].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosE")
				{
					// �J�����ʒu(�|�W�V����E)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����E) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_E].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_E].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Target_Start")
				{
					// �J���������_(�X�^�[�g)�̏ꍇ
					/* ���W�ݒ�(�J���������_) */
					StageStatusList->SetCameraTarget(vecPos);				// �J�����̒����_�ݒ�(���ݒn�_)

					/* ���W�ݒ�(�Œ���W(�J�n�n�_)) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_START].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_START].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosA")
				{
					// �J���������_(�|�W�V����A)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����A) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_A].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_A].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosB")
				{
					// �J���������_(�|�W�V����B)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����B) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_B].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_B].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosC")
				{
					// �J���������_(�|�W�V����C)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����C) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_C].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_C].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosD")
				{
					// �J���������_(�|�W�V����D)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����D) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_D].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_D].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosE")
				{
					// �J���������_(�|�W�V����E)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����E) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_E].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_E].vecTarget	= vecPos;
				}
				else if (name == "SignBoard")
				{
					// �X�N���[���̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃX�N���[����ǉ� */
					Screen* pScreen = new Screen();
					ObjectList->SetPlatform(pScreen);

					/* ���W�ݒ� */
					pScreen->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					pScreen->SetRotation(vecRot);
				}
				else if (name == "LargeScreen")
				{
					// �X�N���[���̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃX�N���[����ǉ� */
					LargeScreen* pLargeScreen = new LargeScreen();
					ObjectList->SetPlatform(pLargeScreen);

					/* ���W�ݒ� */
					pLargeScreen->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					pLargeScreen->SetRotation(vecRot);

					/* �g�嗦�ݒ�*/
					pLargeScreen->SetScale(vecScale);
					}
				else if (name == "FallJudgment")
				{
					// ��������̏ꍇ
					/* ��������p�I�u�W�F�N�g�̎l���̍��W�̕ۑ��ꏊ�쐬 */
					VECTOR vecFourDirections[4];

					/* ��������p�̃I�u�W�F�N�g�̊�T�C�Y�̐ݒ� */
					VECTOR localVertices[4] =
					{
						VGet(+1000.0f,	0.0f, +1000.0f),	// �E��
						VGet(+1000.0f,	0.0f, -1000.0f),	// �E�O
						VGet(-1000.0f,	0.0f, -1000.0f),	// ���O
						VGet(-1000.0f,	0.0f, +1000.0f)		// ����
					};

					/* �s��̍쐬 (�X�P�[�� �� ��] �� ���s�ړ�) */
					MATRIX matScale	= MGetScale(vecScale);
					MATRIX matRotX	= MGetRotX(vecRot.x);
					MATRIX matRotY	= MGetRotY(vecRot.y);
					MATRIX matRotZ	= MGetRotZ(vecRot.z);
					MATRIX matTrans	= MGetTranslate(vecPos);

					/* �ŏI�ϊ��s��̌v�Z */
					MATRIX matTransform = MMult(matScale, MMult(MMult(matRotX, matRotY), MMult(matRotZ, matTrans)));

					/* �e���_�ɍs���K�p���ă��[���h���W���v�Z */
					for (int i = 0; i < 4; i++)
					{
						vecFourDirections[i] = VTransform(localVertices[i], matTransform);
					}

					/* �����쐬 */
					VECTOR topRight = vecFourDirections[0];
					VECTOR topLeft = vecFourDirections[3];
					VECTOR bottomRight = vecFourDirections[1];

					// ���������Ɛ��������̃X�e�b�v
					VECTOR horizontalStep = VScale(VNorm(VSub(topLeft, topRight)), 300.0f);
					VECTOR verticalStep = VScale(VNorm(VSub(bottomRight, topRight)), 300.0f);

					// �ł��E�����獶���܂ŉ��ɐi�݂c�ɖ��߂Ă���
					for (VECTOR startPos = topRight; startPos.x >= topLeft.x; startPos = VAdd(startPos, horizontalStep))
					{
						VECTOR verticalPos = startPos;
						while (verticalPos.z >= bottomRight.z)
						{
							PlatformBase* pFog = new FallFog();
							ObjectList->SetPlatform(pFog);
							pFog->SetPosition(verticalPos);

							verticalPos = VAdd(verticalPos, verticalStep);
						}
					}

					/* "�I�u�W�F�N�g�Ǘ�"�ɗ�������ʒu��ǉ� */
					PlatformBase* pPlatform = new Gimmick_FallJudgment();
					this->ObjectList->SetPlatform(pPlatform);

					/* ���f�� */
					std::string Path = "Object/" + name + "/" + name;
					pPlatform->SetModelHandle(this->ModelList->iGetModel(Path));

					/* ���W */
					pPlatform->SetPosition(vecPos);

					/* ��]�� */
					pPlatform->SetRotation(vecRot);

					/* �g�嗦 */
					pPlatform->SetScale(vecScale);
				}
				else if(name == "Marker_FallRecovery")
				{
					// �������A�|�C���g�̏ꍇ
					/* �������A�|�C���g���̒ǉ� */
					StageStatusList->SetFallRecoveryPoint(vecPos);
				}
			}
		}

		/* �X�J�C�X�t�B�A�ǉ� */
		// ���W���Œǉ�����
		{
			/* "�I�u�W�F�N�g�Ǘ�"�ɃX�J�C�X�t�B�A��ǉ� */
			SkySqhereBasic* pSkySqhere = new SkySqhereBasic();
			ObjectList->SetSkySqhere(pSkySqhere);

			/* ���f�� */
			pSkySqhere->SetModelHandle(this->ModelList->iGetModel("SkySqhere/skysphere"));

			/* �T�C�Y */
			pSkySqhere->SetScale(VGet(5.f, 5.f, 5.f));
		}
	}

	/* ���ׂẴI�u�W�F�N�g�̏��������s�� */
	ObjectList->InitializationAll();

	/* �J�����Œ���W�̑������擾 */
	{
		/* ���������������� */
		this->iMaxCameraFixedPositionNo = 0;

		/* �J�����Œ���W�̑������擾���� */
		for (int i = 0; i < CAMERA_FIXED_POSITION_MAX; ++i)
		{
			/* �g�p��Ԃ��L���ł��邩�m�F */
			if (this->vecCameraPositionInfo[i].bUseFlg == true)
			{
				// �L���ł���ꍇ
				/* ���������Z���� */
				this->iMaxCameraFixedPositionNo += 1;
			}
			else
			{
				// �����ł���ꍇ
				/* ���[�v�𔲂��� */
				break;
			}
		}
	}
}
