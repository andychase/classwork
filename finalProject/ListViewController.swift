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
    var listType:Bool!
    var dataSource:ListModel!

    @IBOutlet var table: UITableView!
    
    override func viewDidLoad() {
            self.dataSource = ListModel(isGlobalListType: self.restorationIdentifier == "globalList")
            table.dataSource = self.dataSource
    }

    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
    }
}

