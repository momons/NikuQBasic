//
//  QBasicStorageFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/21.
//
//

#include "QBasicStorageFunctions.h"

#include "QBasic.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"
#include "QBasicSubFunction.h"
#include "QBasicStorages.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicStorageFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("loadInt", loadInt_params(), { VariableType::Int }, loadInt_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("loadFloat", loadFloat_params(), { VariableType::Float }, loadFloat_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("loadStr", loadStr_params(), { VariableType::Str }, loadStr_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("loadBool", loadBool_params(), { VariableType::Bool }, loadBool_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("loadList", loadList_params(), { VariableType::List, VariableType::Void }, loadList_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("loadDict", loadDict_params(), { VariableType::Dict, VariableType::Void }, loadDict_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("saveInt", saveInt_params(), { VariableType::Void }, saveInt_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("saveFloat", saveFloat_params(), { VariableType::Void }, saveFloat_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("saveStr", saveStr_params(), { VariableType::Void }, saveStr_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("saveBool", saveBool_params(), { VariableType::Void }, saveBool_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("saveList", saveList_params(), { VariableType::Void }, saveList_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("saveDict", saveDict_params(), { VariableType::Void }, saveDict_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("hasFileKey", hasFileKey_params(), { VariableType::Bool }, hasFileKey_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("removeStorage", removeStorage_params(), { VariableType::Void }, removeStorage_qb, nullptr);
	statementList[entity.alias] = entity;
	
	return statementList;
}

/// int読込
vector<QBasicVariableEntity> QBasicStorageFunctions::loadInt_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::loadInt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	return interpreter->storages->read(arg[0].strValue).toInt();
}
/// float読込
vector<QBasicVariableEntity> QBasicStorageFunctions::loadFloat_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::loadFloat_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	return interpreter->storages->read(arg[0].strValue).toFloat();
}
/// str読込
vector<QBasicVariableEntity> QBasicStorageFunctions::loadStr_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::loadStr_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	return interpreter->storages->read(arg[0].strValue).toStr();
}
/// bool読込
vector<QBasicVariableEntity> QBasicStorageFunctions::loadBool_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::loadBool_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	return interpreter->storages->read(arg[0].strValue).toBool();
}
/// list読込
vector<QBasicVariableEntity> QBasicStorageFunctions::loadList_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::loadList_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto value = interpreter->storages->read(arg[0].strValue);
	if (value.types[0] != VariableType::List) {
		value = QBasicVariableEntity("", { VariableType::List, VariableType::Void }, vector<QBasicVariableEntity>());
	}
	return value;
}
/// dict読込
vector<QBasicVariableEntity> QBasicStorageFunctions::loadDict_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::loadDict_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto value = interpreter->storages->read(arg[0].strValue);
	if (value.types[0] != VariableType::Dict) {
		value = QBasicVariableEntity("", { VariableType::Dict, VariableType::Void }, map<string, QBasicVariableEntity>());
	}
	return value;
}
/// int保存
vector<QBasicVariableEntity> QBasicStorageFunctions::saveInt_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	argNames.push_back(QBasicVariableEntity("v", { VariableType::Int }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::saveInt_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	interpreter->storages->write(arg[0].strValue, arg[1]);
	return QBasicVariableEntity("", { VariableType::Void }, nullptr);
}
/// float保存
vector<QBasicVariableEntity> QBasicStorageFunctions::saveFloat_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	argNames.push_back(QBasicVariableEntity("v", { VariableType::Float }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::saveFloat_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	interpreter->storages->write(arg[0].strValue, arg[1]);
	return QBasicVariableEntity("", { VariableType::Void }, nullptr);
}
/// str保存
vector<QBasicVariableEntity> QBasicStorageFunctions::saveStr_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	argNames.push_back(QBasicVariableEntity("v", { VariableType::Str }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::saveStr_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	interpreter->storages->write(arg[0].strValue, arg[1]);
	return QBasicVariableEntity("", { VariableType::Void }, nullptr);
}
/// bool保存
vector<QBasicVariableEntity> QBasicStorageFunctions::saveBool_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	argNames.push_back(QBasicVariableEntity("v", { VariableType::Bool }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::saveBool_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	interpreter->storages->write(arg[0].strValue, arg[1]);
	return QBasicVariableEntity("", { VariableType::Void }, nullptr);
}
/// list保存
vector<QBasicVariableEntity> QBasicStorageFunctions::saveList_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	argNames.push_back(QBasicVariableEntity("v", { VariableType::List, VariableType::Void }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::saveList_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	interpreter->storages->write(arg[0].strValue, arg[1]);
	return QBasicVariableEntity("", { VariableType::Void }, nullptr);
}
/// dict保存
vector<QBasicVariableEntity> QBasicStorageFunctions::saveDict_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	argNames.push_back(QBasicVariableEntity("v", { VariableType::Dict, VariableType::Void }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::saveDict_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	interpreter->storages->write(arg[0].strValue, arg[1]);
	return QBasicVariableEntity("", { VariableType::Void }, nullptr);
}
/// キーが存在するかチェック
vector<QBasicVariableEntity> QBasicStorageFunctions::hasFileKey_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::hasFileKey_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	return interpreter->storages->hasKey(arg[0].strValue);
}
/// 削除
vector<QBasicVariableEntity> QBasicStorageFunctions::removeStorage_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::removeStorage_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	interpreter->storages->remove(arg[0].strValue);
	return QBasicVariableEntity("", { VariableType::Void }, nullptr);
}
