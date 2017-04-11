//
//  QBasicNetFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/18.
//
//

#ifndef QBasicNetFunctions_h
#define QBasicNetFunctions_h

#include <stdio.h>
#include "QBNetFetcher.h"

using namespace std;

class QBasic;
class QBasicStatementEntity;

/// スクリプト 通信操作サブ関数群
class QBasicNetFunctions final: public QBNetFetcherDelegate {
public:

	/// 通信中フラグ
	bool isConnect = false;
	
	/**
	 *  ステートメントを作成
	 *
	 *  @return 文字操作ステートメント
	 */
	static unordered_map<string, QBasicStatementEntity> buildStatements();
	
	/**
	 *  スクリプト用ステートメント
	 *  @param interpreter 親クラス
	 *  @param arg         引数 (0: URL文字列)
	 *  @return 戻り値 (通信結果)
	 */
	/// ネット通信
	static string net_qb(QBasic *interpreter, const vector<string> arg);
	/// ブラウザ
	static string browser_qb(QBasic *interpreter, const vector<string> arg);

	/**
	 *  HTTPスタート
	 *  @param url         URL
	 *  @param retNetValue 返却変数ポインタ
	 */
	void startNetFetcher(const string url, string *retNetValue);
	
	/**
	 *  通信成功
	 *  @param responseData レスポンスデータ
	 */
	void successNetFetcher(const string responseData);
	
	/**
	 *  通信失敗
	 */
	void failureNetFetcher();

	/**
	 *  コンストラクタ
	 */
	QBasicNetFunctions() { }
	
	/**
	 * デストラクタ
	 */
	~QBasicNetFunctions() { }

private:
	
	/// ネット通信用
	QBNetFetcher *netFetcher = nullptr;
	
	/// ネット通信返却用ポインタ
	string *retNetValue = nullptr;
};

#endif /* QBasicNetFunctions_h */
