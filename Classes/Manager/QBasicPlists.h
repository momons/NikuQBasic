//
//  QBasicPlists.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/07/07.
//
//

#ifndef __NikuQBasic__QBasicPlists__
#define __NikuQBasic__QBasicPlists__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

/**
 *  plistを扱うクラス
 */
class QBasicPlists final {
public:
	
	/**
	 *  コンストラクタ
	 *  @param filePath ファイルパス
	 */
	QBasicPlists(const string &filePath);
	
	/**
	 *  デストラクタ
	 */
	~QBasicPlists();
	
	/**
	 *  読込
	 */
	void read();
	
	/**
	 *  書込
	 */
	void write();
		
	/**
	 *  値を取得
	 *  @param key キー
	 *  @return 値
	 */
	string getValue(const string &key);
	
	/**
	 *  値を設定
	 *  @param key   キー
	 *  @param value 値
	 */
	void setValue(const string &key, const string &value);

	/**
	 *  値を削除
	 *  @param key   キー
	 */
	void clearValue(const string &key);

	/**
	 *  全て削除
	 */
	void clearAll();

private:
	
	/// ファイルパス
	string filePath;

	/// データ
	ValueMap data;
};

#endif /* defined(__NikuQBasic__QBasicPlists__) */
