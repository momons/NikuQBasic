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
	returnType = VariableType::Unknown;
	returnSubTypes.clear();
	startOffset = 0;
	endOffset = -1;
}

/**
 * コンストラクタ
 * @param name           関数名
 * @param argNames       引数変数タイプ
 * @param returnType     戻り値タイプ
 * @param returnSubTypes 戻り値サブタイプ
 * @param startOffset    開始オフセット
 * @param endOffset      終了オフセット
 */
QBasicFunctionEntity::QBasicFunctionEntity(
										   const string &name,
										   const vector<QBasicVariableEntity> &argNames,
										   const VariableType returnType,
										   const vector<VariableType> returnSubTypes,
										   const int startOffset,
										   const int endOffset) {
	this->name = name;
	this->argNames = argNames;
	this->returnType = returnType;
	this->returnSubTypes = returnSubTypes;
	this->startOffset = startOffset;
	this->endOffset = endOffset;
	configureAlias();
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
	ostringstream os;
	os << name;
	os << "(";
	for (auto it = argNames.begin();it != argNames.end();it++) {
		os << it->name << ":";
	}
	os << ")";
	return os.str();
}

/**
 * 別名設定
 */
void QBasicFunctionEntity::configureAlias() {
	alias = QBasicFunctionEntity::exchangeAlias(name, argNames);
}
