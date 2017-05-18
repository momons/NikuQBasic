//
//  QBasicIfs.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/12.
//
//

#ifndef QBasicIfs_h
#define QBasicIfs_h

using namespace std;

class QBasicIfEntity;

/**
 * If制御クラス
 */
class QBasicIfs final {
public:
	
	/**
	 * if追加
	 * @param key         最初の開始オフセット
	 * @param startOffset 開始オフセット
	 * @param endOffset   終了オフセット
	 */
	void add(const int key, const int startOffset, const int endOffset);
	
	/**
	 * if取得
	 * @param startOffset 開始オフセット
	 * @return For情報
	 */
	vector<QBasicIfEntity> *operator [] (const int startOffset);
	
	/**
	 * if情報をクリア
	 */
	void clear();
	
	/**
	 * コンストラクタ
	 */
	QBasicIfs();
	
	/**
	 * デストラクタ
	 */
	~QBasicIfs();
	
private:
	
	/// キー = 開始オフセット
	unordered_map<int, vector<QBasicIfEntity>> ifs;
	
};

#endif /* QBasicIfs_h */
