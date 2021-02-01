//
//  MapViewController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 16.11.2020.
//

import UIKit
import MapKit

final class MapViewController: UIViewController {
    @IBOutlet weak var mapView: MKMapView!
    @IBOutlet weak var searchButton: UIButton!
    @IBOutlet weak var layersButton: UIButton!
    @IBOutlet weak var layersStackView: UIStackView!
    
    fileprivate let locationManager = CLLocationManager()
    
    enum NavigationApps: String {
        case appleMaps = "Apple Maps"
        case googleMaps = "Google Maps"
        case waze = "Waze"
    }
    
    private let viewModel: MapViewModeling
    
    init?(coder: NSCoder, viewModel: MapViewModeling) {
        self.viewModel = viewModel
        super.init(coder: coder)
    }
    
    @available(*, unavailable, renamed: "init(coder:viewModel:)")
    required init?(coder: NSCoder) {
        self.viewModel = MapViewModel()
        super.init(coder: coder)
        //fatalError("You must create this view controller with a viewModel.")
    }
    
    var showAnnotationType = [
        "bucketlist": true,
        "visited": true,
        "": true
    ] {
        didSet {
            changeAnnotations()
            print("didSet")
        }
    }
    
    override func loadView() {
        super.loadView()
        
        self.navigationController!.navigationBar.setBackgroundImage(UIImage(), for: .default)
        self.navigationController!.navigationBar.shadowImage = UIImage()
        self.navigationController!.navigationBar.isTranslucent = true
        
        self.layersButton.layer.cornerRadius = 4.0
        self.layersButton.layer.masksToBounds = true
        
        self.searchButton.layer.cornerRadius = 4.0
        self.searchButton.layer.masksToBounds = true
        
        self.layersStackView.layer.cornerRadius = 4.0
        self.layersStackView.layer.masksToBounds = true
        
        locationManager.requestWhenInUseAuthorization()
        locationManager.desiredAccuracy = kCLLocationAccuracyBest
        locationManager.distanceFilter = kCLDistanceFilterNone
        locationManager.startUpdatingLocation()
        mapView.showsUserLocation = true
        
        viewModel.loadPreferences()
        viewModel.loadLighthouses()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        mapView.delegate = self
        
        for lighthouse in viewModel.lighthouses {
            var type = ""
            if viewModel.preferences.visited.contains(lighthouse.id) {
                type = "visited"
            } else if viewModel.preferences.bucketlist.contains(lighthouse.id) {
                type = "bucketlist"
            }
            let annotation = LighthouseAnnotation(
                    name: lighthouse.name,
                    location: lighthouse.location,
                    coordinate: CLLocationCoordinate2D(latitude: lighthouse.lat, longitude: lighthouse.lon),
                    image: lighthouse.image,
                    id: lighthouse.id,
                    type: type
            )
            self.mapView.addAnnotation(annotation)
        }
        mapView.register(LighthouseAnnotationView.self, forAnnotationViewWithReuseIdentifier: "LighthouseAnnotationView")
        
        self.mapView.showAnnotations(self.mapView.annotations, animated: true)
        
        self.centerOnUser()
    }
    
    @IBAction func layersButtonTapped(_ sender: UIButton) {
        self.layersStackView.isHidden = !self.layersStackView.isHidden
    }
    
    @IBAction func searchButtonTapped(_ sender: UIButton) {
        print("search button tapped")
    }
    
    @IBAction func bucketlistSwitchValueChanged(_ sender: UISwitch) {
        self.showAnnotationType["bucketlist"] = sender.isOn
        
    }
    
    @IBAction func visitedSwitchValueChanged(_ sender: UISwitch) {
        self.showAnnotationType["visited"] = sender.isOn
    }
    
    @IBAction func notvisitedSwitchValueChanged(_ sender: UISwitch) {
        self.showAnnotationType[""] = sender.isOn
    }
    
    func changeAnnotations() {
        for annotation in mapView.annotations {
            if let annotation = annotation as? LighthouseAnnotation {
                mapView.view(for: annotation)?.isHidden = !showAnnotationType[annotation.type!]!
            }
        }
    }
    
    func centerOnUser() {
        if let userLocation = locationManager.location?.coordinate {
            let viewRegion = MKCoordinateRegion(center: userLocation, latitudinalMeters: 20000, longitudinalMeters: 20000)
            mapView.setRegion(viewRegion, animated: true)
        }
    }
    
    @IBAction func locationButtonTapped(_ sender: UIButton) {
        self.centerOnUser()
    }
}

