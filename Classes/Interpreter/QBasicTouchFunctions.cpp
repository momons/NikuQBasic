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
string QBasicTouchFunctions::touchbegincnt_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(interpreter->subFunc->scene->touchBegin.size());
}
/// タッチ開始 X座標取得
string QBasicTouchFunctions::touchbeginx_qb(QBasic *interpreter, const vector<string> arg) {
	int index = stoi(arg[0]);
	if (index < 0 || index >= interpreter->subFunc->scene->touchBegin.size()) {
		return INVALID_TOUCH_LOCATION;
	}
	return StringUtil::toString(interpreter->subFunc->scene->touchBegin[index].x);
}
/// タッチ開始 Y座標取得
string QBasicTouchFunctions::touchbeginy_qb(QBasic *interpreter, const vector<string> arg) {
	int index = stoi(arg[0]);
	if (index < 0 || index >= interpreter->subFunc->scene->touchBegin.size()) {
		return INVALID_TOUCH_LOCATION;
	}
	return StringUtil::toString(interpreter->subFunc->scene->touchBegin[index].y);
}
/// タッチ移動 カウント
string QBasicTouchFunctions::touchmovecnt_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(interpreter->subFunc->scene->touchMove.size());
}
/// タッチ移動 X座標取得
string QBasicTouchFunctions::touchmovex_qb(QBasic *interpreter, const vector<string> arg) {
	int index = stoi(arg[0]);
	if (index < 0 || index >= interpreter->subFunc->scene->touchMove.size()) {
		return INVALID_TOUCH_LOCATION;
	}
	return StringUtil::toString(interpreter->subFunc->scene->touchMove[index].x);
}
/// タッチ移動 Y座標取得
string QBasicTouchFunctions::touchmovey_qb(QBasic *interpreter, const vector<string> arg) {
	int index = stoi(arg[0]);
	if (index < 0 || index >= interpreter->subFunc->scene->touchMove.size()) {
		return INVALID_TOUCH_LOCATION;
	}
	return StringUtil::toString(interpreter->subFunc->scene->touchMove[index].y);
}
/// タッチ終了 カウント
string QBasicTouchFunctions::touchendcnt_qb(QBasic *interpreter, const vector<string> arg) {
	return StringUtil::toString(interpreter->subFunc->scene->touchEnd.size());
}
/// タッチ終了 X座標取得
string QBasicTouchFunctions::touchendx_qb(QBasic *interpreter, const vector<string> arg) {
	int index = stoi(arg[0]);
	if (index < 0 || index >= interpreter->subFunc->scene->touchEnd.size()) {
		return INVALID_TOUCH_LOCATION;
	}
	return StringUtil::toString(interpreter->subFunc->scene->touchEnd[index].x);
}
/// タッチ終了 Y座標取得
string QBasicTouchFunctions::touchendy_qb(QBasic *interpreter, const vector<string> arg) {
	int index = stoi(arg[0]);
	if (index < 0 || index >= interpreter->subFunc->scene->touchEnd.size()) {
		return INVALID_TOUCH_LOCATION;
	}
	return StringUtil::toString(interpreter->subFunc->scene->touchEnd[index].y);
}
