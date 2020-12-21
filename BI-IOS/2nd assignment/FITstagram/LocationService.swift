import CoreLocation

protocol LocationServicing {
    func closestPlacemark(for coordinate: CLLocationCoordinate2D, completion: @escaping (CLPlacemark?) -> Void)
}

final class LocationService: LocationServicing {
    func closestPlacemark(for coordinate: CLLocationCoordinate2D, completion: @escaping (CLPlacemark?) -> Void) {
        let geocoder = CLGeocoder()
        let location = CLLocation(latitude: coordinate.latitude, longitude: coordinate.longitude)
        geocoder.reverseGeocodeLocation(location) { (placemarks, error) in
            if let error = error {
                print(error)
            }
            completion(placemarks?.first)
        }
    }
}

