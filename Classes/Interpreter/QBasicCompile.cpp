//
//  QBasicCompile.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/07.
//
//

#include "QBasicCompile.h"

#include "QBasic.h"
#include "QBasicSymbols.h"
#include "QBasicVariableEntity.h"
#include "QBasicValidation.h"
#include "QBasicErrors.h"
#include "QBasicErrorEntity.h"

/**
 * コンストラクタ
 * @param interpreter　メイン
 */
QBasicCompile::QBasicCompile(QBasic *interpreter): QBasicBase(interpreter) {
}

/**
 * and、or、xor判定
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicCompile::expression(const bool run) {
	
	// 式の値取得
	auto value = relop(run);
	
	auto sym = getSymbol();
	while(true) {
		if (sym == "&&" ||
			sym == "||" ) {
			
			int offset = interpreter->symbols->offset();
			
			auto valueDist = relop(run);
			if (!QBasicValidation::isValidExpression(value, valueDist)) {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
			}
			value = QBasicVariableEntity("", "true");
			
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
QBasicVariableEntity QBasicCompile::relop(const bool run) {
	
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
			
			int offset = interpreter->symbols->offset();
			
			auto valueDist = addsub(run);
			if (!QBasicValidation::isValidVariableType(value, valueDist)) {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
			}
			value.set(true);
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
QBasicVariableEntity QBasicCompile::addsub(const bool run) {
	
	QBasicVariableEntity value;
	
	// 値取得
	auto sym = getSymbol();
	if (sym == "+") {
		value = muldiv(run);
	} else if(sym == "-") {
		int offset = interpreter->symbols->offset();
		value = muldiv(run);
		if (QBasicValidation::isValidSub(value)) {
			value = value.mul(value.type, -1);
		} else {
			interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int, VariableType::Float}, value));
		}
	} else if(sym == "not") {
		int offset = interpreter->symbols->offset();
		value = muldiv(run);
		if (QBasicValidation::isValidNot(value)) {
			value = !value;
		} else {
			interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Bool}, value));
		}
	} else {
		pushBack(sym);
		value = muldiv(run);
	}
	
	// 式実行
	sym = getSymbol();
	while (true) {
		if (sym == "+") {
			int offset = interpreter->symbols->offset();
			auto valueDist = muldiv(run);
			if (QBasicValidation::isValidAdd(value, valueDist)) {
				value = value + valueDist;
			} else {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
			}
		} else if(sym == "-") {
			int offset = interpreter->symbols->offset();
			auto valueDist = muldiv(run);
			if (QBasicValidation::isValidSub(value, valueDist)) {
				value = value - valueDist;
			} else {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
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
 * 掛け算、割り算、あまりの計算
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicCompile::muldiv(const bool run) {
	
	// 戻り値取得
	auto value = factor(run);
	
	string sym = getSymbol();
	while (true) {
		if (sym == "*") {
			int offset = interpreter->symbols->offset();
			auto valueDist = factor(run);
			if (QBasicValidation::isValidMul(value, valueDist)) {
				value = value * valueDist;
			} else {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
			}
		} else if (sym == "/") {
			int offset = interpreter->symbols->offset();
			auto valueDist = factor(run);
			if (QBasicValidation::isValidDiv(value, valueDist)) {
				value = value / valueDist;
			} else {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
			}
		} else if (sym == "%") {
			int offset = interpreter->symbols->offset();
			auto valueDist = factor(run);
			if (QBasicValidation::isValidMod(value, valueDist)) {
				value = value % valueDist;
			} else {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
			}
		} else {
			break;
		}
		sym = getSymbol();
	}
	pushBack(sym);
	
	return value;
}


