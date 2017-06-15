//
//  QBasicVariableJsonTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/16.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"
#import "picojson.h"

/// JSON変換テスト
@interface QBasicVariableJsonTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}

@end

@implementation QBasicVariableJsonTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"variable_json" clazz:[self class]];
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
	auto object = interpreter->variables["a"].toJsonObject();
	auto jsonString = picojson::value(object).serialize();
//	auto value = QBasicVariableEntity::buildForStorageJsonObject(object);
//	XCTAssertEqual(value.types.size(), 1);
//	XCTAssertEqual(value.types[0], VariableType::Int);
//	XCTAssertEqual(value.intValue, 10);
//	XCTAssertEqual(value.isNil, false);
}

@end
