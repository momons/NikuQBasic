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
#include "QBasicScene.h"
#include "QBasicVariableEntity.h"
#include "QBasicSetupNodeEntity.h"
#include "QBasicSubFunction.h"
#include "QBasicStringFunctions.h"
#include "QBasicNetFunctions.h"
#include "QBasicValidation.h"
#include "QBasicMessages.h"
#include "StringUtil.h"

/**
 *  コンストラクタ
 *  @param scene     シーン
 *  @param source    ソース
 *  @param projectId プロジェクトId
 */
QBasic::QBasic(QBasicScene *scene, const string &source, const string &projectId) {

    // 定数取得
	statements = QBasicStatements::sharedInstance();
	messages = QBasicMessages::sharedInstance();
	functions = new QBasicFunctions();
	
    // 退避
    this->source = source;
	
	// サブファンクション作成
	netFunc = new QBasicNetFunctions();
	subFunc = new QBasicSubFunction(scene, projectId);
}

/**
 *  デストラクタ
 */
QBasic::~QBasic() {
	// 解放
	delete functions;
	delete netFunc;
	delete subFunc;
	
}

/**
 *  通常実行
 *  @exception コンパイルエラー
 */
void QBasic::run() {
	// コンパイル
	initAndRun(false);
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
	execOffset = 0;
	pushBacked.shrink_to_fit();
	variables.clear();
	localVariables.clear();
	if (!run) {
		compileSymbols.clear();
		compileExecOffsets.clear();
		compileOffset = 0;
		functions->clear();
		lastFunctionName = "";
	}
	gosubPushBacked.clear();
	gosubExecOffset.clear();
	functionPushBacked.clear();
	functionExecOffset.clear();
	functionLocalVariables.clear();
	
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
		pushBacked.clear();
        return pushbackedBackup;
    }
	
	// 実行中
	if (isRun) {
		if (compileOffset >= compileSymbols.size()) {
			return "";
		}
		
		long offsetBack = compileOffset;
		compileOffset++;
		
		// オフセット設定
		execOffset = compileExecOffsets[offsetBack];
		
		return compileSymbols[offsetBack];
	}
    
    // 1文字抽出
    const char *cstr = source.c_str();
    char ch = cstr[execOffset];
  
    // スペースか改行があるかぎりループ
    while (isspace(ch)) {
        execOffset++;
        ch = cstr[execOffset];
    }
    
    // ゼロならばなし
    if(ch == 0x00) {
        return "";
    }
    
    long execOffsetBackup = execOffset;
    
    // 数値が続くかぎりループ
    while (isdigit(ch) || ch == '.') {
        execOffset++;
        ch = cstr[execOffset];
    }
    
    // 位置が変わっていれば
    if(execOffsetBackup != execOffset) {
		string symbol = source.substr(execOffsetBackup,execOffset - execOffsetBackup);
		compileSymbols.push_back(symbol);
		compileExecOffsets.push_back(execOffset);
        return symbol;
    }
    
    // 英数字が続くかぎりループ
    while (isalnum(ch)) {
        execOffset++;
        ch = cstr[execOffset];
    }
    
    // 位置が変わっていれば
    if (execOffsetBackup != execOffset) {
		string symbol = source.substr(execOffsetBackup,execOffset - execOffsetBackup);
		compileSymbols.push_back(symbol);
		compileExecOffsets.push_back(execOffset);
		return symbol;
    }

    // ダブルクォーテーション発見
    if (ch == '"') {
        execOffset++;
        ch = cstr[execOffset];
        // 次のダブルクォーテーションを見つけるまでループ
        while (ch != '"') {
            execOffset++;
            ch = cstr[execOffset];
        }
        execOffset++;
		
		string symbol = source.substr(execOffsetBackup,execOffset - execOffsetBackup);
		compileSymbols.push_back(symbol);
		compileExecOffsets.push_back(execOffset);
		return symbol;
    }
    
    // 小なり発見
    if (ch == '<') {
        execOffset++;
        ch = cstr[execOffset];
        // 次の文字が">"か"="ならばプラス1
        if(ch == '>' || ch == '=') {
            execOffset++;
        }
		
		string symbol = source.substr(execOffsetBackup,execOffset - execOffsetBackup);
		compileSymbols.push_back(symbol);
		compileExecOffsets.push_back(execOffset);
		return symbol;
    }

    // 大なり発見
    if (ch  == '>') {
        execOffset++;
        ch = cstr[execOffset];
        // 次の文字が"="ならばプラス1
        if(ch == '=') {
            execOffset++;
        }
		
		string symbol = source.substr(execOffsetBackup,execOffset - execOffsetBackup);
		compileSymbols.push_back(symbol);
		compileExecOffsets.push_back(execOffset);
		return symbol;
    }
    
    execOffset++;

	string symbol = source.substr(execOffsetBackup,execOffset - execOffsetBackup);
	compileSymbols.push_back(symbol);
	compileExecOffsets.push_back(execOffset);
	return symbol;
}

