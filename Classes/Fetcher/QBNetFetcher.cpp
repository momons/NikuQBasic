//
//  QBNetFetcher.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/06/01.
//
//

#include "QBNetFetcher.h"

/**
 *  通信開始
 *  @param url      URL
 *  @param delegate デリゲート
 */
void QBNetFetcher::startRequest(string url, QBNetFetcherDelegate* delegate) {

	// 退避
	this->url = url;
	this->delegate = delegate;
	
	// 通信設定
	auto request = new network::HttpRequest();
	request->setUrl(url.c_str());
	request->setRequestType(network::HttpRequest::Type::GET);
	request->setResponseCallback([this](network::HttpClient* client, network::HttpResponse* response) {
		
		// エラー
		if(!response->isSucceed() || response->getResponseCode() != 200){
			// 変換エラー
			this->delegate->failureNetFetcher();
			return;
		}
		
		// レスポンス取得
		vector<char> *buff = response->getResponseData();
		
		// デリゲートコール
		this->delegate->successNetFetcher(string(buff->begin(), buff->end()));
	});
	
	// 通信開始
	network::HttpClient::getInstance()->send(request);
}

