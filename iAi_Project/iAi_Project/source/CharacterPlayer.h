/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Input.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Object.h"

//ゲーム全般の設定に関する設定値
namespace GAME_SETTING
{
	const float STICK_DEAD_ZONE = 100; //スティック入力のデッドゾーン（範囲：０～１０００）
	const int GAME_FRAMES_PER_SECOND = 60; //ゲームの設定FPS
}

using namespace GAME_SETTING;

// 計算用マクロ
//#define	PI	(3.1415926535897932386f)
//#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
//#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )
//#define	ACCELERATION(x)	( (x) / GAME_FRAMES_PER_SECOND * GAME_FRAMES_PER_SECOND ) //加速度計算マクロ





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

		//DataList_Input*			InputList;			// 入力管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態
		DataList_Object*		ObjectList;			// オブジェクト管理

		/* 関数 */
		void	Player_Gravity();		// 重力
		void	Player_Move();			// 移動
		void	Player_Jump();			// ジャンプ

		void	CollisionUpdate();		// コリジョン更新
};
