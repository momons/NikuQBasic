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
	alias = "";
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
	// 初期値設定
	this->name = name;
	this->argTypes = argTypes;
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
	configureAlias();
}

/**
 * デストラクタ
 */
QBasicStatementEntity::~QBasicStatementEntity() {
    
    
}

/**
 * 関数名変換
 * @param name       元の名前
 * @param argTypes   引数変数タイプ
 * @return 変換名
 */
string QBasicStatementEntity::exchangeAlias(
										   const string &name,
										   const vector<VariableType> &argTypes) {
	ostringstream os;
	os << name;
	os << "_";
	for (auto it = argTypes.begin();it != argTypes.end();it++) {
		os << QBasicVariableEntity::getVariableTypeString(*it);
		os << "_";
	}
	return os.str();
}

/**
 * 別名設定
 */
void QBasicStatementEntity::configureAlias() {
	alias = QBasicStatementEntity::exchangeAlias(name, argTypes);
}

