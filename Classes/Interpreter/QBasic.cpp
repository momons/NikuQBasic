//
//  QBasic.cpp
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/02/13.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#include "QBasic.h"
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <exception>
#include <sstream>
#include <iostream>
#include "QBasicStatements.h"
#include "QBasicStatementEntity.h"
#include "QBasicFunctions.h"
#include "QBasicFunctionEntity.h"
#include "QBasicFors.h"
#include "QBasicForEntity.h"
#include "QBasicIfs.h"
#include "QBasicIfEntity.h"
#include "QBasicSymbols.h"
#include "QBasicSymbolEntity.h"
#include "QBasicErrors.h"
#include "QBasicErrorEntity.h"
#include "QBasicScene.h"
#include "QBasicVariableEntity.h"
#include "QBasicPushBackEntity.h"
#include "QBasicSetupNodeEntity.h"
#include "QBasicSubFunction.h"
#include "QBasicStringFunctions.h"
#include "QBasicNetFunctions.h"
#include "QBasicValidation.h"
#include "QBasicMessages.h"
#include "StringUtil.h"

/** 関数返却変数名 */
#define FUNCTION_RETURN_VARIABLE_NAME  "__return_variable__"

/**
 *  コンストラクタ
 *  @param scene     シーン
 *  @param source    ソース
 *  @param projectId プロジェクトId
 */
QBasic::QBasic(QBasicScene *scene, const string &source, const string &projectId) {

    // 必要なサブクラスを取得
	statements = QBasicStatements::sharedInstance();
	messages = QBasicMessages::sharedInstance();
	functions = new QBasicFunctions();
	fors = new QBasicFors();
	ifs = new QBasicIfs();
	
    // 退避
    this->source = source;
	
	// サブファンクション作成
	netFunc = new QBasicNetFunctions();
	subFunc = new QBasicSubFunction(scene, projectId);
	
	// シンボル解析
	symbols = new QBasicSymbols(source);
	// エラー確保
	errors = new QBasicErrors(symbols);
}

/**
 *  デストラクタ
 */
QBasic::~QBasic() {
	// 解放
	delete functions;
	delete netFunc;
	delete subFunc;
	delete fors;
	delete ifs;
	delete errors;
	delete symbols;
}

/**
 *  通常実行
 *  @exception コンパイルエラー
 */
void QBasic::run() {
	// コンパイル
	initAndRun(false);
	// コンパイルエラーがあればここで終了
	if (errors->hasError()) {
		throw "Compile error!";
	}
	// 実行
	initAndRun(true);
}

/**
 *  バックグランド実行
 *  @return スレッド
 *  @exception コンパイルエラー
 */
thread QBasic::backgroundRun() {
	thread t1(&QBasic::run, this);
	return t1;
}

/**
 *  コンパイル
 *  @exception コンパイルエラー
 */
void QBasic::compile() {
	// コンパイル
	initAndRun(false);
}

/**
 *  実行 or コンパイル
 *  @param run true:実行 false:コンパイル
 *  @exception コンパイルエラー
 */
void QBasic::initAndRun(const bool run) {
	
	// 初期化
	isRun = run;
	isExit = false;
	isBreak = false;
	isContinue = false;
	pushBacked = "";
	variables.clear();
	localVariables.clear();
	lastFunctionName = "";
	if (!run) {
		functions->clear();
		fors->clear();
		ifs->clear();
	}
	functionPushBacks.clear();
	symbols->jumpOffset(0);
	errors->clear();
	
	// 実行
	while(true) {
		bool isExecute = statement(run);
		if (!isExecute || isExit) {
			break;
		}
	}
}

/**
 * 単語を退避しておく
 * @param symbol 単語
 */
void QBasic::pushBack(const string &symbol) {
	pushBacked = symbol;
}

/**
 * 単語取得
 * @return 単語文字列
 */
string QBasic::getSymbol() {
	
    // 残しておいたシンボルを返却
    if (!pushBacked.empty()) {
        string pushbackedBackup = pushBacked;
		pushBacked = "";
        return pushbackedBackup;
    }

	return symbols->nextSymbol();
}

/**
 * 単語が一致しているかをチェック
 * @param str 比較文字列
 */
void QBasic::match(const string &str) {
    string sym = getSymbol();
    if (sym != str) {
		errors->addError(ErrorType::MissingFound, QBasicErrors::buildMissingFound(str, sym));
    }
}

