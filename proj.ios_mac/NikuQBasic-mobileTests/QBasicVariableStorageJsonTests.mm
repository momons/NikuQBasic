//
//  QBasicVariableStorageJsonTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/15.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"
#import "picojson.h"

/// 保存用JSON変換テスト
@interface QBasicVariableStorageJsonTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}

@end

@implementation QBasicVariableStorageJsonTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"variable_storage_json" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// int編
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toStorageJsonObject();
	auto value = QBasicVariableEntity::build(object);
	XCTAssertEqual(value.types.size(), 1);
	XCTAssertEqual(value.types[0], VariableType::Int);
	XCTAssertEqual(value.intValue, 10);
	XCTAssertEqual(value.isNil, false);
}

/// float編
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toStorageJsonObject();
	auto value = QBasicVariableEntity::build(object);
	XCTAssertEqual(value.types.size(), 1);
	XCTAssertEqual(value.types[0], VariableType::Float);
	XCTAssertEqual(value.floatValue, 20);
	XCTAssertEqual(value.isNil, false);
}

/// str編
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toStorageJsonObject();
	auto value = QBasicVariableEntity::build(object);
	XCTAssertEqual(value.types.size(), 1);
	XCTAssertEqual(value.types[0], VariableType::Str);
	XCTAssertEqual(value.strValue, "abcdefg");
	XCTAssertEqual(value.isNil, false);
}

/// bool編
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toStorageJsonObject();
	auto value = QBasicVariableEntity::build(object);
	XCTAssertEqual(value.types.size(), 1);
	XCTAssertEqual(value.types[0], VariableType::Bool);
	XCTAssertEqual(value.boolValue, true);
	XCTAssertEqual(value.isNil, false);
}

/// list編 その１
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toStorageJsonObject();
	auto value = QBasicVariableEntity::build(object);
	XCTAssertEqual(value.types.size(), 2);
	XCTAssertEqual(value.types[0], VariableType::List);
	XCTAssertEqual(value.types[1], VariableType::Int);
	XCTAssertEqual(value.listValue.size(), 4);
	for (int i = 0;i < value.listValue.size();i++) {
		XCTAssertEqual(value.listValue[i].intValue, i);
		XCTAssertEqual(value.listValue[i].isNil, false);
	}
	XCTAssertEqual(value.isNil, false);
}

/// list編 その２
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toStorageJsonObject();
	auto value = QBasicVariableEntity::build(object);
	XCTAssertEqual(value.types.size(), 3);
	XCTAssertEqual(value.types[0], VariableType::List);
	XCTAssertEqual(value.types[1], VariableType::Dict);
	XCTAssertEqual(value.types[2], VariableType::Str);
	XCTAssertEqual(value.listValue.size(), 4);
	for (int i = 0;i < value.listValue.size();i++) {
		switch (i) {
			case 0:
				XCTAssertEqual(value.listValue[i].dictValue["a"].strValue, "0");
				XCTAssertEqual(value.listValue[i].dictValue["a"].isNil, false);
				break;
			case 1:
				XCTAssertEqual(value.listValue[i].dictValue["b"].strValue, "1");
				XCTAssertEqual(value.listValue[i].dictValue["b"].isNil, false);
				break;
			case 2:
				XCTAssertEqual(value.listValue[i].dictValue["c"].strValue, "2");
				XCTAssertEqual(value.listValue[i].dictValue["c"].isNil, false);
				break;
			case 3:
				XCTAssertEqual(value.listValue[i].dictValue["d"].strValue, "3");
				XCTAssertEqual(value.listValue[i].dictValue["d"].isNil, false);
				break;
		}
	}
	XCTAssertEqual(value.isNil, false);
}

/// dict編 その１
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toStorageJsonObject();
	auto value = QBasicVariableEntity::build(object);
	XCTAssertEqual(value.types.size(), 2);
	XCTAssertEqual(value.types[0], VariableType::Dict);
	XCTAssertEqual(value.types[1], VariableType::Str);
	for (auto it = value.dictValue.begin();it != value.dictValue.end();it++) {
		if (it->first == "a") {
			XCTAssertEqual(it->second.strValue, "aa");
		} else if (it->first == "b") {
			XCTAssertEqual(it->second.strValue, "bb");
		} else if (it->first == "c") {
			XCTAssertEqual(it->second.strValue, "cc");
		} else if (it->first == "d") {
			XCTAssertEqual(it->second.strValue, "dd");
		} else {
			XCTAssert("不正なキーです");
		}
	}
	XCTAssertEqual(value.isNil, false);
}

/// dict編 その２
- (void)test7 {
	interpreter = new QBasic(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toStorageJsonObject();
	auto value = QBasicVariableEntity::build(object);
	XCTAssertEqual(value.types.size(), 3);
	XCTAssertEqual(value.types[0], VariableType::Dict);
	XCTAssertEqual(value.types[1], VariableType::List);
	XCTAssertEqual(value.types[2], VariableType::Float);
	for (auto it = value.dictValue.begin();it != value.dictValue.end();it++) {
		if (it->first == "a") {
			XCTAssertEqual(it->second.listValue.size(), 1);
			XCTAssertEqual(it->second.listValue[0].floatValue, 1.0);
			XCTAssertEqual(it->second.listValue[0].isNil, false);
		} else if (it->first == "b") {
			XCTAssertEqual(it->second.listValue.size(), 1);
			XCTAssertEqual(it->second.listValue[0].floatValue, 2.0);
			XCTAssertEqual(it->second.listValue[0].isNil, false);
		} else if (it->first == "c") {
			XCTAssertEqual(it->second.listValue.size(), 1);
			XCTAssertEqual(it->second.listValue[0].floatValue, 3.0);
			XCTAssertEqual(it->second.listValue[0].isNil, false);
		} else if (it->first == "d") {
			XCTAssertEqual(it->second.listValue.size(), 1);
			XCTAssertEqual(it->second.listValue[0].floatValue, 4.0);
			XCTAssertEqual(it->second.listValue[0].isNil, false);
		} else {
			XCTAssert("不正なキーです");
		}
	}
	XCTAssertEqual(value.isNil, false);
}

@end
