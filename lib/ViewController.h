//
//  ViewController.h
//  LifeLibExample
//
//  Created by HikaruBB on 2016/6/8.
//  Copyright © 2016年 HikaruBB. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LifeLibrary.h"

typedef enum
{
    Job_DoEvent      = 6666,
} LifeLibrary_CustomJobType;

@interface ViewController : UIViewController <LifeLibraryDelegate>
{
    LifeLibrary *lib;
}

@property (weak, nonatomic) IBOutlet UIButton *createBtn;
@property (weak, nonatomic) IBOutlet UIButton *searchBtn;
@property (weak, nonatomic) IBOutlet UIButton *connectBtn;
@property (weak, nonatomic) IBOutlet UIButton *audio_StartBtn;
@property (weak, nonatomic) IBOutlet UIButton *audio_StopBtn;

@property (weak, nonatomic) IBOutlet UIButton *leftup;
@property (weak, nonatomic) IBOutlet UIButton *up;
@property (weak, nonatomic) IBOutlet UIButton *rightup;
@property (weak, nonatomic) IBOutlet UIButton *left;
@property (weak, nonatomic) IBOutlet UIButton *right;
@property (weak, nonatomic) IBOutlet UIButton *leftdown;
@property (weak, nonatomic) IBOutlet UIButton *down;
@property (weak, nonatomic) IBOutlet UIButton *rightdown;

@property (weak, nonatomic) IBOutlet UIImageView *imgview;
@property (weak, nonatomic) IBOutlet UILabel *label;


- (void) setStreamUrl:(NSString *)url;

@end

