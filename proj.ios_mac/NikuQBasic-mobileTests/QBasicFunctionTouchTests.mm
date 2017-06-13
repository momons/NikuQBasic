//
//  QBasicFunctionTouchTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/14.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

/// 文字関数テスト
@interface QBasicFunctionTouchTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicFunctionTouchTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"function_touch" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

// TODO: 細かいテストはおいおい

/// touchBegin
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].listValue.size(), 0);
}

/// touchMove
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].listValue.size(), 0);
}

/// touchEnd
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].listValue.size(), 0);
}

@end
