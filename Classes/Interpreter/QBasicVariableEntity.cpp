//
//  QBasicVariableEntity.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/12.
//
//

#include "QBasicVariableEntity.h"

#include "QBasicValidation.h"
#include "StringUtil.h"

#define MISMATCH_VARIABLE_TYPE_VALUE -9999;
/**
 * コンストラクタ
 */
QBasicVariableEntity::QBasicVariableEntity() {
	
}

/**
 * コンストラクタ
 * @param name  変数名
 * @param type  変数タイプ
 * @param value 値のポインタ
 */
QBasicVariableEntity::QBasicVariableEntity(const string &name, const VariableType type, const void *value) {
	// 退避
	this->name = name;
	this->type = type;
	if (value != nullptr) {
		switch (this->type) {
			case VariableType::Int:
				intValue = *(int *)value;
				break;
			case VariableType::Float:
				floatValue = *(float *)value;
				break;
			case VariableType::Str:
				strValue = string((char *)value);
				break;
			case VariableType::Bool:
				boolValue = *(bool *)value;
				break;
			case VariableType::List:
				// まだ未対応
				break;
			case VariableType::Dict:
				// まだ未対応
				break;
			default:
				break;
		}
	}
}

/**
 * コンストラクタ
 * @param name  変数名
 * @param value 値の文字列
 */
QBasicVariableEntity::QBasicVariableEntity(const string &name, const string &value) {
	// 退避
	this->name = name;
	type = VariableType::Unknown;

	// タイプ判定
	if (QBasicValidation::isInt(value)) {
		this->type = VariableType::Int;
		this->intValue = atoi(value.c_str());
		return;
	}
	if (QBasicValidation::isFloat(value)) {
		this->type = VariableType::Float;
		this->floatValue = atof(value.c_str());
		return;
	}
	if (QBasicValidation::isStr(value)) {
		this->type = VariableType::Str;
		this->strValue = value.substr(1, value.length() - 2);
		return;
	}
	if (QBasicValidation::isBool(value)) {
		this->type = VariableType::Bool;
		this->boolValue = value.compare("true") == 0;
		return;
	}
}

/**
 * デストラクタ
 */
QBasicVariableEntity::~QBasicVariableEntity() {
	
}

#pragma mark - 比較

/**
 * entityと比較
 * @param entity 変数entity
 * @return 比較結果
 */
int QBasicVariableEntity::compare(const QBasicVariableEntity &entity) {
	if (type != entity.type) {
		return MISMATCH_VARIABLE_TYPE_VALUE;
	}
	switch (type) {
		case VariableType::Int:
			if (intValue < entity.intValue) {
				return -1;
			}
			if (intValue > entity.intValue) {
				return 1;
			}
			return 0;
		case VariableType::Float:
			if (floatValue < entity.floatValue) {
				return -1;
			}
			if (floatValue > entity.floatValue) {
				return 1;
			}
			return 0;
		case VariableType::Str:
			return strValue.compare(entity.strValue);
		case VariableType::Bool:
			if (!boolValue && entity.boolValue) {
				return -1;
			}
			if (boolValue && !entity.boolValue) {
				return 1;
			}
			return 0;
		default:
			return 0;
	}
}

/**
 * intと比較
 * @param intValue int値
 * @return 比較結果
 */
int QBasicVariableEntity::compare(const int intValue) {
	if (type != VariableType::Int) {
		return MISMATCH_VARIABLE_TYPE_VALUE;
	}
	if (this->intValue < intValue) {
		return -1;
	}
	if (this->intValue > intValue) {
		return 1;
	}
	return 0;
}

/**
 * floatと比較
 * @param floatValue float値
 * @return 比較結果
 */
int QBasicVariableEntity::compare(const double floatValue) {
	if (type != VariableType::Float) {
		return MISMATCH_VARIABLE_TYPE_VALUE;
	}
	if (this->floatValue < floatValue) {
		return -1;
	}
	if (this->floatValue > floatValue) {
		return 1;
	}
	return 0;
}

/**
 * stringと比較
 * @param strValue string値
 * @return 比較結果
 */
int QBasicVariableEntity::compare(const string strValue) {
	if (type != VariableType::Str) {
		return MISMATCH_VARIABLE_TYPE_VALUE;
	}
	return this->strValue.compare(strValue);
}

/**
 * boolと比較
 * @param boolValue bool値
 * @return 比較結果
 */
int QBasicVariableEntity::compare(const bool boolValue) {
	if (type != VariableType::Bool) {
		return MISMATCH_VARIABLE_TYPE_VALUE;
	}
	if (!this->boolValue && boolValue) {
		return -1;
	}
	if (this->boolValue && !boolValue) {
		return 1;
	}
	return 0;
}

#pragma mark - 四則演算

