//
//  QBasicTouchFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/21.
//
//

#include "QBasicTouchFunctions.h"

#include "QBasic.h"
#include "StringUtil.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"
#include "QBasicSubFunction.h"
#include "QBasicScene.h"

/** 範囲外の場合の座標 **/
#define INVALID_TOUCH_LOCATION		"-9999"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicTouchFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("touchbegincnt", 0, true, touchbegincnt_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("touchbeginx", 1, true, touchbeginx_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("touchbeginy", 1, true, touchbeginy_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("touchmovecnt", 0, true, touchmovecnt_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("touchmovex", 1, true, touchmovex_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("touchmovey", 1, true, touchmovey_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("touchendcnt", 0, true, touchendcnt_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("touchendx", 1, true, touchendx_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("touchendy", 1, true, touchendy_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// タッチ開始 カウント
QBasicVariableEntity *QBasicTouchFunctions::touchbegincnt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(interpreter->subFunc->scene->touchBegin.size());
	return nullptr;
}
/// タッチ開始 X座標取得
QBasicVariableEntity *QBasicTouchFunctions::touchbeginx_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	int index = stoi(arg[0]);
//	if (index < 0 || index >= interpreter->subFunc->scene->touchBegin.size()) {
//		return INVALID_TOUCH_LOCATION;
//	}
//	return StringUtil::toString(interpreter->subFunc->scene->touchBegin[index].x);
	return nullptr;
}
/// タッチ開始 Y座標取得
QBasicVariableEntity *QBasicTouchFunctions::touchbeginy_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	int index = stoi(arg[0]);
//	if (index < 0 || index >= interpreter->subFunc->scene->touchBegin.size()) {
//		return INVALID_TOUCH_LOCATION;
//	}
//	return StringUtil::toString(interpreter->subFunc->scene->touchBegin[index].y);
	return nullptr;
}
/// タッチ移動 カウント
QBasicVariableEntity *QBasicTouchFunctions::touchmovecnt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(interpreter->subFunc->scene->touchMove.size());
	return nullptr;
}
/// タッチ移動 X座標取得
QBasicVariableEntity *QBasicTouchFunctions::touchmovex_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	int index = stoi(arg[0]);
//	if (index < 0 || index >= interpreter->subFunc->scene->touchMove.size()) {
//		return INVALID_TOUCH_LOCATION;
//	}
//	return StringUtil::toString(interpreter->subFunc->scene->touchMove[index].x);
	return nullptr;
}
/// タッチ移動 Y座標取得
QBasicVariableEntity *QBasicTouchFunctions::touchmovey_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	int index = stoi(arg[0]);
//	if (index < 0 || index >= interpreter->subFunc->scene->touchMove.size()) {
//		return INVALID_TOUCH_LOCATION;
//	}
//	return StringUtil::toString(interpreter->subFunc->scene->touchMove[index].y);
	return nullptr;
}
/// タッチ終了 カウント
QBasicVariableEntity *QBasicTouchFunctions::touchendcnt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(interpreter->subFunc->scene->touchEnd.size());
	return nullptr;
}
/// タッチ終了 X座標取得
QBasicVariableEntity *QBasicTouchFunctions::touchendx_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	int index = stoi(arg[0]);
//	if (index < 0 || index >= interpreter->subFunc->scene->touchEnd.size()) {
//		return INVALID_TOUCH_LOCATION;
//	}
//	return StringUtil::toString(interpreter->subFunc->scene->touchEnd[index].x);
	return nullptr;
}
/// タッチ終了 Y座標取得
QBasicVariableEntity *QBasicTouchFunctions::touchendy_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	int index = stoi(arg[0]);
//	if (index < 0 || index >= interpreter->subFunc->scene->touchEnd.size()) {
//		return INVALID_TOUCH_LOCATION;
//	}
//	return StringUtil::toString(interpreter->subFunc->scene->touchEnd[index].y);
	return nullptr;
}
