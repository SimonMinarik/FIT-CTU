//
//  PostCell.swift
//  FITstagram
//
//  Created by Jakub Olejník on 28.10.2020.
//

import UIKit

class PostCell: UITableViewCell {
    @IBOutlet weak var personButton: UIButton!
    @IBOutlet weak var photoHeader: PhotoHeader!
    @IBOutlet weak var followButton: UIButton!
    @IBOutlet weak var photoImageView: UIImageView!
    @IBOutlet weak var likeButton: LikeButton!
    @IBOutlet weak var descriptionLabel: UILabel!
    
    var personTapped: (() -> (Void))?
    
    var post: Post? {
        didSet {
            photoHeader.usernameLabel.text = post?.author
            photoHeader.locationButton.setTitle(post?.location, for: .normal)
            photoImageView.image = post?.image
            descriptionLabel.text = post?.caption
            followButton.isSelected = false
            likes = 0
            followButton.isHidden = post?.author == UserDefaults.standard.string(forKey: "username")
        }
    }
    
    private var likes = 0 {
        didSet {
            likeButton.setTitle("\(likes) likes", for: .normal)
        }
    }
    
    @IBAction func followButtonTapped(_ sender: UIButton) {
        sender.isSelected = !sender.isSelected
    }
    
    @IBAction func personButtonTapped(_ sender: Any) {
        personTapped?()
    }
    
    @IBAction func likeButtonTapped(_ sender: Any) {
        likes += 1
    }
}