/**
 * 足し算
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::add(const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	switch (type) {
		case VariableType::Int:
			returnEntity.intValue = intValue + entity.intValue;
			break;
		case VariableType::Float:
			returnEntity.floatValue = floatValue + entity.floatValue;
			break;
		case VariableType::Str:
			returnEntity.strValue = strValue + entity.strValue;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

/**
 * 引き算
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::sub(const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	switch (type) {
		case VariableType::Int:
			returnEntity.intValue = intValue - entity.intValue;
			break;
		case VariableType::Float:
			returnEntity.floatValue = floatValue - entity.floatValue;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

/**
 * 掛け算
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::mul(const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	switch (type) {
		case VariableType::Int:
			returnEntity.intValue = intValue * entity.intValue;
			break;
		case VariableType::Float:
			returnEntity.floatValue = floatValue * entity.floatValue;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

/**
 * 掛け算 数値
 * @param type  変数タイプ
 * @param value 値
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::mul(VariableType type, double value) {
	QBasicVariableEntity returnEntity = copyNotValue();
	switch (type) {
		case VariableType::Int:
			returnEntity.intValue = intValue * (int)value;
			break;
		case VariableType::Float:
			returnEntity.floatValue = floatValue * value;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

/**
 * 割り算
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::div(const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	switch (type) {
		case VariableType::Int:
			returnEntity.intValue = intValue / entity.intValue;
			break;
		case VariableType::Float:
			returnEntity.floatValue = floatValue / entity.floatValue;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

/**
 * 余り
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::mod(const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	switch (type) {
		case VariableType::Int:
			returnEntity.intValue = intValue % entity.intValue;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

#pragma mark - 論理演算

/**
 * And論理演算
 * @param entity 変数entity
 * @return 比較結果
 */
QBasicVariableEntity QBasicVariableEntity::expressionAnd(const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	switch (type) {
		case VariableType::Bool:
			returnEntity.boolValue = boolValue & entity.boolValue;
			break;
		case VariableType::Int:
			returnEntity.intValue = intValue & entity.intValue;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

/**
 * OR論理演算
 * @param entity 変数entity
 * @return 比較結果
 */
QBasicVariableEntity QBasicVariableEntity::expressionOr(const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	switch (type) {
		case VariableType::Bool:
			returnEntity.boolValue = boolValue | entity.boolValue;
			break;
		case VariableType::Int:
			returnEntity.intValue = intValue | entity.intValue;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

/**
 * XOR論理演算
 * @param entity 変数entity
 * @return 比較結果
 */
QBasicVariableEntity QBasicVariableEntity::expressionXor(const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	switch (type) {
		case VariableType::Bool:
			returnEntity.boolValue = boolValue ^ entity.boolValue;
			break;
		case VariableType::Int:
			returnEntity.intValue = intValue ^ entity.intValue;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

/**
 * NOT論理演算
 * @param entity 変数entity
 * @return 比較結果
 */
QBasicVariableEntity QBasicVariableEntity::expressionNot() {
	QBasicVariableEntity returnEntity = copyNotValue();
	switch (type) {
		case VariableType::Bool:
			returnEntity.boolValue = !boolValue;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

#pragma mark - 変換

/**
 * Intへ変換
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::toInt() {
	QBasicVariableEntity returnEntity;
	switch (type) {
		case VariableType::Float:
			returnEntity.intValue = !boolValue;
			break;
		case VariableType::Str:
			returnEntity.intValue = atoi(strValue.c_str());
			break;
		case VariableType::Bool:
			returnEntity.intValue = boolValue ? 1 : 0;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	returnEntity.type = VariableType::Int;
	return returnEntity;
}

/**
 * Floatへ変換
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::toFloat() {
	QBasicVariableEntity returnEntity;
	switch (type) {
		case VariableType::Int:
			returnEntity.floatValue = (double)intValue;
			break;
		case VariableType::Str:
			returnEntity.floatValue = atof(strValue.c_str());
			break;
		case VariableType::Bool:
			returnEntity.floatValue = boolValue ? 1 : 0;
			break;
		default:
			break;
	}
	returnEntity.type = VariableType::Float;
	return returnEntity;
}

/**
 * Strへ変換
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::toStr() {
	QBasicVariableEntity returnEntity;
	switch (type) {
		case VariableType::Int:
			returnEntity.strValue = StringUtil::toString((double)intValue);
			break;
		case VariableType::Float:
			returnEntity.strValue = StringUtil::toString(floatValue);
			break;
		case VariableType::Bool:
			returnEntity.strValue = boolValue ? "true" : "false";
			break;
		default:
			break;
	}
	returnEntity.type = VariableType::Str;
	return returnEntity;
}

/**
 * Boolへ変換
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::toBool() {
	QBasicVariableEntity returnEntity;
	switch (type) {
		case VariableType::Int:
			returnEntity.boolValue = intValue != 0;
			break;
		case VariableType::Str:
			returnEntity.boolValue = strValue.compare("true") == 0;
			break;
		case VariableType::Float:
			returnEntity.boolValue = floatValue != 0;
			break;
		default:
			break;
	}
	returnEntity.type = VariableType::Bool;
	return returnEntity;
}

#pragma mark - その他

/**
 * 値なしコピー
 * @return コピーEntity
 */
QBasicVariableEntity QBasicVariableEntity::copyNotValue() {
	QBasicVariableEntity returnEntity;
	returnEntity.name = name;
	returnEntity.type = type;
	return returnEntity;
}




