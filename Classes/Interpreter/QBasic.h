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
class QBasicSubFunction;
class QBasicStringFunctions;
class QBasicNetFunctions;
class QBasicScene;
class QBasicMessages;
class QBasicFunctionEntity;
class QBasicVariableEntity;

/** 変数最大数 */
#define MAX_COUNT_VARIABLE 26

/**
 * イベントスクリプトインタプリタクラス
 */
class QBasic final {
public:
	
	/// 文字列操作用サブファンクション
	QBasicStringFunctions *stringFunc;
	/// 通信用サブファンクション
	QBasicNetFunctions *netFunc;
	/// サブファンクション
	QBasicSubFunction *subFunc;
	
	/// グローバル変数
	map<string, QBasicVariableEntity> variables;
	/// ローカル変数
	map<string, string> localVariables;

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
	
private:
    
    /// 実行プログラムソース
    string source;
	
	/// コンパイル済みのシンボル
	vector<string> compileSymbols;
	/// 各命令のオフセット
	vector<long> compileExecOffsets;
	/// コンパイル中オフセット
	long compileOffset;
	
	/// runフラグ
	bool isRun;
	/// 終了フラグ
	bool isExit;

    /// 現在の処理位置
    long execOffset;
	
    /// プッシュバック用
    string pushBacked;
	
	/// gosub情報
	vector<string> gosubPushBacked;
	vector<long> gosubExecOffset;
	vector<string *> gosubLocalVariable;
	
	/// ファンクション退避
	vector<string> functionPushBacked;
	vector<long> functionExecOffset;
	vector<map<string, string>> functionLocalVariables;
	
	/// 最後にアクセスした関数名
	string lastFunctionName;

    /// ラベル情報
    map<string, long> labelName;
    
    /// ステートメント群
	QBasicStatements *statements;
	/// ファンクション群
	map<string, QBasicFunctionEntity> functions;
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
    string expression(const bool run);
    
    /**
     * =、<、<=、>、>=、<>判定
     * @param run 実行中フラグ
     * @return 値
     */
    string relop(const bool run);
    
    /**
     * 足し算、引き算、NOTの計算
     * @param run 実行中フラグ
     * @return 値
     */
    string addsub(const bool run);
    
    /**
     * 掛け算、割り算、あまりの計算
     * @param run 実行中フラグ
     * @return 値
     */
    string muldiv(const bool run);
    
    /**
     * 戻り値の取得
     * @param run 実行中フラグ
     * @return 値
     */
    string factor(const bool run);
    
    /**
     * 戻り値なし実行
     * @param run 実行中フラグ
     * @return 終了フラグ false:終了 true:進行
     */
    bool statement(const bool run);
    
    /**
     * 引数取得
     * @param run 実行モード
     * @param argCount 引数取得
     * @return 引数群
     */
    vector<string> getArg(const bool run, const int argCount);

	/**
	 * func実行
	 * @param run          実行中フラグ
	 * @param functionName 関数名
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool executeFunction(const bool run, const string functionName);
	
	/**
	 * func可否
	 * @param functionName 関数名
	 * @return func可否 true:func false:それ以外
	 */
	bool isFunction(const string functionName);
	
	/**
	 * 変数を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisVar(const bool run);

	/**
	 * if文を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisIf(const bool run);
	
	/**
	 * label文を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisLabel(const bool run);
	
	/**
	 * goto、gosub文を解析
	 * @param run     実行中フラグ
	 * @param isGosub gosubか
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisJump(const bool run, const bool isGosub);
	
	/**
	 * return文を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisReturn(const bool run);
	
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
	 * Endを解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisEnd(const bool run);

	/**
	 * コメントを解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisRem(const bool run);
	
};

#endif /* defined(__ToolQTheWorld__QBasic__) */