/**
 * 単語が一致しているかをチェック
 * @param str 比較文字列
 */
void QBasic::match(const string &str) {
    string sym = getSymbol();
    if (sym != str) {
		// [ERROR]想定の文字が見つかりませんでした。
		ostringstream stream;
		stream << "o:'" << str << "' x:'" << sym << "'";
		setThrow("MissingFound", stream.str().c_str());
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
        if (sym == "and" ||
			sym == "or" ||
			sym == "xor" ) {
			
			auto valueDist = relop(run);
			if (QBasicValidation::isValidExpression(value, valueDist)) {
				if (sym == "and") {
					value = value.expressionAnd(valueDist);
				} else if (sym == "or") {
					value = value.expressionOr(valueDist);
				} else {
					value = value.expressionXor(valueDist);
				}
			} else {
				setThrow("BadCompareVariableType");
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
        if (sym == "=" ||
			sym == "<" ||
			sym == "<=" ||
			sym == ">" ||
			sym == ">=" ||
			sym == "<>" ) {
			
			auto valueDist = addsub(run);
			if (value.type == valueDist.type) {
				int result = value.compare(valueDist);
				value.type = VariableType::Bool;
				value.boolValue = ((sym == "=" && result == 0) ||
								   (sym == "<" && result < 0) ||
								   (sym == "<=" && result <= 0) ||
								   (sym == ">" && result > 0) ||
								   (sym == ">=" && result >= 0) ||
								   (sym == "<>" && result != 0));
			} else {
				setThrow("BadCompareVariableType");
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
        value = muldiv(run);
		if (QBasicValidation::isValidSub(value)) {
			value = value.mul(value.type, -1);
		} else {
			setThrow("BadVariableTypeSub", nullptr);
		}
    } else if(sym == "not") {
		value = muldiv(run);
		if (QBasicValidation::isValidNot(value)) {
			value = value.expressionNot();
		} else {
			setThrow("BadVariableTypeNot", nullptr);
		}
    } else {
        pushBack(sym);
        value = muldiv(run);
    }
    
    // 式実行
    sym = getSymbol();
    while (true) {
        if (sym == "+") {
            auto valueDist = muldiv(run);
			if (QBasicValidation::isValidAdd(value, valueDist)) {
				value = value.add(valueDist);
			} else {
				setThrow("BadVariableTypeAdd", nullptr);
			}
        } else if(sym == "-") {
			auto valueDist = muldiv(run);
			if (QBasicValidation::isValidSub(value, valueDist)) {
				value = value.sub(valueDist);
			} else {
				setThrow("BadVariableTypeSub", nullptr);
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
			auto valueDist = factor(run);
			if (QBasicValidation::isValidMul(value, valueDist)) {
				value = value.mul(valueDist);
			} else {
				setThrow("BadVariableTypeMul", nullptr);
			}
		} else if (sym == "/") {
			auto valueDist = factor(run);
			if (QBasicValidation::isValidDiv(value, valueDist)) {
				if (run) {
					value = value.div(valueDist);
				} else {
					// TODO:
					value = QBasicVariableEntity("", value.type, nullptr);
				}
			} else {
				setThrow("BadVariableTypeDiv", nullptr);
			}
		} else if (sym == "%") {
			auto valueDist = factor(run);
			if (QBasicValidation::isValidMod(value, valueDist)) {
				if (run) {
					value = value.mod(valueDist);
				} else {
					// TODO:
					value = QBasicVariableEntity("", value.type, nullptr);
				}
			} else {
				setThrow("BadVariableTypeMod", nullptr);
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
    
	if (variables.find(sym) != variables.end()) {
		// 変数
		auto variable = getVariable(run, sym);
		if (variable == nullptr) {
			return QBasicVariableEntity();
		}
		return *variable;
	} else if (sym.length() == 1) {
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
	if(statements->hasName(sym)) {
		// 引数取得
		auto argList = getArg(run);
		auto entity = statements->getStatement(sym, argList);
		if (entity != nullptr) {
			if (entity->returnType == VariableType::Void) {
				setThrow("ReturnTypeVoid", nullptr);
			}
			if (run) {
				return entity->func(this, argList);
			} else {
				return QBasicVariableEntity("", entity->returnType, nullptr);
			}
		}
	}
	
	// ファンクション
	
	// [ERROR]不明な文字が見つかりました。
	setThrow("UnknownSymbol", sym.c_str());

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

	if(variables.find(sym) != variables.end()) {
		// 変数取得
		auto variable = getVariable(run, sym);
		if (variable == nullptr) {
			return false;
		}
		// 変数
		match("=");
		auto value = expression(run);
		value.valueTypes = QBasicVariableEntity::getVariableTypes(value);
		if (!QBasicValidation::isValidVariableType(value, variable->type, variable->valueTypes)) {
			setThrow("BadVariableType", nullptr);
			return false;
		}
		if (run) {
			value.name = sym;
			*variable = value;
		}
		return true;
	} else if(sym == "var") {
		return analysisVar(run);
    } else if(sym == "if") {
		return analysisIf(run);
    } else if(sym == "for") {
		return analysisFor(run);
    } else if(sym == "rem" || sym == "'") {
		return analysisRem(run);
	} else if(sym == "func") {
		return analysisFunc(run);
	} else if(sym == "end" || sym == "return") {
		return analysisEnd(run);
	} else if(sym == "exit") {
		if (run) {
			isExit = true;
		}
		return !run;
    } else {
        // 戻り値ステートメントかな？
		if (statements->hasName(sym)) {
			// 引数取得
			auto argList = getArg(run);
			auto entity = statements->getStatement(sym, argList);
			if (run) {
				// ステートメント実行
				entity->func(this, argList);
			}
			return true;
		}
		
		if (functions->hasName(sym)) {
			return executeFunction(run, sym);
		}
		
		pushBack(sym);
		expression(run);
		
		return true;
    }
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
			popBack(run);
			match(",");
			sym = getSymbol();
		}
		QBasicVariableEntity value;
		if (sym == "[") {
			value = listValue(run);
		} else if(sym == "{") {
			value = dictValue(run);
		} else {
			popBack(run);
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
		popBack(run);
		if (count > 0) {
			match(",");
		}
		auto keyValue = expression(run);
		if (keyValue.type != VariableType::Str) {
			setThrow("BadVariableType", nullptr);
		}
		match(":");
		QBasicVariableEntity value;
		sym = getSymbol();
		if (sym == "[") {
			value = listValue(run);
		} else if(sym == "{") {
			value = dictValue(run);
		} else {
			popBack(run);
			value = expression(run);
		}
		returnValue.dictValue[keyValue.strValue] = value;
		count += 1;
	}
	return returnValue;
}

/**
 * 引数取得
 * @param run      実行モード
 * @return 引数群
 */
vector<QBasicVariableEntity> QBasic::getArg(const bool run) {
	
    // 引数取得
    vector<QBasicVariableEntity> argList;
    match("(");
	int count = 0;
	while(true) {
		auto sym = getSymbol();
		if (sym == ")") {
			break;
		}
		popBack(run);
		if (count > 0) {
			match(",");
		}
		auto value = expression(run);
		argList.push_back(value);
		count += 1;
	}
	
    return argList;
}

/**
 * 例外を設定
 * @param message メッセージ
 * @exception コンパイルエラー
 */
void QBasic::setThrow(const string &message) {
	// 行数を検索
	int row = 1;
	for (int i = 0;i < execOffset - 1;i++) {
		if (source[i] == '\n') {
			row++;
		}
	}
	// ログ出力
	ostringstream stream;
	stream << "row:" << row << " " << message;
	stream << message;
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

/**
 *  処理を１つ戻す
 * @param run 実行中フラグ
 */
void QBasic::popBack(const bool run) {
	if (run) {
		compileOffset -= 1;
	} else {
		compileSymbols.pop_back();
		compileExecOffsets.pop_back();
		execOffset = compileExecOffsets[compileExecOffsets.size() - 1];
	}
}

#pragma mark - 実行

/**
 * func実行
 * @param run          実行中フラグ
 * @param functionName 関数名
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::executeFunction(const bool run, const string functionName) {
	
	// 引数取得
	auto argList = getArg(run);
	// 関数エリアス取得
	auto entity = functions->getFunction(functionName, argList);

	if (!run) {
		return true;
	}
	
	// ローカル変数に行数とプッシュバック変数を退避
	functionPushBacked.push_back(pushBacked);
	functionExecOffset.push_back(compileOffset);
	functionLocalVariables.push_back(localVariables);

	// 実行オフセットを設定
	compileOffset = entity->startOffset;
	execOffset = compileExecOffsets[compileOffset];
	
	// 情報クリア
	pushBacked.clear();
	localVariables.clear();
	
	// ローカル変数に引数を設定する
	for (int i = 0;i < entity->argNames.size();i++) {
		localVariables[entity->argNames[i].name] = argList[i];
	}
	// ファンクション変数も設定
	localVariables[functionName] = QBasicVariableEntity(functionName, entity->returnVariableType, nullptr);

	return true;
}

#pragma mark - 個別解析

/**
 * 変数取得
 * @param name 変数名
 * @param run  実行中フラグ
 * @return 変数取得
 */
QBasicVariableEntity *QBasic::getVariable(const bool run, const string name) {

	// 変数があるかどうかは上位でチェックしている
	QBasicVariableEntity *variable = &variables[name];
	while (true) {
		if (variable->type != VariableType::List &&
			variable->type != VariableType::Dict) {
			break;
		}
		
		auto sym = getSymbol();
		if (sym != "[") {
			popBack(run);
			break;
		}
		
		auto keyValue = expression(run);
		match("]");
		
		if (variable->type == VariableType::List) {
			if (keyValue.type != VariableType::Int) {
				setThrow("BadVariableTypeListKey", nullptr);
				return nullptr;
			}
			if (keyValue.intValue < 0 || keyValue.intValue >= variable->listValue.size()) {
				setThrow("ListIndexOutOfBounds", nullptr);
				return nullptr;
			}
			variable = &variable->listValue[keyValue.intValue];
		} else {
			if (keyValue.type != VariableType::Str) {
				setThrow("BadVariableTypeDictKey", nullptr);
				return nullptr;
			}
			if (variable->dictValue.find(keyValue.strValue) == variable->dictValue.end()) {
				setThrow("DictUnknownKey", nullptr);
				return nullptr;
			}
			variable = &variable->dictValue[keyValue.strValue];
		}
	}
	
	return variable;
}

/**
 * 変数を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisVar(const bool run) {
	// 変数宣言
	auto variableName = getSymbol();
	if (!run) {
		// 名前が不適切
		if (!QBasicValidation::isValidVariableName(variableName)) {
			setThrow(QBasicValidation::errorMessage);
			return false;
		}
		// すでに宣言済み
		if (variables.find(variableName) != variables.end()) {
			// [ERROR]変数名が二重に定義されています。
			setThrow("VariableNameOverlap", variableName.c_str());
			return false;
		}
		// TODO:関数名ともチェック
		
	}

	auto sym = getSymbol();

	auto variableType = VariableType::Unknown;
	vector<VariableType> valueVariableTypes;
	if (sym != "=") {
		// 型をチェック
		variableType = QBasicVariableEntity::getVariableType(sym);
		if (!run) {
			if (variableType == VariableType::Void ||
				variableType == VariableType::Unknown) {
				// [ERROR]変数のタイプが不正です。
				setThrow("BadVariableType", variableName.c_str());
				return false;
			}
		}
		if (variableType == VariableType::List ||
			variableType == VariableType::Dict ) {
			// 配列の場合は型の宣言が必要
			auto isExec = analysisVarListDict(run, variableName, &valueVariableTypes);
			if (!isExec) {
				return false;
			}
		}
		
		// 次を取得
		sym = getSymbol();
	}
	
	// 初期値設定されているか
	if (sym != "=") {
		if (!sym.empty()) {
			popBack(run);
		}
		switch (variableType) {
			case VariableType::List:
				variables[variableName] = QBasicVariableEntity(variableName, valueVariableTypes, vector<QBasicVariableEntity>());
				break;
			case VariableType::Dict:
				variables[variableName] = QBasicVariableEntity(variableName, valueVariableTypes, map<string, QBasicVariableEntity>());
				break;
			default:
				variables[variableName] = QBasicVariableEntity(variableName, variableType, nullptr);
				break;
		}
		return true;
	}

	// 初期値取得
	QBasicVariableEntity value = expression(run);
	if (variableType != VariableType::Unknown) {
		if (!QBasicValidation::isValidVariableType(value, variableType, valueVariableTypes)) {
			setThrow("BadVariableType", nullptr);
			return false;
		}
	} else {
		value.valueTypes = QBasicVariableEntity::getVariableTypes(value);
	}

	value.name = variableName;
	variables[variableName] = value;
	
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
		auto sym = getSymbol();
		auto valueVariableType = QBasicVariableEntity::getVariableType(sym);
		if (!run) {
			if (valueVariableType == VariableType::Void ||
				valueVariableType == VariableType::Unknown) {
				// [ERROR]変数のタイプが不正です。
				setThrow("BadVariableType", variableName.c_str());
				return false;
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
	// if文
	auto value = expression(run);
	if (!QBasicValidation::isValidIf(value)) {
		setThrow("BadVariableTypeIf", nullptr);
		return false;
	}
	bool isValid = value.boolValue;
	bool isElse = false;
	match("then");
	while (statement(isValid && run && !isExit)) {
		auto sym = getSymbol();
		if (sym == "endif") {
			break;
		} else if(sym == "elseif") {
			if (isElse) {
				// [ERROR]不正な場所にelseifがあります。
				setThrow("BadElseif", nullptr);
				return false;
			}
			auto value = expression(run);
			if (!QBasicValidation::isValidIf(value)) {
				setThrow("BadVariableTypeIf", nullptr);
				return false;
			}
			isValid = value.boolValue;
			match("then");
		} else if(sym == "else") {
			if (isElse) {
				// [ERROR]不正な場所にelseがあります。
				setThrow("BadElse", nullptr);
				return false;
			}
			isValid = !isValid;
			// フラグON
			isElse = true;
		} else {
			pushBack(sym);
		}
	}
	return !isExit;
}

/**
 * for文を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisFor(const bool run) {
	string variableName = getSymbol();
	
	if (!run) {
		if (variables.find(variableName) == variables.end()) {
			// [ERROR]定義されていない変数名が指定されています。
			setThrow("VariableUnknown", variableName.c_str());
			return false;
		}
		if (!QBasicValidation::isValidFor(variables[variableName])) {
			setThrow("BadVariableType", variableName.c_str());
			return false;
		}
	}
	
	match("=");
	
	auto value = expression(run);
	if (!QBasicValidation::isValidFor(value)) {
		setThrow("BadVariableType", nullptr);
		return false;
	}
	variables[variableName].intValue = run ? value.intValue : 0;
	
	int from = variables[variableName].intValue;
	
	match("to");

	value = expression(run);
	if (!QBasicValidation::isValidFor(value)) {
		setThrow("BadVariableType", nullptr);
		return false;
	}
	
	int to = run ? value.intValue : 0;
	
	bool isUpLoop = true;
	int step = 0;
	auto sym = getSymbol();
	if (sym == "step") {
		value = expression(run);
		if (!QBasicValidation::isValidFor(value)) {
			setThrow("BadVariableType", nullptr);
			return false;
		}
		step = run ? value.intValue : 0;
		isUpLoop = step >= 0 ? true : false;
	} else {
		if (run) {
			if (from <= to) {
				step = 1;
			} else {
				step = -1;
				isUpLoop = false;
			}
		}
		pushBack(sym);
	}
	
	int count = 0;
	long pcfor;
	if (isRun) {
		pcfor = compileOffset;
	} else {
		pcfor = execOffset;
	}
	string pushbackfor = pushBacked;
	while (!run ||
		   (isUpLoop && variables[variableName].intValue <= to) ||
		   (!isUpLoop && variables[variableName].intValue >= to)) {
		
		if (isRun) {
			compileOffset = pcfor;
			execOffset = compileExecOffsets[compileOffset];
		} else {
			execOffset = pcfor;
		}
		pushBacked = pushbackfor;
		
		while (true) {
			sym = getSymbol();
			if (sym == "next") {
				break;
			} else {
				pushBack(sym);
			}
			if (!statement(run)) {
				if (isExit) {
					return false;
				}
				break;
			}
		}
		
		// カウント加算
		count++;
		
		if (run) {
			variables[variableName].intValue += step;
		} else {
			break;
		}
	}
	if (count <= 0) {
		// 一回もループされなかったら捨てループ
		while (true) {
			sym = getSymbol();
			if (sym == "next") {
				break;
			} else {
				pushBack(sym);
			}
			if (!statement(false)) {
				if (isExit) {
					return false;
				}
				break;
			}
		}
	}
	return true;
}


/**
 * 関数を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisFunc(const bool run) {

	// func内にfuncを定義
	if (!run && !lastFunctionName.empty()) {
		// [ERROR]関数名が二重に定義されています。
		setThrow("FunctionOverFunction", lastFunctionName.c_str());
		return false;
	}
	
	// 関数名取得
	auto functionName = getSymbol();

	if (!run) {
		// 名前が不適切
		if (!QBasicValidation::isValidFunctionName(functionName)) {
			setThrow(QBasicValidation::errorMessage);
			return false;
		}
		// TODO: 変数名とかぶる
	}

	// 引数を解析
	vector<QBasicVariableEntity> argNames;
	bool isSuccess = analysisArg(run, argNames);
	if (!isSuccess) {
		return false;
	}
	
	// function取得
	auto entity = functions->getFunction(functionName, argNames);
	
	if (run) {
		// 実行中ならば、endまで処理を飛ばす
		compileOffset = entity->endOffset;
		execOffset = compileExecOffsets[compileOffset];
		return true;
	}
	
	// すでに宣言済み
	if (entity != nullptr) {
		// [ERROR]関数名が二重に定義されています。
		setThrow("FunctionNameOverlap", functionName.c_str());
		return false;
	}
	
	// 戻り値タイプを解析
	string returnVariableName = getSymbol();
	auto returnVariableType = QBasicVariableEntity::getVariableType(returnVariableName);
	if (returnVariableType == VariableType::Unknown) {
		// 省略されてる可能性があるので情報を戻す
		returnVariableType = VariableType::Void;
		// オフセットを戻す
		if (!returnVariableName.empty()) {
			popBack(run);
		}
	}

	// ファンクション追加
	entity = functions->addUpdate(functionName, argNames, returnVariableType, compileSymbols.size(), 0);
	
	// 最後の関数名を退避
	lastFunctionName = entity->alias;
	
	return true;
}

/**
 * 引数を解析
 * @param argNames 出力引数
 * @param run      実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisArg(const bool run, vector<QBasicVariableEntity> &argNames) {

	// 引数を解析
	match("(");
	while(true) {
		auto variableName = getSymbol();
		if (variableName == ")") {
			// 終了
			break;
		}
		if (argNames.size() > 0) {
			popBack(run);
			match(",");
			variableName = getSymbol();
		}
		
		// 変数名
		if (!run) {
			// 変数名が不正
			if (!QBasicValidation::isValidVariableName(variableName)) {
				setThrow(QBasicValidation::errorMessage);
				return false;
			}
			// すでに宣言済み
			if (variables.find(variableName) != variables.end()) {
				// [ERROR]変数名が二重に定義されています。
				setThrow("VariableNameOverlap", variableName.c_str());
				return false;
			}
			for (auto it = argNames.begin();it != argNames.end();it++) {
				if (it->name == variableName) {
					// [ERROR]変数名が二重に定義されています。
					setThrow("VariableNameOverlap", variableName.c_str());
					return false;
				}
			}
		}
		
		auto variableType = VariableType::Unknown;
		vector<VariableType> valueVariableTypes;
		auto sym = getSymbol();
		if (sym == ":") {
			// 型指定へ
			sym = getSymbol();
			variableType = QBasicVariableEntity::getVariableType(sym);
			if (!run) {
				if (variableType == VariableType::Void ||
					variableType == VariableType::Unknown) {
					// [ERROR]変数のタイプが不正です。
					setThrow("BadVariableType", variableName.c_str());
					return false;
				}
			}
			if (variableType == VariableType::List ||
				variableType == VariableType::Dict ) {
				// 配列の場合は型の宣言が必要
				auto isExec = analysisVarListDict(run, variableName, &valueVariableTypes);
				if (!isExec) {
					return false;
				}
			}
			
			// 次を取得
			sym = getSymbol();
		}
		
		QBasicVariableEntity variableEntity;
		variableEntity.name = variableName;
		variableEntity.type = variableType;
		variableEntity.valueTypes = valueVariableTypes;
		if (sym != "=") {
			if (variableType == VariableType::Unknown) {
				// [ERROR]変数のタイプが不正です。
				setThrow("BadVariableType", variableName.c_str());
				return false;
			}
			if (!sym.empty()) {
				popBack(run);
			}
		} else {
			// デフォルト値指定へ
			QBasicVariableEntity value = expression(run);
			if (variableType != VariableType::Unknown) {
				// 型が一致するかをチェック
				if (!QBasicValidation::isValidVariableType(value, variableType, valueVariableTypes)) {
					setThrow("BadVariableType", nullptr);
					return false;
				}
			} else {
				variableEntity.type = value.type;
				variableEntity.valueTypes = QBasicVariableEntity::getVariableTypes(value);
			}
		}
		
		argNames.push_back(variableEntity);
	}

	return true;
}

/**
 * Endを解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisEnd(const bool run) {
	if (run) {
		// endできない
		if (functionPushBacked.size() <= 0) {
			// [ERROR]これ以上endはできません。
			setThrow("CannotEnd", nullptr);
			return false;
		}
		// 退避していたものを戻す
		pushBacked = *(functionPushBacked.end() - 1);
		compileOffset = *(functionExecOffset.end() - 1);
		execOffset = compileExecOffsets[compileOffset];
		localVariables.clear();
		localVariables = *(functionLocalVariables.end() - 1);
		// 削除
		functionPushBacked.pop_back();
		functionExecOffset.pop_back();
		functionLocalVariables.pop_back();
	} else {
		// 終了オフセットを退避
		auto entity = functions->getFunction(lastFunctionName);
		entity->endOffset = (long)compileSymbols.size();
		// 最後の関数名をクリア
		lastFunctionName = "";
	}
	return true;
}

/**
 * コメントを解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisRem(const bool run) {
	const char *cstr = source.c_str();
	while (execOffset < source.length() && cstr[execOffset] != '\n') {
		execOffset++;
	}
	return true;
}
