//
//  QBasicPushBackEntity.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/01.
//
//

#include "QBasicPushBackEntity.h"

#include "QBasicVariableEntity.h"

/**
 * コンストラクタ
 * @param name           関数名
 * @param symbol         退避文字
 * @param execOffset     実行オフセット
 * @param localVariables ローカル変数
 */
QBasicPushBackEntity::QBasicPushBackEntity(
										   const string &name,
										   const string &symbol,
										   const long execOffset,
										   const unordered_map<string, QBasicVariableEntity> &localVariables) {
	this->name = name;
	this->symbol = symbol;
	this->execOffset = execOffset;
	this->localVariables = localVariables;
}

/**
 * デストラクタ
 */
QBasicPushBackEntity::~QBasicPushBackEntity() {
	
}
