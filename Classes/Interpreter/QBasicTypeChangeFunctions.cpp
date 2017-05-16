//
//  QBasicTypeChangeFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/27.
//
//

#include "QBasicTypeChangeFunctions.h"

#include "QBasic.h"
#include "StringUtil.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicTypeChangeFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("float2int", float2int_params(), VariableType::Int, float2int_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("str2int", str2int_params(), VariableType::Int, str2int_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("bool2int", bool2int_params(), VariableType::Int, bool2int_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("int2float", int2float_params(), VariableType::Float, int2float_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("str2float", str2float_params(), VariableType::Float, str2float_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("bool2float", bool2float_params(), VariableType::Float, bool2float_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("int2str", int2str_params(), VariableType::Str, int2str_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("float2str", float2str_params(), VariableType::Str, float2str_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("bool2str", bool2str_params(), VariableType::Str, bool2str_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("int2bool", int2bool_params(), VariableType::Bool, int2bool_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("float2bool", float2bool_params(), VariableType::Bool, float2bool_qb);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("str2bool", str2bool_params(), VariableType::Bool, str2bool_qb);
	statementList[entity.alias] = entity;

	return statementList;
}

/// float→int変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::float2int_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::float2int_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	int answer = (int)arg[0].floatValue;
	return QBasicVariableEntity("", VariableType::Int, &answer);
}
/// str→int変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::str2int_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::str2int_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	int answer = atoi(arg[0].strValue.c_str());
	return QBasicVariableEntity("", VariableType::Int, &answer);
}
/// bool→int変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::bool2int_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::bool2int_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	int answer = arg[0].boolValue ? 1 : 0;
	return QBasicVariableEntity("", VariableType::Int, &answer);
}
/// int→float変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::int2float_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Int, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::int2float_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	double answer = arg[0].intValue;
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// str→float変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::str2float_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::str2float_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	double answer = atof(arg[0].strValue.c_str());
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// bool→float変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::bool2float_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Bool, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::bool2float_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	double answer = arg[0].boolValue ? 1 : 0;
	return QBasicVariableEntity("", VariableType::Float, &answer);
}
/// int→str変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::int2str_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Int, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::int2str_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	string answer = to_string(arg[0].intValue);
	return QBasicVariableEntity("", VariableType::Str, &answer);
}
/// float→str変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::float2str_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::float2str_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	string answer = StringUtil::toString(arg[0].floatValue);
	return QBasicVariableEntity("", VariableType::Str, &answer);
}
/// bool→str変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::bool2str_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Bool, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::bool2str_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	string answer = arg[0].boolValue ? "true" : "false";
	return QBasicVariableEntity("", VariableType::Str, &answer);
}
/// int→bool変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::int2bool_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Int, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::int2bool_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	bool answer = arg[0].intValue != 0;
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
/// float→bool変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::float2bool_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Float, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::float2bool_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	bool answer = arg[0].floatValue != 0;
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
/// str→bool変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::str2bool_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", VariableType::Str, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::str2bool_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	bool answer = arg[0].strValue == "true";
	return QBasicVariableEntity("", VariableType::Bool, &answer);
}
