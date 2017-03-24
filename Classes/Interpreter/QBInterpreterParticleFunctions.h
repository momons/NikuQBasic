//
//  QBInterpreterParticleFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#ifndef QBInterpreterParticleFunctions_h
#define QBInterpreterParticleFunctions_h

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/// スクリプト パーティクルサブ関数群
class QBInterpreterParticleFunctions final {
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
	/// パーティクル読み込み
	static string loadparticle_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// パーティクル描画
	static string drawparticle_qb(QBInterpreter *interpreter, const vector<string> arg);
};

#endif /* QBInterpreterParticleFunctions_h */
