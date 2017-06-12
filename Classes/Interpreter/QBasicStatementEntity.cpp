//
//  QBasicStatementEntity.cpp
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/02/18.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#include "QBasicStatementEntity.h"

#include "QBasicFunctionEntity.h"
#include "QBasicVariableEntity.h"

/**
 * コンストラクタ
 */
QBasicStatementEntity::QBasicStatementEntity() {
    // 初期値設定
    name = "";
	alias = "";
	argNames.clear();
	returnTypes = { VariableType::Void };
	execFunc = nullptr;
	compileFunc = nullptr;
}

/**
 * コンストラクタ
 * @param name           ステートメント名
 * @param argTypes       引数変数タイプ
 * @param returnTypes    戻り値
 * @param execFunc		 実行ファンクション
 * @param compileFunc    コンパイルファンクション
 */
QBasicStatementEntity::QBasicStatementEntity(
											 const string &name,
											 const vector<QBasicVariableEntity> &argNames,
											 const vector<VariableType> &returnTypes,
											 const statmentFunction &execFunc,
											 const compileFunction &compileFunc) {
	// 初期値設定
	this->name = name;
	this->argNames = argNames;
	this->returnTypes = returnTypes;
	this->execFunc = execFunc;
	this->compileFunc = compileFunc;
	configureAlias();
}

/**
 * デストラクタ
 */
QBasicStatementEntity::~QBasicStatementEntity() {
    
    
}

/**
 * 別名設定
 */
void QBasicStatementEntity::configureAlias() {
	alias = QBasicFunctionEntity::exchangeAlias(name, argNames);
}

