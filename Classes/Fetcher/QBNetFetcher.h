//
//  QBNetFetcher.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/06/01.
//
//

#ifndef __NikuQBasic__QBNetFetcher__
#define __NikuQBasic__QBNetFetcher__

#include <string>
#include "cocos2d.h"
#include "picojson.h"
#include "network/HttpClient.h"

using namespace std;
USING_NS_CC;

/**
 *  通信デリゲート
 */
class QBNetFetcherDelegate {
public:
	
	/**
	 *  通信成功
	 *  @param responseData レスポンスデータ
	 */
	virtual void successNetFetcher(string responseData) = 0;
	
	/**
	 *  通信失敗
	 */
	virtual void failureNetFetcher() = 0;
};

/**
 *  通信フェッチャクラス
 */
class QBNetFetcher final {
public:
	
	/**
	 *  通信開始
	 *  @param url      URL
	 *  @param delegate デリゲート
	 */
	void startRequest(string url, QBNetFetcherDelegate* delegate);

private:

	/** URL */
	string url;

	/** デリゲート */
	QBNetFetcherDelegate *delegate;

};

#endif /* defined(__NikuQBasic__QBNetFetcher__) */