/**
 * and、or、xor判定
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasic::expression(const bool run) {
	
    // 式の値取得
    auto value = relop(run);
    
    auto sym = getSymbol();
    while(true) {
        if (sym == "&&" ||
			sym == "||" ) {
			
			int offset = symbols->offset();
			
			auto valueDist = relop(run);
			if (run) {
				if (sym == "&&") {
					value = value && valueDist;
				} else {
					value = value || valueDist;
				}
			} else {
				if (!QBasicValidation::isValidExpression(value, valueDist)) {
					errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
				}
				return QBasicVariableEntity("", "true");
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
QBasicVariableEntity QBasic::relop(const bool run) {
    
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
			
			int offset = symbols->offset();
			
			auto valueDist = addsub(run);
			if (run) {
				value.boolValue = ((sym == "==" && value == valueDist) ||
								   (sym == "<" && value < valueDist) ||
								   (sym == "<=" && value <= valueDist) ||
								   (sym == ">" && value > valueDist) ||
								   (sym == ">=" && value >= valueDist) ||
								   (sym == "!=" && value != valueDist));
				value.type = VariableType::Bool;
			} else {
				if (value.type != valueDist.type) {
					errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
				}
				value.type = VariableType::Bool;
				value.boolValue = true;
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
 * 足し算、引き算、NOTの計算
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasic::addsub(const bool run) {
    
    QBasicVariableEntity value;
    
    // 値取得
    auto sym = getSymbol();
    if (sym == "+") {
        value = muldiv(run);
    } else if(sym == "-") {
		int offset = symbols->offset();
        value = muldiv(run);
		if (run || QBasicValidation::isValidSub(value)) {
			value = value.mul(value.type, -1);
		} else {
			errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int, VariableType::Float}, value));
		}
    } else if(sym == "not") {
		int offset = symbols->offset();
		value = muldiv(run);
		if (run || QBasicValidation::isValidNot(value)) {
			value = !value;
		} else {
			errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Bool}, value));
		}
    } else {
        pushBack(sym);
        value = muldiv(run);
    }
    
    // 式実行
    sym = getSymbol();
    while (true) {
        if (sym == "+") {
			int offset = symbols->offset();
            auto valueDist = muldiv(run);
			if (run || QBasicValidation::isValidAdd(value, valueDist)) {
				value = value + valueDist;
			} else {
				errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
			}
        } else if(sym == "-") {
			int offset = symbols->offset();
			auto valueDist = muldiv(run);
			if (run || QBasicValidation::isValidSub(value, valueDist)) {
				value = value - valueDist;
			} else {
				errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
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
QBasicVariableEntity QBasic::muldiv(const bool run) {
    
    // 戻り値取得
    auto value = factor(run);
    
    string sym = getSymbol();
    while (true) {
		if (sym == "*") {
			int offset = symbols->offset();
			auto valueDist = factor(run);
			if (run || QBasicValidation::isValidMul(value, valueDist)) {
				value = value * valueDist;
			} else {
				errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
			}
		} else if (sym == "/") {
			int offset = symbols->offset();
			auto valueDist = factor(run);
			if (run || QBasicValidation::isValidDiv(value, valueDist)) {
				value = value / valueDist;
			} else {
				errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
			}
		} else if (sym == "%") {
			int offset = symbols->offset();
			auto valueDist = factor(run);
			if (run || QBasicValidation::isValidMod(value, valueDist)) {
				value = value % valueDist;
			} else {
				errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value, valueDist));
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
 * 戻り値の取得
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasic::factor(const bool run) {
    
    string sym = getSymbol();
    
	if (localVariables.find(sym) != localVariables.end() ||
		variables.find(sym) != variables.end()) {
		auto operate = getSymbol();
		if (operate != "(") {
			pushBack(operate);
			auto variable = getVariable(run, sym);
			return *variable;
		}
		pushBack(operate);
	}
 
	if (sym.length() == 1) {
		switch (sym.c_str()[0]) {
			case '(': {
				auto value = expression(run);
				match(")");
				return value;
			}
			case '[': {
				auto value = listValue(run);
				return value;
			}
			case '{': {
				auto value = dictValue(run);
				return value;
			}
        }
    }
    
    // 数値ならば
	if (QBasicValidation::isFloat(sym)) {
		return QBasicVariableEntity("", sym);
	}

	// 文字ならば
    if (sym.find("\"") == 0) {
		return QBasicVariableEntity("", sym);
	}
	
	// bool値ならば
	if (sym == "true" || sym == "false") {
		return QBasicVariableEntity("", sym);
	}
	
	// ステートメント
	if (statements->hasName(sym)) {
		auto value = executeStatement(run, sym, true);
		return value;
	}
	
	// ファンクション
	if (functions->hasName(sym)) {
		return executeFunction(run, sym);
	}
	
	// 不明な文字が見つかりました。
	errors->addError(ErrorType::UnknownSymbol, sym);

    return QBasicVariableEntity("", sym);
}

/**
 * 戻り値なし実行
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::statement(const bool run) {
    
    auto sym = getSymbol();
    
    // 終了
    if (sym.empty()) {
        return false;
    }

	if (localVariables.find(sym) != localVariables.end() ||
		variables.find(sym) != variables.end()) {
		auto operate = getSymbol();
		if (operate != "(") {
			pushBack(operate);
			return analysisValueAssigned(run, sym);
		}
		pushBack(operate);
	}
	if (sym == "var") {
		return analysisVar(run);
    }
	if (sym == "if") {
		return analysisIf(run);
    }
	if (sym == "for") {
		return analysisFor(run);
	}
	if (sym == "break") {
		if (run) {
			// TODO: ループ内ではないときの対応を入れる
			isBreak = true;
		}
		return !run;
	}
	if (sym == "continue") {
		if (run) {
			// TODO: ループ内ではないときの対応を入れる
			isContinue = true;
		}
		return !run;
	}
	if (sym == "func") {
		return analysisFunc(run);
	}
	if (sym == "return") {
		return analysisReturn(run);
	}
	if (sym == "endfunc") {
		return analysisEndfunc(run);
	}
	if (sym == "exit") {
		if (run) {
			isExit = true;
		}
		return !run;
	}
	if (sym == "pass") {
		return true;
    }
	if (statements->hasName(sym)) {
        // ステートメント
		executeStatement(run, sym, false);
		return true;
	}
	if (functions->hasName(sym)) {
		// ファンクション
		executeFunction(run, sym);
		return true;
	}
	if (sym.c_str()[0] == '#') {
		// コメント
		return true;
	}
 
	pushBack(sym);
	expression(run);
	
	return true;
}

/**
 * list型の取得
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasic::listValue(const bool run) {
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
			symbols->popBack();
			match(",");
			sym = getSymbol();
		}
		QBasicVariableEntity value;
		if (sym == "[") {
			value = listValue(run);
		} else if(sym == "{") {
			value = dictValue(run);
		} else {
			symbols->popBack();
			value = expression(run);
		}
		returnValue.listValue.push_back(value);
		count += 1;
	}
	return returnValue;
}

/**
 * dict型の取得
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasic::dictValue(const bool run) {
	QBasicVariableEntity returnValue;
	returnValue.type = VariableType::Dict;
	// 上位で"{"のチェックがされる
	int count = 0;
	while (true) {
		auto sym = getSymbol();
		if (sym == "}") {
			break;
		}
		symbols->popBack();
		if (count > 0) {
			match(",");
		}
		int offset = symbols->offset();
		auto keyValue = expression(run);
		if (!run && keyValue.type != VariableType::Str) {
			errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Str}, keyValue));
		}
		match(":");
		QBasicVariableEntity value;
		sym = getSymbol();
		if (sym == "[") {
			value = listValue(run);
		} else if(sym == "{") {
			value = dictValue(run);
		} else {
			symbols->popBack();
			value = expression(run);
		}
		returnValue.dictValue[keyValue.strValue] = value;
		count += 1;
	}
	return returnValue;
}

/**
 * 例外を設定
 * @param message メッセージ
 * @exception コンパイルエラー
 */
