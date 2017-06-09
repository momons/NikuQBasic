//
//  QBasicTypeIsFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/10.
//
//

#include "QBasicTypeIsFunctions.h"

#include "QBasic.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicTypeIsFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("isInt", isInt_params(), VariableType::Bool, isInt_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("isFloat", isFloat_params(), VariableType::Bool, isFloat_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("isStr", isStr_params(), VariableType::Bool, isStr_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("isBool", isBool_params(), VariableType::Bool, isBool_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("isList", isList_params(), VariableType::Bool, isList_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("isDict", isDict_params(), VariableType::Bool, isDict_qb, nullptr);
	statementList[entity.alias] = entity;
	
	return statementList;
}

/// int判定
vector<QBasicVariableEntity> QBasicTypeIsFunctions::isInt_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Unknown, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeIsFunctions::isInt_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	bool answer = arg[0].type == VariableType::Int;
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
/// float判定
vector<QBasicVariableEntity> QBasicTypeIsFunctions::isFloat_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Unknown, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeIsFunctions::isFloat_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	bool answer = arg[0].type == VariableType::Float;
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
/// str判定
vector<QBasicVariableEntity> QBasicTypeIsFunctions::isStr_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Unknown, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeIsFunctions::isStr_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	bool answer = arg[0].type == VariableType::Str;
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
/// bool判定
vector<QBasicVariableEntity> QBasicTypeIsFunctions::isBool_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Unknown, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeIsFunctions::isBool_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	bool answer = arg[0].type == VariableType::Bool;
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
/// list判定
vector<QBasicVariableEntity> QBasicTypeIsFunctions::isList_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Unknown, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeIsFunctions::isList_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	bool answer = arg[0].type == VariableType::List;
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
/// dict判定
vector<QBasicVariableEntity> QBasicTypeIsFunctions::isDict_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Unknown, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeIsFunctions::isDict_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	bool answer = arg[0].type == VariableType::Dict;
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
