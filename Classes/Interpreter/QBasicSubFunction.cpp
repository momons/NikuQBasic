//
//  QBasicSubFunction.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/06/02.
//
//

#include "QBasicSubFunction.h"

#include "QBasicSetupNodeEntity.h"
#include "QBasicScene.h"

/**
 *  コンストラクタ
 *  @param scene     シーン
 *  @param projectId プロジェクトId
 */
QBasicSubFunction::QBasicSubFunction(QBasicScene *scene, const string &projectId) {
	
	// 退避
	this->scene = scene;
	this->projectId = projectId;
	
	// 初期化
	init();
}

/**
 *  デストラクタ
 */
QBasicSubFunction::~QBasicSubFunction() {
}

/**
 *  初期化
 */
void QBasicSubFunction::init() {

	color = cocos2d::Color4F(0, 0, 0, 1);
	lineWidth = 1;
	fontName = "";
	fontSize = 10;
	
}

#pragma mark - 描画

/**
 *  カラー設定
 *  @param r 赤
 *  @param g 緑
 *  @param b 青
 *  @param a 透明度
 */
void QBasicSubFunction::setColor(const double r, const double g, const double b, const double a) {
	color = Color4F(r, g, b, a);
}

/**
 *  線の太さを設定
 *  @param width 線の太さ
 */
void QBasicSubFunction::setLineWidth(const double width) {
	lineWidth = width;
}

#pragma mark - 図形

/**
 *  線描画
 *  @param index インデックス
 *  @param x1    X座標1
 *  @param y1    Y座標1
 *  @param x2    X座標2
 *  @param y2    Y座標2
 */
void QBasicSubFunction::drawLine(const int index, const double x1, const double y1, const double x2, const double y2) {
	auto entity = QBasicSetupNodeEntity();
	entity.line(x1, y1, x2, y2, color, lineWidth);
	scene->addNode(index, entity);
}

/**
 *  四角描画
 *  @param index  インデックス
 *  @param x      X座標
 *  @param y      Y座標
 *  @param width  幅
 *  @param height 高さ
 *  @param isFill 塗りつぶし
 */
void QBasicSubFunction::drawRect(const int index, const double x, const double y, const double width, const double height, const bool isFill) {
	auto entity = QBasicSetupNodeEntity();
	entity.rect(x, y, width, height, color, lineWidth, isFill);
	this->scene->addNode(index, entity);
}

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
void QBasicSubFunction::drawTriangle(const int index, const double x1, const double y1, const double x2, const double y2, const double x3, const double y3, const bool isFill) {
	auto entity = QBasicSetupNodeEntity();
	entity.triangle(x1, y1, x2, y2, x3, y3, color, lineWidth, isFill);
	this->scene->addNode(index, entity);
}

/**
 *  円描画
 *  @param index  インデックス
 *  @param x      X座標
 *  @param y      Y座標
 *  @param width  幅
 *  @param height 高さ
 *  @param isFill 塗りつぶし
 */
void QBasicSubFunction::drawCircle(const int index, const double x, const double y, const double width, const double height, const bool isFill) {
	auto entity = QBasicSetupNodeEntity();
	entity.circle(x, y, width, height, color, lineWidth, isFill);
	this->scene->addNode(index, entity);
}

#pragma mark - 文字描画

/**
 *  フォント設定
 *  @param fontName フォント名
 *  @param fontSize フォントサイズ
 */
void QBasicSubFunction::setFont(const string fontName, const double fontSize) {
	this->fontName = fontName;
	this->fontSize = fontSize;
}

/**
 *  テキスト描画
 *  @param index インデックス
 *  @param text  テキスト
 *  @param x     X座標
 *  @param y     Y座標
 */
void QBasicSubFunction::drawText(const int index, const string &text, const double x, const double y) {
	auto entity = QBasicSetupNodeEntity();
	entity.drawText(text, x, y, color, fontName, fontSize);
	this->scene->addNode(index, entity);
}

#pragma mark - パーティクル

/**
 *  パーティクル描画
 *  @param index         インデックス
 *  @param particleIndex パーティクルインデックス
 *  @param x             X座標
 *  @param y             Y座標
 */
void QBasicSubFunction::drawParticle(const int index, const int particleIndex, const double x, const double y) {
	auto entity = QBasicSetupNodeEntity();
	entity.drawParticle(particleIndex, x, y);
	this->scene->addNode(index, entity);
}

#pragma mark - 通信

