//
//  QBasicSoundFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#ifndef QBasicSoundFunctions_h
#define QBasicSoundFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト サウンドサブ関数群
class QBasicSoundFunctions final {
public:
	
	/**
	 *  ステートメントを作成
	 *
	 *  @return 文字操作ステートメント
	 */
	static unordered_map<string, QBasicStatementEntity> buildStatements();
	
	/**
	 *  スクリプト用ステートメント
	 *  @param interpreter 親クラス
	 *  @param arg         引数
	 *  @return 戻り値
	 */
	/// BGM読み込み
	static QBasicVariableEntity *loadbgm_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// BGM再生
	static QBasicVariableEntity *playbgm_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// BGM停止
	static QBasicVariableEntity *stopbgm_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 効果音読み込み
	static QBasicVariableEntity *loadse_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 効果音再生
	static QBasicVariableEntity *playse_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 効果音停止
	static QBasicVariableEntity *stopse_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	
};

#endif /* QBasicSoundFunctions_h */
