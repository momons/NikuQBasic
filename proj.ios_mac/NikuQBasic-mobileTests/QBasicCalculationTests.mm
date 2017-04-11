//
//  QBasicCalculationTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/25.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"

/// スクリプト 計算テスト
@interface QBasicCalculationTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicCalculationTests

- (void)setUp {
    [super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"calculation" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
    [super tearDown];
}

/// 足し算 15
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "15");
}

/// 引き算 0
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "0");
}

/// 掛け算 24
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "24");
}

/// 割り算 6
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "6");
}

/// まぜこぜ計算その１ 58
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "58");
}

/// まぜこぜ計算その２ 0
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "0");
}

/// かっこ付き計算その１ 5
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "5");
}

/// かっこ付き計算その２ 2
- (void)test7 {
	interpreter = new QBasic(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "2");
}

/// 小数点 その１ 0.5
- (void)test8 {
	interpreter = new QBasic(nullptr, [scripts[8] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "0.5");
}

/// 小数点 その２　0.4
- (void)test9 {
	interpreter = new QBasic(nullptr, [scripts[9] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "0.4");
}

@end
