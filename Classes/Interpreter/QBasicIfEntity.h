//
//  QBasicIfEntity.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/12.
//
//

#ifndef QBasicIfEntity_h
#define QBasicIfEntity_h

using namespace std;

/**
 * If制御用Entity
 */
class QBasicIfEntity final {
	
public:
	
	/// 開始オフセット
	int startOffset = 0;
	
	/// 終了オフセット
	int endOffset = 0;
	
	/**
	 * コンストラクタ
	 */
	QBasicIfEntity();
	
	/**
	 * デストラクタ
	 */
	~QBasicIfEntity();
	
};

#endif /* QBasicIfEntity_h */
