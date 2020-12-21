//
//  CreateViewModel.swift
//  FITstagram
//
//  Created by Lukáš Hromadník on 11/11/2020.
//

import UIKit
import CoreLocation

protocol CreateViewModeling: AnyObject {
    var caption: String { get set }
    var image: UIImage? { get set }
    var locationName: String? { get }
    var locationImage: UIImage? { get }
    var locationState: LocationState { get }
    var viewModelDidChange: (CreateViewModeling) -> Void { get set }
    
    func createPost(completion: @escaping (Bool) -> Void)
    func showLocation(_ coordinate: CLLocationCoordinate2D)
    func removeUserLocation()
}

enum LocationState {
    case shown
    case notShown
}

final class CreateViewModel: CreateViewModeling {
    var caption = ""
    var locationState: LocationState = .notShown
    var image: UIImage? {
        didSet {
            self.viewModelDidChange(self)
        }
    }
    
    var locationName: String? {
        didSet {
            self.viewModelDidChange(self)
        }
    }
    
    var locationImage: UIImage? = UIImage(systemName: "location.fill") {
        didSet {
            self.viewModelDidChange(self)
        }
    }
    
    var viewModelDidChange: (CreateViewModeling) -> Void = { _ in }
    
    private var username: String {
        UserDefaults.standard.string(forKey: "username") ?? "username"
    }
    
    private var currentLocationCoordinate: CLLocationCoordinate2D? = nil
    
    private let networkService: NetworkServicing
    private let locationService: LocationServicing
    
    // MARK: - Initialization
    
    init(
        networkService: NetworkServicing = NetworkService(),
        locationService: LocationServicing = LocationService()
    ) {
        self.networkService = networkService
        self.locationService = locationService
    }
    
    // MARK: - Public methods
    
    func createPost(completion: @escaping (Bool) -> Void) {
        var urlRequest = URLRequest(url: URL(string: "https://ackeeedu.000webhostapp.com/api.php/records/posts")!)
        urlRequest.allHTTPHeaderFields = ["Content-Type": "application/json"]
        urlRequest.httpMethod = "POST"
        
        let maxSize = UIScreen.main.bounds.width/UIScreen.main.scale
        let resizedImage = image?.imageResized(to: CGSize(width: maxSize, height: maxSize))
        
        let body: [String: Any?] = [
            "image": resizedImage?.jpegData(compressionQuality: 0.5)?.base64EncodedString(),
            "username": username,
            "caption": caption,
            "lat": currentLocationCoordinate?.latitude,
            "lon": currentLocationCoordinate?.longitude,
            "location": locationName
        ]
        urlRequest.httpBody = try! JSONSerialization.data(withJSONObject: body)
        
        networkService.fetch(urlRequest: urlRequest) { result in
            switch result {
            case .success:
                completion(true)
            
            case .failure:
                completion(false)
            }
        }
    }
    
    func showLocation(_ coordinate: CLLocationCoordinate2D) {
        locationService.closestPlacemark(for: coordinate) { [weak self] in
            if let placemark = $0 {
                self?.currentLocationCoordinate = coordinate
                self?.locationName = placemark.subLocality
                self?.locationImage = UIImage(systemName: "trash.fill")
                self?.locationState = .shown
            } else {
                self?.removeUserLocation()
            }
        }
    }
    
    func removeUserLocation() {
        currentLocationCoordinate = nil
        locationState = .notShown
        locationName = "No location"
        locationImage = UIImage(systemName: "location.fill")
    }
}

