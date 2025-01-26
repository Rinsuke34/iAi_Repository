/* 2024.12.15 駒沢風助 ファイル作成 */
/* 2025.01.09 菊池雅道 回避関連の関数追加 */
/* 2025.01.22 菊池雅道 攻撃関連の関数追加 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Input.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Object.h"
#include "DataList_Model.h"

/* オブジェクト */
#include "BulletPlayerMeleeWeak.h"
#include "BulletPlayerMeleeStrong.h"

/* プレイヤークラスの宣言 */

// プレイヤークラス
class CharacterPlayer : public CharacterBase
{
	public:
		CharacterPlayer();				// コンストラクタ
		virtual ~CharacterPlayer() {};	// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
		virtual void	Draw()				override;		// 描写
		virtual void	CollisionDraw()		override;		// 当たり判定描写

	private:
	protected:
		/* 使用するデータリスト */
		// 毎回データリストサーバーから取得するのは非効率なため、ここで保存しておく
		DataList_Input*			InputList;			// 入力管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態
		DataList_Object*		ObjectList;			// オブジェクト管理

		/* 関数 */
		void	CollisionUpdate();		// コリジョン更新

		// 移動アクション
		void	Player_Jump();				// ジャンプ
		void	Player_Gravity();			// 重力処理
		void	Player_Move();				// 移動
		void	Player_Dodg();				// 回避 2025.01.09 菊池雅道 関数追加
		void	Movement_Vertical();		// 移動処理(垂直方向)
		void	Movement_Horizontal();		// 移動処理(水平方向)

		// 攻撃アクション
		void	Player_Attack_Transition();			// 攻撃状態遷移管理
		void	Player_Melee_Posture();				// 近接攻撃(構え)
		void	Player_Melee_Weak();				// 近接攻撃(弱)
		void	Player_Charge_Attack();				// プレイヤー溜め攻撃　2025.01.22 菊池雅道 関数追加  
		void	Player_Projectile_Posture();		// 遠距離攻撃(構え)
		void	Player_Projectile();				// 遠距離攻撃

		/* オブジェクトのハンドル */
		// ※プレイヤー側から削除タイミングを指定するためにハンドルを所持
		BulletPlayerMeleeWeak* pBulletMeleeWeak;	// 近接攻撃(弱)の弾

		/* 変数 */
		VECTOR				vecMove;				// 移動量

		/* 変数デバッグ用 */
		COLLISION_LINE		stVerticalCollision;			// 垂直方向のコリジョン
		COLLISION_CAPSULE	stHorizontalCollision[2];		// 水平方向コリジョン(0:上側, 1:下側)
		COLLISION_CAPSULE	stMeleeStrongMoveCollsion;		// 近接攻撃(強)のコリジョン(移動後の座標)
};
