//
//  QBasicVariableEntity.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/12.
//
//

#include "QBasicVariableEntity.h"

#include "QBasicValidation.h"

#define MISMATCH_VARIABLE_TYPE_VALUE -9999;

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

	// タイプ判定
	if (QBasicValidation::isInt(value)) {
		this->type = VariableType::Int;
		this->intValue = atoi(value.c_str());
		return;
	}
	if (QBasicValidation::isFloat(value)) {
		this->type = VariableType::Float;
		this->intValue = atof(value.c_str());
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
int QBasicVariableEntity::compare(const float floatValue) {
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

#pragma mark - 判定
