//
//  QBasicFunctionListTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/11.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "StringUtil.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

/// 文字関数テスト
@interface QBasicFunctionListTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicFunctionListTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"function_list" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// count
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 5);
	XCTAssertEqual(interpreter->variables["b"].intValue, 10);
}

/// append
- (void)test1 {
//	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
//	XCTAssertNoThrow(interpreter->run());
//	XCTAssertEqual(interpreter->variables["a"].listValue.size(), 4);
//	XCTAssertEqual(interpreter->variables["a"].listValue[0].intValue, 1);
//	XCTAssertEqual(interpreter->variables["a"].listValue[1].intValue, 2);
//	XCTAssertEqual(interpreter->variables["a"].listValue[2].intValue, 3);
//	XCTAssertEqual(interpreter->variables["a"].listValue[3].intValue, 4);
}


@end
