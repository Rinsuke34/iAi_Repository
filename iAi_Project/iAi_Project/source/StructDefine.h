/* 2024.01.03 駒沢風助 ファイル作成 */

#pragma once

/* 前方参照 */
// ※AppFrameで定義されていないクラスを使用する場合、循環参照対策に実施する。
class Enemy_Basic;

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
	Enemy_Basic* pEnemy;		// エネミーのポインタ
	float fDistance;		// 画面中心からの距離(軽量化のため座標の差の二乗)
};

// 会話パート用のテキストデータ
struct TEXT_DATA
{
	std::string	aText;				// 文章
	int			iFocusCharacter;	// 立ち絵を手前に持ってくるキャラクター(0:どちらも持ってこない / 1:左 / 2:右 / 3:両方 )
	int			iLeftCharactorCg;	// 左のキャラクターの立ち絵No
	int			iRightCharactorCg;	// 右のキャラクターの立ち絵No
	int			iSpeed;				// 描写速度
	int			iVoiceNo;			// ボイス番号
};
