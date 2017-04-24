//
//  QBasicStatementEntity.cpp
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/02/18.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"

/**
 * コンストラクタ
 */
QBasicStatementEntity::QBasicStatementEntity() {
    // 初期値設定
    name = "";
	argTypes.clear();
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
											 const vector<VariableType> &argTypes,
											 const VariableType returnType,
											 const statmentFunction &func) {
	QBasicStatementEntity(name, argTypes, returnType, {}, func);
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
											 const vector<VariableType> &argTypes,
											 const VariableType returnType,
											 const vector<VariableType> &returnSubTypes,
											 const statmentFunction &func) {
	// 初期値設定
	this->name = name;
	this->argTypes = argTypes;
	this->returnType = returnType;
	this->returnSubTypes = returnSubTypes;
	this->func = func;
}

/**
 * デストラクタ
 */
QBasicStatementEntity::~QBasicStatementEntity() {
    
    
}
