//
//  QBasicFunctionEntity.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/10.
//
//

#include "QBasicFunctionEntity.h"

#include "QBasicVariableEntity.h"

/**
 * コンストラクタ
 */
QBasicFunctionEntity::QBasicFunctionEntity() {
	// 初期値設定
	name = "";
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
