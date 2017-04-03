//
//  QBInterpreter.h
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/02/13.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#ifndef __ToolQTheWorld__QBInterpreter__
#define __ToolQTheWorld__QBInterpreter__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class QBInterpreterStatements;
class QBInterpreterSubFunction;
class QBInterpreterStringFunctions;
class QBInterpreterNetFunctions;
class QBInterpreterScene;
class QBInterpreterMessages;

/** 変数最大数 */
#define MAX_COUNT_VARIABLE 26

/**
 * イベントスクリプトインタプリタクラス
 */
class QBInterpreter final {
public:
	
	/// 文字列操作用サブファンクション
	QBInterpreterStringFunctions *stringFunc;
	/// 通信用サブファンクション
	QBInterpreterNetFunctions *netFunc;
	/// サブファンクション
	QBInterpreterSubFunction *subFunc;
	
	/// グローバル変数
	map<string, string> variables;

	/**
	 *  コンストラクタ
	 *  @param scene     シーン
	 *  @param source    ソース
	 *  @param projectId プロジェクトId
	 */
	QBInterpreter(QBInterpreterScene *scene, const string source, const string projectId);
		
    /**
     *  デストラクタ
     */
    ~QBInterpreter();
	
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
	void setThrow(const string message);
	
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

    /// 現在の処理位置
    long execOffset;
	
    /// プッシュバック用
    string pushBacked;
	
    /// ローカル変数
    string localVariable[MAX_COUNT_VARIABLE];
	
	/// gosub情報
	vector<string> gosubPushBacked;
	vector<long> gosubExecOffset;
	vector<string *> gosubLocalVariable;

    /// ラベル情報
    map<string, long> labelName;
    
    /// インタプリタ用コンスタント
	QBInterpreterStatements *statements;
	/// インタプリタ用メッセージ
	QBInterpreterMessages *messages;
	
	/**
	 *  実行 or コンパイル
	 *  @param run true:実行 false:コンパイル
	 *  @exception コンパイルエラー
	 */
	void initAndRun(const bool run);
	
	/**
	 *  グローバル変数を初期化
	 */
	
	void initGlobalVariable();
	
    /**
     * 単語を退避しておく
     * @param symbol 単語
     */
    void pushBack(const string symbol);
    
    /**
     * 単語取得
     * @return 単語文字列
     */
    string getSymbol();
    
    /**
     * 単語が一致しているかをチェック
     * @param str 比較文字列
     */
    void match(const string str);
    
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
	 *  数値チェック
	 *  @param num 文字
	 *  @return 数値か否か
	 */
	bool isNumeric(const string num);
};

#endif /* defined(__ToolQTheWorld__QBInterpreter__) */
