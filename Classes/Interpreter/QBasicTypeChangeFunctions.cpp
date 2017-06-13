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
#include "QBasicErrors.h"
#include "QBasicErrorEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicTypeChangeFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("toInt", toInt_params(), { VariableType::Int }, toInt_qb, toInt_compile);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("toFloat", toFloat_params(), { VariableType::Float }, toFloat_qb, toFloat_compile);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("toStr", toStr_params(), { VariableType::Str }, toStr_qb, toStr_compile);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("toBool", toBool_params(), { VariableType::Float }, toBool_qb, toBool_compile);
	statementList[entity.alias] = entity;

	return statementList;
}

/// int変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::toInt_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", { VariableType::Unknown }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::toInt_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	auto entity = arg[0].toInt();
	return QBasicVariableEntity("", { VariableType::Int }, entity.isNil ? nullptr : &entity.intValue);
}
void QBasicTypeChangeFunctions::toInt_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset) {
	vector<VariableType> variableTypes = {
		VariableType::Int,
		VariableType::Float,
		VariableType::Str,
		VariableType::Bool,
	};
	if (find(variableTypes.begin(), variableTypes.end(), arg[0].types[0]) == variableTypes.end()){
		interpreter->errors->addError(symbolOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(variableTypes, arg[0]));
	}
}
/// float変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::toFloat_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", { VariableType::Unknown }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::toFloat_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	auto entity = arg[0].toFloat();
	return QBasicVariableEntity("", { VariableType::Float }, entity.isNil ? nullptr : &entity.floatValue);
}
void QBasicTypeChangeFunctions::toFloat_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset) {
	vector<VariableType> variableTypes = {
		VariableType::Int,
		VariableType::Float,
		VariableType::Str,
		VariableType::Bool,
	};
	if (find(variableTypes.begin(), variableTypes.end(), arg[0].types[0]) == variableTypes.end()){
		interpreter->errors->addError(symbolOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(variableTypes, arg[0]));
	}
}
/// str変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::toStr_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", { VariableType::Unknown }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::toStr_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	auto entity = arg[0].toStr();
	return QBasicVariableEntity("", { VariableType::Str }, entity.isNil ? nullptr : &entity.strValue);
}
void QBasicTypeChangeFunctions::toStr_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset) {
	vector<VariableType> variableTypes = {
		VariableType::Int,
		VariableType::Float,
		VariableType::Str,
		VariableType::Bool,
	};
	if (find(variableTypes.begin(), variableTypes.end(), arg[0].types[0]) == variableTypes.end()){
		interpreter->errors->addError(symbolOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(variableTypes, arg[0]));
	}
}
/// bool変換
vector<QBasicVariableEntity> QBasicTypeChangeFunctions::toBool_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", { VariableType::Unknown }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicTypeChangeFunctions::toBool_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	auto entity = arg[0].toBool();
	return QBasicVariableEntity("", { VariableType::Bool }, entity.isNil ? nullptr : &entity.boolValue);
}
void QBasicTypeChangeFunctions::toBool_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset) {
	vector<VariableType> variableTypes = {
		VariableType::Int,
		VariableType::Float,
		VariableType::Str,
		VariableType::Bool,
	};
	if (find(variableTypes.begin(), variableTypes.end(), arg[0].types[0]) == variableTypes.end()){
		interpreter->errors->addError(symbolOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(variableTypes, arg[0]));
	}
}
