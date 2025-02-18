/* 2024.01.03 駒沢風助 ファイル作成 */

#pragma once

/* 前方参照 */
// ※AppFrameで定義されていないクラスを使用する場合、循環参照対策に実施する。
class EnemyBasic;

/* プロジェクトで使用する構造体の宣言 */

// 座標(2D上)
// ※可読性向上のため、名称に数字を使用
struct st2DPosition
{
	int ix;
	int iy;
};

// 指定箇所とエネミーの距離判定用の構造体
struct NearEnemy
{
	EnemyBasic* pEnemy;		// エネミーのポインタ
	float fDistance;		// 画面中心からの距離(軽量化のため座標の差の二乗)
};
