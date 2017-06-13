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
	name = "";
	types = { VariableType::Unknown };
	intValue = 0;
	floatValue = 0;
	strValue = "";
	boolValue = false;
	listValue.clear();
	dictValue.clear();
	isNil = true;
}

/**
 * コンストラクタ
 * @param name  変数名
 * @param type  変数タイプ
 * @param value 値のポインタ
 */
QBasicVariableEntity::QBasicVariableEntity(const string &name, const vector<VariableType> &types, void *value) {
	configureEntity(name, types, value);
}

/**
 * コンストラクタ
 * @param name  変数名
 * @param value 値の文字列
 */
QBasicVariableEntity::QBasicVariableEntity(const string &name, const string &value) {
	// 退避
	this->name = name;
	types = { VariableType::Unknown };

	// タイプ判定
	if (QBasicValidation::isInt(value)) {
		types[0] = VariableType::Int;
		intValue = atoi(value.c_str());
		isNil = false;
		return;
	}
	if (QBasicValidation::isFloat(value)) {
		types[0] = VariableType::Float;
		floatValue = atof(value.c_str());
		isNil = false;
		return;
	}
	if (QBasicValidation::isStr(value)) {
		types[0] = VariableType::Str;
		strValue = value.substr(1, value.length() - 2);
		isNil = false;
		return;
	}
	if (QBasicValidation::isBool(value)) {
		types[0] = VariableType::Bool;
		boolValue = value.compare("true") == 0;
		isNil = false;
		return;
	}
}

/**
 * コンストラクタ 配列用
 * @param name   変数名
 * @param types  値変数タイプ群
 * @param values 値
 */
QBasicVariableEntity::QBasicVariableEntity(const string &name, const vector<VariableType> &types, const vector<QBasicVariableEntity> &values) {
	// 退避
	this->name = name;
	this->types = types;
	listValue = values;
	isNil = listValue.size() <= 0;
}

/**
 * コンストラクタ 連想配列用
 * @param name   変数名
 * @param types  値変数タイプ群
 * @param values 値
 */
QBasicVariableEntity::QBasicVariableEntity(const string &name, const vector<VariableType> &types, const map<string, QBasicVariableEntity> &values) {
	// 退避
	this->name = name;
	this->types = types;
	dictValue = values;
	isNil = listValue.size() <= 0;
}

/**
 * デストラクタ
 */
QBasicVariableEntity::~QBasicVariableEntity() {
	
}

/**
 * 値取得
 * @return 値
 */
void *QBasicVariableEntity::getValue() {
	if (isNil) {
		return nullptr;
	}
	switch (types[0]) {
		case VariableType::Int:
			return (void *)&intValue;
			break;
		case VariableType::Float:
			return (void *)&floatValue;
			break;
		case VariableType::Str:
			return (void *)strValue.c_str();
			break;
		case VariableType::Bool:
			return (void *)&boolValue;
			break;
		default:
			break;
	}
	return nullptr;
}


#pragma mark - 比較

/**
 * entityと比較
 * @param entity 変数entity
 * @return 比較結果
 */
