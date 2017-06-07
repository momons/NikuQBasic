//
//  QBasicCompile.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/07.
//
//

#ifndef QBasicCompile_h
#define QBasicCompile_h

#include "QBasicBase.h"

/// インタプリタメイン コンパイル用
class QBasicCompile final: public QBasicBase {
public:
	
	/**
	 * コンストラクタ
	 * @param interpreter　メイン
	 */
	QBasicCompile(QBasic *interpreter);
	
	/**
	 * デストラクタ
	 */
	~QBasicCompile() {}

private:

	/**
	 * 単語が一致しているかをチェック
	 * @param str 比較文字列
	 */
	void match(const string &str) override;
	
	/**
	 * and、or、xor判定
	 * @param run 実行中フラグ
	 * @return 値
	 */
	QBasicVariableEntity expression(const bool run) override;
	
	/**
	 * =、<、<=、>、>=、<>判定
	 * @param run 実行中フラグ
	 * @return 値
	 */
	QBasicVariableEntity relop(const bool run) override;
	
	/**
	 * 足し算、引き算、NOTの計算
	 * @param run 実行中フラグ
	 * @return 値
	 */
	QBasicVariableEntity addsub(const bool run) override;
	
	/**
	 * 掛け算、割り算、あまりの計算
	 * @param run 実行中フラグ
	 * @return 値
	 */
	QBasicVariableEntity muldiv(const bool run) override;
	
	/**
	 * 戻り値の取得
	 * @param run 実行中フラグ
	 * @return 値
	 */
	QBasicVariableEntity factor(const bool run) override;
	
	/**
	 * 戻り値なし実行
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool statement(const bool run) override;
	
	/**
	 * dict型の取得
	 * @param run 実行中フラグ
	 * @return 値
	 */
	QBasicVariableEntity dictValue(const bool run) override;

	/**
	 * 変数取得
	 * @param name 変数名
	 * @param run  実行中フラグ
	 * @return 変数取得
	 */
	QBasicVariableEntity *getVariable(const bool run, const string &name) override;
	
	/**
	 * ステートメント実行
	 * @param run              実行中フラグ
	 * @param functionName     関数名
	 * @param needsReturnValue 戻り値
	 * @return 戻り値
	 */
	QBasicVariableEntity executeStatement(const bool run, const string &functionName, const bool needsReturnValue) override;
	
	/**
	 * func実行
	 * @param run            実行中フラグ
	 * @param functionName   関数名
	 * @return 戻り値
	 */
	QBasicVariableEntity executeFunction(const bool run, const string &functionName) override;
	
	/**
	 * 変数に代入
	 * @param run          実行中フラグ
	 * @param variableName 変数名
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisValueAssigned(const bool run, const string &variableName) override;
	
	/**
	 * 変数を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisVar(const bool run) override;
	
	/**
	 * 変数を解析 配列型
	 * @param run                実行中フラグ
	 * @param variableName       変数名
	 * @param valueVariableTypes 値タイプ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisVarListDict(const bool run, const string &variableName, vector<VariableType> &valueVariableTypes) override;
	
	/**
	 * if文を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisIf(const bool run) override;
	
	/**
	 * for文を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisFor(const bool run) override;
	
	/**
	 * 関数を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisFunc(const bool run) override;
	
	/**
	 * 引数を解析
	 * @param argNames 出力引数
	 * @param run      実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisArguments(const bool run, vector<QBasicVariableEntity> &argNames) override;
	
	/**
	 * returnを解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisReturn(const bool run) override;
	
	/**
	 * endfuncを解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	bool analysisEndfunc(const bool run) override;
};

#endif /* QBasicCompile_h */
