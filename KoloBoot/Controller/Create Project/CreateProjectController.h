//
//  CreateProjectController.h
//  KoloBoot
//
//  Created by Abu Muhammad on 03/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <map>
#import <string>

@protocol CreateProjectControllerDelegate <NSObject>
@optional
- (void)saveDataProject:(std::map<std::string, std::string>)dta;
@end

@interface CreateProjectController : UIViewController <UITextFieldDelegate>
@property (weak) id<CreateProjectControllerDelegate> delegate;
@property (nonatomic, weak) IBOutlet UITextField *baseUrlField;
@property (nonatomic, weak) IBOutlet UITextField *nameField;
@property (nonatomic, weak) IBOutlet UIScrollView *scrollView;
@property (nonatomic, weak) IBOutlet UIView *contentView;

@end
