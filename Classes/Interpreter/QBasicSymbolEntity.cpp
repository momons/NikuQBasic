//
//  QBasicSymbolEntity.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/02.
//
//

#include "QBasicSymbolEntity.h"

/**
 * コンストラクタ
 */
QBasicSymbolEntity::QBasicSymbolEntity() {
	symbol = "";
	row = 0;
	col = 0;
}

/**
 * コンストラクタ
 * @param symbol  シンボル
 * @param row     行
 * @param col     項
 */
QBasicSymbolEntity::QBasicSymbolEntity(const string &symbol, int row, int col) {
	this->symbol = symbol;
	this->row = row;
	this->col = col;
}

/**
 * デストラクタ
 */
QBasicSymbolEntity::~QBasicSymbolEntity() {
	
}
