//
//  PostsLocationAnnotation.swift
//  FITstagram
//
//  Created by Šimon Minárik on 13.12.2020.
//

import Foundation
import MapKit

final class PostsLocationAnnotation: NSObject, MKAnnotation {
    let coordinate: CLLocationCoordinate2D
    let title: String?
    let subtitle: String?
    let image: UIImage?
    
    init(
        coordinate: CLLocationCoordinate2D,
        title: String?,
        subtitle: String?,
        image: UIImage?
    ) {
        self.coordinate = coordinate
        self.title = title
        self.subtitle = subtitle
        self.image = image
    }
}
