//
//  SecondViewController.swift
//  finalProject
//
//  Created by Andy Chase on 12/5/15.
//  Copyright © 2015 Andy Chase. All rights reserved.
//

import UIKit

class AccountViewController: UIViewController {
    
    @IBAction func pressSignOutButton(sender: AnyObject) {
        self.dismissViewControllerAnimated(true, completion: {});
    }
}

