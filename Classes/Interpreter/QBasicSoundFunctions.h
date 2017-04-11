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
	static string loadbgm_qb(QBasic *interpreter, const vector<string> arg);
	/// BGM再生
	static string playbgm_qb(QBasic *interpreter, const vector<string> arg);
	/// BGM停止
	static string stopbgm_qb(QBasic *interpreter, const vector<string> arg);
	/// 効果音読み込み
	static string loadse_qb(QBasic *interpreter, const vector<string> arg);
	/// 効果音再生
	static string playse_qb(QBasic *interpreter, const vector<string> arg);
	/// 効果音停止
	static string stopse_qb(QBasic *interpreter, const vector<string> arg);
	
};

#endif /* QBasicSoundFunctions_h */
