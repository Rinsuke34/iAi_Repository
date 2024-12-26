/* 2024.12.08 駒沢風助 ファイル作成 */

#pragma once
#include <DxLib.h>

/* AppFrameで使用する構造体の宣言 */

// 入力関連
namespace Struct_Input
{
	struct PLAYER_INPUT_JOYPAD	// プレイヤー入力(ジョイパッド)
	{
		/* ジョイパッド */
		int	    igInput[3];			// ジョイパッド入力(0:ホールド、1:トリガ、2:リリース)

		/* ジョイパッド(左アナログスティック) */
		int		iXAnalog;		// X軸アナログ入力
		int		iYAnalog;		// Y軸アナログ入力
	};
	
	struct PLAYER_INPUT_KEYBOARD_MOUSE	// プレイヤー入力(キーボード、マウス)
	{
		/* キーボード */
		char	cgInput[3][256];	// キー入力(0:ホールド、1:トリガ、2:リリース)

		/* マウス */
		int	    igInput[3];		// 入力(0:ホールド、1:トリガ、2:リリース)

		int		iMouseMoveX;	// X移動量
		int		iMouseMoveY;	// Y移動量
	};
}

// コリジョン関連
namespace Struct_Collision
{
	struct COLLISION_CAPSULE	// カプセルコリジョン
	{
		VECTOR	vecCapsuleTop;		// カプセルの上部
		VECTOR	vecCapsuleBottom;	// カプセルの下部
		float	fCapsuleRadius;		// カプセルの半径
	};

	struct COLLISION_SQHERE		// 球体コリジョン
	{
		VECTOR	vecSqhere;			// 球体の中心
		float	fSqhereRadius;		// 球体の半径
	};
};