int QBasicVariableEntity::compare(const QBasicVariableEntity &entity) {
	if (isNil && entity.isNil) {
		return 0;
	}
	if (isNil && !entity.isNil) {
		return 1;
	}
	if (!isNil && entity.isNil) {
		return -1;
	}
	if (types[0] != entity.types[0]) {
		return MISMATCH_VARIABLE_TYPE_VALUE;
	}
	switch (types[0]) {
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
 * ==比較
 * @param entity 変数entity
 * @return 比較結果
 */
bool QBasicVariableEntity::operator == (const QBasicVariableEntity &entity) {
	return compare(entity) == 0;
}

/**
 * !=比較
 * @param entity 変数entity
 * @return 比較結果
 */
bool QBasicVariableEntity::operator != (const QBasicVariableEntity &entity) {
	return compare(entity) != 0;
}

/**
 * >比較
 * @param entity 変数entity
 * @return 比較結果
 */
bool QBasicVariableEntity::operator > (const QBasicVariableEntity &entity) {
	return compare(entity) > 0;
}

/**
 * <比較
 * @param entity 変数entity
 * @return 比較結果
 */
bool QBasicVariableEntity::operator < (const QBasicVariableEntity &entity) {
	return compare(entity) < 0;
}

/**
 * >=比較
 * @param entity 変数entity
 * @return 比較結果
 */
bool QBasicVariableEntity::operator >= (const QBasicVariableEntity &entity) {
	return compare(entity) >= 0;
}

/**
 * <=比較
 * @param entity 変数entity
 * @return 比較結果
 */
bool QBasicVariableEntity::operator <= (const QBasicVariableEntity &entity) {
	return compare(entity) <= 0;
}

#pragma mark - 四則演算

/**
 * 代入
 * @param entity 変数entity
 */
void QBasicVariableEntity::set(const QBasicVariableEntity &entity) {
	if (entity.isNil) {
		isNil = true;
		return;
	}
	switch (entity.types[0]) {
		case VariableType::Int:
			intValue = entity.intValue;
			types = entity.types;
			isNil = false;
			break;
		case VariableType::Float:
			floatValue = entity.floatValue;
			types = entity.types;
			isNil = false;
			break;
		case VariableType::Str:
			strValue = entity.strValue;
			types = entity.types;
			isNil = false;
			break;
		case VariableType::Bool:
			boolValue = entity.boolValue;
			types = entity.types;
			isNil = false;
			break;
		case VariableType::List:
			listValue = entity.listValue;
			types = entity.types;
			isNil = false;
			break;
		case VariableType::Dict:
			dictValue = entity.dictValue;
			types = entity.types;
			isNil = false;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
}


/**
 * int代入
 * @param value 値
 */
void QBasicVariableEntity::set(const int value) {
	types = { VariableType::Int };
	intValue = value;
	isNil = false;
}

/**
 * float代入
 * @param value 値
 */
void QBasicVariableEntity::set(const double value) {
	types = { VariableType::Float };
	floatValue = value;
	isNil = false;
}

/**
 * str代入
 * @param value 値
 */
void QBasicVariableEntity::set(const string &value) {
	types = { VariableType::Str };
	strValue = value;
	isNil = false;
}

/**
 * bool代入
 * @param value 値
 */
void QBasicVariableEntity::set(const bool value) {
	types = { VariableType::Bool };
	boolValue = value;
	isNil = false;
}

/**
 * 足し算
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::operator + (const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	if (isNil || entity.isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Int:
			returnEntity.intValue = intValue + entity.intValue;
			returnEntity.isNil = false;
			break;
		case VariableType::Float:
			returnEntity.floatValue = floatValue + entity.floatValue;
			returnEntity.isNil = false;
			break;
		case VariableType::Str:
			returnEntity.strValue = strValue + entity.strValue;
			returnEntity.isNil = false;
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
QBasicVariableEntity QBasicVariableEntity::operator - (const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	if (isNil || entity.isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Int:
			returnEntity.intValue = intValue - entity.intValue;
			returnEntity.isNil = false;
			break;
		case VariableType::Float:
			returnEntity.floatValue = floatValue - entity.floatValue;
			returnEntity.isNil = false;
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
QBasicVariableEntity QBasicVariableEntity::operator * (const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	if (isNil || entity.isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Int:
			returnEntity.intValue = intValue * entity.intValue;
			returnEntity.isNil = false;
			break;
		case VariableType::Float:
			returnEntity.floatValue = floatValue * entity.floatValue;
			returnEntity.isNil = false;
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
QBasicVariableEntity QBasicVariableEntity::mul(const vector<VariableType> types, const double value) {
	QBasicVariableEntity returnEntity = copyNotValue();
	if (isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Int:
			returnEntity.intValue = intValue * (int)value;
			returnEntity.isNil = false;
			break;
		case VariableType::Float:
			returnEntity.floatValue = floatValue * value;
			returnEntity.isNil = false;
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
QBasicVariableEntity QBasicVariableEntity::operator / (const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	if (isNil || entity.isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Int:
			if (entity.intValue != 0) {
				returnEntity.intValue = intValue / entity.intValue;
				returnEntity.isNil = false;
			}
			break;
		case VariableType::Float:
			if (entity.floatValue != 0) {
				returnEntity.floatValue = floatValue / entity.floatValue;
				returnEntity.isNil = false;
			}
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
QBasicVariableEntity QBasicVariableEntity::operator % (const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	if (isNil || entity.isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Int:
			if (entity.intValue != 0) {
				returnEntity.intValue = intValue % entity.intValue;
				returnEntity.isNil = false;
			} else {
				returnEntity.intValue = intValue;
				returnEntity.isNil = false;
			}
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
QBasicVariableEntity QBasicVariableEntity::operator & (const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	if (isNil || entity.isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Bool:
			returnEntity.boolValue = boolValue & entity.boolValue;
			returnEntity.isNil = false;
			break;
		case VariableType::Int:
			returnEntity.intValue = intValue & entity.intValue;
			returnEntity.isNil = false;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

/**
 * And比較論理演算
 * @param entity 変数entity
 * @return 比較結果
 */
QBasicVariableEntity QBasicVariableEntity::operator && (const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	if (isNil || entity.isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Bool:
			returnEntity.boolValue = boolValue && entity.boolValue;
			returnEntity.isNil = false;
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
QBasicVariableEntity QBasicVariableEntity::operator | (const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	if (isNil || entity.isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Bool:
			returnEntity.boolValue = boolValue | entity.boolValue;
			returnEntity.isNil = false;
			break;
		case VariableType::Int:
			returnEntity.intValue = intValue | entity.intValue;
			returnEntity.isNil = false;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

/**
 * OR比較論理演算
 * @param entity 変数entity
 * @return 比較結果
 */
QBasicVariableEntity QBasicVariableEntity::operator || (const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	if (isNil || entity.isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Bool:
			returnEntity.boolValue = boolValue || entity.boolValue;
			returnEntity.isNil = false;
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
QBasicVariableEntity QBasicVariableEntity::operator ^ (const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	if (isNil || entity.isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Bool:
			returnEntity.boolValue = boolValue ^ entity.boolValue;
			returnEntity.isNil = false;
			break;
		case VariableType::Int:
			returnEntity.intValue = intValue ^ entity.intValue;
			returnEntity.isNil = false;
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
QBasicVariableEntity QBasicVariableEntity::operator ! () {
	QBasicVariableEntity returnEntity = copyNotValue();
	if (isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Bool:
			returnEntity.boolValue = !boolValue;
			returnEntity.isNil = false;
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

#pragma mark - 要素操作

/**
 * 要素追加
 * @param entity 変数entity
 * @return 結果entity
 */
QBasicVariableEntity QBasicVariableEntity::append(const QBasicVariableEntity &entity) {
	QBasicVariableEntity returnEntity = copyNotValue();
	switch (types[0]) {
		case VariableType::List:
			returnEntity.listValue.push_back(entity);
			returnEntity.isNil = false;
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
	returnEntity.types = { VariableType::Int };
	if (isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Int:
			returnEntity.set(intValue);
			break;
		case VariableType::Float:
			returnEntity.set((int)floatValue);
			break;
		case VariableType::Str:
			returnEntity.set(atoi(strValue.c_str()));
			break;
		case VariableType::Bool:
			returnEntity.set((int)(boolValue ? 1 : 0));
			break;
		default:
			// 上位でチェックしているのでエラーは不要
			break;
	}
	return returnEntity;
}

/**
 * Floatへ変換
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::toFloat() {
	QBasicVariableEntity returnEntity;
	returnEntity.types = { VariableType::Float };
	if (isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Int:
			returnEntity.set((double)intValue);
			break;
		case VariableType::Str:
			returnEntity.set(atof(strValue.c_str()));
			break;
		case VariableType::Bool:
			returnEntity.set((double)(boolValue ? 1 : 0));
			break;
		default:
			break;
	}
	return returnEntity;
}

/**
 * Strへ変換
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::toStr() {
	QBasicVariableEntity returnEntity;
	returnEntity.types = { VariableType::Str };
	if (isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Int:
			returnEntity.set(StringUtil::toString((double)intValue));
			break;
		case VariableType::Float:
			returnEntity.set(StringUtil::toString(floatValue));
			break;
		case VariableType::Bool:
			returnEntity.set((string)(boolValue ? "true" : "false"));
			break;
		default:
			break;
	}
	return returnEntity;
}

/**
 * Boolへ変換
 * @param entity 変数entity
 * @return 結果
 */
QBasicVariableEntity QBasicVariableEntity::toBool() {
	QBasicVariableEntity returnEntity;
	returnEntity.types = { VariableType::Bool };
	if (isNil) {
		return returnEntity;
	}
	switch (types[0]) {
		case VariableType::Int:
			returnEntity.set((bool)(intValue != 0));
			break;
		case VariableType::Str:
			returnEntity.set((bool)(strValue == "true"));
			break;
		case VariableType::Float:
			returnEntity.set((bool)(floatValue != 0));
			break;
		default:
			break;
	}
	return returnEntity;
}

#pragma mark - チェック

/**
 *  変数タイプのチェック
 *  @param str 文字
 *  @return 変数タイプ
 */
VariableType QBasicVariableEntity::getVariableType(const string &str) {
	if (str.compare("void") == 0) {
		return VariableType::Void;
	}
	if (str.compare("int") == 0) {
		return VariableType::Int;
	}
	if (str.compare("float") == 0) {
		return VariableType::Float;
	}
	if (str.compare("str") == 0) {
		return VariableType::Str;
	}
	if (str.compare("bool") == 0) {
		return VariableType::Bool;
	}
	if (str.compare("list") == 0) {
		return VariableType::List;
	}
	if (str.compare("dict") == 0) {
		return VariableType::Dict;
	}
	return VariableType::Unknown;
}

/**
 *  変数タイプ文字の取得
 *  @param variableType 変数タイプ
 *  @return 文字
 */
string QBasicVariableEntity::getVariableTypeString(const VariableType variableType) {
	switch (variableType) {
		case VariableType::Void:
			return "void";
		case VariableType::Int:
			return "int";
		case VariableType::Float:
			return "float";
		case VariableType::Str:
			return "str";
		case VariableType::Bool:
			return "bool";
		case VariableType::List:
			return "list";
		case VariableType::Dict:
			return "dict";
		default:
			return "";
	}
}

/**
 *  変数タイプの取得 階層
 * @param entity 変数entity
 *  @return 変数タイプ群
 */
vector<VariableType> QBasicVariableEntity::getVariableTypes(const QBasicVariableEntity &entity) {
	
	auto variableTypes = entity.types;
	variableTypes.push_back(VariableType::Unknown);
	if (entity.types[0] == VariableType::List) {
		for (auto it = entity.listValue.begin();it != entity.listValue.end();it++) {
			if (variableTypes[1] == VariableType::Unknown) {
				variableTypes[1] = it->types[0];
				continue;
			}
			if (variableTypes[1] != it->types[0]) {
				// 型が不整合ならばvoid
				variableTypes[1] = VariableType::Void;
				break;
			}
		}
	} else if (entity.types[0] == VariableType::Dict) {
		for (auto it = entity.dictValue.begin();it != entity.dictValue.end();it++) {
			if (variableTypes[1] == VariableType::Unknown) {
				variableTypes[1] = it->second.types[0];
				continue;
			}
			if (variableTypes[1] != it->second.types[0]) {
				// 型が不整合ならばvoid
				variableTypes[1] = VariableType::Void;
				break;
			}
		}
	} else {
		return entity.types;
	}
	if (variableTypes[1] == VariableType::Unknown) {
		// 値入ってないからわからない
		return variableTypes;
	}
	if (variableTypes[1] == VariableType::List ||
		variableTypes[1] == VariableType::Dict) {
		QBasicVariableEntity childEntity;
		if (variableTypes[0] == VariableType::List && entity.listValue.size() > 0) {
			childEntity = entity.listValue[0];
		} else if (entity.dictValue.size() > 0) {
			childEntity = entity.dictValue.begin()->second;
		} else {
			variableTypes.push_back(VariableType::Unknown);
			return variableTypes;
		}
		auto childVariableTypes = getVariableTypes(childEntity);
		if (childVariableTypes[1] == VariableType::Unknown) {
			return variableTypes;
		}
		// 1の要素を消去
		variableTypes.pop_back();
		copy(childVariableTypes.begin(), childVariableTypes.end(), back_inserter(variableTypes));
	}
	
	return variableTypes;
}

#pragma mark - その他

/**
 *  変数タイプを文字列に変換
 *  @param name  変数名
 *  @param type  変数タイプ
 *  @param value 値のポインタ
 *  @return 文字列
 */
void QBasicVariableEntity::configureEntity(const string &name, const vector<VariableType> &types, void *value) {
	// 退避
	this->name = name;
	this->types = types;
	if (value != nullptr) {
		switch (this->types[0]) {
			case VariableType::Int:
				intValue = *(int *)value;
				break;
			case VariableType::Float:
				floatValue = *(double *)value;
				break;
			case VariableType::Str:
				strValue = *reinterpret_cast<string*>(value);
				break;
			case VariableType::Bool:
				boolValue = *(bool *)value;
				break;
			case VariableType::List:
				listValue = *reinterpret_cast<vector<QBasicVariableEntity>*>(value);
				break;
			case VariableType::Dict:
				dictValue = *reinterpret_cast<map<string, QBasicVariableEntity>*>(value);
				break;
			default:
				break;
		}
		isNil = false;
	}
}

/**
 * 値なしコピー
 * @return コピーEntity
 */
QBasicVariableEntity QBasicVariableEntity::copyNotValue() {
	QBasicVariableEntity returnEntity;
	returnEntity.name = name;
	returnEntity.types = types;
	return returnEntity;
}

/**
 *  変数タイプを文字列に変換
 *  @param type      メインタイプ
 *  @param subTypes  サブタイプ
 *  @return 文字列
 */
string QBasicVariableEntity::toString(const vector<VariableType> &types) {
	ostringstream stream;
	auto it = types.begin();
	// メインタイプ
	stream << getVariableTypeString(*it);
	// サブタイプ
	for (;it != types.end();it++) {
		stream << "<" << getVariableTypeString(*it);
	}
	for (int i = 0;i < types.size() - 1;i++) {
		stream << ">";
	}
	return stream.str();
}
