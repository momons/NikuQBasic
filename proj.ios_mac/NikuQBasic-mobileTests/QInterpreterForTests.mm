//
//  QInterpreterForTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/06.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBInterpreter.h"

@interface QBInterpreterForTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBInterpreter *interpreter;
}
@end

@implementation QBInterpreterForTests

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
	interpreter = new QBInterpreter(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "55");
	XCTAssertEqual(interpreter->variables["i"], "11");
}

/// 1から10まで2ステップでループ
- (void)test1 {
	interpreter = new QBInterpreter(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "25");
	XCTAssertEqual(interpreter->variables["i"], "11");
}

/// 10から1まで-1ステップでループ
- (void)test2 {
	interpreter = new QBInterpreter(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "55");
	XCTAssertEqual(interpreter->variables["i"], "0");
}

/// 10から1まで-2ステップでループ
- (void)test3 {
	interpreter = new QBInterpreter(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "30");
	XCTAssertEqual(interpreter->variables["i"], "0");
}

/// 二重ループ
- (void)test4 {
	interpreter = new QBInterpreter(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "55");
	XCTAssertEqual(interpreter->variables["b"], "550");
	XCTAssertEqual(interpreter->variables["i"], "11");
	XCTAssertEqual(interpreter->variables["j"], "11");
}

/// stepなしでもstep-1
- (void)test5 {
	interpreter = new QBInterpreter(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "55");
	XCTAssertEqual(interpreter->variables["i"], "0");
}


@end
