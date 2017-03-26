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
#include "QBInterpreterStatementEntity.h"
#include "QBInterpreterScene.h"
#include "QBInterpreterSetupNodeEntity.h"
#include "QBInterpreterSubFunction.h"
#include "QBInterpreterStringFunctions.h"
#include "QBInterpreterNetFunctions.h"
#include "QBInterpreterValidation.h"
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
	execOffset = 0;
	pushBacked.shrink_to_fit();
	initGlobalVariable();
	if (!run) {
		compileSymbols.clear();
		compileExecOffsets.clear();
		compileOffset = 0;
		labelName.clear();
	}
	if (!gosubPushBacked.empty()) {
		for(auto it = gosubPushBacked.begin();it != gosubPushBacked.end();it++){
			it->shrink_to_fit();
			gosubPushBacked.erase(it);
		}
		gosubPushBacked.shrink_to_fit();
		gosubExecOffset.shrink_to_fit();
	}
	
	// 実行
	while(statement(run));
}

/**
 *  グローバル変数を初期化
 */
void QBInterpreter::initGlobalVariable() {
	variables.clear();
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
    if(ch == 0x00){
        return "";
    }
    
    long execOffsetBackup = execOffset;
    
    // 数値が続くかぎりループ
    while (isdigit(ch) || ch == '.') {
        execOffset++;
        ch = cstr[execOffset];
    }
    
    // 位置が変わっていれば
    if(execOffsetBackup != execOffset){
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
        if(ch == '>' || ch == '='){
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
        if(ch == '='){
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
		ostringstream stream;
		stream << "'" << str << "' missing ('" << sym << "' found)";
		setThrow(stream.str());
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
        if (sym.compare("and") == 0){
            num = ((stoi(relop(run)) & stoi(num)) == 0) ? "0" : "1";
        } else if (sym.compare("or") == 0){
            num = ((stoi(relop(run)) | stoi(num)) == 0) ? "0" : "1";
        } else if (sym.compare("xor") == 0){
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
        if(num.find("-") == 0){
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
			if (isNumeric(num) && isNumeric(num2)) {
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
        QBInterpreterStatementEntity *entity = statements.getStatement(sym);
        if(entity != nullptr && entity->argCount > 0 && entity->isReturnValue){
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
	if (isNumeric(sym)) {
		return StringUtil::toString(stof(sym));
	}
	
    if (sym.find("\"") == 0) {
        // ダブルクォーテーション
        return sym.substr(1, sym.length() - 2);
    } else {
        // 引数付きメソッドかな？
        QBInterpreterStatementEntity *entity = statements.getStatement(sym);
        if(entity != nullptr && entity->argCount <= 0 && entity->isReturnValue){
			if (run) {
				// ステートメント実行
				return entity->func(this, vector<string>());
			} else {
				return "1";
			}
        } else {
            // メソッドがないよ
            ostringstream stream;
			stream << "unknown symbol '" << sym << "'";
			setThrow(stream.str());
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
		// 変数宣言
		sym = getSymbol();
		if (!run) {
			// 名前が不適切
			if (!QBInterpreterValidation::isValidVariableName(sym)) {
				setThrow("変数名が不適切です。");
			}
			// すでに宣言済み
			if (variables.find(sym) != variables.end()) {
				setThrow("変数が２重に定義されています。");
			}
		}
		variables[sym] = "";
		return true;
    } else if(sym.compare("if") == 0) {
        // if文
        bool b = !(expression(run).compare("0") == 0);
		bool isElse = false;
        match("then");
        while (statement(b && run)) {
            sym = getSymbol();
            if (sym.compare("endif") == 0) {
                break;
			} else if(sym.compare("elseif") == 0) {
				if (isElse) {
					setThrow("bad 'elseif'");
					return false;
				}
				b = !(expression(run).compare("0") == 0);
				match("then");
            } else if(sym.compare("else") == 0) {
				if (isElse) {
					setThrow("bad second 'else'");
					return false;
				}
                b = !b;
				// フラグON
				isElse = true;
            } else {
                pushBack(sym);
            }
        }
        return true;
    } else if(sym.compare("label") == 0) {
		// ラベル
		sym = getSymbol();
		if (!run) {
			// 保存
			labelName[sym] = (int)compileSymbols.size();
		}
        return true;
    } else if(sym.compare("goto") == 0 || sym.compare("gosub") == 0) {
        // ジャンプ
        string num = expression(run);
        if (run) {
            if (labelName.find(num) == labelName.end()) {
                ostringstream stream;
                stream << "unknown label '" << num << "'";
                setThrow(stream.str());
                return false;
            }
            int loc = (int)labelName[num];
            if (sym.compare("gosub") == 0) {
                // ローカル変数に行数とプッシュバック変数を退避
				gosubPushBacked.push_back(pushBacked);
				gosubExecOffset.push_back(compileOffset);
				gosubLocalVariable.push_back(localVariable);
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
				ostringstream stream;
				stream << "can not return";
				setThrow(stream.str());
				return false;
			}
			
			// 退避していたものを戻す
			pushBacked = *(gosubPushBacked.end() - 1);
			compileOffset = *(gosubExecOffset.end() - 1);
			execOffset = compileExecOffsets[compileOffset];
			// 削除
			gosubPushBacked.pop_back();
			gosubExecOffset.pop_back();
			gosubLocalVariable.pop_back();
        }
        return true;
    } else if(sym.compare("for") == 0) {
        sym = getSymbol();

		if (variables.find(sym) != variables.end()) {
			
            match("=");
			
            string num = expression(run);
			variables[sym] = run ? num : "0";
			
			int from = stoi(variables[sym]);
				
            sym = getSymbol();
            if (sym.compare("to") == 0) {
                num = expression(run);
                int to = run ? stoi(num) : 0;
				
				bool isUpLoop = true;
				int step = 0;
                sym = getSymbol();
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
					   (isUpLoop && stoi(variables[sym]) <= to) ||
					   (!isUpLoop && stoi(variables[sym]) >= to)) {
					
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
                            break;
                        }
                    }
					
					// カウント加算
					count++;
					
                    if (run) {
                        variables[sym] = StringUtil::toString(stoi(variables[sym]) + step);
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
							break;
						}
					}
				}
                return true;
            }
            // エラー
            ostringstream stream;
            stream << "variable missing(2)";
            setThrow(stream.str());
            return false;
        }
        
    } else if(sym.compare("rem") == 0 || sym.compare("'") == 0){
        const char *cstr = source.c_str();
        while (execOffset < source.length() && cstr[execOffset] != '\n') {
            execOffset++;
        }
        return true;
	} else if(sym.compare("exit") == 0){
		if (!run) {
			return true;
		} else {
			return false;
		}
    } else {
        // 引数付きメソッドかな？
        QBInterpreterStatementEntity *entity = statements.getStatement(sym);
//        if(entity != nullptr && entity->argCount > 0){
		if(entity != nullptr && !entity->isReturnValue){
            // 引数取得
			vector<string> argList;
			if (entity->argCount > 0){
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
    for(int i = 0;i < argCount;i++){
        string arg = expression(run);
        argList.push_back(arg);
        if(i < argCount - 1){
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
		if (source[i] == '\n'){
			row++;
		}
	}
	// ログ出力
	ostringstream stream;
	stream << "row:" << row << " " << message;
	stream << message;
	throw stream.str();
}

/**
 *  数値チェック
 *  @param num 文字
 *  @return 数値か否か
 */
bool QBInterpreter::isNumeric(const string num) {
	
	if (num.length() <= 0) {
		return false;
	}
	
	const char *cstr = num.c_str();
	if (num.length() > 0 && (cstr[0] == '-' || cstr[0] == '.' || isdigit(cstr[0]))) {
		int i = 0;
		for(i = 1; i < num.length(); i++) {
			if (!(isdigit(cstr[i]) || cstr[i] == '.')) {
				break;
			}
		}
		if (i >= num.length()) {
			// 数字なので一度数値に変換して戻す
			return true;
		}
	}
	
	return false;
}