void QBasic::setThrow(const string &message) {
	// 行数取得
	auto symbolEntity = symbols->beforeSymbolEntity();
	// ログ出力
	ostringstream stream;
	stream << "row:" << symbolEntity->row << " col:" << symbolEntity->col << " " << message;
	throw runtime_error(stream.str());
}

/**
 *  例外を設定
 *  @param messegeCode メッセージコード
 *  @param params   　  パラメータ
 *  @exception コンパイルエラー
 */
void QBasic::setThrow(const string &messegeCode, const char *params) {
	string message = messages->getMessage(messegeCode, params);
	setThrow(message);
}

#pragma mark - 実行

/**
 * ステートメント実行
 * @param run              実行中フラグ
 * @param functionName     関数名
 * @param needsReturnValue 戻り値
 * @return 戻り値
 */
QBasicVariableEntity QBasic::executeStatement(const bool run, const string &functionName, const bool needsReturnValue) {
	int offset = symbols->offset() - 1;
	
	// 引数取得
	auto argList = getArguments(run);
	// 省略引数とマージ
	argList = statements->mergeArguments(functionName, argList);

	auto entity = statements->getStatement(functionName, argList);
	if (run) {
		return entity->func(this, argList);
	}
	// 該当のステートメントなし
	if (entity == nullptr) {
		errors->addError(offset, ErrorType::UnknownFunction, functionName);
		return QBasicVariableEntity();
	}
	// 戻り値がvoid
	if (needsReturnValue && entity->returnType == VariableType::Void) {
		errors->addError(offset, ErrorType::ReturnTypeVoid, entity->alias);
		return QBasicVariableEntity();
	}
	return QBasicVariableEntity("", entity->returnType, nullptr);
}

