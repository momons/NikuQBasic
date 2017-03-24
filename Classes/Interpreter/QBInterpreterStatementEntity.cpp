//
//  QBInterpreterStatementEntity.cpp
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/02/18.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#include "QBInterpreterStatementEntity.h"

/**
 * コンストラクタ
 */
QBInterpreterStatementEntity::QBInterpreterStatementEntity() {
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
QBInterpreterStatementEntity::QBInterpreterStatementEntity(
														   const string name,
														   const int argCount,
														   const bool isReturnValue,
														   const statmentFunction func
														   ) {
    // 初期値設定
    this->name = name;
    this->argCount = argCount;
    this->isReturnValue = isReturnValue;
	this->func = func;
}

/**
 * デストラクタ
 */
QBInterpreterStatementEntity::~QBInterpreterStatementEntity() {
    
    
}
