//
//  QBInterpreterSoundFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#ifndef QBInterpreterSoundFunctions_h
#define QBInterpreterSoundFunctions_h

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/// スクリプト サウンドサブ関数群
class QBInterpreterSoundFunctions final {
public:
	
	/**
	 *  ステートメントを作成
	 *
	 *  @return 文字操作ステートメント
	 */
	static unordered_map<string, QBInterpreterStatementEntity> buildStatements();
	
	/**
	 *  スクリプト用ステートメント
	 *  @param interpreter 親クラス
	 *  @param arg         引数
	 *  @return 戻り値
	 */
	/// BGM読み込み
	static string loadbgm_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// BGM再生
	static string playbgm_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// BGM停止
	static string stopbgm_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 効果音読み込み
	static string loadse_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 効果音再生
	static string playse_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 効果音停止
	static string stopse_qb(QBInterpreter *interpreter, const vector<string> arg);
	
};

#endif /* QBInterpreterSoundFunctions_h */
