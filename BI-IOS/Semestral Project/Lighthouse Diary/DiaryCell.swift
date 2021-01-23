//
//  DiaryCell.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 16.11.2020.
//

import UIKit

class DiaryCell: UITableViewCell {
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var visitedLabel: UILabel!
    @IBOutlet weak var infoButton: UIButton!
    @IBOutlet weak var lighthouseImageView: UIImageView!
    
    struct info {
        let name: String
        let image: String
        let visited: String
    }
}
