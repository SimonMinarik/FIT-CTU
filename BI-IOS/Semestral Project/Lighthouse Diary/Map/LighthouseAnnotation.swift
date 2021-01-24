//
//  LighthouseAnnotation.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 24.01.2021.
//

import Foundation
import MapKit

final class LighthouseAnnotation: NSObject, MKAnnotation {
    let title: String?
    let subtitle: String?
    let coordinate: CLLocationCoordinate2D
    let image: UIImage?
    let id: Int?
    let type: String?
    
    init(
        name: String?,
        location: String?,
        coordinate: CLLocationCoordinate2D,
        image: UIImage?,
        id: Int?,
        type: String?
        ) {
        self.title = name
        self.subtitle = location
        self.coordinate = coordinate
        self.image = image
        self.id = id
        self.type = type
    }
}
