//
//  QBasicSubFunction.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/06/02.
//
//

#ifndef __NikuQBasic__QBasicSubFunction__
#define __NikuQBasic__QBasicSubFunction__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class QBasicScene;
class QBUserDefaultsManager;

/**
 *  スクリプト　サブファンクション
 */
class QBasicSubFunction final {
public:
	
	/** シーン */
	QBasicScene *scene;
	
	/** セーブ */
	QBUserDefaultsManager *userDefaultsManager;
	
	/**
	 *  コンストラクタ
	 *  @param scene     シーン
	 *  @param projectId プロジェクトId
	 */
	QBasicSubFunction(QBasicScene *scene, const string &projectId);

	/**
	 *  デストラクタ
	 */
	~QBasicSubFunction();
	
	/**
	 *  初期化
	 */
	void init();

#pragma mark - 描画
	
	/**
	 *  カラー設定
	 *  @param r 赤
	 *  @param g 緑
	 *  @param b 青
	 *  @param a 透明度
	 */
	void setColor(const double r, const double g, const double b, const double a);
	
	/**
	 *  線の太さを設定
	 *  @param width 線の太さ
	 */
	void setLineWidth(const double width);
	
#pragma mark - 図形
	
	/**
	 *  線描画
	 *  @param index インデックス
	 *  @param x1    X座標1
	 *  @param y1    Y座標1
	 *  @param x2    X座標2
	 *  @param y2    Y座標2
	 */
	void drawLine(const int index, const double x1, const double y1, const double x2, const double y2);
	
	/**
	 *  線四角描画
	 *  @param index  インデックス
	 *  @param x      X座標
	 *  @param y      Y座標
	 *  @param width  幅
	 *  @param height 高さ
	 *  @param isFill 塗りつぶし
	 */
	void drawRect(const int index, const double x, const double y, const double width, const double height, const bool isFill);
	
	/**
	 *  三角描画
	 *  @param index  インデックス
	 *  @param x1     X座標
	 *  @param y1     X座標
	 *  @param x2     Y座標
	 *  @param y2     X座標
	 *  @param x3     Y座標
	 *  @param y3     Y座標
	 *  @param isFill 塗りつぶし
	 */
	void drawTriangle(const int index, const double x1, const double y1, const double x2, const double y2, const double x3, const double y3,const bool isFill);
	
	/**
	 *  円描画
	 *  @param index  インデックス
	 *  @param x      X座標
	 *  @param y      Y座標
	 *  @param width  幅
	 *  @param height 高さ
	 *  @param isFill 塗りつぶし
	 */
	void drawCircle(const int index, const double x, const double y, const double width, const double height, const bool isFill);
	
#pragma mark - 文字
	
	/**
	 *  フォント設定
	 *  @param fontName フォント名
	 *  @param fontSize フォントサイズ
	 */
	void setFont(const string fontName, const double fontSize);
	
	/**
	 *  テキスト描画
	 *  @param index インデックス
	 *  @param text  テキスト
	 *  @param x     X座標
	 *  @param y     Y座標
	 */
	void drawText(const int index, const string &text, const double x, const double y);

#pragma mark - パーティクル

	/**
	 *  パーティクル描画
	 *  @param index         インデックス
	 *  @param particleIndex パーティクルインデックス
	 *  @param x             X座標
	 *  @param y             Y座標
	 */
	void drawParticle(const int index, const int particleIndex, const double x, const double y);
	
private:
	
	/** 現在のカラー */
	Color4F color;
	
	/** 線の太さ */
	double lineWidth;
	
	/** 現在のフォント */
	string fontName;
	
	/** 現在のフォントサイズ */
	double fontSize;

	/** プロジェクトId */
	string projectId;
	
};

#endif /* defined(__NikuQBasic__QBasicSubFunction__) */
