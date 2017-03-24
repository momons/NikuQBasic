//
//  QBPlistManager.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/07/07.
//
//

#ifndef __NikuQBasic__QBPlistManager__
#define __NikuQBasic__QBPlistManager__

#include "cocos2d.h"
#include <string>
#include <map>

using namespace std;
USING_NS_CC;

/**
 *  スクリプトインフォマネージャ
 */
class QBPlistManager {
public:
	
	/**
	 *  コンストラクタ
	 *  @param filePath ファイルパス
	 */
	QBPlistManager(string filePath);
	
	/**
	 *  デストラクタ
	 */
	~QBPlistManager();
	
	/**
	 *  読込
	 *  @param filePath ファイルパス
	 */
	void read(string filePath);
	
	/**
	 *  書込
	 *  @param filePath ファイルパス
	 */
	void write(string filePath);
		
	/**
	 *  値を取得
	 *  @param key キー
	 *  @return 値
	 */
	string getValue(string key);
	
	/**
	 *  値を設定
	 *  @param key   キー
	 *  @param value 値
	 */
	void setValue(string key, string value);
	
private:
	
	/** ファイルパス */
	string filePath;

	/** データ */
	ValueMap data;
	
};

#endif /* defined(__NikuQBasic__QBPlistManager__) */
