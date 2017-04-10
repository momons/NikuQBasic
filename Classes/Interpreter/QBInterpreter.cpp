//
//  QBInterpreter.cpp
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/02/13.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#include "QBInterpreter.h"
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <exception>
#include <sstream>
#include <iostream>
#include "QBInterpreterStatements.h"
#include "QBInterpreterStatementEntity.h"
#include "QBInterpreterScene.h"
#include "QBInterpreterFunctionEntity.h"
#include "QBInterpreterSetupNodeEntity.h"
#include "QBInterpreterSubFunction.h"
#include "QBInterpreterStringFunctions.h"
#include "QBInterpreterNetFunctions.h"
#include "QBInterpreterValidation.h"
#include "QBInterpreterMessages.h"
#include "StringUtil.h"

/**
 *  コンストラクタ
 *  @param scene     シーン
 *  @param source    ソース
 *  @param projectId プロジェクトId
 */
QBInterpreter::QBInterpreter(QBInterpreterScene *scene, const string source, const string projectId) {

    // 定数取得
	statements = QBInterpreterStatements::sharedInstance();
	messages = QBInterpreterMessages::sharedInstance();
	
    // 退避
    this->source = source;
	
	// サブファンクション作成
	stringFunc = new QBInterpreterStringFunctions();
	netFunc = new QBInterpreterNetFunctions();
	subFunc = new QBInterpreterSubFunction(scene, projectId);
}

/**
 *  デストラクタ
 */
QBInterpreter::~QBInterpreter() {
	// 解放
	delete stringFunc;
	delete netFunc;
	delete subFunc;
	
}

/**
 *  通常実行
 *  @exception コンパイルエラー
 */
