//
//  QBasicFunctionMathTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/25.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "StringUtil.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

/// スクリプト math関連テスト
@interface QBasicFunctionMathTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicFunctionMathTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"function_math" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// abs
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 1.0);
	XCTAssertEqual(interpreter->variables["b"].floatValue, 10.0);
}
/// max
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].floatValue, 2.0);
}
/// min
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 1.0);
}
/// deg2red
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// sin
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// cos
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// tan
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// asin
- (void)test7 {
	interpreter = new QBasic(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// acos
- (void)test8 {
	interpreter = new QBasic(nullptr, [scripts[8] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// atan
- (void)test9 {
	interpreter = new QBasic(nullptr, [scripts[9] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// atan2
- (void)test10 {
	interpreter = new QBasic(nullptr, [scripts[10] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 0.78539816339744828);
}
/// cbrt
- (void)test11 {
	interpreter = new QBasic(nullptr, [scripts[11] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 1.0);
}
/// pow
- (void)test12 {
	interpreter = new QBasic(nullptr, [scripts[12] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 1.0);
}
/// rand
- (void)test13 {
	interpreter = new QBasic(nullptr, [scripts[13] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["isValid"].boolValue, true);
}
/// rad2deg
- (void)test14 {
	interpreter = new QBasic(nullptr, [scripts[14] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(roundf(interpreter->variables["a"].floatValue), 45.0);
}
/// round
- (void)test15 {
	interpreter = new QBasic(nullptr, [scripts[15] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(roundf(interpreter->variables["a"].floatValue), 0.0);
	XCTAssertEqual(roundf(interpreter->variables["b"].floatValue), 1.0);
}
/// floor
- (void)test16 {
	interpreter = new QBasic(nullptr, [scripts[16] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(roundf(interpreter->variables["a"].floatValue), 0.0);
	XCTAssertEqual(roundf(interpreter->variables["b"].floatValue), 0.0);
}
/// ceil
- (void)test17 {
	interpreter = new QBasic(nullptr, [scripts[17] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(roundf(interpreter->variables["a"].floatValue), 1.0);
	XCTAssertEqual(roundf(interpreter->variables["b"].floatValue), 1.0);
}
/// sinh
- (void)test18 {
	interpreter = new QBasic(nullptr, [scripts[18] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// cosh
- (void)test19 {
	interpreter = new QBasic(nullptr, [scripts[19] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// tanh
- (void)test20 {
	interpreter = new QBasic(nullptr, [scripts[20] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// exp
- (void)test21 {
	interpreter = new QBasic(nullptr, [scripts[21] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// log
- (void)test22 {
	interpreter = new QBasic(nullptr, [scripts[22] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// log10
- (void)test23 {
	interpreter = new QBasic(nullptr, [scripts[23] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}
/// abs(int型)
- (void)test24 {
	interpreter = new QBasic(nullptr, [scripts[24] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(roundf(interpreter->variables["a"].intValue), 1);
	XCTAssertEqual(roundf(interpreter->variables["b"].intValue), 10);
}
/// max(int型)
- (void)test25 {
	interpreter = new QBasic(nullptr, [scripts[25] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(roundf(interpreter->variables["a"].intValue), 2);
	XCTAssertEqual(roundf(interpreter->variables["b"].intValue), 2);
}
/// min(int型)
- (void)test26 {
	interpreter = new QBasic(nullptr, [scripts[26] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(roundf(interpreter->variables["a"].intValue), 1);
	XCTAssertEqual(roundf(interpreter->variables["b"].intValue), 0);
}

@end
