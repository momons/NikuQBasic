//
//  QBInterpreterMessages.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/28.
//
//

#ifndef QBInterpreterMessages_h
#define QBInterpreterMessages_h

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

/// インタプリタ メッセージ関連クラス
class QBInterpreterMessages final {
public:
	
	/**
	 * インスタンスシェア
	 * @return インスタンス
	 */
	static QBInterpreterMessages *sharedInstance();
	
	/**
	 * デストラクタ
	 */
	~QBInterpreterMessages();
	
	/**
	 *  メッセージ取得
	 *  @param key    キー
	 *  @param params パラメータ
	 *  @return メッセージ
	 */
	string getMessage(const string key, const char *params);
	
private:
	
	/// メッセージ一覧
	unordered_map<string, string> localizable;
	
	/// インスタンス
	static QBInterpreterMessages *interpreterMessagesInstance;
	
	/**
	 * 初期化
	 */
	static void initialize();
	
	/**
	 * コンストラクタ
	 */
	QBInterpreterMessages() {}
	
	/**
	 * メッセージ一覧作成
	 */
	void build();
};

#endif /* QBInterpreterMessages_h */
