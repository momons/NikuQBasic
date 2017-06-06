//
//  QBasicExec.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/07.
//
//

#include "QBasicExec.h"

#include "QBasic.h"
#include "QBasicSymbols.h"
#include "QBasicVariableEntity.h"

/**
 * コンストラクタ
 * @param interpreter　メイン
 */
QBasicExec::QBasicExec(QBasic *interpreter): QBasicBase(interpreter) {
}

/**
 * and、or、xor判定
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicExec::expression(const bool run) {
	
	// 式の値取得
	auto value = relop(run);
	
	auto sym = getSymbol();
	while(true) {
		if (sym == "&&" ||
			sym == "||" ) {
			
			auto valueDist = relop(run);
			if (sym == "&&") {
				value = value && valueDist;
			} else {
				value = value || valueDist;
			}
			
		} else {
			break;
		}
		sym = getSymbol();
	}
	pushBack(sym);
	
	return value;
}

/**
 * =、<、<=、>、>=、<>判定
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicExec::relop(const bool run) {
	
	// 足し算、引き算の値取得
	auto value = addsub(run);
	
	auto sym = getSymbol();
	while(true) {
		if (sym == "==" ||
			sym == "<" ||
			sym == "<=" ||
			sym == ">" ||
			sym == ">=" ||
			sym == "!=" ) {
			
			auto valueDist = addsub(run);
			bool boolValue = ((sym == "==" && value == valueDist) ||
							  (sym == "<" && value < valueDist) ||
							  (sym == "<=" && value <= valueDist) ||
							  (sym == ">" && value > valueDist) ||
							  (sym == ">=" && value >= valueDist) ||
							  (sym == "!=" && value != valueDist));
			value.set(boolValue);
		} else {
			break;
		}
		sym = getSymbol();
	}
	pushBack(sym);
	
	return value;
}

/**
 * 足し算、引き算、NOTの計算
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicExec::addsub(const bool run) {
	
	QBasicVariableEntity value;
	
	// 値取得
	auto sym = getSymbol();
	if (sym == "+") {
		value = muldiv(run);
	} else if(sym == "-") {
		value = muldiv(run);
		value = value.mul(value.type, -1);
	} else if(sym == "not") {
		value = muldiv(run);
		value = !value;
	} else {
		pushBack(sym);
		value = muldiv(run);
	}
	
	// 式実行
	sym = getSymbol();
	while (true) {
		if (sym == "+") {
			auto valueDist = muldiv(run);
			value = value + valueDist;
		} else if(sym == "-") {
			auto valueDist = muldiv(run);
			value = value - valueDist;
		} else {
			break;
		}
		sym = getSymbol();
	}
	pushBack(sym);
	
	return value;
}

/**
 * 掛け算、割り算、あまりの計算
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicExec::muldiv(const bool run) {
	
	// 戻り値取得
	auto value = factor(run);
	
	string sym = getSymbol();
	while (true) {
		if (sym == "*") {
			auto valueDist = factor(run);
			value = value * valueDist;
		} else if (sym == "/") {
			auto valueDist = factor(run);
			value = value / valueDist;
		} else if (sym == "%") {
			auto valueDist = factor(run);
			value = value % valueDist;
		} else {
			break;
		}
		sym = getSymbol();
	}
	pushBack(sym);
	
	return value;
}
