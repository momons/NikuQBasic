//
//  QBasicVariableFloatTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/22.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

/// スクリプト float変数テスト
@interface QBasicVariableFloatTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicVariableFloatTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"variable_float" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// 型テスト float
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 9999.888);
}

/// 型テスト floatにintはダメ
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト floatにstrはダメ
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト floatにboolはダメ
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト 型推論テスト float
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 3.0);
}


/// 型テスト 省略足し算
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 2.0);
}

/// 型テスト 省略引き算
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 1.0);
}

/// 型テスト 省略掛け算
- (void)test7 {
	interpreter = new QBasic(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 9.0);
}

/// 型テスト 省略割り算
- (void)test8 {
	interpreter = new QBasic(nullptr, [scripts[8] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 2.0);
}

/// 型テスト 省略余り
- (void)test9 {
	interpreter = new QBasic(nullptr, [scripts[9] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 初期値nil
- (void)test10 {
	interpreter = new QBasic(nullptr, [scripts[10] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].isNil, true);
}

/// nil + 1.0 = nil
- (void)test11 {
	interpreter = new QBasic(nullptr, [scripts[11] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].isNil, true);
}

/// nil - 1.0 = nil
- (void)test12 {
	interpreter = new QBasic(nullptr, [scripts[12] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].isNil, true);
}

/// nil * 1.0 = nil
- (void)test13 {
	interpreter = new QBasic(nullptr, [scripts[13] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].isNil, true);
}

/// nil / 1.0 = nil
- (void)test14 {
	interpreter = new QBasic(nullptr, [scripts[14] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].isNil, true);
}

/// nilの代入
- (void)test15 {
	interpreter = new QBasic(nullptr, [scripts[15] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].isNil, true);
}

@end