void QBInterpreter::run() {
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
thread QBInterpreter::backgroundRun() {
	thread t1(&QBInterpreter::run, this);
	return t1;
}

/**
 *  コンパイル
 *  @exception コンパイルエラー
 */
void QBInterpreter::compile() {
	// コンパイル
	initAndRun(false);
}

/**
 *  実行 or コンパイル
 *  @param run true:実行 false:コンパイル
 *  @exception コンパイルエラー
 */
void QBInterpreter::initAndRun(const bool run) {
	
	// 初期化
	isRun = run;
	isExit = false;
	execOffset = 0;
	pushBacked.shrink_to_fit();
	variables.clear();
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
void QBInterpreter::pushBack(const string symbol) {
	pushBacked = symbol;
}

/**
 * 単語取得
 * @return 単語文字列
 */
string QBInterpreter::getSymbol() {
    
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
void QBInterpreter::match(const string str) {
    string sym = getSymbol();
    if (sym.compare(str) != 0) {
		// [ERROR]想定の文字が見つかりませんでした。
		ostringstream stream;
		stream << "o:'" << str << "' x:'" << sym << "'";
		string message = messages->getMessage("MissingFound", stream.str().c_str());
		setThrow(message);
    }
}

/**
 * and、or、xor判定
 * @param run 実行中フラグ
 * @return 値
 */
string QBInterpreter::expression(const bool run) {
    
    // 式の値取得
    string num = relop(run);
    
    string sym = getSymbol();
    while(true) {
        if (sym.compare("and") == 0) {
            num = ((stoi(relop(run)) & stoi(num)) == 0) ? "0" : "1";
        } else if (sym.compare("or") == 0) {
            num = ((stoi(relop(run)) | stoi(num)) == 0) ? "0" : "1";
        } else if (sym.compare("xor") == 0) {
            num = ((stoi(relop(run)) ^ stoi(num)) == 0) ? "0" : "1";
        } else {
            break;
        }
        sym = getSymbol();
    }
    pushBack(sym);
    
    return num;
}

/**
 * =、<、<=、>、>=、<>判定
 * @param run 実行中フラグ
 * @return 値
 */
string QBInterpreter::relop(const bool run) {
    
    // 足し算、引き算の値取得
    string num = addsub(run);
    
    string sym = getSymbol();
    while(true) {
        if (sym.compare("=") == 0) {
            num = (num.compare(addsub(run)) == 0) ? "1" : "0";
        } else if (sym.compare("<") == 0) {
            num = (num.compare(addsub(run)) < 0) ? "1" : "0";
        } else if (sym.compare("<=") == 0) {
            num = (num.compare(addsub(run)) <= 0) ? "1" : "0";
        } else if (sym.compare(">") == 0) {
            num = (num.compare(addsub(run)) > 0) ? "1" : "0";
        } else if (sym.compare(">=") == 0) {
            num = (num.compare(addsub(run)) >= 0) ? "1" : "0";
        } else if (sym.compare("<>") == 0) {
            num = (num.compare(addsub(run)) != 0) ? "1" : "0";
        } else {
            break;
        }
        sym = getSymbol();
    }
    pushBack(sym);
    
    return num;
}

/**
 * 足し算、引き算、NOTの計算
 * @param run 実行中フラグ
 * @return 値
 */
string QBInterpreter::addsub(const bool run) {
    
    string num;
    
    // 値取得
    string sym = getSymbol();
    if (sym.compare("+") == 0) {
        num = muldiv(run);
    } else if(sym.compare("-") == 0) {
        num = muldiv(run);
        if(num.find("-") == 0) {
            // マイナスが2つ重なったので+に
            num = num.substr(1, num.length());
        } else {
            num = "-" + num;
        }
    } else if(sym.compare("not") == 0) {
        num = muldiv(run).compare("0") == 0 ? "1" : "0";
    } else {
        pushBack(sym);
        num = muldiv(run);
    }
    
    // 式実行
    sym = getSymbol();
    while (true) {
        if (sym.compare("+") == 0) {
            string num2 = muldiv(run);
			if (QBInterpreterValidation::isNumeric(num) && QBInterpreterValidation::isNumeric(num2)) {
				// 数値同士の足し算
				num = StringUtil::toString(stof(num) + stof(num2));
			} else {
				// 文字列の足し算
                num += num2;
            }
        } else if(sym.compare("-") == 0) {
            num = StringUtil::toString(stof(num) - stof(muldiv(run)));
        } else {
            break;
        }
        sym = getSymbol();
    }
    pushBack(sym);
    
    return num;
}

/**
 * 掛け算、割り算、あまりの計算
 * @param run 実行中フラグ
 * @return 値
 */
string QBInterpreter::muldiv(const bool run) {
    
    // 戻り値取得
    string num = factor(run);
    
    string sym = getSymbol();
    while (true) {
        if (sym.compare("*") == 0) {
            num = StringUtil::toString(stof(num) * stof(factor(run)));
        } else if(sym.compare("/") == 0) {
            int num2 = stof(factor(run));
            num = StringUtil::toString(stof(num) / (run ? num2 : 1));
        } else if(sym.compare("%") == 0) {
            int num2 = stof(factor(run));
            num = StringUtil::toString(stoi(num) % (run ? num2 : 1));
        } else {
            break;
        }
        sym = getSymbol();
    }
    pushBack(sym);
    
    return num;
}

/**
 * 戻り値の取得
 * @param run 実行中フラグ
 * @return 値
 */
string QBInterpreter::factor(const bool run) {
    
    string sym = getSymbol();
    
	if (variables.find(sym) != variables.end()) {
		// 変数
		return run ? variables[sym] : "1";
	} else if (sym.length() == 1) {
		if(sym.c_str()[0] == '(') {
            string num = expression(run);
            match(")");
            return num;
        }
    } else {
        // 引数付きメソッドかな？
        QBInterpreterStatementEntity *entity = statements->getStatement(sym);
        if(entity != nullptr && entity->argCount > 0 && entity->isReturnValue) {
            // 引数取得
            vector<string> argList = getArg(run,entity->argCount);
			if (run) {
				// ステートメント実行
				return entity->func(this, argList);
			} else {
				return "1";
			}
        }
    }
    
    // 数値ならば
	if (QBInterpreterValidation::isNumeric(sym)) {
		return StringUtil::toString(stof(sym));
	}
	
    if (sym.find("\"") == 0) {
        // ダブルクォーテーション
        return sym.substr(1, sym.length() - 2);
    } else {
        // 引数付きメソッドかな？
        QBInterpreterStatementEntity *entity = statements->getStatement(sym);
        if(entity != nullptr && entity->argCount <= 0 && entity->isReturnValue) {
			if (run) {
				// ステートメント実行
				return entity->func(this, vector<string>());
			} else {
				return "1";
			}
        } else {
			// [ERROR]不明な文字が見つかりました。
			string message = messages->getMessage("UnknownSymbol", sym.c_str());
			setThrow(message);
        }
    }
    
    return sym;
}

/**
 * 戻り値なし実行
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBInterpreter::statement(const bool run) {
    
    string sym = getSymbol();
    
    // 終了
    if (sym.length() == 0) {
        return false;
    }

	if(variables.find(sym) != variables.end()) {
		// 変数
		match("=");
		string num = expression(run);
		if (run) {
			variables[sym] = num;
		}
		return true;
	} else if(sym.compare("var") == 0) {
		return analysisVar(run);
    } else if(sym.compare("if") == 0) {
		return analysisIf(run);
    } else if(sym.compare("label") == 0) {
		// ラベル
		sym = getSymbol();
		if (!run) {
			// 既存チェック
			if (labelName.find(sym) != labelName.end()) {
				// [ERROR]ラベル名が二重で定義されています。
				string message = messages->getMessage("LabelNameOverlap", sym.c_str());
				setThrow(message);
				return false;
			}
			labelName[sym] = (int)compileSymbols.size();
		}
        return true;
    } else if(sym.compare("goto") == 0 || sym.compare("gosub") == 0) {
        // ジャンプ
        string num = expression(run);
        if (run) {
            if (labelName.find(num) == labelName.end()) {
				// [ERROR]定義されていないラベル名が指定されています。
				string message = messages->getMessage("LabelNameUnknown", num.c_str());
				setThrow(message);
                return false;
            }
            int loc = (int)labelName[num];
            if (sym.compare("gosub") == 0) {
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
    } else if(sym.compare("return") == 0) {
        if (run) {
			// リターンできない
			if (gosubPushBacked.size() <= 0) {
				// [ERROR]これ以上returnはできません。
				string message = messages->getMessage("CannotReturn", nullptr);
				setThrow(message);
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
        // 引数付きメソッドかな？
        QBInterpreterStatementEntity *entity = statements->getStatement(sym);
		if(entity != nullptr && !entity->isReturnValue) {
            // 引数取得
			vector<string> argList;
			if (entity->argCount > 0) {
				argList = getArg(run,entity->argCount);
			}
			if (run) {
				// ステートメント実行
				entity->func(this, argList);
			}
        } else {
            pushBack(sym);
            expression(run);
            
            return true;
        }
    }
    
    return true;
}

/**
 * 引数取得
 * @param run 実行モード
 * @param argCount 引数取得
 * @return 引数群
 */
vector<string> QBInterpreter::getArg(const bool run, const int argCount) {
    
    // 引数取得
    vector<string> argList = vector<string>();
    match("(");
    for(int i = 0;i < argCount;i++) {
        string arg = expression(run);
        argList.push_back(arg);
        if(i < argCount - 1) {
            match(",");
        }else {
            // 最後の引数
            match(")");
        }
    }
    
    return argList;
}

/**
 * 例外を設定
 * @param message メッセージ
 * @exception コンパイルエラー
 */
void QBInterpreter::setThrow(const string message) {
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
	throw stream.str();
}

#pragma mark - 個別解析

/**
 * 変数を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBInterpreter::analysisVar(const bool run) {
	// 変数宣言
	auto sym = getSymbol();
	if (!run) {
		// 名前が不適切
		if (!QBInterpreterValidation::isValidVariableName(sym)) {
			setThrow(QBInterpreterValidation::errorMessage);
			return false;
		}
		// すでに宣言済み
		if (variables.find(sym) != variables.end()) {
			// [ERROR]変数名が二重に定義されています。
			string message = messages->getMessage("VariableNameOverlap", sym.c_str());
			setThrow(message);
			return false;
		}
	}
	variables[sym] = "";
	return true;
}

/**
 * if文を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBInterpreter::analysisIf(const bool run) {
	// if文
	bool b = !(expression(run).compare("0") == 0);
	bool isElse = false;
	match("then");
	while (statement(b && run && !isExit)) {
		auto sym = getSymbol();
		if (sym.compare("endif") == 0) {
			break;
		} else if(sym.compare("elseif") == 0) {
			if (isElse) {
				// [ERROR]不正な場所にelseifがあります。
				string message = messages->getMessage("BadElseif", nullptr);
				setThrow(message);
				return false;
			}
			b = !(expression(run).compare("0") == 0);
			match("then");
		} else if(sym.compare("else") == 0) {
			if (isElse) {
				// [ERROR]不正な場所にelseがあります。
				string message = messages->getMessage("BadElse", nullptr);
				setThrow(message);
				return false;
			}
			b = !b;
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
bool QBInterpreter::analysisFor(const bool run) {
	string variableSym = getSymbol();
	
	if (variables.find(variableSym) == variables.end()) {
		// [ERROR]定義されていない変数名が指定されています。
		string message = messages->getMessage("VariableUnknown", variableSym.c_str());
		setThrow(message);
		return false;
	}
	
	match("=");
	
	string num = expression(run);
	variables[variableSym] = run ? num : "0";
	
	int from = stoi(variables[variableSym]);
	
	match("to");

	num = expression(run);
	int to = run ? stoi(num) : 0;
	
	bool isUpLoop = true;
	int step = 0;
	auto sym = getSymbol();
	if (sym.compare("step") == 0) {
		num = expression(run);
		step = run ? stoi(num) : 0;
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
		   (isUpLoop && stoi(variables[variableSym]) <= to) ||
		   (!isUpLoop && stoi(variables[variableSym]) >= to)) {
		
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
			variables[variableSym] = StringUtil::toString(stoi(variables[variableSym]) + step);
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
bool QBInterpreter::analysisFunc(const bool run) {

	if (run) {
		// 実行中ならば、endまで処理を飛ばす
		string functionName = getSymbol();
		compileOffset = functions[functionName].endOffset;
		execOffset = compileExecOffsets[compileOffset];
		return true;
	}
	
	// func内にfuncを定義
	if (lastFunctionName.length() > 0) {
		// [ERROR]関数名が二重に定義されています。
		string message = messages->getMessage("FunctionOverFunction", lastFunctionName.c_str());
		setThrow(message);
		return false;
	}
	
	string functionName = getSymbol();
	
	// 名前が不適切
	if (!QBInterpreterValidation::isValidFunctionName(functionName)) {
		setThrow(QBInterpreterValidation::errorMessage);
		return false;
	}
	// すでに宣言済み
	if (functions.find(functionName) != functions.end()) {
		// [ERROR]関数名が二重に定義されています。
		string message = messages->getMessage("FunctionNameOverlap", functionName.c_str());
		setThrow(message);
		return false;
	}

	// 引数を解析
	vector<string> argNames;
	match("(");
	while(true) {
		string sym = getSymbol();
		if (sym.compare(")") == 0) {
			break;
		}
		if (argNames.size() > 0) {
			if (sym.compare(",") != 0) {
				// [ERROR]想定の文字が見つかりませんでした。
				ostringstream stream;
				stream << "o:',' x:'" << sym << "'";
				string message = messages->getMessage("MissingFound", stream.str().c_str());
				setThrow(message);
				return false;
			}
			sym = getSymbol();
		}
		if (!QBInterpreterValidation::isValidVariableName(sym)) {
			setThrow(QBInterpreterValidation::errorMessage);
			return false;
		}
		// すでに宣言済み
		if (variables.find(sym) != variables.end() ||
			find(argNames.begin(), argNames.end(), sym) != argNames.end()) {
			// [ERROR]変数名が二重に定義されています。
			string message = messages->getMessage("VariableNameOverlap", sym.c_str());
			setThrow(message);
			return false;
		}
		argNames.push_back(sym);
	}
	
	QBInterpreterFunctionEntity entity;
	entity.argNames = argNames;
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
bool QBInterpreter::analysisEnd(const bool run) {
	if (run) {
		// endできない
		if (functionPushBacked.size() <= 0) {
			// [ERROR]これ以上endはできません。
			string message = messages->getMessage("CannotEnd", nullptr);
			setThrow(message);
			return false;
		}
		// 退避していたものを戻す
		pushBacked = *(functionPushBacked.end() - 1);
		compileOffset = *(functionExecOffset.end() - 1);
		execOffset = compileExecOffsets[compileOffset];
		// 削除
		functionPushBacked.pop_back();
		functionExecOffset.pop_back();
		//※			gosubLocalVariable.pop_back();
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
bool QBInterpreter::analysisRem(const bool run) {
	const char *cstr = source.c_str();
	while (execOffset < source.length() && cstr[execOffset] != '\n') {
		execOffset++;
	}
	return true;
}
