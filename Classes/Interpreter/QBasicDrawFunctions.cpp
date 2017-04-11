//
//  QBasicDrawFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#include "QBasicDrawFunctions.h"

#include "QBasic.h"
#include "QBasicStatementEntity.h"
#include "QBasicSubFunction.h"
#include "QBasicScene.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicDrawFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("color", 4, false, color_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("colorchg", 5, false, colorchg_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("linewidth", 1, false, linewidth_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("drawlock", 1, false, drawlock_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("hidden", 1, false, hidden_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("move", 3, false, move_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("moveadd", 3, false, moveadd_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("scale", 3, false, scale_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("scaleadd", 3, false, scaleadd_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("rotation", 2, false, rotation_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("rotationadd", 2, false, rotationadd_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("mirror", 3, false, mirror_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

#pragma mark - 描画

/// 色指定
string QBasicDrawFunctions::color_qb(QBasic *interpreter, const vector<string> arg) {
	interpreter->subFunc->setColor(
								   (double)stoi(arg[0]) / 255.0f,
								   (double)stoi(arg[1]) / 255.0f,
								   (double)stoi(arg[2]) / 255.0f,
								   (double)stoi(arg[3]) / 255.0f
								   );
	return nullptr;
}
/// 色変更
string QBasicDrawFunctions::colorchg_qb(QBasic *interpreter, const vector<string> arg) {
	return nullptr;
}
/// 線のサイズ指定
string QBasicDrawFunctions::linewidth_qb(QBasic *interpreter, const vector<string> arg) {
	interpreter->subFunc->setLineWidth(stod(arg[0]));
	return nullptr;
}
/// 描画ロック
string QBasicDrawFunctions::drawlock_qb(QBasic *interpreter, const vector<string> arg) {
	interpreter->subFunc->scene->drawLock = (arg[0].compare("1")==0);
	return nullptr;
}
/// 非表示
string QBasicDrawFunctions::hidden_qb(QBasic *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->hidden();
	}
	return nullptr;
}
/// 指定位置に移動
string QBasicDrawFunctions::move_qb(QBasic *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->moveNode(stod(arg[1]), stod(arg[2]));
	}
	return nullptr;
}
/// 現在地から移動
string QBasicDrawFunctions::moveadd_qb(QBasic *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->moveAddNode(stod(arg[1]), stod(arg[2]));
	}
	return nullptr;
}
/// 拡大縮小
string QBasicDrawFunctions::scale_qb(QBasic *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->scaleNode(stod(arg[1]), stod(arg[2]));
	}
	return nullptr;
}
/// 現在の状態から拡大縮小
string QBasicDrawFunctions::scaleadd_qb(QBasic *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->scaleAddNode(stod(arg[1]), stod(arg[2]));
	}
	return nullptr;
}
/// 回転
string QBasicDrawFunctions::rotation_qb(QBasic *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->rotationNode(stod(arg[1]));
	}
	return nullptr;
}
/// 現在の状態から回転
string QBasicDrawFunctions::rotationadd_qb(QBasic *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->rotationAddNode(stod(arg[1]));
	}
	return nullptr;
}
/// 反転
string QBasicDrawFunctions::mirror_qb(QBasic *interpreter, const vector<string> arg) {
	return nullptr;
}