/**
 * func実行
 * @param run            実行中フラグ
 * @param functionName   関数名
 * @return 戻り値
 */
QBasicVariableEntity QBasic::executeFunction(const bool run, const string &functionName) {

	int offset = symbols->offset() - 1;
	
	// 引数取得
	auto argList = getArguments(run);
	// 省略引数とマージ
	argList = functions->mergeArguments(functionName, argList);
	
	// 関数エリアス取得
	auto entity = functions->getFunction(functionName, argList);

	if (!run) {
		if (entity == nullptr) {
			errors->addError(offset, ErrorType::UnknownFunction, functionName);
			return QBasicVariableEntity("", VariableType::Void, nullptr);
		}
		return QBasicVariableEntity("", entity->returnType, entity->returnSubTypes, nullptr);
	}
	
	// ローカル変数に行数とプッシュバック変数を退避
	auto pushBackEntity = QBasicPushBackEntity(lastFunctionName, pushBacked, symbols->offset(), localVariables);
	functionPushBacks.push_back(pushBackEntity);

	// 実行オフセットを設定
	lastFunctionName = entity->alias;
	symbols->jumpOffset(entity->startOffset);
	
	// 情報クリア
	pushBacked.clear();
	localVariables.clear();
	
	// ローカル変数に引数を設定する
	for (auto it = argList.begin();it != argList.end();it++) {
		localVariables[it->name] = *it;
	}

	// 実行
	while(true) {
		bool isExecute = statement(run);
		if (!isExecute || isExit) {
			break;
		}
	}
	
	// 戻り値が設定されているので返却
	if (variables.find(FUNCTION_RETURN_VARIABLE_NAME) != variables.end()) {
		return variables[FUNCTION_RETURN_VARIABLE_NAME];
	} else {
		return QBasicVariableEntity("", VariableType::Void, nullptr);
	}
}

/**
 * func終了実行
 * @param run          実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::executeFunctionEnd(const bool run) {
	// 関数内ではない
	if (functionPushBacks.size() <= 0) {
		return false;
	}
	// 退避していたものを戻す
	QBasicPushBackEntity entity = *(functionPushBacks.end() - 1);
	lastFunctionName = entity.name;
	pushBacked = entity.symbol;
	symbols->jumpOffset(entity.execOffset);
	localVariables.clear();
	localVariables = entity.localVariables;
	// 削除
	functionPushBacks.pop_back();
	return true;
}

/**
 * 引数取得
 * @param run      実行モード
 * @return 引数群
 */
vector<QBasicVariableEntity> QBasic::getArguments(const bool run) {
	
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
			symbols->popBack();
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
			symbols->popBack();
			symbols->popBack();
			auto value = expression(run);
			value.name = "";
			argList.push_back(value);
		}
		count += 1;
	}
	
	return argList;
}

#pragma mark - 個別解析

/**
 * 変数取得
 * @param name 変数名
 * @param run  実行中フラグ
 * @return 変数取得
 */
QBasicVariableEntity *QBasic::getVariable(const bool run, const string &name) {

	// 変数があるかどうかは上位でチェックしている
	QBasicVariableEntity *variable;
	if (localVariables.find(name) != localVariables.end()) {
		// ローカル
		variable = &localVariables[name];
	} else {
		// グローバル
		variable = &variables[name];
	}
	while (true) {
		if (variable->type != VariableType::List &&
			variable->type != VariableType::Dict) {
			break;
		}
		
		auto sym = getSymbol();
		if (sym != "[") {
			symbols->popBack();
			break;
		}
		
		int offset = symbols->offset();
		
		auto keyValue = expression(run);
		match("]");
		
		if (variable->type == VariableType::List) {
			if (!run) {
				if (keyValue.type != VariableType::Int) {
					errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int}, keyValue));
					return nullptr;
				}
			} else {
				if (keyValue.intValue < 0 || keyValue.intValue >= variable->listValue.size()) {
					errors->setThrow(offset, ErrorType::ListIndexOutOfBounds, QBasicErrors::buildListIndexOutOfBounds(0, (int)variable->listValue.size() - 1, keyValue.intValue));
					return nullptr;
				}
			}
			variable = &variable->listValue[keyValue.intValue];
		} else {
			if (!run) {
				if (keyValue.type != VariableType::Str) {
					errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Str}, keyValue));
					return nullptr;
				}
			} else {
				if (variable->dictValue.find(keyValue.strValue) == variable->dictValue.end()) {
					errors->setThrow(offset, ErrorType::DictUnknownKey, keyValue.strValue);
					return nullptr;
				}
			}
			variable = &variable->dictValue[keyValue.strValue];
		}
	}
	
	return variable;
}

