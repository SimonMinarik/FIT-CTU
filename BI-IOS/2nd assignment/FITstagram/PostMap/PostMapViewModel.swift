import Foundation
import CoreLocation
import UIKit

protocol PostMapViewModeling {
    var coordinate: CLLocationCoordinate2D { get }
    var locationTitle: String { get }
    var postImage: UIImage? { get }
}

final class PostMapViewModel: PostMapViewModeling {
    let coordinate: CLLocationCoordinate2D
    let locationTitle: String
    let postImage: UIImage?
    
    init(
        coordinate: CLLocationCoordinate2D,
        locationTitle: String,
        postImage: UIImage?
    ) {
        self.coordinate = coordinate
        self.locationTitle = locationTitle
        self.postImage = postImage
    }
}
