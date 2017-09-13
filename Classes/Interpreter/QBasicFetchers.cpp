//
//  QBasicFetchers.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/06/01.
//
//

#include "QBasicFetchers.h"

#include "picojson.h"
#include "QBasicQueries.h"
#include "QBasicJsons.h"

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
	if (bodyData.size() > 0) {
		request->setRequestData(bodyData.data(), bodyData.size());
	}
	// ヘッダ設定
	vector<string> headers = this->headers;
	switch (bodyEncodeType) {
		case BodyEncodeType::JSON:
			headers.push_back("Content-Type: application/json; charset=UTF-8");
			break;
		default:
			headers.push_back("Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
			break;
	}
	request->setHeaders(headers);
	request->setResponseCallback([this](network::HttpClient* client, network::HttpResponse* response) {
		
		// エラー
		if(!response->isSucceed()) {
			this->delegate->failure(this, 0L, QBasicFetchersErrorType::ConnectFailure);
			return;
		}
		
		// レスポンス取得
		vector<char> *buff = response->getResponseData();
		string responseString = string(buff->begin(), buff->end());
		
		// JSON変換のみ
		picojson::value jsonValue;
		string error;
		QBasicJsons::toObject(jsonValue, &error, responseString);
		
		if (error.length() > 0) {
			// 変換エラー
			this->delegate->failure(this, response->getResponseCode(), QBasicFetchersErrorType::JSONError);
			return;
		}
		
		QBasicVariableEntity responseEntity;
		if (jsonValue.is<picojson::array>()) {
			responseEntity = QBasicVariableEntity::buildForJsonArray(jsonValue.get<picojson::array>());
		} else if (jsonValue.is<picojson::object>()) {
			responseEntity = QBasicVariableEntity::buildForJsonObject(jsonValue.get<picojson::object>());
		}
		
		// 成功
		this->delegate->success(this, response->getResponseCode(), responseEntity);
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
 *  @param body           値
 *  @param bodyEncodeType エンコードタイプ
 */
void QBasicFetchers::setBody(QBasicVariableEntity &body, const BodyEncodeType bodyEncodeType) {
	
	// 退避
	this->body = body;
	this->bodyEncodeType = bodyEncodeType;
	
	string bodyString;
	switch(bodyEncodeType) {
		case BodyEncodeType::JSON:
			bodyString = body.toJsonString();
			break;
		case BodyEncodeType::Quary:
			bodyString = QBasicQueries::toQueryString(body);
			break;
		case BodyEncodeType::Binary:
			// TODO:まぁそのうち
			break;
	}
	
	bodyData = vector<char>(bodyString.begin(), bodyString.end());
}

/**
 *  ヘッダ指定
 *  @param headers ヘッダ
 */
void QBasicFetchers::setHeaders(QBasicVariableEntity &value) {
	// Dict以外は無視
	if (value.types[0] != VariableType::Dict) {
		return;
	}

	headers.clear();
	// 日本語のエンコードは...まいっか
	for (auto it = value.dictValue.begin();it != value.dictValue.end();it++) {
		ostringstream oss;
		oss << it->first << ": " << it->second.toStr().strValue;
		headers.push_back(oss.str());
	}
}