extension MapViewController: MKMapViewDelegate {
    func mapView(_ mapView: MKMapView, viewFor annotation: MKAnnotation) -> MKAnnotationView? {
        guard let annotation = annotation as? LighthouseAnnotation else { return nil }
        let lighthouseAnnotationView = mapView.dequeueReusableAnnotationView(withIdentifier: "LighthouseAnnotationView") as! LighthouseAnnotationView
        lighthouseAnnotationView.canShowCallout = true
        
        let btn = UIButton(type: .infoLight)
        btn.setImage(UIImage(systemName: "car.circle"), for: .normal)
        lighthouseAnnotationView.rightCalloutAccessoryView = btn
        lighthouseAnnotationView.displayPriority = .required
        lighthouseAnnotationView.isHidden = !showAnnotationType[annotation.type!]!
        return lighthouseAnnotationView
    }
    
    func mapView(_ mapView: MKMapView, annotationView view: MKAnnotationView, calloutAccessoryControlTapped control: UIControl) {
        guard let annotation = view.annotation as? LighthouseAnnotation else { return }
        openMapForLocation(annotation: annotation)
    }
    
    func mapView(_ mapView: MKMapView, didSelect view: MKAnnotationView) {
        self.mapView.setCenter(view.annotation!.coordinate, animated: true)
        guard let annotation = view.annotation as? LighthouseAnnotation else { return }
        guard viewModel.lighthouses.first(where: { $0.id == annotation.id }) != nil else { return }
        
        let gesture = UITapGestureRecognizer(target: self, action: #selector(MapViewController.calloutTapped(_:)))
        view.addGestureRecognizer(gesture)
    }
    
    @objc func calloutTapped(_ sender:UITapGestureRecognizer){
        guard let annotation = (sender.view as? MKAnnotationView)?.annotation as? LighthouseAnnotation else { return }
        guard let lighthouse = viewModel.lighthouses.first(where: { $0.id == annotation.id }) else { return }
        let vc = self.storyboard?.instantiateViewController(identifier: "detailVC") {
            return DetailViewController(coder: $0, viewModel: DetailViewModel(lighthouse: lighthouse, userData: UserData(type: annotation.type!)))
        }
        self.show(vc!, sender: self)
    }
    
    func openMapForLocation(annotation: LighthouseAnnotation) {
        let location = (latitude: annotation.coordinate.latitude, longitude: annotation.coordinate.longitude)
        let installedNavigationApps : [[String:String]] = [[NavigationApps.appleMaps.rawValue:""], [NavigationApps.googleMaps.rawValue:"comgooglemaps://"], [NavigationApps.waze.rawValue:"waze://"]]

        var alertAction: UIAlertAction?

        let alert = UIAlertController(title: "Select Navigation App", message: "Open in", preferredStyle: .actionSheet)

        for app in installedNavigationApps {
            let appName = app.keys.first
            if (appName == NavigationApps.appleMaps.rawValue ||
                appName == NavigationApps.googleMaps.rawValue || UIApplication.shared.canOpenURL(URL(string:app[appName!]!)!))
            {

                alertAction = UIAlertAction(title: appName, style: .default, handler: { (action) in
                    switch appName {
                    case NavigationApps.appleMaps.rawValue?:
                        let regionDistance:CLLocationDistance = 10000
                        let coordinates = CLLocationCoordinate2DMake(location.latitude, location.longitude)
                        let regionSpan = MKCoordinateRegion(center: coordinates, latitudinalMeters: regionDistance, longitudinalMeters: regionDistance)
                        let options = [
                            MKLaunchOptionsMapCenterKey: NSValue(mkCoordinate: regionSpan.center),
                            MKLaunchOptionsMapSpanKey: NSValue(mkCoordinateSpan: regionSpan.span)
                        ]
                        let placemark = MKPlacemark(coordinate: coordinates, addressDictionary: nil)
                        let mapItem = MKMapItem(placemark: placemark)
                        mapItem.name = annotation.title
                        mapItem.openInMaps(launchOptions: options)
                        break

                    case NavigationApps.googleMaps.rawValue?:
                        if UIApplication.shared.canOpenURL(URL(string:app[appName!]!)!) {
                            UIApplication.shared.open(URL(string:
                                "comgooglemaps://?saddr=&daddr=\(location.latitude),\(location.longitude)&directionsmode=driving")!)
                        } else {
                            let string = "https://maps.google.com/?q=@\(location.latitude),\(location.longitude)"
                            UIApplication.shared.open(URL(string: string)!)
                        }
                        break

                    case NavigationApps.waze.rawValue?:
                        if UIApplication.shared.canOpenURL(URL(string: app[appName!]!)!) {
                        UIApplication.shared.open(URL(string:
                            "waze://?ll=\(location.latitude),\(location.longitude)&navigate=yes")!)
                        } else {
                            UIApplication.shared.open(URL(string: "http://itunes.apple.com/us/app/id323229106")!)
                        }
                        break

                    default:
                        break
                    }
                })
                alert.addAction(alertAction!)
            }
            else
            {
                print("Can't open URL scheme")
            }
        }

        alertAction = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
        alert.addAction(alertAction!)

        self.present(alert, animated: true, completion: nil)
    }
}
