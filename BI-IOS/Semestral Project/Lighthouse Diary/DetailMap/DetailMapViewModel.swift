//
//  DetailMapViewModel.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit
import CoreLocation

protocol DetailMapViewModeling: AnyObject {
    var coordinate: CLLocationCoordinate2D { get }
    var name: String { get }
}

final class DetailMapViewModel: DetailMapViewModeling {
    let coordinate: CLLocationCoordinate2D
    let name: String
    
    init(
        coordinate: CLLocationCoordinate2D,
        name: String
    ) {
        self.coordinate = coordinate
        self.name = name
    }
}
