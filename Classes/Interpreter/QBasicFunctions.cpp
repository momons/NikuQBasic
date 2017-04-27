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
 * @param name          関数名
 * @param variableTypes 引数タイプ
 * @param returnVariableType 戻り値タイプ
 * @param startOffset   開始オフセット
 * @param endOffset     終了オフセット
 */
void QBasicFunctions::addUpdate(
		 const string &name,
		 const vector<QBasicVariableEntity> variableTypes,
		 VariableType returnVariableType,
		 long startOffset,
		 long endOffset) {
	
	auto func = getFunction(name, variableTypes);
	if (func != nullptr) {
		// 更新
		func->returnVariableType = returnVariableType;
		func->startOffset = startOffset;
		func->endOffset = endOffset;
		return;
	}
	// 追加
	QBasicFunctionEntity entity = QBasicFunctionEntity(name, variableTypes, returnVariableType, startOffset, endOffset);
	functions[entity.alias] = entity;
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
