//
//  QBasicDebugFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#include "QBasicDebugFunctions.h"

#include <iostream>

#include "QBasic.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicDebugFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
//	entity = QBasicStatementEntity("wait", 1, true, wait_qb);
//	statementList[entity.name] = entity;
//	entity = QBasicStatementEntity("log", 1, false, log_qb);
//	statementList[entity.name] = entity;
//	entity = QBasicStatementEntity("error", 1, false, error_qb);
//	statementList[entity.name] = entity;
	
	return statementList;
}

QBasicVariableEntity *QBasicDebugFunctions::wait_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	this_thread::sleep_for(chrono::milliseconds(stoi(arg[0])));
	return nullptr;
}
QBasicVariableEntity *QBasicDebugFunctions::print_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//#if COCOS2D_DEBUG
//	cout << arg[0] << "\n";
//#endif
	return nullptr;
}
QBasicVariableEntity *QBasicDebugFunctions::error_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	interpreter->setThrow(arg[0]);
	return nullptr;
}
