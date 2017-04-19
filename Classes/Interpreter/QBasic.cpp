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
#include "QBasicScene.h"
#include "QBasicFunctionEntity.h"
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
	
    // 退避
    this->source = source;
	
	// サブファンクション作成
	stringFunc = new QBasicStringFunctions();
	netFunc = new QBasicNetFunctions();
	subFunc = new QBasicSubFunction(scene, projectId);
}

/**
 *  デストラクタ
 */
QBasic::~QBasic() {
	// 解放
	delete stringFunc;
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
		labelName.clear();
		functions.clear();
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
    if (sym.compare(str) != 0) {
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
        if (sym.compare("and") == 0 ||
			sym.compare("or") == 0 ||
			sym.compare("xor") == 0 ) {
			
			auto valueDist = relop(run);
			if (QBasicValidation::isValidExpression(value, valueDist)) {
				if (sym.compare("and") == 0) {
					value = value.expressionAnd(valueDist);
				} else if (sym.compare("or") == 0) {
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
        if (sym.compare("=") == 0 ||
			sym.compare("<") == 0 ||
			sym.compare("<=") == 0 ||
			sym.compare(">") == 0 ||
			sym.compare(">=") == 0 ||
			sym.compare("<>") == 0 ) {
			
			auto valueDist = addsub(run);
			if (value.type == valueDist.type) {
				int result = value.compare(valueDist);
				value.type = VariableType::Bool;
				value.boolValue = ((sym.compare("=") == 0 && result == 0) ||
								   (sym.compare("<") == 0 && result < 0) ||
								   (sym.compare("<=") == 0 && result <= 0) ||
								   (sym.compare(">") == 0 && result > 0) ||
								   (sym.compare(">=") == 0 && result >= 0) ||
								   (sym.compare("<>") == 0 && result != 0));
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
    if (sym.compare("+") == 0) {
        value = muldiv(run);
    } else if(sym.compare("-") == 0) {
        value = muldiv(run);
		if (QBasicValidation::isValidSub(value)) {
			value = value.mul(value.type, -1);
		} else {
			setThrow("BadVariableTypeSub", nullptr);
		}
    } else if(sym.compare("not") == 0) {
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
        if (sym.compare("+") == 0) {
            auto valueDist = muldiv(run);
			if (QBasicValidation::isValidAdd(value, valueDist)) {
				value = value.add(valueDist);
			} else {
				setThrow("BadVariableTypeAdd", nullptr);
			}
        } else if(sym.compare("-") == 0) {
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
		if (sym.compare("*") == 0) {
			auto valueDist = factor(run);
			if (QBasicValidation::isValidMul(value, valueDist)) {
				value = value.mul(valueDist);
			} else {
				setThrow("BadVariableTypeMul", nullptr);
			}
		} else if (sym.compare("/") == 0) {
			auto valueDist = factor(run);
			if (QBasicValidation::isValidDiv(value, valueDist)) {
				value = value.div(valueDist);
				// TODO: num = StringUtil::toString(stof(num) / (run ? num2 : 1));
			} else {
				setThrow("BadVariableTypeDiv", nullptr);
			}
		} else if (sym.compare("%") == 0) {
			auto valueDist = factor(run);
			if (QBasicValidation::isValidMod(value, valueDist)) {
				value = value.mod(valueDist);
				// TODO: num = StringUtil::toString(stof(num) % (run ? num2 : 1));
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
		return variables[sym];
//		return TODO: run ? variables[sym].strValue : "1";
	} else if (sym.length() == 1) {
		if(sym.c_str()[0] == '(') {
            auto value = expression(run);
            match(")");
            return value;
        }
    } else {
        // 引数付きメソッドかな？
        auto *entity = statements->getStatement(sym);
        if(entity != nullptr && entity->argCount > 0 && entity->isReturnValue) {
            // 引数取得
            auto argList = getArg(run, entity->argTypes);
			if (run) {
				// TODO:
//				run ? entity->func(this, argList)
			} else {
				return QBasicVariableEntity("", "1");
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
	if (sym.compare("true") == 0 || sym.compare("false") == 0) {
		return QBasicVariableEntity("", sym);
	}
	
	// 引数付きメソッドかな？
	auto *entity = statements->getStatement(sym);
	if(entity != nullptr && entity->argCount <= 0 && entity->isReturnValue) {
		// TODO: 見直す
		if (run) {
			return *entity->func(this, vector<QBasicVariableEntity>());
		} else {
			QBasicVariableEntity("", "true");
		}
	} else {
		// [ERROR]不明な文字が見つかりました。
		setThrow("UnknownSymbol", sym.c_str());
	}

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
		// 変数
		match("=");
		auto value = expression(run);
		if (value.type != variables[sym].type) {
			setThrow("BadVariableType", nullptr);
			return false;
		}
		if (run) {
			value.name = sym;
			variables[sym] = value;
		}
		return true;
	} else if(sym.compare("var") == 0) {
		return analysisVar(run);
    } else if(sym.compare("if") == 0) {
		return analysisIf(run);
    } else if(sym.compare("label") == 0) {
		return analysisLabel(run);
    } else if(sym.compare("goto") == 0) {
		return analysisJump(run, false);
	} else if(sym.compare("gosub") == 0) {
		return analysisJump(run, true);
    } else if(sym.compare("return") == 0) {
		return analysisReturn(run);
    } else if(sym.compare("for") == 0) {
		return analysisFor(run);
    } else if(sym.compare("rem") == 0 || sym.compare("'") == 0) {
		return analysisRem(run);
	} else if(sym.compare("func") == 0) {
		return analysisFunc(run);
	} else if(sym.compare("end") == 0) {
		return analysisEnd(run);
	} else if(sym.compare("exit") == 0) {
		if (run) {
			isExit = true;
		}
		return !run;
    } else {
        // 戻り値ステートメントかな？
        auto *entity = statements->getStatement(sym);
		if(entity != nullptr && !entity->isReturnValue) {
            // 引数取得
			vector<QBasicVariableEntity> argList;
			argList = getArg(run, entity->argTypes);
			if (run) {
				// TODO: ステートメント実行
//				entity->func(this, argList);
			}
			return true;
		}
		
		if (isFunction(sym)) {
			return executeFunction(run, sym);
		}
		
		pushBack(sym);
		expression(run);
		
		return true;
    }
}

/**
 * 引数取得
 * @param run      実行モード
 * @param argTypes 引数タイプ
 * @return 引数群
 */
vector<QBasicVariableEntity> QBasic::getArg(const bool run, const vector<VariableType> &argTypes) {
	
    // 引数取得
    vector<QBasicVariableEntity> argList;
    match("(");
    for(int i = 0;i < argTypes.size();i++) {
        auto value = expression(run);
		if (!run) {
			if (value.type != argTypes[i]) {
				// 引数の型が不正
				setThrow("BadVariableType", nullptr);
				return vector<QBasicVariableEntity>();
			}
		}
        argList.push_back(value);
        if(i < argTypes.size() - 1) {
            match(",");
        }
    }
	// 最後の引数
	match(")");
	
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
	
	auto entity = functions[functionName];

	vector<VariableType> argTypes;
	for (auto it = entity.argNames.begin();it != entity.argNames.end();it++) {
		argTypes.push_back(it->type);
	}
	
	// 引数取得
	auto argList = getArg(run, argTypes);
	
	if (!run) {
		return true;
	}
	
	// ローカル変数に行数とプッシュバック変数を退避
	functionPushBacked.push_back(pushBacked);
	functionExecOffset.push_back(compileOffset);
	functionLocalVariables.push_back(localVariables);

	// 実行オフセットを設定
	compileOffset = entity.startOffset;
	execOffset = compileExecOffsets[compileOffset];
	
	// 情報クリア
	pushBacked.clear();
	localVariables.clear();
	
	// ローカル変数に引数を設定する
	for (int i = 0;i < entity.argNames.size();i++) {
		localVariables[entity.argNames[i].name] = argList[i];
	}
	// ファンクション変数も設定
	localVariables[functionName] = QBasicVariableEntity(functionName, entity.returnVariableType, nullptr);

	return true;
}

/**
 * func可否
 * @param functionName 関数名
 * @return func可否 true:func false:それ以外
 */
bool QBasic::isFunction(const string functionName) {
	return functions.find(functionName) != functions.end();
}

#pragma mark - 個別解析

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
	if (sym.compare("=") != 0) {
		// 型をチェック
		variableType = QBasicValidation::checkVariableType(sym);
		if (!run) {
			if (variableType == VariableType::Void || variableType == VariableType::Unknown) {
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
	if (sym.compare("=") != 0) {
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
	auto value = expression(run);
	
	if (variableType != VariableType::Unknown && value.type != variableType) {
		setThrow("BadVariableType", nullptr);
		return false;
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
		auto valueVariableType = QBasicValidation::checkVariableType(sym);
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
		if (sym.compare("endif") == 0) {
			break;
		} else if(sym.compare("elseif") == 0) {
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
		} else if(sym.compare("else") == 0) {
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
 * label文を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisLabel(const bool run) {
	// ラベル
	auto sym = getSymbol();
	if (!run) {
		// 既存チェック
		if (labelName.find(sym) != labelName.end()) {
			// [ERROR]ラベル名が二重で定義されています。
			setThrow("LabelNameOverlap", nullptr);
			return false;
		}
		labelName[sym] = (int)compileSymbols.size();
	}
	return true;
}

/**
 * goto、gosub文を解析
 * @param run     実行中フラグ
 * @param isGosub gosubか
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisJump(const bool run, const bool isGosub) {
	// ジャンプ
	auto value = expression(run);
	if (run) {
		if (labelName.find(value.strValue) == labelName.end()) {
			// [ERROR]定義されていないラベル名が指定されています。
			setThrow("LabelNameUnknown", nullptr);
			return false;
		}
		int loc = (int)labelName[value.strValue];
		if (isGosub) {
			// ローカル変数に行数とプッシュバック変数を退避
			gosubPushBacked.push_back(pushBacked);
			gosubExecOffset.push_back(compileOffset);
			//※				gosubLocalVariable.push_back(localVariable);
		}
		compileOffset = loc;
		execOffset = compileExecOffsets[loc];
		pushBacked.clear();
	}
	return true;
}

/**
 * return文を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasic::analysisReturn(const bool run) {
	if (run) {
		// リターンできない
		if (gosubPushBacked.size() <= 0) {
			// [ERROR]これ以上returnはできません。
			setThrow("CannotReturn", nullptr);
			return false;
		}
		// 退避していたものを戻す
		pushBacked = *(gosubPushBacked.end() - 1);
		compileOffset = *(gosubExecOffset.end() - 1);
		execOffset = compileExecOffsets[compileOffset];
		// 削除
		gosubPushBacked.pop_back();
		gosubExecOffset.pop_back();
		//※			gosubLocalVariable.pop_back();
	}
	return true;
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
	if (sym.compare("step") == 0) {
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
			if (sym.compare("next") == 0) {
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
			if (sym.compare("next") == 0) {
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

	if (run) {
		// 実行中ならば、endまで処理を飛ばす
		string functionName = getSymbol();
		compileOffset = functions[functionName].endOffset;
		execOffset = compileExecOffsets[compileOffset];
		return true;
	}
	
	// func内にfuncを定義
	if (!lastFunctionName.empty()) {
		// [ERROR]関数名が二重に定義されています。
		setThrow("FunctionOverFunction", lastFunctionName.c_str());
		return false;
	}
	
	string functionName = getSymbol();
	
	if (!isRun) {
		// 名前が不適切
		if (!QBasicValidation::isValidFunctionName(functionName)) {
			setThrow(QBasicValidation::errorMessage);
			return false;
		}
		// すでに宣言済み
		if (functions.find(functionName) != functions.end()) {
			// [ERROR]関数名が二重に定義されています。
			setThrow("FunctionNameOverlap", functionName.c_str());
			return false;
		}
		// TODO:変数名ともチェック
	}

	// 引数を解析
	vector<QBasicVariableEntity> argNames;
	match("(");
	while(true) {
		string variableName = getSymbol();
		if (variableName.compare(")") == 0) {
			break;
		}
		if (argNames.size() > 0) {
			if (variableName.compare(",") != 0) {
				// [ERROR]想定の文字が見つかりませんでした。
				ostringstream stream;
				stream << "o:',' x:'" << variableName << "'";
				setThrow("MissingFound", stream.str().c_str());
				return false;
			}
			variableName = getSymbol();
		}
		
		// 変数名
		if (!isRun) {
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
				if (it->name.compare(variableName) == 0) {
					// [ERROR]変数名が二重に定義されています。
					setThrow("VariableNameOverlap", variableName.c_str());
					return false;
				}
			}
		}
		
		// 型
		auto sym = getSymbol();
		auto variableType = QBasicValidation::checkVariableType(sym);
		if (!isRun) {
			if (variableType == VariableType::Unknown || variableType == VariableType::Void) {
				// [ERROR]変数のタイプが不正です。
				setThrow("BadVariableType", functionName.c_str());
				return false;
			}
		}
		
		QBasicVariableEntity variableEntity;
		variableEntity.name = variableName;
		variableEntity.type = variableType;
		argNames.push_back(variableEntity);
	}
	
	QBasicFunctionEntity entity;
	entity.name = functionName;
	entity.argNames = argNames;

	// 戻り値タイプを解析
	string returnVariableName = getSymbol();
	auto returnVariableType = QBasicValidation::checkVariableType(returnVariableName);
	if (returnVariableType != VariableType::Unknown) {
		entity.returnVariableType = returnVariableType;
	} else {
		// 省略されてる可能性があるので情報を戻す
		entity.returnVariableType = VariableType::Void;
		// オフセットを戻す
		if (!returnVariableName.empty()) {
			popBack(run);
		}
	}
	entity.startOffset = (long)compileSymbols.size();
	functions[functionName] = entity;
	
	// 最後の関数名を退避
	lastFunctionName = functionName;
	
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
		functions[lastFunctionName].endOffset = (long)compileSymbols.size();
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
