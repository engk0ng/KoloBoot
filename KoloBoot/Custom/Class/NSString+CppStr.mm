//
//  NSString+CppStr.m
//  KoloBoot
//
//  Created by Abu Muhammad on 07/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "NSString+CppStr.h"

@implementation NSString (CppStr)
- (std::string)toStdString {
    if (self) {
        return std::string([self UTF8String]);
    }
    return std::string("");
}
@end
