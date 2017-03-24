//
//  QBInterpreterSetupNodeEntity.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/05/03.
//
//

#ifndef __NikuQBasic__QBInterpreterSetupNodeEntity__
#define __NikuQBasic__QBInterpreterSetupNodeEntity__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

/// enum→数値変換用マクロ
#define ENUM_INT(value) static_cast<int>(value)
/// 数値→QBInterpreterSetupNodeType変換用マクロ
#define SETUP_NODE_TYPE_RAW_VALUE(value) static_cast<QBInterpreterSetupNodeType>(value)
/// 数値→QBInterpreterSetupType変換用マクロ
#define SETUP_TYPE_RAW_VALUE(value) static_cast<QBInterpreterSetupType>(value)

/// 円の頂点の数
#define CIRCLE_POINT_COUNT		48

/// ノードタイプ
enum class QBInterpreterSetupNodeType {
	Line,		/// 線
	Rect,		/// 四角
	Circle,		/// 円
	Triangle,	/// 三角
	Text,		/// 文字
	Image,		/// 画像
	Particle,	/// パーティクル
};

/// 処理フラグ
enum class QBInterpreterSetupType {
	Hidden,			/// 消去
	Create,			/// 作成
	Move,			/// 移動
	MoveAdd,		/// 追加移動
	Scale,			/// 拡大縮小
	ScaleAdd,		/// 追加拡大縮小
	Rotation,		/// 回転
	RotationAdd,	/// 追加回転
	Mirror,			/// ミラー
};

/**
 *  スクリプト ステートメントEntity
 */
class QBInterpreterSetupNodeEntity final {
public:
	
	/** 処理フラグ */
	vector<QBInterpreterSetupType> setupTypes;
	
	/** ノードタイプ */
	QBInterpreterSetupNodeType type;
	
	/** インデックス */
	int index;
	/** 中心X座標 */
	double centerX;
	/** 中心Y座標 */
	double centerY;
	/** X座標 */
	double x1;
	/** Y座標 */
	double y1;
	/** X座標 */
	double x2;
	/** Y座標 */
	double y2;
	/** X座標 */
	double x3;
	/** Y座標 */
	double y3;
	
	/** 幅 */
	double width;
	/** 高さ */
	double height;
	
	/** 色 */
	Color4F color;
	
	/** 線の太さ */
	double lineWidth;
	
	/** 塗りつぶし */
	bool isFill;
	
	/** 文字 */
	string text;

	/** フォント名 */
	string fontName;
	
	/** フォントサイズ */
	double fontSize;

	/** 移動X */
	double moveX;
	/** 移動Y */
	double moveY;
	
	/** 拡大X */
	double scaleX;
	/** 拡大Y */
	double scaleY;
	
	/** 回転 */
	double rotation;
	
	/**
	 *  コンストラクタ
	 */
	QBInterpreterSetupNodeEntity();
	
	/**
	 *  デストラクタ
	 */
	~QBInterpreterSetupNodeEntity();

	/**
	 *  ノード消去
	 */
	void hidden();
	
	/**
	 *  移動
	 *  @param moveX 移動X
	 *  @param moveY 移動Y
	 */
	void moveNode(const double moveX, const double moveY);
	
	/**
	 *  追加移動
	 *  @param moveX 移動X
	 *  @param moveY 移動Y
	 */
	void moveAddNode(const double moveX, const double moveY);
	
	/**
	 *  拡大縮小
	 *  @param scaleX 拡大幅
	 *  @param scaleY 拡大高さ
	 */
	void scaleNode(const double scaleX, const double scaleY);
	
	/**
	 *  追加拡大縮小
	 *  @param scaleX 拡大幅
	 *  @param scaleY 拡大高さ
	 */
	void scaleAddNode(const double scaleX, const double scaleY);
	
	/**
	 *  回転
	 *  @param rotation 回転
	 */
	void rotationNode(const double rotation);
	
	/**
	 *  追加回転
	 *  @param rotation 回転
	 */
	void rotationAddNode(const double rotation);
	
	/**
	 *  線設定
	 *  @param x1        X座標1
	 *  @param y1        Y座標1
	 *  @param x2        X座標2
	 *  @param y2        Y座標2
	 *  @param color     カラー
	 *  @param lineWidth 線の太さ
	 */
	void line(
			  const double x1,
			  const double y1,
			  const double x2,
			  const double y2,
			  const Color4F color,
			  const double lineWidth
			  );
	
	/**
	 *  四角の設定
	 *  @param x         X座標
	 *  @param y         Y座標
	 *  @param width     幅
	 *  @param height    高さ
	 *  @param color     カラー
	 *  @param lineWidth 線の太さ
	 *  @param isFill    塗りつぶし
	 */
	void rect(
			  const double x,
			  const double y,
			  const double width,
			  const double height,
			  const Color4F color,
			  const double lineWidth,
			  const bool isFill
			  );
	
	/**
	 *  三角の設定
	 *  @param x1        X座標
	 *  @param y1        Y座標
	 *  @param x2        X座標
	 *  @param y2        Y座標
	 *  @param x3        X座標
	 *  @param y3        Y座標
	 *  @param color     カラー
	 *  @param lineWidth 線の太さ
	 *  @param isFill    塗りつぶし
	 */
	void triangle(
			   const double x1,
			   const double y1,
			   const double x2,
			   const double y2,
			   const double x3,
			   const double y3,
			   const Color4F color,
			   const double lineWidth,
			   const bool isFill
			   );
	
	/**
	 *  円の設定
	 *  @param x         X座標
	 *  @param y         Y座標
	 *  @param width     幅
	 *  @param height    高さ
	 *  @param color     カラー
	 *  @param lineWidth 線の太さ
	 *  @param isFill    塗りつぶし
	 */
	void circle(
			   const double x,
			   const double y,
			   const double width,
			   const double height,
			   const Color4F color,
			   const double lineWidth,
			   const bool isFill
			   );
	
	/**
	 *  テキスト
	 *  @param text     テキスト
	 *  @param x        X座標
	 *  @param y        Y座標
	 *  @param color    カラー
	 *  @param fontName フォント名
	 *  @param fontSize フォントサイズ
	 */
	void drawText(
				  const string text,
				  const double x,
				  const double y,
				  const Color4F color,
				  const string fontName,
				  const double fontSize
				  );
	
	/**
	 *  パーティクル
	 *  @param index インデックス
	 *  @param x     X座標
	 *  @param y     Y座標
	 */
	void drawParticle(
					  const int index,
					  const double x,
					  const double y
					  );
};

#endif /* defined(__NikuQBasic__QBInterpreterSetupNodeEntity__) */
