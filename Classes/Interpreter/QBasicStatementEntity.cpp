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
    argCount = 0;
    isReturnValue = false;
	func = nullptr;
}

/**
 * コンストラクタ
 * @param name          ステートメント名
 * @param argCount      引数数
 * @param isReturnValue 戻り値
 * @param func			実行ファンクション
 */
QBasicStatementEntity::QBasicStatementEntity(
											 const string &name,
											 const int argCount,
											 const bool isReturnValue,
											 const statmentFunction &func) {
    // 初期値設定
    this->name = name;
    this->argCount = argCount;
    this->isReturnValue = isReturnValue;
	this->func = func;
}

/**
 * コンストラクタ
 * @param name          ステートメント名
 * @param argTypes      引数変数タイプ
 * @param isReturnValue 戻り値
 * @param func			実行ファンクション
 */
QBasicStatementEntity::QBasicStatementEntity(
											 const string &name,
											 const vector<VariableType> &argTypes,
											 const VariableType returnType,
											 const statmentFunction &func) {
	// 初期値設定
	this->name = name;
	this->argTypes = argTypes;
	this->returnType = returnType;
	this->func = func;
}

/**
 * デストラクタ
 */
QBasicStatementEntity::~QBasicStatementEntity() {
    
    
}