/**
 * 変数に代入
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisValueAssigned(const bool run, const string &variableName) {
	
	// 変数取得
	auto variable = getVariable(run, variableName);
	if (variable == nullptr) {
		return false;
	}
	// 記号
	int operateOffset = symbols->offset();
	auto operate = getSymbol();
	// 変数
	int valueOffset = symbols->offset();
	auto value = expression(run);
	value.valueTypes = QBasicVariableEntity::getVariableTypes(value);
	if (run) {
		if (operate == "+=") {
			value = *variable + value;
		} else if (operate == "-=") {
			value = *variable - value;
		} else if (operate == "*=") {
			value = *variable * value;
		} else if (operate == "/=") {
			value = *variable / value;
		} else if (operate == "%=") {
			value = *variable % value;
		}
		value.name = variableName;
		*variable = value;
		return true;
	}
	if (!QBasicValidation::isValidVariableType(value, variable->type, variable->valueTypes)) {
		errors->addError(valueOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({variable->type}, value));
	}
	if (operate == "+=") {
		if (!QBasicValidation::isValidAdd(*variable, value)) {
			errors->addError(operateOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int, VariableType::Float, VariableType::Str}, value));
		}
	} else if (operate == "-=") {
		if (!QBasicValidation::isValidSub(*variable, value)) {
			errors->addError(operateOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int, VariableType::Float}, value));
		}
	} else if (operate == "*=") {
		if (!QBasicValidation::isValidMul(*variable, value)) {
			errors->addError(operateOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int, VariableType::Float}, value));
		}
	} else if (operate == "/=") {
		if (!QBasicValidation::isValidDiv(*variable, value)) {
			errors->addError(operateOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int, VariableType::Float}, value));
		}
	} else if (operate == "%=") {
		if (!QBasicValidation::isValidMod(*variable, value)) {
			errors->addError(operateOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int}, value));
		}
	} else if (operate != "=") {
		errors->addError(operateOffset, ErrorType::UnknownSymbol, operate);
	}
	return true;
}

/**
 * 変数を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisVar(const bool run) {
	// 変数宣言
	int variableOffset = symbols->offset();
	auto variableName = getSymbol();
	if (!run) {
		// 名前が不適切
		if (!QBasicValidation::isValidVariableName(variableName)) {
			errors->addError(variableOffset, ErrorType::BadVariableName, variableName);
		}
		if (!lastFunctionName.empty()) {
			// func内の宣言ならばローカル変数
			if (localVariables.find(variableName) != localVariables.end()) {
				errors->addError(variableOffset, ErrorType::OverlapVariableName, variableName);
			}
		} else {
			// すでに宣言済み
			if (variables.find(variableName) != variables.end()) {
				errors->addError(variableOffset, ErrorType::OverlapVariableName, variableName);
			}
		}
	}

	auto sym = getSymbol();

	auto variableType = VariableType::Unknown;
	vector<VariableType> valueVariableTypes;
	if (sym == ":") {
		// 型をチェック
		int offset = symbols->offset();
		sym = getSymbol();
		variableType = QBasicVariableEntity::getVariableType(sym);
		if (!run) {
			if (variableType == VariableType::Void ||
				variableType == VariableType::Unknown) {
				errors->addError(offset, ErrorType::UnknownSymbol, sym);
			}
		}
		if (variableType == VariableType::List ||
			variableType == VariableType::Dict ) {
			// 配列の場合は型の宣言が必要
			analysisVarListDict(run, variableName, &valueVariableTypes);
		}
	
		// 次を取得
		sym = getSymbol();
	}
	
	// 初期値設定されているか
	if (sym != "=") {
		if (!run && variableType == VariableType::Unknown) {
			errors->addError(variableOffset, ErrorType::BadVariableType, variableName);
		}
		if (!sym.empty()) {
			symbols->popBack();
		}
		QBasicVariableEntity variableEntity;
		switch (variableType) {
			case VariableType::List:
				variableEntity = QBasicVariableEntity(variableName, valueVariableTypes, vector<QBasicVariableEntity>());
				break;
			case VariableType::Dict:
				variableEntity = QBasicVariableEntity(variableName, valueVariableTypes, map<string, QBasicVariableEntity>());
				break;
			default:
				variableEntity = QBasicVariableEntity(variableName, variableType, nullptr);
				break;
		}
		if (!lastFunctionName.empty()) {
			localVariables[variableName] = variableEntity;
		} else {
			variables[variableName] = variableEntity;
		}
		return true;
	}

	// 初期値取得
	int offset = symbols->offset();
	auto value = expression(run);
	if (variableType != VariableType::Unknown) {
		if (!QBasicValidation::isValidVariableType(value, variableType, valueVariableTypes)) {
			errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({variableType}, value));
		}
	} else {
		value.valueTypes = QBasicVariableEntity::getVariableTypes(value);
	}

	value.name = variableName;
	if (!lastFunctionName.empty()) {
		localVariables[variableName] = value;
	} else {
		variables[variableName] = value;
	}
	
	return true;
}

/**
 * 変数を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisVarListDict(const bool run, const string &variableName, vector<VariableType> *valueVariableTypes) {
	// リストの場合は型の宣言が必要
	while(true) {
		match("<");
		int offset = symbols->offset();
		auto sym = getSymbol();
		auto valueVariableType = QBasicVariableEntity::getVariableType(sym);
		if (!run) {
			if (valueVariableType == VariableType::Void ||
				valueVariableType == VariableType::Unknown) {
				errors->addError(offset, ErrorType::UnknownSymbol, sym);
			}
		}
		valueVariableTypes->push_back(valueVariableType);
		if (valueVariableType != VariableType::List && valueVariableType != VariableType::Dict) {
			break;
		}
	}
	for (auto i = 0;i < valueVariableTypes->size();i++) {
		match(">");
	}
	return true;
}

/**
 * if文を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisIf(const bool run) {

	int ifKey = symbols->offset();
	int startOffset = ifKey;
	int ifIndex = 0;
	bool isElse = false;
	
	// if文
	auto value = expression(run);
	if (!run && !QBasicValidation::isValidIf(value)) {
		errors->addError(ifKey, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Bool}, value));
	}
	if (run && !value.boolValue) {
		ifIndex += 1;
		if (!jumpIf(ifKey, ifIndex)) {
			return true;
		}
	} else {
		if (!statement(run)) {
			return !isExit;
		}
		if (run) {
			jumpIf(ifKey, -1);
			return !isExit;
		}
	}
	while (true) {
		if (isBreak || isContinue) {
			// ループを抜ける
			jumpIf(ifKey, -1);
			break;
		}
		int offset = symbols->offset();
		auto sym = getSymbol();
		if (!run && sym.empty()) {
			errors->addError(ErrorType::NothingEndif, "");
			break;
		}
		if (sym == "endif") {
			if (run) {
				// ループを抜ける
				jumpIf(ifKey, -1);
			} else {
				ifs->add(ifKey, startOffset, symbols->offset());
			}
			break;
		} else if(sym == "elseif") {
			if (!run) {
				if (isElse) {
					errors->addError(offset, ErrorType::BadElseif, "");
				}
				ifs->add(ifKey, startOffset, symbols->offset() - 2);
				startOffset = symbols->offset() - 1;
			}
			int offset = symbols->offset();
			auto value = expression(run);
			if (!run && !QBasicValidation::isValidIf(value)) {
				errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Bool}, value));
			}
			if (run && !value.boolValue) {
				ifIndex += 1;
				if (!jumpIf(ifKey, ifIndex)) {
					break;
				}
			} else {
				if (!statement(run)) {
					break;
				}
				if (run) {
					jumpIf(ifKey, -1);
					break;
				}
			}
		} else if(sym == "else") {
			if (!run) {
				if (isElse) {
					errors->addError(offset, ErrorType::BadElse, "");
				}
				ifs->add(ifKey, startOffset, symbols->offset() - 2);
				startOffset = symbols->offset() - 1;
			}
			if (!statement(run)) {
				break;
			}
			// フラグON
			isElse = true;
		} else {
			pushBack(sym);
			if (!statement(run)) {
				break;
			}
		}
	}
	return !isExit;
}

/**
 * 次のif分へ
 * @param key   キー
 * @param index インデックス
 * @return 終了フラグ false:もうなし true:次へ
 */
