//
//  MainViewController.h
//  SMP3-101
//
//  Created by Adalbert Kitzig on 26.08.14.
//  Copyright (c) 2014 PlaceWorkers. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SMPDelegate.h"
#import "SMPController.h"

@interface MainViewController : UIViewController <smpDelegate, UITableViewDataSource>

// Our buttons and result table
@property (weak, nonatomic) IBOutlet UIButton *registerButton;
@property (weak, nonatomic) IBOutlet UIButton *downloadDataButton;
@property (weak, nonatomic) IBOutlet UITableView *resultsTable;


// Our actions on the buttons
- (IBAction)startRegistration:(id)sender;
- (IBAction)startDataDownload:(id)sender;



@end
