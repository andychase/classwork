//
//  FirstViewController.swift
//  finalProject
//
//  Created by Andy Chase on 12/5/15.
//  Copyright © 2015 Andy Chase. All rights reserved.
//

import UIKit

class ListViewController: UIViewController {
    var userId:Int!
    var global:Bool!

    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        if let id = self.userId {
            print(id)
        }
    }
}

