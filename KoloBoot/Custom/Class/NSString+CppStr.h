//
//  NSString+CppStr.h
//  KoloBoot
//
//  Created by Abu Muhammad on 07/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <string>

@interface NSString (CppStr)
- (std::string)toStdString;
@end
