//
//  QBInterpreterFunctionEntity.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/10.
//
//

#include "QBInterpreterFunctionEntity.h"

/**
 * コンストラクタ
 */
QBInterpreterFunctionEntity::QBInterpreterFunctionEntity() {
	// 初期値設定
	argNames.clear();
	startOffset = 0;
	endOffset = -1;
}

/**
 * デストラクタ
 */
QBInterpreterFunctionEntity::~QBInterpreterFunctionEntity() {
	
	
}
