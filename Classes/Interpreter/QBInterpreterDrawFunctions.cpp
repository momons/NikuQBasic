//
//  QBInterpreterDrawFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#include "QBInterpreterDrawFunctions.h"

#include "QBInterpreter.h"
#include "QBInterpreterStatementEntity.h"
#include "QBInterpreterSubFunction.h"
#include "QBInterpreterScene.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterDrawFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;
	
	entity = QBInterpreterStatementEntity("color", 4, false, color_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("colorchg", 5, false, colorchg_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("linewidth", 1, false, linewidth_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("drawlock", 1, false, drawlock_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("hidden", 1, false, hidden_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("move", 3, false, move_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("moveadd", 3, false, moveadd_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("scale", 3, false, scale_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("scaleadd", 3, false, scaleadd_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("rotation", 2, false, rotation_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("rotationadd", 2, false, rotationadd_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("mirror", 3, false, mirror_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

#pragma mark - 描画

/// 色指定
string QBInterpreterDrawFunctions::color_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->subFunc->setColor(
								   (double)stoi(arg[0]) / 255.0f,
								   (double)stoi(arg[1]) / 255.0f,
								   (double)stoi(arg[2]) / 255.0f,
								   (double)stoi(arg[3]) / 255.0f
								   );
	return nullptr;
}
/// 色変更
string QBInterpreterDrawFunctions::colorchg_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return nullptr;
}
/// 線のサイズ指定
string QBInterpreterDrawFunctions::linewidth_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->subFunc->setLineWidth(stod(arg[0]));
	return nullptr;
}
/// 描画ロック
string QBInterpreterDrawFunctions::drawlock_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->subFunc->scene->drawLock = (arg[0].compare("1")==0);
	return nullptr;
}
/// 非表示
string QBInterpreterDrawFunctions::hidden_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->hidden();
	}
	return nullptr;
}
/// 指定位置に移動
string QBInterpreterDrawFunctions::move_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->moveNode(stod(arg[1]), stod(arg[2]));
	}
	return nullptr;
}
/// 現在地から移動
string QBInterpreterDrawFunctions::moveadd_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->moveAddNode(stod(arg[1]), stod(arg[2]));
	}
	return nullptr;
}
/// 拡大縮小
string QBInterpreterDrawFunctions::scale_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->scaleNode(stod(arg[1]), stod(arg[2]));
	}
	return nullptr;
}
/// 現在の状態から拡大縮小
string QBInterpreterDrawFunctions::scaleadd_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->scaleAddNode(stod(arg[1]), stod(arg[2]));
	}
	return nullptr;
}
/// 回転
string QBInterpreterDrawFunctions::rotation_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->rotationNode(stod(arg[1]));
	}
	return nullptr;
}
/// 現在の状態から回転
string QBInterpreterDrawFunctions::rotationadd_qb(QBInterpreter *interpreter, const vector<string> arg) {
	auto nodeEntity = interpreter->subFunc->scene->getSetupNode(stoi(arg[0]));
	if (nodeEntity != nullptr) {
		nodeEntity->rotationAddNode(stod(arg[1]));
	}
	return nullptr;
}
/// 反転
string QBInterpreterDrawFunctions::mirror_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return nullptr;
}

