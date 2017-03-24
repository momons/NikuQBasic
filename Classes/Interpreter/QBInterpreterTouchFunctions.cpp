//
//  QBInterpreterTouchFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/21.
//
//

#include "QBInterpreterTouchFunctions.h"

#include "QBInterpreter.h"
#include "StringUtil.h"
#include "QBInterpreterStatementEntity.h"
#include "QBInterpreterSubFunction.h"
#include "QBInterpreterScene.h"

/** 範囲外の場合の座標 **/
#define INVALID_TOUCH_LOCATION		"-9999"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterTouchFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;
	
	entity = QBInterpreterStatementEntity("touchbegincnt", 0, true, touchbegincnt_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("touchbeginx", 1, true, touchbeginx_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("touchbeginy", 1, true, touchbeginy_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("touchmovecnt", 0, true, touchmovecnt_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("touchmovex", 1, true, touchmovex_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("touchmovey", 1, true, touchmovey_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("touchendcnt", 0, true, touchendcnt_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("touchendx", 1, true, touchendx_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("touchendy", 1, true, touchendy_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// タッチ開始 カウント
string QBInterpreterTouchFunctions::touchbegincnt_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(interpreter->subFunc->scene->touchBegin.size());
}
/// タッチ開始 X座標取得
string QBInterpreterTouchFunctions::touchbeginx_qb(QBInterpreter *interpreter, const vector<string> arg) {
	int index = stoi(arg[0]);
	if (index < 0 || index >= interpreter->subFunc->scene->touchBegin.size()) {
		return INVALID_TOUCH_LOCATION;
	}
	return StringUtil::toString(interpreter->subFunc->scene->touchBegin[index].x);
}
/// タッチ開始 Y座標取得
string QBInterpreterTouchFunctions::touchbeginy_qb(QBInterpreter *interpreter, const vector<string> arg) {
	int index = stoi(arg[0]);
	if (index < 0 || index >= interpreter->subFunc->scene->touchBegin.size()) {
		return INVALID_TOUCH_LOCATION;
	}
	return StringUtil::toString(interpreter->subFunc->scene->touchBegin[index].y);
}
/// タッチ移動 カウント
string QBInterpreterTouchFunctions::touchmovecnt_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(interpreter->subFunc->scene->touchMove.size());
}
/// タッチ移動 X座標取得
string QBInterpreterTouchFunctions::touchmovex_qb(QBInterpreter *interpreter, const vector<string> arg) {
	int index = stoi(arg[0]);
	if (index < 0 || index >= interpreter->subFunc->scene->touchMove.size()) {
		return INVALID_TOUCH_LOCATION;
	}
	return StringUtil::toString(interpreter->subFunc->scene->touchMove[index].x);
}
/// タッチ移動 Y座標取得
string QBInterpreterTouchFunctions::touchmovey_qb(QBInterpreter *interpreter, const vector<string> arg) {
	int index = stoi(arg[0]);
	if (index < 0 || index >= interpreter->subFunc->scene->touchMove.size()) {
		return INVALID_TOUCH_LOCATION;
	}
	return StringUtil::toString(interpreter->subFunc->scene->touchMove[index].y);
}
/// タッチ終了 カウント
string QBInterpreterTouchFunctions::touchendcnt_qb(QBInterpreter *interpreter, const vector<string> arg) {
	return StringUtil::toString(interpreter->subFunc->scene->touchEnd.size());
}
/// タッチ終了 X座標取得
string QBInterpreterTouchFunctions::touchendx_qb(QBInterpreter *interpreter, const vector<string> arg) {
	int index = stoi(arg[0]);
	if (index < 0 || index >= interpreter->subFunc->scene->touchEnd.size()) {
		return INVALID_TOUCH_LOCATION;
	}
	return StringUtil::toString(interpreter->subFunc->scene->touchEnd[index].x);
}
/// タッチ終了 Y座標取得
string QBInterpreterTouchFunctions::touchendy_qb(QBInterpreter *interpreter, const vector<string> arg) {
	int index = stoi(arg[0]);
	if (index < 0 || index >= interpreter->subFunc->scene->touchEnd.size()) {
		return INVALID_TOUCH_LOCATION;
	}
	return StringUtil::toString(interpreter->subFunc->scene->touchEnd[index].y);
}
