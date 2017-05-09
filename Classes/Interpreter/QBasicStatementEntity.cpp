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
	returnType = VariableType::Void;
	returnSubTypes.clear();
	func = nullptr;
}

/**
 * コンストラクタ
 * @param name           ステートメント名
 * @param argTypes       引数変数タイプ
 * @param returnType     戻り値
 * @param func		 	実行ファンクション
 */
QBasicStatementEntity::QBasicStatementEntity(
											 const string &name,
											 const vector<QBasicVariableEntity> &argNames,
											 const VariableType returnType,
											 const statmentFunction &func) {
	// 初期値設定
	this->name = name;
	this->argNames = argNames;
	this->returnType = returnType;
	this->func = func;
	configureAlias();
}

/**
 * コンストラクタ
 * @param name           ステートメント名
 * @param argTypes       引数変数タイプ
 * @param returnType     戻り値
 * @param returnSubTypes 戻り値サブタイプ
 * @param func		 	実行ファンクション
 */
QBasicStatementEntity::QBasicStatementEntity(
											 const string &name,
											 const vector<QBasicVariableEntity> &argNames,
											 const VariableType returnType,
											 const vector<VariableType> &returnSubTypes,
											 const statmentFunction &func) {
	// 初期値設定
	this->name = name;
	this->argNames = argNames;
	this->returnType = returnType;
	this->returnSubTypes = returnSubTypes;
	this->func = func;
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

