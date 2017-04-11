//
//  QBasicParticleFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#ifndef QBasicParticleFunctions_h
#define QBasicParticleFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;

/// スクリプト パーティクルサブ関数群
class QBasicParticleFunctions final {
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
	/// パーティクル読み込み
	static string loadparticle_qb(QBasic *interpreter, const vector<string> arg);
	/// パーティクル描画
	static string drawparticle_qb(QBasic *interpreter, const vector<string> arg);
};

#endif /* QBasicParticleFunctions_h */
