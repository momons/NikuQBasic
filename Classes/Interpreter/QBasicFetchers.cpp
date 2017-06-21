//
//  QBasicFetchers.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/06/01.
//
//

#include "QBasicFetchers.h"

#include "picojson.h"

/**
 *  コンストラクタ
 */
QBasicFetchers::QBasicFetchers() {
	request = new network::HttpRequest();
	method = network::HttpRequest::Type::GET;
}

/**
 *  デストラクタ
 */
QBasicFetchers::~QBasicFetchers() {
	delete request;
}

/**
 *  通信開始
 *  @param url      URL
 *  @param delegate デリゲート
 */
void QBasicFetchers::startRequest(string url, QBasicFetchersDelegate* delegate) {

	// 退避
	this->url = url;
	this->delegate = delegate;
	
	// 通信設定
	request->setUrl(url.c_str());
	request->setRequestType(method);
	request->setResponseCallback([this](network::HttpClient* client, network::HttpResponse* response) {
		
		// エラー
		if(!response->isSucceed() ||
		   response->getResponseCode() != 200){
			// 変換エラー
			this->delegate->failure(this, response->getResponseCode(), response->getErrorBuffer());
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

/**
 *  メソッド指定
 *  @param method   メソッド
 */
void QBasicFetchers::setMethodString(const string &method) {
	if (method == "GET") {
		this->method = network::HttpRequest::Type::GET;
	} else if (method == "POST") {
		this->method = network::HttpRequest::Type::POST;
	} else if (method == "PUT") {
		this->method = network::HttpRequest::Type::PUT;
	} else if (method == "DELETE") {
		this->method = network::HttpRequest::Type::DELETE;
	} else {
		// フォールバックはGET
		this->method = network::HttpRequest::Type::GET;
	}
}

/**
 *  ボディ指定
 *  @param value          値
 *  @param bodyEncodeType エンコードタイプ
 */
void QBasicFetchers::setBody(const QBasicVariableEntity &body, const BodyEncodeType bodyEncodeType) {
	
	// 退避
	this->body = body;
	this->bodyEncodeType = bodyEncodeType;
	
	
}


