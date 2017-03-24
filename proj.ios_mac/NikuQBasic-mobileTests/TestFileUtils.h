//
//  FileUtils.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/25.
//
//

#import <Foundation/Foundation.h>

@interface TestFileUtils : NSObject 

/// ファイル読み込み
+ (NSString *)loadFile:(NSString *)fileName clazz:(Class)clazz;

@end
