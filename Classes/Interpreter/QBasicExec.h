//
//  QBasicExec.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/07.
//
//

#ifndef QBasicExec_h
#define QBasicExec_h

#include "QBasicBase.h"

/// インタプリタメイン 実行用
class QBasicExec final: public QBasicBase {
public:
	
	/**
	 * コンストラクタ
	 * @param interpreter　メイン
	 */
	QBasicExec(QBasic *interpreter);
	
	/**
	 * デストラクタ
	 */
	~QBasicExec() {}

private:
	
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
	
	
};

#endif /* QBasicExec_h */
