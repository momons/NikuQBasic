//
//  QBUserDefaultsManager.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/05/30.
//
//

#ifndef __NikuQBasic__QBUserDefaultsManager__
#define __NikuQBasic__QBUserDefaultsManager__

#include "cocos2d.h"
#include <string>
#include <map>

class QBPlistManager;

using namespace std;
USING_NS_CC;

/**
 *  UserDefaultsマネージャ
 */
class QBUserDefaultsManager final {
public:
	
	/**
	 *  コンストラクタ
	 *  @param projectId プロジェクトId
	 */
	QBUserDefaultsManager(string projectId);
	
	/**
	 *  デストラクタ
	 */
	~QBUserDefaultsManager();
	
	/**
	 *  読込
	 *  @param key キー
	 *  @return 文字列
	 */
	string read(string key);
	
	/**
	 *  書込
	 *  @param key   キー
	 *  @param value 値
	 */
	void write(string key, string value);
	
	/**
	 *  全てを書込
	 */
	void writeAll();

private:
	
	/** ファイルパス */
	string filePath;
	
	/** セーブデータ */
	map<string, string> data;
	
	/** plistマネージャ */
	QBPlistManager *plistManager;
	
};

#endif /* defined(__NikuQBasic__QBUserDefaultsManager__) */
