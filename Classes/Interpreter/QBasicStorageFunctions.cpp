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
	
	entity = QBasicStatementEntity("loadFile", loadFile_params(), { VariableType::Void }, loadFile_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("saveFile", saveFile_params(), { VariableType::Void }, saveFile_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("hasFileKey", hasFileKey_params(), { VariableType::Bool }, hasFileKey_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("removeFile", removeFile_params(), { VariableType::Void }, removeFile_qb, nullptr);
	statementList[entity.alias] = entity;
	
	return statementList;
}

/// 読み込み
vector<QBasicVariableEntity> QBasicStorageFunctions::loadFile_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::loadFile_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	return interpreter->storages->read(arg[0].strValue);
}

/// セーブ
vector<QBasicVariableEntity> QBasicStorageFunctions::saveFile_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	argNames.push_back(QBasicVariableEntity("value", { VariableType::Void }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::saveFile_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
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
vector<QBasicVariableEntity> QBasicStorageFunctions::removeFile_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("key", { VariableType::Str }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicStorageFunctions::removeFile_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	interpreter->storages->remove(arg[0].strValue);
	return QBasicVariableEntity("", { VariableType::Void }, nullptr);
}
