//
//  QBasicFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/28.
//
//

#include "QBasicFunctions.h"

#include "QBasicFunctionEntity.h"
#include "QBasicVariableEntity.h"

/**
 * コンストラクタ
 */
QBasicFunctions::QBasicFunctions() {
	functions.clear();
}

/**
 * デストラクタ
 */
QBasicFunctions::~QBasicFunctions() {
	
}

/**
 * 関数追加
 * @param name           関数名
 * @param variableTypes  引数タイプ
 * @param returnType     戻り値タイプ
 * @param returnSubTypes 戻り値サブタイプ
 * @param startOffset    開始オフセット
 * @param endOffset      終了オフセット
 * @return 関数情報
 */
QBasicFunctionEntity *QBasicFunctions::addUpdate(
												 const string &name,
												 const vector<QBasicVariableEntity> &variableTypes,
												 const VariableType returnType,
												 const vector<VariableType> returnSubTypes,
												 const long startOffset,
												 const long endOffset) {

	auto func = getFunction(name, variableTypes);
	if (func != nullptr) {
		// 更新
		func->returnType = returnType;
		func->returnSubTypes = returnSubTypes;
		func->startOffset = startOffset;
		func->endOffset = endOffset;
		return func;
	}
	// 追加
	QBasicFunctionEntity entity = QBasicFunctionEntity(name, variableTypes, returnType, returnSubTypes, startOffset, endOffset);
	functions[entity.alias] = entity;
	return &functions[entity.alias];
}

/**
 * 名前で存在判定
 * @param name 関数名
 * @return 存在可否
 */
bool QBasicFunctions::hasName(const string &name) {
	return find(summaryNames.begin(), summaryNames.end(), name) != summaryNames.end();
}

/**
 * 名前で存在判定
 * @param name          関数名
 * @param variableTypes 引数タイプ
 * @return 存在可否
 */
bool QBasicFunctions::hasFunction(const string &name, const vector<QBasicVariableEntity> &variableTypes) {
	return getFunction(name, variableTypes) != nullptr;
}

/**
 * 名前と引数で取得
 * @param name          関数名
 * @param variableTypes 引数タイプ
 * @return 関数情報
 */
QBasicFunctionEntity *QBasicFunctions::getFunction(const string &name, const vector<QBasicVariableEntity> &variableTypes) {
	// エリアス取得
	auto alias = QBasicFunctionEntity::exchangeAlias(name, variableTypes);
	return functions.find(alias) != functions.end() ? &functions[alias] : nullptr;
}

/**
 * 別名で取得
 * @param name          関数名
 * @param variableTypes 引数タイプ
 * @return 関数情報
 */
QBasicFunctionEntity *QBasicFunctions::getFunction(const string &alias) {
	return functions.find(alias) != functions.end() ? &functions[alias] : nullptr;
}

/**
 *  クリア
 */
void QBasicFunctions::clear() {
	functions.clear();
}

