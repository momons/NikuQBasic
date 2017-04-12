//
//  QBasicValidationTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/13.
//
//

#import <XCTest/XCTest.h>

#include "QBasicValidation.h"

@interface QBasicValidationTests : XCTestCase {
@private
}
@end

@implementation QBasicValidationTests

- (void)setUp {
	[super setUp];
}

- (void)tearDown {
	[super tearDown];
}

/// isIntテスト
- (void)test_isInt {
	// 整数値
	XCTAssertTrue(QBasicValidation::isInt("12345678"));
	// 小数値
	XCTAssertFalse(QBasicValidation::isInt(".12345678"));
	// マイナス整数値
	XCTAssertTrue(QBasicValidation::isInt("-12345678"));
	// プラスはダメなんです
	XCTAssertFalse(QBasicValidation::isInt("+12345678"));
}

/// isFloatテスト
- (void)test_isFloat {
	// 整数値
	XCTAssertTrue(QBasicValidation::isFloat("12345678"));
	// 小数値
	XCTAssertTrue(QBasicValidation::isFloat("1234.5678"));
	// マイナス整数値
	XCTAssertTrue(QBasicValidation::isFloat("-12345678"));
	// マイナス小数値
	XCTAssertTrue(QBasicValidation::isFloat("-1234.5678"));
	// 最初が.
	XCTAssertTrue(QBasicValidation::isFloat(".12345678"));
	// 最後が.
	XCTAssertTrue(QBasicValidation::isFloat("12345678."));
	// .2つ
	XCTAssertFalse(QBasicValidation::isFloat("123.45678."));
	// マイナス2つ
	XCTAssertFalse(QBasicValidation::isFloat("--12345678"));
	// プラスはダメ
	XCTAssertFalse(QBasicValidation::isFloat("+12345678"));
}

/// isStrテスト
- (void)test_isStr {
	// 半角文字
	XCTAssertTrue(QBasicValidation::isStr("\"a\""));
	// マルチ文字
	XCTAssertTrue(QBasicValidation::isStr("\"あ\""));
	// ダブルクォートなし
	XCTAssertFalse(QBasicValidation::isStr("あいうえお"));
	// ダブルクォート前方なし
	XCTAssertFalse(QBasicValidation::isStr("あいうえお\""));
	// ダブルクォート後方なし
	XCTAssertFalse(QBasicValidation::isStr("\"あいうえお"));
}

/// isBoolテスト
- (void)test_isBool {
	// true
	XCTAssertTrue(QBasicValidation::isBool("true"));
	// false
	XCTAssertTrue(QBasicValidation::isBool("false"));
	// 大文字TRUEとかダメ
	XCTAssertFalse(QBasicValidation::isBool("TRUE"));
}

@end
