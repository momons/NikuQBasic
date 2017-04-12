//
//  QBasicForTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/06.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

@interface QBasicForTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicForTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"for" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// 1から10までループ
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "55");
	XCTAssertEqual(interpreter->variables["i"].strValue, "11");
}

/// 1から10まで2ステップでループ
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "25");
	XCTAssertEqual(interpreter->variables["i"].strValue, "11");
}

/// 10から1まで-1ステップでループ
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "55");
	XCTAssertEqual(interpreter->variables["i"].strValue, "0");
}

/// 10から1まで-2ステップでループ
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "30");
	XCTAssertEqual(interpreter->variables["i"].strValue, "0");
}

/// 二重ループ
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "55");
	XCTAssertEqual(interpreter->variables["b"].strValue, "550");
	XCTAssertEqual(interpreter->variables["i"].strValue, "11");
	XCTAssertEqual(interpreter->variables["j"].strValue, "11");
}

/// stepなしでもstep-1
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "55");
	XCTAssertEqual(interpreter->variables["i"].strValue, "0");
}


@end
