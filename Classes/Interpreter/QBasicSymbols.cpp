//
//  QBasicSymbols.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/02.
//
//

#include "QBasicSymbols.h"

#include "QBasicSymbolEntity.h"

/**
 *  コンストラクタ
 *  @param source プログラムソース
 */
QBasicSymbols::QBasicSymbols(const string &source) {
	buildSymbols(source);
}

/**
 *  デストラクタ
 */
QBasicSymbols::~QBasicSymbols() {
	
}

/**
 *  次のシンボルへ
 *  @return シンボル
 */
string QBasicSymbols::nextSymbol() {
	if (execOffset >= symbols.size()) {
		return "";
	}
	auto sym = symbols[execOffset].symbol;
	execOffset += 1;
	return sym;
}

/**
 *  一個前のシンボルを取得
 *  @return シンボル
 */
QBasicSymbolEntity *QBasicSymbols::beforeSymbolEntity() {
	int offset = execOffset;
	if (offset < 0) {
		offset = 0;
	}
	return &symbols[offset];
}

/**
 *  オフセット設定
 *  @param offset オフセット
 */
void QBasicSymbols::jumpOffset(const int offset) {
	execOffset = offset;
}

/**
 *  オフセット一つ下げる
 */
void QBasicSymbols::popBack() {
	if (execOffset > 0) {
		execOffset--;
	}
}

/**
 *  現在のオフセット取得
 *  @return 現在のオフセット
 */
int QBasicSymbols::offset() {
	return execOffset;
}


/**
 *  シンボルをビルド
 *  @param source プログラムソース
 */
void QBasicSymbols::buildSymbols(const string &source) {
	
	symbols.clear();
	this->source = source;
	execOffset = 0;
	row = 0;
	col = 0;
	
	while(true) {
		QBasicSymbolEntity entity;
		// シンボル取得
		getSymbol(entity);
		if (entity.symbol.empty()) {
			break;
		}
		symbols.push_back(entity);
	}

	// 初期化
	execOffset = 0;
}

/**
 * 単語取得
 * @param symbolEntity 単語Entity
 */
void QBasicSymbols::getSymbol(QBasicSymbolEntity &symbolEntity) {
	
	// 1文字抽出
	const char *cstr = source.c_str();
	char ch = cstr[execOffset];
	// 現在の解析行数を退避
	symbolEntity.row = row;
	symbolEntity.col = col;

	// スペースか改行があるかぎりループ
	while (isspace(ch)) {
		updateRowCol(ch);
		execOffset++;
		ch = cstr[execOffset];
		// 現在の解析行数を退避
		symbolEntity.row = row;
		symbolEntity.col = col;
	}

	// ゼロならばなし
	if(ch == 0x00) {
		return;
	}

	int execOffsetBackup = execOffset;

	// 数値が続くかぎりループ
	while (isdigit(ch) || ch == '.') {
		updateRowCol(ch);
		execOffset++;
		ch = cstr[execOffset];
	}

	// 位置が変わっていれば
	if(execOffsetBackup != execOffset) {
		symbolEntity.symbol = source.substr(execOffsetBackup,execOffset - execOffsetBackup);
		return;
	}

	// 英数字が続くかぎりループ
	while (isalnum(ch)) {
		updateRowCol(ch);
		execOffset++;
		ch = cstr[execOffset];
	}

	// 位置が変わっていれば
	if (execOffsetBackup != execOffset) {
		symbolEntity.symbol = source.substr(execOffsetBackup,execOffset - execOffsetBackup);
		return;
	}

	// ダブルクォーテーション発見
	if (ch == '"') {
		updateRowCol(ch);
		execOffset++;
		ch = cstr[execOffset];
		// 次のダブルクォーテーションを見つけるまでループ
		while (ch != '"' && ch != 0x00) {
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
		}
		execOffset++;
		
		symbolEntity.symbol = source.substr(execOffsetBackup,execOffset - execOffsetBackup);
		return;
	}

	switch(ch) {
		case '#':
			// コメント発見
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			while (ch != '\n' && ch != 0x00) {
				updateRowCol(ch);
				execOffset++;
				ch = cstr[execOffset];
			}
			updateRowCol(ch);
			execOffset++;
			break;
		case '=':
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			if(ch == '=') {
				updateRowCol(ch);
				execOffset++;
			}
			break;
		case '+':
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			if(ch == '=') {
				updateRowCol(ch);
				execOffset++;
			}
			break;
		case '-':
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			if(ch == '>' || ch == '=') {
				updateRowCol(ch);
				execOffset++;
			}
			break;
		case '*':
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			if(ch == '=') {
				updateRowCol(ch);
				execOffset++;
			}
			break;
		case '/':
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			if(ch == '=') {
				updateRowCol(ch);
				execOffset++;
			}
			break;
		case '%':
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			if(ch == '=') {
				updateRowCol(ch);
				execOffset++;
			}
			break;
		case '<':
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			if(ch == '=') {
				updateRowCol(ch);
				execOffset++;
			}
			break;
		case '>':
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			if(ch == '=') {
				updateRowCol(ch);
				execOffset++;
			}
			break;
		case '!':
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			if(ch == '=') {
				updateRowCol(ch);
				execOffset++;
			}
			break;
		case '&':
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			if(ch == '&' || ch == '=') {
				updateRowCol(ch);
				execOffset++;
			}
			break;
		case '|':
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			if(ch == '|' || ch == '=') {
				updateRowCol(ch);
				execOffset++;
			}
			break;
		case '^':
			updateRowCol(ch);
			execOffset++;
			ch = cstr[execOffset];
			if(ch == '=') {
				updateRowCol(ch);
				execOffset++;
			}
			break;
		default:
			updateRowCol(ch);
			execOffset++;
			break;
	}
	
	symbolEntity.symbol = source.substr(execOffsetBackup,execOffset - execOffsetBackup);
}

/**
 *  行項アップデート
 *  @param ch 文字
 */
void QBasicSymbols::updateRowCol(char ch) {
	if (ch == '\n') {
		row += 1;
		col = 0;
	} else {
		col += 1;
	}
}

