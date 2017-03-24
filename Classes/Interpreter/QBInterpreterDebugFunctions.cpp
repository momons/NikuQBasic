//
//  QBInterpreterDebugFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#include "QBInterpreterDebugFunctions.h"

#include <iostream>

#include "QBInterpreter.h"
#include "QBInterpreterStatementEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterDebugFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;
	
	entity = QBInterpreterStatementEntity("wait", 1, true, wait_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("log", 1, false, log_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("error", 1, false, error_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

string QBInterpreterDebugFunctions::wait_qb(QBInterpreter *interpreter, const vector<string> arg) {
	this_thread::sleep_for(chrono::milliseconds(stoi(arg[0])));
	return "";
}
string QBInterpreterDebugFunctions::log_qb(QBInterpreter *interpreter, const vector<string> arg) {
#if COCOS2D_DEBUG
	cout << arg[0] << "\n";
#endif
	return "";
}
string QBInterpreterDebugFunctions::error_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->setThrow(arg[0]);
	return "";
}
