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
	
	entity = QBasicStatementEntity("wait", wait_params(), VariableType::Void, wait_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("print", print_params(), VariableType::Void, print_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("error", error_params(), VariableType::Void, error_qb);
	statementList[entity.alias] = entity;
	
	return statementList;
}

/// ウエイトを入れる
vector<QBasicVariableEntity> QBasicDebugFunctions::wait_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("ms", VariableType::Int, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicDebugFunctions::wait_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	this_thread::sleep_for(chrono::milliseconds(arg[0].intValue));
	return QBasicVariableEntity("", VariableType::Void, nullptr);
}
/// 標準出力
vector<QBasicVariableEntity> QBasicDebugFunctions::print_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("msg", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicDebugFunctions::print_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
#if COCOS2D_DEBUG
	cout << arg[0].strValue << "\n";
#endif
	return QBasicVariableEntity("", VariableType::Void, nullptr);
}
/// エラーを発生させる
vector<QBasicVariableEntity> QBasicDebugFunctions::error_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("msg", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicDebugFunctions::error_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	throw arg[0].strValue;
	return QBasicVariableEntity("", VariableType::Void, nullptr);
}
