//
//  QBasicFors.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/12.
//
//

#include "QBasicFors.h"

#include "QBasicForEntity.h"

/**
 * For追加
 * @param startOffset 開始オフセット
 * @param endOffset   終了オフセット
 * @return For情報
 */
QBasicForEntity *QBasicFors::addUpdate(const int startOffset, const int endOffset) {
	QBasicForEntity entity;
	entity.startOffset = startOffset;
	entity.endOffset = endOffset;
	fors[startOffset] = entity;
	return &fors[startOffset];
}

/**
 * For取得
 * @param startOffset 開始オフセット
 * @return For情報
 */
QBasicForEntity *QBasicFors::getFor(const int startOffset) {
	if (fors.find(startOffset) == fors.end()) {
		return nullptr;
	}
	return &fors[startOffset];
}

/**
 * for情報をクリア
 */
void QBasicFors::clear() {
	fors.clear();
}

/**
 * コンストラクタ
 */
QBasicFors::QBasicFors() {
	
}

/**
 * デストラクタ
 */
QBasicFors::~QBasicFors() {
	
}

