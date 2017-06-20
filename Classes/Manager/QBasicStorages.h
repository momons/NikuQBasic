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
	 *  キーの存在チェック
	 *  @param key キー
	 *  @return キーあり/キーなし
	 */
	QBasicVariableEntity hasKey(const string &key);

	/**
	 *  読込
	 *  @param key キー
	 *  @return 変数Entity
	 */
	QBasicVariableEntity read(const string &key);

	/**
	 *  書込
	 *  @param key   キー
	 *  @param value 変数Entity
	 */
	void write(const string &key, QBasicVariableEntity &value);

	/**
	 *  削除
	 *  @param key   キー
	 */
	void remove(const string &key);
	
	/**
	 *  全て削除
	 */
	void removeAll();

private:
	
	/// ファイルパス
	string filePath;
	
	/// plistマネージャ
	QBasicPlists *plistManager;
	
};

#endif /* defined(__NikuQBasic__QBasicStorages__) */
