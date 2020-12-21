//
//  PostAnnotation.swift
//  FITstagram
//
//  Created by Šimon Minárik on 13.12.2020.
//

import Foundation
import MapKit

class PostAnnotation: NSObject, MKAnnotation {
    let title: String?
    let subtitle: String?
    let coordinate: CLLocationCoordinate2D
    let image: UIImage?
    let postId: Int?

    init(
        author: String?,
        locationName: String?,
        image: UIImage?,
        coordinate: CLLocationCoordinate2D,
        postId: Int?
    ) {
        self.title = author
        self.subtitle = locationName
        self.image = image
        self.coordinate = coordinate
        self.postId = postId
        
        super.init()
  }
}
