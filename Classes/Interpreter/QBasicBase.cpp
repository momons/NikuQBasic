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
#include "QBasicVariableEntity.h"

/**
 * コンストラクタ
 * @param interpreter　メイン
 */
QBasicBase::QBasicBase(QBasic *interpreter) {
	this->interpreter = interpreter;
	pushBacked = "";
	lastFunctionName = "";
	hasReturnSymbol = false;
}

/**
 * デストラクタ
 */
QBasicBase::~QBasicBase() {
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

/**
 * list型の取得
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicBase::listValue(const bool run) {
	QBasicVariableEntity returnValue;
	returnValue.type = VariableType::List;
	// 上位で"["のチェックがされる
	int count = 0;
	while (true) {
		auto sym = getSymbol();
		if (sym == "]") {
			break;
		}
		if (count > 0) {
			interpreter->symbols->popBack();
			match(",");
			sym = getSymbol();
		}
		QBasicVariableEntity value;
		if (sym == "[") {
			value = listValue(run);
		} else if(sym == "{") {
			value = dictValue(run);
		} else {
			interpreter->symbols->popBack();
			value = expression(run);
		}
		returnValue.listValue.push_back(value);
		count += 1;
	}
	return returnValue;
}

/**
 * 引数取得
 * @param run      実行モード
 * @return 引数群
 */
vector<QBasicVariableEntity> QBasicBase::getArguments(const bool run) {
	
	// 引数取得
	vector<QBasicVariableEntity> argList;
	match("(");
	int count = 0;
	while(true) {
		auto variableName = getSymbol();
		if (variableName == ")") {
			break;
		}
		if (count > 0) {
			interpreter->symbols->popBack();
			match(",");
			variableName = getSymbol();
		}
		auto sym = getSymbol();
		if (sym == "=") {
			auto value = expression(run);
			value.name = variableName;
			argList.push_back(value);
		} else {
			// 2個戻す
			interpreter->symbols->popBack();
			interpreter->symbols->popBack();
			auto value = expression(run);
			value.name = "";
			argList.push_back(value);
		}
		count += 1;
	}
	
	return argList;
}
