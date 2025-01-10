/* 2024.12.15 駒沢風助 ファイル作成 */
/* 2025.01.09 菊池雅道 移動関連の変数・定数追加 */


#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Input.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Object.h"

/* 2025.01.09 菊池雅道 移動関連の定数追加開始 */

//プレイヤーに関する設定値
namespace PLAYER_STATUS
{

	//移動関係
	const float PLAYER_WALK_MOVE_SPEED = 1.0f; //プレイヤーの歩きの移動速度
	const float PLAER_DASH_NOMAL_SPEED = 5.0f; //プレイヤーの走り（通常）の移動速度
	const float PLAER_DASH_MAX_SPEED = 10.0f; //プレイヤーの走り（最大）の移動速度
	const int FLAME_COUNT_TO_MAX_SPEED = 180; //プレイヤーの走りの通常→最大になるフレーム数
	const int STICK_TILT_PLAER_DASH = 700; //プレイヤーが走り状態になるスティックの傾き　（範囲：０～１０００）

	//ジャンプ関係
	const float PLAYER_JUMP_SPEED = 50.0f; //プレイヤーのジャンプの速度
	const float GRAVITY_SREED = -9.8f; //重力の速度　Y軸の下方向なのでマイナスとする
	const float GRAVITY_BUFFER = 0.1f; //キャラクターにかかる重力調整　１より大きいと重くなる　１より小さいと軽くなる
	const int PLAYER_JUMPING_IN_AIR_LIMIT = 1;//プレイヤーが空中ジャンプできる回数
	//回避関係
	const float PLAYER_DODGE_SPEED = 3000.0f;//プレイヤーの回避速度
}

//ゲーム全般の設定に関する設定値
namespace GAME_SETTING
{
	const float STICK_DEAD_ZONE = 100; //スティック入力のデッドゾーン（範囲：０～１０００）
	const int GAME_FRAMES_PER_SECOND = 60; //ゲームの設定FPS
}

using namespace GAME_SETTING;

// 計算用マクロ
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )
#define	ACCELERATION(x)	( (x) / GAME_FRAMES_PER_SECOND * GAME_FRAMES_PER_SECOND ) //加速度計算マクロ


/* 2025.01.09 菊池雅道 移動関連の定数追加終了 */



/* プレイヤークラスの宣言 */

// プレイヤークラス
class CharacterPlayer : public CharacterBase
{
	public:
		CharacterPlayer();				// コンストラクタ
		virtual ~CharacterPlayer() {};	// デストラクタ

		virtual void	Update();	// 更新
		virtual void	Draw();		// 描写

	private:
	protected:
		/* 使用するデータリスト */
		// 毎回データリストサーバーから取得するのは非効率なため、ここで保存しておく
		DataList_Input*	InputList;	// 入力管理

		/* 2025.01.09 菊池雅道 移動関連の変数追加開始 */

		VECTOR vecPlayerDirection;	// プレイヤーの向き
		
		//移動関係（歩き・走り等）
		float fPlayerMoveSpeed; //プレイヤー移動速度
		VECTOR vecPlayerOldVector; //プレイヤーの移動時のベクトルを保存する（ジャンプ慣性等に使用）
		float fPlayerOldRadian;  //プレイヤーの移動時の角度を保持する※単位はラジアン（方向転換時等に使用）
		int iPlayerNormalDashFlameCount; //通常ダッシュ時経過フレーム数（高速ダッシュへの移行に使用）

		//ジャンプ関係
		bool bPlayerJumpingFlag = false; //プレイヤーがジャンプ中かのフラグ
		int iPlayerJumpCount = 0; //プレイヤージャンプ回数
		float fPlayerJumpSpeed = 0.0f; //プレイヤージャンプ速度

		//回避関係
		bool bPlayerDodgingFlag = false; //プレイヤーが回避中かのフラグ
		float fPlayerDodgeProgress = 0.0f; // プレイヤー回避モーション進行率 (範囲：0.0～1.0)
		float fPlayerDodgeTime = 0.3f; // プレイヤー回避時間 
		VECTOR vecPlayerDodgeDirection = VGet(0, 0, 0); // プレイヤー回避方向
		float fPlayerDodgeSpeed = 0.0f; //プレイヤー回避速度
		int iPlayerDodgeWhileJumpingCount; //プレイヤージャンプ中の回避回数
		bool bPlayerAfterDodgeFlag;//プレイヤーの回避後フラグ



		/* 2025.01.09 菊池雅道 移動関連の変数追加終了 */

		DataList_Input*			InputList;			// 入力管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態
		DataList_Object*		ObjectList;			// オブジェクト管理

		/* 関数 */
		void	Player_Gravity();		// 重力
		void	Player_Move();			// 移動
		void	Player_Jump();			// ジャンプ

		void	CollisionUpdate();		// コリジョン更新
};
