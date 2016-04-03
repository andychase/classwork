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
    var rows:[UITableViewCell] = []
    var table:UITableView!
    var userId:String!
    
    init(table:UITableView, isGlobalListType:Bool, userId:String) {
        self.table = table
        self.isGlobalListType = isGlobalListType
        self.userId = userId
    }
    
    func loadRows() {
        var userList = "false"
        if (self.isGlobalListType != nil && self.isGlobalListType != true) {
            userList = "true"
        }
        
        ListWebModel.getListItems(userList, userId: self.userId!, callback: { list in
            self.rows = list.map { item in
                let newCell = UITableViewCell()
                newCell.textLabel!.text = item
                return newCell
            }
            self.table.reloadData()
        })
    }
    
    func saveRows() {
        var userList = "false"
        if let listType = self.isGlobalListType {
            if (!listType) {
                userList = "true"
            }
        }
        let data:[String] = self.rows.map({ item in
            return item.textLabel!.text!
        })
        ListWebModel.setListItems(userList, userId: self.userId!, data: data)
    }
    
    // Add an item to the list
    func addItem(item: String) {
        let newCell = UITableViewCell()
        newCell.textLabel!.text = item
        self.rows.append(newCell)
        self.table.reloadData()
    }
    
    // Save a deletion to the list
    func tableView(tableView: UITableView,
        commitEditingStyle editingStyle: UITableViewCellEditingStyle,
        forRowAtIndexPath indexPath: NSIndexPath) {
            switch editingStyle {
            case .Delete:
                self.rows.removeAtIndex(indexPath.row)
                self.table.deleteRowsAtIndexPaths([indexPath], withRowAnimation: .Top)
            default:
                return
            }
            self.saveRows()
    }
    
    // Save a move to the list
    func tableView(tableView: UITableView,
        moveRowAtIndexPath sourceIndexPath: NSIndexPath,
        toIndexPath destinationIndexPath: NSIndexPath) {
            let val = self.rows.removeAtIndex(sourceIndexPath.row)
            self.rows.insert(val, atIndex: destinationIndexPath.row)
            self.saveRows()
    }
    
    // Set all items to be deletable
    func tableView(tableView: UITableView,
        editingStyleForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCellEditingStyle {
            return UITableViewCellEditingStyle.Delete
    }
    
    // Get item
    func tableView(tableView: UITableView,
        cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
            return rows[indexPath.row]
    }
    
    // Get number of rows
    func tableView(tableView: UITableView,
        numberOfRowsInSection section: Int) -> Int {
            if (section == 0) {
                return rows.count
            }  else {
                return 0
            }
    }
    
}