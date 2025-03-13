/* 2025.02.14 菊池雅道 ファイル作成 */

#include "BulletPlayerKunai.h"

/* クナイクラスの定義 */

// コンストラクタ
BulletPlayerKunai::BulletPlayerKunai() : BulletBase()
{
	/* 初期化 */
	this->iObjectType					= OBJECT_TYPE_BULLET_PLAYER;		// オブジェクトの種類を"弾(プレイヤー)"に設定
	this->vecKunaiTargetPosition		= VGet(0,0,0);						// ターゲット座標
	this->vecKunaiMoveDirection			= VGet(0, 0, 0);					// クナイの移動する方向
	this->fKunaiTargetDistance			= 0.0f;								// クナイの発射地点からターゲットまでの距離
	this->fKunaiMoveDistance			= 0.0f;								// クナイの移動距離
	this->fKunaiAngleX					= 0.0f;								// クナイのX軸回転角度
	this->fKunaiAngleY					= 0.0f;								// クナイのY軸回転角度
	this->iKunaiDeleteCount				= KUNAI_ATTACK_COUNT;				// クナイの削除カウント(攻撃時間)
	this->bKunaiAttackFlg				= false;							// クナイの攻撃フラグ

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Bullet/Kunai_0218");
	}

	/* データリスト取得 */
	{
		/* "入力管理"を取得 */
		this->InputList = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));

		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
		
		/* "プレイヤー状態管理"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "ステージ状態管理"を管理 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}
}

// デストラクタ
BulletPlayerKunai::~BulletPlayerKunai()
{
	
}

// 初期化
void BulletPlayerKunai::Initialization()
{

}

// 描画
void BulletPlayerKunai::Draw()
{
	
}

// 更新
void BulletPlayerKunai::Update()
{
	
}

//void BulletPlayerKunai::Move()
//{
//	/* ターゲットエネミーが存在するか確認 */
//	if (this->pTargetEnemy != nullptr)
//	{
//		// ターゲットエネミーが存在する場合
//		//敵の後ろにワープし、撃破する
//		/* クナイの座標をターゲット座標に固定 */
//		this->vecPosition = pTargetEnemy->vecGetPosition();
//
//		/* モデルを非表示に設定 */
//		MV1SetVisible(this->iModelHandle, false);
//
//		/* クナイの攻撃フラグが立っていないか確認 */
//		if (this->bKunaiAttackFlg == false)
//		{
//			/* エネミーの角度からY軸の回転行列を求める */
//			MATRIX matEnemyrRotation = MGetRotY((pTargetEnemy->vecGetRotation().y));
//
//			/* エネミーの向きのベクトル */
//			VECTOR vecEnemyDirection = VGet(0, 0, 1);
//
//			/* 行列をベクトルに変換 */
//			vecEnemyDirection = VTransform(vecEnemyDirection, matEnemyrRotation);
//
//			/* エネミーの向きを正規化 */
//			vecEnemyDirection = VNorm(vecEnemyDirection);
//
//			/* エネミーの向きの角度(ラジアン)を取得 */
//			float fEnemyRotate = -atan2f(vecEnemyDirection.x, vecEnemyDirection.z);
//
//			/* プレイヤーの向きを敵と逆に設定 */
//			this->PlayerStatusList->SetPlayerAngleX(fEnemyRotate - PI);
//
//			/* プレイヤーのワープ位置を敵の後ろに設定 */
//			VECTOR vecPlayerWarpPotition = VScale(vecEnemyDirection, 250);
//			vecPlayerWarpPotition = VAdd(pTargetEnemy->vecGetPosition(), vecPlayerWarpPotition);
//
//			/* プレイヤーの座標をワープ位置に設定 */
//			this->ObjectList->GetCharacterPlayer()->SetPosition(vecPlayerWarpPotition);
//
//			/* プレイヤーの攻撃状態を取得 */
//			int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();
//
//			/* プレイヤーの攻撃状態が遠距離攻撃構え状態であるか確認 */
//			if (iPlayerAttackState == PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
//			{
//				// 遠距離攻撃構え状態である場合
//				/* 遠距離攻撃構え状態をキャンセルする */
//				this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
//			}
//
//			/* プレイヤーの状態を"自由状態"に遷移 */
//			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
//
//			/* プレイヤーのモーションを"近距離攻撃(強)(終了)"に変更 */
//			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG_END);
//
//			
//			/* 当たり判定設定 */
//			{
//				/* 敵の位置に当たり判定を設定 */
//				this->stCollisionSqhere.vecSqhere = pTargetEnemy->vecGetPosition();
//
//				/* 当たり判定の半径を設定 */
//				this->stCollisionSqhere.fSqhereRadius = 50;
//			}
//
//			/* クナイの攻撃フラグを設定 */
//			this->bKunaiAttackFlg = true;
//			
//		}		
//	}
//	else
//	{
//		// ターゲットエネミーが存在する場合
//		// ターゲット座標にワープする
//		/* クナイの座標をターゲット座標に固定 */
//		this->vecPosition = this->vecKunaiTargetPosition;
//
//		/* プレイヤーをクナイの座標に移動 */
//		this->ObjectList->GetCharacterPlayer()->SetPosition(this->vecPosition);
//
//		/* プレイヤーの攻撃状態を取得 */
//		int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();
//
//		/* プレイヤーの攻撃状態が遠距離攻撃構え状態であるか確認 */
//		if (iPlayerAttackState == PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
//		{
//			// 遠距離攻撃構え状態である場合
//			/* プレイヤーの状態を"自由状態"に遷移 */
//			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);
//
//			/* プレイヤーのモーションを無しに設定 */
//			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);
//
//			/* 遠距離攻撃構え状態をキャンセルする */
//			this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
//		}
//
//		/* クナイの削除フラグを設定 */
//		this->bDeleteFlg = true;
//	}
//	
//	/* クナイの攻撃フラグが立っているか確認 */
//	if (this->bKunaiAttackFlg == true)
//	{
//		// クナイの攻撃フラグが立っている場合
//		// クナイの削除処理
//		/* クナイの削除カウント(攻撃時間)が残っていた場合 */
//		if (iKunaiDeleteCount > 0)
//		{
//			/* クナイの削除カウント(攻撃時間)を減算 */
//			iKunaiDeleteCount--;
//		}
//		/* クナイの削除カウント(攻撃時間)が0になった場合 */
//		else
//		{
//			/* クナイの削除フラグを設定 */
//			this->bDeleteFlg = true;
//		}	
//	}
//}
