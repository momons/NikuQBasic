//
//  QBInterpreterRemTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/06.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBInterpreter.h"

@interface QBInterpreterRemTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBInterpreter *interpreter;
}
@end

@implementation QBInterpreterRemTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"rem" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// 1行コメント
- (void)test0 {
	interpreter = new QBInterpreter(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "0");
}

/// シングルクォーテーションでもコメント
- (void)test1 {
	interpreter = new QBInterpreter(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "0");
}

/// 行の途中からコメント
- (void)test2 {
	interpreter = new QBInterpreter(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"], "1");
}

@end
