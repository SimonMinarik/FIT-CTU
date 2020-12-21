//
//  PostsMapViewModel.swift
//  FITstagram
//
//  Created by Šimon Minárik on 13.12.2020.
//

import Foundation
import CoreLocation
import UIKit

protocol PostsMapViewModeling {
    var coordinate: CLLocationCoordinate2D { get }
    var locationTitle: String { get }
    var author: String { get }
    var postImage: UIImage? { get }
}

final class PostsMapViewModel: PostsMapViewModeling {
    let coordinate: CLLocationCoordinate2D
    let locationTitle: String
    let author: String
    let postImage: UIImage?
    
    init(
        coordinate: CLLocationCoordinate2D,
        locationTitle: String,
        author: String,
        postImage: UIImage?
    ) {
        self.coordinate = coordinate
        self.locationTitle = locationTitle
        self.author = author
        self.postImage = postImage
    }
}
