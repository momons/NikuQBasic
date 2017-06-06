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
	~QBasicBase() {}

protected:
	
	/// 大元クラス
	QBasic *interpreter;
	/// プッシュバック用
	string pushBacked;

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
	 * 戻り値なし実行
	 * @param run 実行中フラグ
	 * @return 終了フラグ false:終了 true:進行
	 */
	virtual bool statement(const bool run) = 0;

};

#endif /* QBasicBase_h */
