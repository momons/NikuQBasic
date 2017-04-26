//
//  QBasicFunctionEntity.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/10.
//
//

#include "QBasicFunctionEntity.h"

#include "QBasicVariableEntity.h"
#include "QBasicStatementEntity.h"

/**
 * コンストラクタ
 */
QBasicFunctionEntity::QBasicFunctionEntity() {
	// 初期値設定
	name = "";
	alias = "";
	argNames.clear();
	returnVariableType = VariableType::Unknown;
	startOffset = 0;
	endOffset = -1;
}

/**
 * デストラクタ
 */
QBasicFunctionEntity::~QBasicFunctionEntity() {
	
	
}

/**
 * 関数名変換
 * @param name       元の名前
 * @param argNames   引数変数タイプ
 * @param returnType 戻り値タイプ
 * @return 変換名
 */
string QBasicFunctionEntity::exchangeAlias(const string &name, const vector<QBasicVariableEntity> &argNames) {
	vector<VariableType> argTypes;
	for (auto it = argNames.begin();it != argNames.end();it++) {
		argTypes.push_back(it->type);
	}
	return QBasicStatementEntity::exchangeAlias(name, argTypes);
}

/**
 * 別名設定
 */
void QBasicFunctionEntity::configureAlias() {
	alias = QBasicFunctionEntity::exchangeAlias(name, argNames);
}
