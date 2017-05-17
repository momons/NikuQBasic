//
//  QBasicErrorEntity.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/17.
//
//

#include "QBasicErrorEntity.h"

/**
 * コンストラクタ
 */
QBasicErrorEntity::QBasicErrorEntity() {
}

/**
 * コンストラクタ
 * @param symbolIndex  シンボルインデックス
 * @param type         エラータイプ
 * @param message      メッセージ
 */
QBasicErrorEntity::QBasicErrorEntity(const int symbolIndex, const ErrorType type, const string &message) {
	this->symbolIndex = symbolIndex;
	this->type = type;
	this->message = message;
}

/**
 * デストラクタ
 */
QBasicErrorEntity::~QBasicErrorEntity() {
	
}
