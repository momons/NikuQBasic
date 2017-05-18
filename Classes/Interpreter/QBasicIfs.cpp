//
//  QBasicIfs.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/12.
//
//

#include "QBasicIfs.h"

#include "QBasicIfEntity.h"

/**
 * For追加
 * @param key         最初の開始オフセット
 * @param startOffset 開始オフセット
 * @param endOffset   終了オフセット
 */
void QBasicIfs::add(const int key, const int startOffset, const int endOffset) {
	QBasicIfEntity entity;
	entity.startOffset = startOffset;
	entity.endOffset = endOffset;
	// 現在のものを取得
	if (ifs.find(key) == ifs.end()) {
		ifs[key] = vector<QBasicIfEntity> { entity };
	} else {
		ifs[key].push_back(entity);
	}
}

/**
 * For取得
 * @param startOffset 開始オフセット
 * @return For情報
 */
vector<QBasicIfEntity> *QBasicIfs::operator [] (const int startOffset) {
	if (ifs.find(startOffset) == ifs.end()) {
		return nullptr;
	}
	return &ifs[startOffset];
}

/**
 * for情報をクリア
 */
void QBasicIfs::clear() {
	ifs.clear();
}

/**
 * コンストラクタ
 */
QBasicIfs::QBasicIfs() {
	
}

/**
 * デストラクタ
 */
QBasicIfs::~QBasicIfs() {
	
}

