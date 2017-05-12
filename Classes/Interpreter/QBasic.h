//
//  QBasic.h
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/02/13.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#ifndef __ToolQTheWorld__QBasic__
#define __ToolQTheWorld__QBasic__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class QBasicStatements;
class QBasicFunctions;
class QBasicSymbols;
class QBasicFors;
class QBasicIfs;
class QBasicPushBackEntity;
class QBasicSubFunction;
class QBasicStringFunctions;
class QBasicNetFunctions;
class QBasicScene;
class QBasicMessages;
class QBasicFunctionEntity;
class QBasicVariableEntity;
enum class VariableType;

/**
 * イベントスクリプトインタプリタクラス
 */
class QBasic final {
public:
	
	/// 通信用サブファンクション
	QBasicNetFunctions *netFunc;
	/// サブファンクション
	QBasicSubFunction *subFunc;
	
	/// グローバル変数
	unordered_map<string, QBasicVariableEntity> variables;
	/// ローカル変数
	unordered_map<string, QBasicVariableEntity> localVariables;

	/**
	 *  コンストラクタ
	 *  @param scene     シーン
	 *  @param source    ソース
	 *  @param projectId プロジェクトId
	 */
	QBasic(QBasicScene *scene, const string &source, const string &projectId);
		
    /**
     *  デストラクタ
     */
    ~QBasic();
	
	/**
	 *  実行
	 *  @exception コンパイルエラー
	 */
	void run();
	
	/**
	 *  バックグランド実行
	 *  @return スレッド
	 *  @exception コンパイルエラー
	 */
	thread backgroundRun();

	/**
	 *  コンパイル
	 *  @exception コンパイルエラー
	 */
	void compile();

	/**
	 *  例外を設定
	 *  @param message メッセージ
	 *  @exception コンパイルエラー
	 */
	void setThrow(const string &message);
	
	/**
	 *  例外を設定
	 *  @param messegeCode メッセージコード
	 *  @param params   　  パラメータ
	 *  @exception コンパイルエラー
	 */
	void setThrow(const string &messegeCode, const char *params);

private:
    
    /// 実行プログラムソース
    string source;
	
	/// シンボル制御
	QBasicSymbols *symbols;
	
	/// runフラグ
	bool isRun;
	/// 終了フラグ
	bool isExit;
	/// breakフラグ
	bool isBreak;
	/// continueフラグ
	bool isContinue;

    /// プッシュバック用
    string pushBacked;
	
	/// ファンクション退避
	vector<QBasicPushBackEntity> functionPushBacks;
	
	/// 最後にアクセスした関数名
	string lastFunctionName;
	/// returnがあったかどうか
	bool hasReturnSymbol;

    /// ステートメント群
	QBasicStatements *statements;
	/// ファンクション群
	QBasicFunctions *functions;
	/// for群
	QBasicFors *fors;
	/// if群
	QBasicIfs *ifs;
	/// コンパイルメッセージ群
	QBasicMessages *messages;
	
	/**
	 *  実行 or コンパイル
	 *  @param run true:実行 false:コンパイル
	 *  @exception コンパイルエラー
	 */
	void initAndRun(const bool run);
	
    /**
     * 単語を退避しておく
     * @param symbol 単語
     */
    void pushBack(const string &symbol);
    
    /**
     * 単語取得
     * @return 単語文字列
     */
    string getSymbol();
    
    /**
     * 単語が一致しているかをチェック
     * @param str 比較文字列
     */
    void match(const string &str);
    
    /**
     * and、or、xor判定
     * @param run 実行中フラグ
     * @return 値
     */
    QBasicVariableEntity expression(const bool run);
    
    /**
     * =、<、<=、>、>=、<>判定
     * @param run 実行中フラグ
     * @return 値
     */
    QBasicVariableEntity relop(const bool run);
    
    /**
     * 足し算、引き算、NOTの計算
     * @param run 実行中フラグ
     * @return 値
     */
    QBasicVariableEntity addsub(const bool run);
    
    /**
     * 掛け算、割り算、あまりの計算
     * @param run 実行中フラグ
     * @return 値
     */
    QBasicVariableEntity muldiv(const bool run);
    
    /**
     * 戻り値の取得
     * @param run 実行中フラグ
     * @return 値
     */
    QBasicVariableEntity factor(const bool run);
	
	/**
	 * list型の取得
	 * @param run 実行中フラグ
	 * @return 値
	 */
	QBasicVariableEntity listValue(const bool run);

	/**
	 * dict型の取得
	 * @param run 実行中フラグ
	 * @return 値
	 */
	QBasicVariableEntity dictValue(const bool run);
	
    /**
     * 戻り値なし実行
     * @param run 実行中フラグ
     * @return 終了フラグ false:終了 true:進行
     */
    bool statement(const bool run);
    
	/**
	 *  処理を１つ戻す
	 * @param run 実行中フラグ
	 */
	void popBack(const bool run);

#pragma mark - 実行
	
	/**
	 * func実行
	 * @param run            実行中フラグ
	 * @param functionName   関数名
	 * @param returnVariable 戻り値
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool executeFunction(const bool run, const string &functionName, QBasicVariableEntity &returnVariable);
	
	/**
	 * func終了実行
	 * @param run          実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool executeFunctionEnd(const bool run);

	/**
	 * 引数取得
	 * @param run      実行モード
	 * @return 引数群
	 */
	vector<QBasicVariableEntity> getArguments(const bool run);

#pragma mark - 個別解析

	/**
	 * 変数取得
	 * @param name 変数名
	 * @param run  実行中フラグ
	 * @return 変数取得
	 */
	QBasicVariableEntity *getVariable(const bool run, const string &name);

	/**
	 * 変数に代入
	 * @param run          実行中フラグ
	 * @param variableName 変数名
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisValueAssigned(const bool run, const string &variableName);

	/**
	 * 変数を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisVar(const bool run);

	/**
	 * 変数を解析 配列型
	 * @param run                実行中フラグ
	 * @param variableName       変数名
	 * @param valueVariableTypes 値タイプ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisVarListDict(const bool run, const string &variableName, vector<VariableType> *valueVariableTypes);

	/**
	 * if文を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisIf(const bool run);
	
	/**
	 * 次のif分へ
	 * @param key   キー
	 * @param index インデックス
	 * @return 終了フラグ false:もうなし true:次へ
	 */
	bool jumpIf(const int key, const int index);
	
	/**
	 * for文を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisFor(const bool run);
	
	/**
	 * 関数を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisFunc(const bool run);
	
	/**
	 * 引数を解析
	 * @param argNames 出力引数
	 * @param run      実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisArg(const bool run, vector<QBasicVariableEntity> &argNames);
	
	/**
	 * returnを解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisReturn(const bool run);

	/**
	 * Endを解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisEnd(const bool run);
	
};

#endif /* defined(__ToolQTheWorld__QBasic__) */
