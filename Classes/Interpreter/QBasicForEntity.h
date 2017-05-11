//
//  QBasicForEntity.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/12.
//
//

#ifndef QBasicForEntity_h
#define QBasicForEntity_h

using namespace std;

/**
 * For制御用Entity
 */
class QBasicForEntity final {
	
public:
	
	/// 開始オフセット
	int startOffset = 0;
	
	/// 終了オフセット (nextがある位置)
	int endOffset = 0;
	
	/**
	 * コンストラクタ
	 */
	QBasicForEntity();
	
	/**
	 * デストラクタ
	 */
	~QBasicForEntity();
	
};

#endif /* QBasicForEntity_h */
