//
//  QBasicMessages.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/28.
//
//

#ifndef QBasicMessages_h
#define QBasicMessages_h

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

/// インタプリタ メッセージ関連クラス
class QBasicMessages final {
public:
	
	/**
	 * インスタンスシェア
	 * @return インスタンス
	 */
	static QBasicMessages *sharedInstance();
	
	/**
	 * デストラクタ
	 */
	~QBasicMessages();
	
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
	static QBasicMessages *interpreterMessagesInstance;
	
	/**
	 * 初期化
	 */
	static void initialize();
	
	/**
	 * コンストラクタ
	 */
	QBasicMessages() {}
	
	/**
	 * メッセージ一覧作成
	 */
	void build();
};

#endif /* QBasicMessages_h */
