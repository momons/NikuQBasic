//
//  QBasicBase.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/07.
//
//

#ifndef QBasicBase_h
#define QBasicBase_h

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class QBasic;
class QBasicVariableEntity;
enum class VariableType;

/// インタプリタメイン ベース
class QBasicBase {
public:
	
	/**
	 * コンストラクタ
	 * @param interpreter　メイン
	 */
	QBasicBase(QBasic *interpreter);
	
	/**
	 * デストラクタ
	 */
	~QBasicBase();

	/**
	 * 戻り値なし実行
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	virtual bool statement(const bool run) = 0;
	
protected:
	
	/// 大元クラス
	QBasic *interpreter;
	/// プッシュバック用
	string pushBacked;
	
	/// 最後にアクセスした関数名
	string lastFunctionName;
	/// returnがあったかどうか
	bool hasReturnSymbol;
	
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
	virtual void match(const string &str) = 0;

	/**
	 * and、or、xor判定
	 * @param run 実行中フラグ
	 * @return 値
	 */
	virtual QBasicVariableEntity expression(const bool run) = 0;
	
	/**
	 * =、<、<=、>、>=、<>判定
	 * @param run 実行中フラグ
	 * @return 値
	 */
	virtual QBasicVariableEntity relop(const bool run) = 0;
	
	/**
	 * 足し算、引き算、NOTの計算
	 * @param run 実行中フラグ
	 * @return 値
	 */
	virtual QBasicVariableEntity addsub(const bool run) = 0;
	
	/**
	 * 掛け算、割り算、あまりの計算
	 * @param run 実行中フラグ
	 * @return 値
	 */
	virtual QBasicVariableEntity muldiv(const bool run) = 0;
	
	/**
	 * 戻り値の取得
	 * @param run 実行中フラグ
	 * @return 値
	 */
	virtual QBasicVariableEntity factor(const bool run) = 0;

	/**
	 * list型の取得
	 * @param run 実行中フラグ
	 * @return 値
	 */
	virtual QBasicVariableEntity listValue(const bool run);
	
	/**
	 * dict型の取得
	 * @param run 実行中フラグ
	 * @return 値
	 */
	virtual QBasicVariableEntity dictValue(const bool run) = 0;

	/**
	 * 変数取得
	 * @param name 変数名
	 * @param run  実行中フラグ
	 * @return 変数取得
	 */
	virtual QBasicVariableEntity *getVariable(const bool run, const string &name) = 0;
	
	/**
	 * ステートメント実行
	 * @param run              実行中フラグ
	 * @param functionName     関数名
	 * @param needsReturnValue 戻り値
	 * @return 戻り値
	 */
	virtual QBasicVariableEntity executeStatement(const bool run, const string &functionName, const bool needsReturnValue) = 0;
	
	/**
	 * 引数取得
	 * @param run      実行モード
	 * @return 引数群
	 */
	virtual vector<QBasicVariableEntity> getArguments(const bool run);
	
	/**
	 * func実行
	 * @param run            実行中フラグ
	 * @param functionName   関数名
	 * @return 戻り値
	 */
	virtual QBasicVariableEntity executeFunction(const bool run, const string &functionName) = 0;

	/**
	 * 変数に代入
	 * @param run          実行中フラグ
	 * @param variableName 変数名
	 * @return 終了フラグ false:終了 true:進行
	 */
	virtual bool analysisValueAssigned(const bool run, const string &variableName) = 0;
	
	/**
	 * 変数を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	virtual bool analysisVar(const bool run) = 0;
	
	/**
	 * 変数を解析 配列型
	 * @param run                実行中フラグ
	 * @param variableName       変数名
	 * @param valueVariableTypes 値タイプ
	 * @return 終了フラグ false:終了 true:進行
	 */
	virtual bool analysisVarListDict(const bool run, const string &variableName, vector<VariableType> &valueVariableTypes) = 0;
	
	/**
	 * if文を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	virtual bool analysisIf(const bool run) = 0;
	
	/**
	 * for文を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	virtual bool analysisFor(const bool run) = 0;
	
	/**
	 * 関数を解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	virtual bool analysisFunc(const bool run) = 0;
	
	/**
	 * 引数を解析
	 * @param argNames 出力引数
	 * @param run      実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	virtual bool analysisArguments(const bool run, vector<QBasicVariableEntity> &argNames) = 0;
	
	/**
	 * returnを解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	virtual bool analysisReturn(const bool run) = 0;
	
	/**
	 * endfuncを解析
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	virtual bool analysisEndfunc(const bool run) = 0;

};

#endif /* QBasicBase_h */
