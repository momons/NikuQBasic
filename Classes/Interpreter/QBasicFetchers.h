//
//  QBasicFetchers.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/06/01.
//
//

#ifndef __NikuQBasic__QBasicFetchers__
#define __NikuQBasic__QBasicFetchers__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "QBasicVariableEntity.h"

using namespace std;
USING_NS_CC;

class QBasicFetchers;

/// ボディデータエンコードタイプ
enum class BodyEncodeType {
	/// JSON
	JSON,
	/// クエリ
	Quary
};

/**
 *  通信デリゲート
 */
class QBasicFetchersDelegate {
public:
	
	/**
	 *  通信成功
	 *  @param responseData レスポンスデータ
	 */
	virtual void successNetFetcher(string responseData) = 0;
	
	/**
	 *  通信失敗
	 *  @param fetcher 対象フェッチャー
	 *  @param status  HTTPステータス
	 *  @param message メッセージ
	 */
	virtual void failure(const QBasicFetchers *fetcher, const long status, const string &message) = 0;
};

/**
 *  通信フェッチャクラス
 */
class QBasicFetchers final {
public:
	
	/**
	 *  コンストラクタ
	 */
	QBasicFetchers();
	
	/**
	 *  デストラクタ
	 */
	~QBasicFetchers();
	
	/**
	 *  通信開始
	 *  @param url      URL
	 *  @param delegate デリゲート
	 */
	void startRequest(string url, QBasicFetchersDelegate* delegate);
	
	/**
	 *  メソッド指定
	 *  @param method   メソッド
	 */
	void setMethodString(const string &method);
	
	/**
	 *  ボディ指定
	 *  @param value          値
	 *  @param bodyEncodeType エンコードタイプ
	 */
	void setBody(const QBasicVariableEntity &body, const BodyEncodeType bodyEncodeType);
	
private:

	/// URL
	string url;
	
	/// リクエスト
	network::HttpRequest *request;
	/// メソッド
	network::HttpRequest::Type method;
	/// ボディデータ
	QBasicVariableEntity body;
	/// ボディエンコードタイプ
	BodyEncodeType bodyEncodeType;

	/// デリゲート
	QBasicFetchersDelegate *delegate;

};

#endif /* defined(__NikuQBasic__QBasicFetchers__) */
