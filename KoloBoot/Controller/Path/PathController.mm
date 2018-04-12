//
//  PathController.m
//  KoloBoot
//
//  Created by Abu Muhammad on 08/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "PathController.h"
#import "RequestPopupController.h"
#import "DBManager.hpp"
#import "Path.hpp"
#import "AppDelegate.h"
#import "NSString+CppStr.h"
#import <iostream>
#import "Utils.h"
#import "Project.hpp"

@interface PathController () <RequestPopupControllerDelegate, UITextFieldDelegate>
@property (nonatomic, assign) Model::Project project;
@end

@implementation PathController

- (void)viewDidLoad {
    [super viewDidLoad];
    _namaRequestField.delegate = self;
    _pathField.delegate = self;
    _dbase->getProjectById(_lastId, [&](Model::Project proj){
        _project = proj;
    });
    _baseUrlLbl.text = [NSString stringWithFormat:@"Base URL: %s", _project.getBaseUrl().c_str()];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardChangingFrame:) name:UIKeyboardWillChangeFrameNotification object:nil];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)chooseRequestAction:(id)sender {
    RequestPopupController *reqPop = [[RequestPopupController alloc] initWithNibName:@"RequestPopupController" bundle:nil];
    reqPop.delegate = self;
    [reqPop show];
}

- (IBAction)savePathAction:(id)sender {
    BOOL status = YES;
    if ([_namaRequestField.text isEqualToString:@""]) {
        status = NO;
        [[AppDelegate sharedAppdelegate] messageNotification:@"Error" description:@"Nama request tidak boleh kosong" visible:YES delay:4 type:TWMessageBarMessageTypeError errorCode:0];
        return;
    }
    if ([_pathField.text isEqualToString:@""]) {
        status = NO;
        [[AppDelegate sharedAppdelegate] messageNotification:@"Error" description:@"Request path tidak boleh kosong" visible:YES delay:4 type:TWMessageBarMessageTypeError errorCode:0];
        return;
    }
    
    if (status) {
        Model::Path path;
        path.setName([_namaRequestField.text toStdString]);
        path.setPath([_pathField.text toStdString]);
        path.setType([_typeBtn.titleLabel.text toStdString]);
        path.setProjectId(_lastId);
        _dbase->savePath(path, [&](int res){
            if (res > 0) {
                [[AppDelegate sharedAppdelegate] messageNotification:@"Success" description:@"Path request berhasil disimpan" visible:YES delay:4 type:TWMessageBarMessageTypeSuccess errorCode:0];
                _namaRequestField.text = @"";
                _pathField.text = @"";
                if ([_delegate respondsToSelector:@selector(refreshDataProject)]) {
                    [_delegate refreshDataProject];
                }
                return;
            }
            else {
                [[AppDelegate sharedAppdelegate] messageNotification:@"Error" description:@"Path request gagal disimpan" visible:YES delay:4 type:TWMessageBarMessageTypeError errorCode:0];
                return;
            }
        });
    }
}

#pragma mark - RequestPopupControllerDelegate

- (void)sendTypeSelected:(NSString *)txt {
    [_typeBtn setTitle:txt forState:UIControlStateNormal];
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField {
    if ([textField isEqual:_pathField]) {
        std::string bs;
        size_t length = _project.getBaseUrl().length();
        if (_project.getBaseUrl().at(length - 1) != '/') {
            bs = "/";
        }
        textField.text = [Utils toNSString:bs];
    }
}

- (void)dealloc {
    _dbase.reset();
}

#pragma mark - Helper

- (void)keyboardChangingFrame:(NSNotification *)notif {
    NSDictionary *info = [notif userInfo];
    CGRect keyboardEndFram = [info[UIKeyboardFrameEndUserInfoKey] CGRectValue];
    CGFloat offset = [[UIScreen mainScreen] bounds].size.height - CGRectGetMinY(keyboardEndFram) - 60;
    UIEdgeInsets inset = _scrollView.contentInset;
    inset.bottom = offset;
    _scrollView.contentInset = inset;
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
