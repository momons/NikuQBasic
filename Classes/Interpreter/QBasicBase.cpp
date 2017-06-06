//
//  QBasicBase.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/07.
//
//

#include "QBasicBase.h"

#include "QBasic.h"
#include "QBasicSymbols.h"

/**
 * コンストラクタ
 * @param interpreter　メイン
 */
QBasicBase::QBasicBase(QBasic *interpreter) {
	this->interpreter = interpreter;
	pushBacked = "";
}

/**
 * 単語を退避しておく
 * @param symbol 単語
 */
void QBasicBase::pushBack(const string &symbol) {
	pushBacked = symbol;
}

/**
 * 単語取得
 * @return 単語文字列
 */
string QBasicBase::getSymbol() {
	
	// 残しておいたシンボルを返却
	if (!pushBacked.empty()) {
		string pushbackedBackup = pushBacked;
		pushBacked = "";
		return pushbackedBackup;
	}
	
	return interpreter->symbols->nextSymbol();
}
