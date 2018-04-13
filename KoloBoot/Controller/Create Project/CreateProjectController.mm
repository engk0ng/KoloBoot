//
//  CreateProjectController.m
//  KoloBoot
//
//  Created by Abu Muhammad on 03/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "CreateProjectController.h"
#import "AppDelegate.h"
#import "NSString+CppStr.h"
#import "ProgressView.h"
#import "PathController.h"
#import "DBManager.hpp"
#import "Utils.h"

@interface CreateProjectController ()
@end

@implementation CreateProjectController
@synthesize dbase;
- (void)viewDidLoad {
    [super viewDidLoad];
    _nameField.delegate = self;
    _baseUrlField.delegate = self;
    
    _nameField.clearButtonMode = UITextFieldViewModeWhileEditing;
    _baseUrlField.clearButtonMode = UITextFieldViewModeWhileEditing;
    NSString *lblBtn = @"";
    if (_project.getName().empty()) {
        lblBtn = @"Next";
    }
    else {
        lblBtn = @"Update";
    }
    [self.navigationItem setLeftBarButtonItem:[[UIBarButtonItem alloc] initWithTitle:lblBtn style:UIBarButtonItemStylePlain target:self action:@selector(saveAction:)]];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardChangingFrame:) name:UIKeyboardWillChangeFrameNotification object:nil];
    if (!_project.getName().empty()) {
        _nameField.text = [Utils toNSString:_project.getName()];
        _baseUrlField.text = [Utils toNSString:_project.getBaseUrl()];
    }
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField {
    textField.text = @"https://";
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

#pragma mark - Action

- (void)saveAction:(id)sender {
    Model::Project proj([_nameField.text toStdString], [_baseUrlField.text toStdString]);
    NSString *msg = @"";
    bool status = true;
    if (proj.getName().empty()) {
        msg = @"Nama project tidak boleh kosong";
        status = false;
    }
    if (proj.getBaseUrl().empty()) {
        msg = @"Base URL tidak boleh kosong";
        status = false;
    }
    
    if (status == false) {
        [[AppDelegate sharedAppdelegate] messageNotification:@"Error" description:msg visible:YES delay:4 type:TWMessageBarMessageTypeError errorCode:0];
        return;
    }
    else {
        int last_id = 0;
        if (_project.getName().empty()) {
            auto saves = dbase->saveProject();
            last_id = saves(proj);
        }
        else {
            _project.setName([_nameField.text toStdString]);
            _project.setBaseUrl([_baseUrlField.text toStdString]);
            auto saves = dbase->updateProject();
            last_id = saves(_project);
        }
        
        if (last_id != 0) {
            if ([_delegate respondsToSelector:@selector(refreshDataProject)]) {
                [_delegate refreshDataProject];
            }
            if (_project.getName().empty()) {
                _nameField.text = @"";
                _baseUrlField.text = @"";
                PathController *pathVC = [self.storyboard instantiateViewControllerWithIdentifier:@"PathController"];
                pathVC.preferredContentSize = CGSizeMake(320, 280);
                pathVC.title = @"Insert Request";
                pathVC.lastId = last_id;
                pathVC.dbase = dbase;
                pathVC.delegate = _delegate;
                [self.navigationController pushViewController:pathVC animated:YES];
            }
            else
            {
                [[AppDelegate sharedAppdelegate] messageNotification:@"Success" description:@"Data project berhasil diubah" visible:YES delay:4 type:TWMessageBarMessageTypeSuccess errorCode:0];
            }
        }
        else {
            [[AppDelegate sharedAppdelegate] messageNotification:@"Error" description:@"Data gagal disimpan" visible:YES delay:4 type:TWMessageBarMessageTypeError errorCode:0];
        }
    }
}

- (void)dealloc {
    dbase.reset();
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillChangeFrameNotification object:nil];
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
