//
//  AppDelegate.h
//  KoloBoot
//
//  Created by Abu Muhammad on 31/03/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "helper_onc.h"

struct FirebaseAccess;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (nonatomic, assign) struct FirebaseAccess *serverConnect;
+ (AppDelegate *)sharedAppdelegate;
- (const void *)get_firebase_connector:(FirebaseType)tp;
@end

