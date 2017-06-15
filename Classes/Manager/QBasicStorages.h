//
//  QBasicStorages.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/05/30.
//
//

#ifndef __NikuQBasic__QBasicStorages__
#define __NikuQBasic__QBasicStorages__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class QBasicPlists;
class QBasicVariableEntity;

/**
 *  データストレージを扱うクラス
 */
class QBasicStorages final {
public:
	
	/**
	 *  コンストラクタ
	 *  @param projectId プロジェクトId
	 */
	QBasicStorages(const string &projectId);
	
	/**
	 *  デストラクタ
	 */
	~QBasicStorages();
	
	/**
	 *  読込
	 *  @param key キー
	 *  @return 文字列
	 */
	string read(const string &key);
	
	/**
	 *  書込
	 *  @param key   キー
	 *  @param value 値
	 */
	void write(const string &key, const string &value);

	/**
	 *  書込
	 *  @param key   キー
	 *  @param value 値
	 */
	void write(const string &key, const QBasicVariableEntity &value);

	/**
	 *  全てを書込
	 */
	void writeAll();

private:
	
	/// ファイルパス
	string filePath;
	
	/// セーブデータ
	map<string, string> data;
	
	/// plistマネージャ
	QBasicPlists *plistManager;
	
};

#endif /* defined(__NikuQBasic__QBasicStorages__) */
