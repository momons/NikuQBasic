//
//  QBasicNetFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/18.
//
//

#ifndef QBasicNetFunctions_h
#define QBasicNetFunctions_h

#include "QBasicFetchers.h"

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト 通信操作サブ関数群
class QBasicNetFunctions final: public QBasicFetchersDelegate {
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
	static QBasicVariableEntity *net_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ブラウザ
	static QBasicVariableEntity *browser_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);

	/**
	 *  HTTPスタート
	 *  @param url         URL
	 *  @param retNetValue 返却変数ポインタ
	 */
	void startNetFetcher(const string &url, string *retNetValue);
	
	/**
	 *  通信成功
	 *  @param responseData レスポンスデータ
	 */
	void successNetFetcher(const string responseData) override;
	
	/**
	 *  通信失敗
	 *  @param fetcher 対象フェッチャー
	 *  @param status  HTTPステータス
	 *  @param message メッセージ
	 */
	void failure(const QBasicFetchers *fetcher, const long status, const string &message) override;

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
	QBasicFetchers *fetcher = nullptr;
	
	/// ネット通信返却用ポインタ
	string *retNetValue = nullptr;
};

#endif /* QBasicNetFunctions_h */
