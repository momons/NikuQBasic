//
//  QBasicSetupNodeEntity.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/05/03.
//
//

#include "QBasicSetupNodeEntity.h"

/**
 *  コンストラクタ
 */
QBasicSetupNodeEntity::QBasicSetupNodeEntity() {
	scaleX = 1;
	scaleY = 1;
}

/**
 *  デストラクタ
 */
QBasicSetupNodeEntity::~QBasicSetupNodeEntity() {
	
	
}

#pragma mark - 描画

/**
 *  ノード消去
 */
void QBasicSetupNodeEntity::hidden() {
	setupTypes.push_back(QBasicSetupType::Hidden);
}

/**
 *  移動
 *  @param moveX 移動X
 *  @param moveY 移動Y
 */
void QBasicSetupNodeEntity::moveNode(const double moveX, const double moveY) {
	this->moveX = moveX;
	this->moveY = moveY;
	setupTypes.push_back(QBasicSetupType::Move);
}

/**
 *  追加移動
 *  @param moveX 移動X
 *  @param moveY 移動Y
 */
void QBasicSetupNodeEntity::moveAddNode(const double moveX, const double moveY) {
	this->moveX = moveX;
	this->moveY = moveY;
	setupTypes.push_back(QBasicSetupType::MoveAdd);
}

/**
 *  拡大縮小
 *  @param scaleX 拡大幅
 *  @param scaleY 拡大高さ
 */
void QBasicSetupNodeEntity::scaleNode(const double scaleX, const double scaleY) {
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	setupTypes.push_back(QBasicSetupType::Scale);
}

/**
 *  追加拡大縮小
 *  @param scaleX 拡大幅
 *  @param scaleY 拡大高さ
 */
void QBasicSetupNodeEntity::scaleAddNode(const double scaleX, const double scaleY) {
	this->scaleX *= scaleX;
	this->scaleY *= scaleY;
	setupTypes.push_back(QBasicSetupType::ScaleAdd);
}

/**
 *  回転
 *  @param rotation 回転
 */
void QBasicSetupNodeEntity::rotationNode(const double rotation) {
	this->rotation = rotation;
	setupTypes.push_back(QBasicSetupType::Rotation);
}

/**
 *  追加回転
 *  @param rotation 回転
 */
void QBasicSetupNodeEntity::rotationAddNode(const double rotation) {
	this->rotation += rotation;
	setupTypes.push_back(QBasicSetupType::RotationAdd);
}

#pragma mark - 図形

/**
 *  線設定
 *  @param x1        X座標1
 *  @param y1        Y座標1
 *  @param x2        X座標2
 *  @param y2        Y座標2
 *  @param color     カラー
 *  @param lineWidth 線の太さ
 */
void QBasicSetupNodeEntity::line(
								   const double x1,
								   const double y1,
								   const double x2,
								   const double y2,
								   const Color4F color,
								   const double lineWidth
								   ) {
	setupTypes.clear();
	setupTypes.push_back(QBasicSetupType::Create);
	type = QBasicSetupNodeType::Line;
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->color = color;
	this->lineWidth = lineWidth;
	centerX = (x1 + x2) / 2;
	centerY = (y1 + y2) / 2;
}

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
void QBasicSetupNodeEntity::rect(
								   const double x,
								   const double y,
								   const double width,
								   const double height,
								   const Color4F color,
								   const double lineWidth,
								   const bool isFill
								   ) {
	setupTypes.clear();
	setupTypes.push_back(QBasicSetupType::Create);
	type = QBasicSetupNodeType::Rect;
	this->x1 = x;
	this->y1 = y;
	this->width = width;
	this->height = height;
	this->color = color;
	this->lineWidth = lineWidth;
	this->isFill = isFill;
	centerX = x + width / 2;
	centerY = y + height / 2;
}

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
void QBasicSetupNodeEntity::triangle(
									   const double x1,
									   const double y1,
									   const double x2,
									   const double y2,
									   const double x3,
									   const double y3,
									   const Color4F color,
									   const double lineWidth,
									   const bool isFill
									   ) {
	setupTypes.clear();
	setupTypes.push_back(QBasicSetupType::Create);
	type = QBasicSetupNodeType::Triangle;
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->x3 = x3;
	this->y3 = y3;
	this->color = color;
	this->lineWidth = lineWidth;
	this->isFill = isFill;
	centerX = (x1 + x2 + x3) / 3;
	centerY = (y1 + y2 + y3) / 3;
}

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
void QBasicSetupNodeEntity::circle(
									 const double x,
									 const double y,
									 const double width,
									 const double height,
									 const Color4F color,
									 const double lineWidth,
									 const bool isFill
									 ) {
	setupTypes.clear();
	setupTypes.push_back(QBasicSetupType::Create);
	type = QBasicSetupNodeType::Circle;
	this->x1 = x;
	this->y1 = y;
	this->width = width;
	this->height = height;
	this->color = color;
	this->lineWidth = lineWidth;
	this->isFill = isFill;
	centerX = x;
	centerY = y;
}

#pragma mark - 文字

/**
 *  テキスト
 *  @param text     テキスト
 *  @param x        X座標
 *  @param y        Y座標
 *  @param color    カラー
 *  @param fontName フォント名
 *  @param fontSize フォントサイズ
 */
void QBasicSetupNodeEntity::drawText(
									   const string text,
									   const double x,
									   const double y,
									   const Color4F color,
									   const string fontName,
									   const double fontSize
									   ) {
	setupTypes.clear();
	setupTypes.push_back(QBasicSetupType::Create);
	type = QBasicSetupNodeType::Text;
	this->text = text;
	this->x1 = x;
	this->y1 = y;
	this->color = color;
	this->fontName = fontName;
	this->fontSize = fontSize;
	centerX = x;
	centerY = y;
}

#pragma mark - パーティクル

/**
 *  パーティクル
 *  @param index インデックス
 *  @param x     X座標
 *  @param y     Y座標
 */
void QBasicSetupNodeEntity::drawParticle(
										  const int index,
										  const double x,
										  const double y
										   ) {
	setupTypes.clear();
	setupTypes.push_back(QBasicSetupType::Create);
	type = QBasicSetupNodeType::Particle;
	this->index = index;
	this->x1 = x;
	this->y1 = y;
	centerX = x;
	centerY = y;
}

