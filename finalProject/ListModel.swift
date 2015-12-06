//
//  ListModel.swift
//  finalProject
//
//  Created by Andy Chase on 12/6/15.
//  Copyright © 2015 Andy Chase. All rights reserved.
//

import UIKit

class ListModel: NSObject, UITableViewDataSource, UITableViewDelegate {
    
    var isGlobalListType:Bool!
    var rows = [
        UITableViewCell(),
        UITableViewCell(),
        UITableViewCell(),
        UITableViewCell()
    ]
    var table:UITableView!
    
    init(table:UITableView, isGlobalListType:Bool) {
        self.table = table
        self.isGlobalListType = isGlobalListType
        rows[3].textLabel!.text = "Text"
    }
    
    // called when a row deletion action is confirmed
    func tableView(tableView: UITableView,
        commitEditingStyle editingStyle: UITableViewCellEditingStyle,
        forRowAtIndexPath indexPath: NSIndexPath) {
            switch editingStyle {
            case .Delete:
                // remove the deleted item from the model
                self.rows.removeAtIndex(indexPath.row)
                
                // remove the deleted item from the `UITableView`
                self.table.deleteRowsAtIndexPaths([indexPath], withRowAnimation: .Fade)
            default:
                return
            }
    }
    
    // called when a row is moved
    func tableView(tableView: UITableView,
        moveRowAtIndexPath sourceIndexPath: NSIndexPath,
        toIndexPath destinationIndexPath: NSIndexPath) {
            // remove the dragged row's model
            let val = self.rows.removeAtIndex(sourceIndexPath.row)
            
            // insert it into the new position
            self.rows.insert(val, atIndex: destinationIndexPath.row)
    }
    
    func tableView(tableView: UITableView,
        editingStyleForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCellEditingStyle {
            return UITableViewCellEditingStyle.Delete
    }
    
    func tableView(tableView: UITableView,
        cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
            return rows[indexPath.row]
    }
    
    func tableView(tableView: UITableView,
        numberOfRowsInSection section: Int) -> Int {
            if (section == 0) {
                return rows.count
            }  else {
                return 0
            }
    }
    
}