bool QBasic::jumpIf(const int key, const int index) {
	pushBacked = "";
	auto ifEntities = (*ifs)[key];
	if (ifEntities == nullptr) {
		return false;
	}
	if (index < 0 || index >= ifEntities->size()) {
		// もう次がない
		symbols->jumpOffset((ifEntities->end() - 1)->endOffset);
		return false;
	}
	symbols->jumpOffset(ifEntities->at(index).startOffset);
	return true;
}

/**
 * for文を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisFor(const bool run) {
	
	int offset = symbols->offset();
	string variableName = getSymbol();
	QBasicVariableEntity *valueEntity = getVariable(run, variableName);
	
	if (!run) {
		if (valueEntity == nullptr) {
			errors->addError(offset, ErrorType::UnknownVariable, variableName);
		} else {
			if (!QBasicValidation::isValidFor(variables[variableName])) {
				errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int}, *valueEntity));
			}
		}
	}
	
	match("=");
	
	offset = symbols->offset();
	auto value = expression(run);
	if (!run && !QBasicValidation::isValidFor(value)) {
		errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int}, value));
	}
	variables[variableName].intValue = run ? value.intValue : 0;
	
	int from = variables[variableName].intValue;
	
	match("to");

	offset = symbols->offset();
	value = expression(run);
	if (!run && !QBasicValidation::isValidFor(value)) {
		errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int}, value));
	}
	
	int to = run ? value.intValue : 0;
	
	bool isUpLoop = true;
	int step = 0;
	auto sym = getSymbol();
	if (sym == "step") {
		value = expression(run);
		if (!run && !QBasicValidation::isValidFor(value)) {
			errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int}, value));
		}
		step = run ? value.intValue : 0;
		isUpLoop = step >= 0 ? true : false;
	} else {
		symbols->popBack();
		if (run) {
			if (from <= to) {
				step = 1;
			} else {
				step = -1;
				isUpLoop = false;
			}
		}
	}

	int startOffset = symbols->offset();

	int count = 0;
	int pcfor = symbols->offset();
	string pushbackfor = pushBacked;
	isBreak = false;
	isContinue = false;
	while (!run ||
		   (isUpLoop && variables[variableName].intValue <= to) ||
		   (!isUpLoop && variables[variableName].intValue >= to)) {
		
		symbols->jumpOffset(pcfor);
		pushBacked = pushbackfor;

		while (true) {
			sym = getSymbol();
			if (!run && sym.empty()) {
				errors->addError(ErrorType::NothingNext, "");
				break;
			}
			if (sym == "next") {
				if (!run) {
					// forに追加
					fors->addUpdate(startOffset, symbols->offset() - 1);
				}
				break;
			}
			pushBack(sym);
			if (!statement(run && !isContinue)) {
				if (isExit) {
					return false;
				}
				break;
			}
			if (isBreak || isContinue) {
				break;
			}
		}
		
		// カウント加算
		count++;
		
		isContinue = false;
		
		if (isBreak) {
			isBreak = false;
			break;
		}
		
		if (run) {
			variables[variableName].intValue += step;
		} else {
			break;
		}
	}
	
	// 次の処理まで飛ばす
	if (run) {
		auto forEntity = (*fors)[startOffset];
		symbols->jumpOffset(forEntity->endOffset + 1);
	}
	
	return true;
}


/**
 * 関数を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisFunc(const bool run) {

	int offset = symbols->offset();
	
	// func内にfuncを定義
	if (!run && !lastFunctionName.empty()) {
		errors->addError(offset, ErrorType::FunctionOverFunction, lastFunctionName);
	}
	
	// 関数名取得
	auto functionName = getSymbol();

	if (!run) {
		// 名前が不適切
		if (!QBasicValidation::isValidFunctionName(functionName)) {
			errors->addError(offset, ErrorType::BadVariableName, functionName);
		}
	}

	// 引数を解析
	vector<QBasicVariableEntity> argNames;
	bool isSuccess = analysisArguments(run, argNames);
	if (!isSuccess) {
		return false;
	}
	
	// function取得
	auto entity = functions->getFunction(functionName, argNames);
	
	if (run) {
		// 実行中ならば、endまで処理を飛ばす
		symbols->jumpOffset(entity->endOffset);
		return true;
	}
	
	// すでに宣言済み
	if (entity != nullptr) {
		errors->addError(offset, ErrorType::OverlapFunctionName, lastFunctionName);
	}
	
	// 戻り値タイプを解析
	auto sym = getSymbol();
	VariableType returnType;
	vector<VariableType> valueVariableTypes;
	if (sym != ":") {
		// 引数省略
		returnType = VariableType::Void;
		// オフセットを戻す
		if (!sym.empty()) {
			symbols->popBack();
		}
	} else {
		string returnVariableName = getSymbol();
		returnType = QBasicVariableEntity::getVariableType(returnVariableName);
		if (!run) {
			if (returnType == VariableType::Unknown) {
				errors->addError(offset, ErrorType::BadVariableType, returnVariableName);
			}
		}
		if (returnType == VariableType::List ||
			returnType == VariableType::Dict ) {
			// 配列の場合は型の宣言が必要
			analysisVarListDict(run, "", &valueVariableTypes);
		}
	}

	// ファンクション追加
	entity = functions->addUpdate(functionName, argNames, returnType, valueVariableTypes, symbols->offset(), 0);
	
	// 最後の関数名を退避
	lastFunctionName = entity->alias;
	// ローカル変数に引数を設定する
	localVariables.clear();
	for (auto it = argNames.begin();it != argNames.end();it++) {
		localVariables[it->name] = *it;
	}
	
	// 初期化
	hasReturnSymbol = false;
	
	return true;
}

/**
 * 引数を解析
 * @param argNames 出力引数
 * @param run      実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisArguments(const bool run, vector<QBasicVariableEntity> &argNames) {

	// 引数を解析
	match("(");
	while(true) {
		int offset = symbols->offset();
		auto variableName = getSymbol();
		if (!run && variableName.empty()) {
			break;
		}
		if (variableName == ")") {
			// 終了
			break;
		}
		if (argNames.size() > 0) {
			symbols->popBack();
			match(",");
			variableName = getSymbol();
		}
		
		// 変数名
		if (!run) {
			// 変数名が不正
			if (!QBasicValidation::isValidVariableName(variableName)) {
				errors->addError(offset, ErrorType::BadVariableName, variableName);
			}
			for (auto it = argNames.begin();it != argNames.end();it++) {
				if (it->name == variableName) {
					errors->addError(offset, ErrorType::OverlapVariableName, variableName);
				}
			}
		}
		
		auto variableType = VariableType::Unknown;
		vector<VariableType> valueVariableTypes;
		auto sym = getSymbol();
		if (sym == ":") {
			// 型指定へ
			int offset = symbols->offset();
			sym = getSymbol();
			variableType = QBasicVariableEntity::getVariableType(sym);
			if (!run) {
				if (variableType == VariableType::Void ||
					variableType == VariableType::Unknown) {
					errors->addError(offset, ErrorType::BadVariableType, sym);
				}
			}
			if (variableType == VariableType::List ||
				variableType == VariableType::Dict ) {
				// 配列の場合は型の宣言が必要
				analysisVarListDict(run, variableName, &valueVariableTypes);
			}
			
			// 次を取得
			sym = getSymbol();
		}
		
		QBasicVariableEntity variableEntity;
		if (sym != "=") {
			if (!run && variableType == VariableType::Unknown) {
				errors->addError(offset, ErrorType::BadVariableType, variableName);
			}
			if (!sym.empty()) {
				symbols->popBack();
			}
			variableEntity.name = variableName;
			variableEntity.type = variableType;
			variableEntity.valueTypes = valueVariableTypes;
		} else {
			// デフォルト値指定へ
			int offset = symbols->offset();
			QBasicVariableEntity value = expression(run);
			if (variableType != VariableType::Unknown) {
				// 型が一致するかをチェック
				if (!QBasicValidation::isValidVariableType(value, variableType, valueVariableTypes)) {
					errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({variableType}, value));
				}
			}
			variableEntity = value;
			variableEntity.name = variableName;
			variableEntity.valueTypes = valueVariableTypes;
			variableEntity.isEmpty = false;
		}
		
		argNames.push_back(variableEntity);
	}

	return true;
}

/**
 * returnを解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisReturn(const bool run) {
	auto entity = (*functions)[lastFunctionName];
	if (!run && entity == nullptr) {
		return true;
	}
	// 終了オフセットを退避
	if (entity->returnType == VariableType::Void) {
		if (run) {
			executeFunctionEnd(run);
		}
		return !run;
	}
	// 戻り値取得
	int offset = symbols->offset();
	auto value = expression(run);
	if (run) {
		executeFunctionEnd(run);
		// 値をグローバル変数に設定
		variables[FUNCTION_RETURN_VARIABLE_NAME] = value;
		return false;
	}
	if (!QBasicValidation::isValidVariableType(value, entity->returnType, entity->returnSubTypes)) {
		errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({entity->returnType}, value));
	}
	hasReturnSymbol = true;
	return true;
}

/**
 * endfuncを解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisEndfunc(const bool run) {
	auto entity = (*functions)[lastFunctionName];
	if (run) {
		// 戻り値あるはずがない
		if (entity->returnType != VariableType::Void) {
			errors->setThrow(symbols->offset() - 1, ErrorType::NothingReturnValue, "");
			return false;
		}
		executeFunctionEnd(run);
		// 終了
		return false;
	}
	if (entity == nullptr) {
		return true;
	}
	if (entity->returnType != VariableType::Void && !hasReturnSymbol) {
		errors->addError(ErrorType::NothingReturnValue, "");
	}
	// 終了オフセットを退避
	entity->endOffset = symbols->offset();
	// 最後の関数名をクリア
	lastFunctionName = "";
	localVariables.clear();
	return true;
}
