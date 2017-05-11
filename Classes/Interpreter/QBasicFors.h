//
//  QBasicFors.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/12.
//
//

#ifndef QBasicFors_h
#define QBasicFors_h

using namespace std;

class QBasicForEntity;

/**
 * For制御クラス
 */
class QBasicFors final {
public:

	/**
	 * For追加
	 * @param startOffset 開始オフセット
	 * @param endOffset   終了オフセット
	 * @return For情報
	 */
	QBasicForEntity *addUpdate(int startOffset, int endOffset);
	
	/**
	 * For取得
	 * @param startOffset 開始オフセット
	 * @return For情報
	 */
	QBasicForEntity *getFor(int startOffset);
	
	/**
	 * for情報をクリア
	 */
	void clear();
	
	/**
	 * コンストラクタ
	 */
	QBasicFors();
	
	/**
	 * デストラクタ
	 */
	~QBasicFors();
	
private:
	
	/// キー = 開始オフセット
	unordered_map<int, QBasicForEntity> fors;
	
};


#endif /* QBasicFors_h */
