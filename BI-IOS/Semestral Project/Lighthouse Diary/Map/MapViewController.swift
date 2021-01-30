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
    @IBOutlet weak var bucketlistSwitch: UISwitch!
    @IBOutlet weak var visitedSwitch: UISwitch!
    @IBOutlet weak var notvisitedSwitch: UISwitch!
    
    fileprivate let locationManager = CLLocationManager()
    
    let viewModel: MapViewModeling
    
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
        self.mapView.showAnnotations(self.mapView.annotations, animated: true)
        
        self.centerOnUser()
    }
    
    @IBAction func layersButtonTapped(_ sender: UIButton) {
        self.layersStackView.isHidden = !self.layersStackView.isHidden
    }
    
    @IBAction func searchButtonTapped(_ sender: UIButton) {
        print("search button tapped")
    }
    
    @IBAction func bucketlistSwitchTapped(_ sender: UISwitch) {
        self.showAnnotationType["bucketlist"] = sender.isOn
        
    }
    
    @IBAction func visitedSwitchTapped(_ sender: UISwitch) {
        self.showAnnotationType["visited"] = sender.isOn
    }
    
    @IBAction func notvisitedSwitchTapped(_ sender: UISwitch) {
        self.showAnnotationType[""] = sender.isOn
    }
    
    func changeAnnotations() {
        for annotation in mapView.annotations {
            guard let annotation = annotation as? LighthouseAnnotation else {
                break
            }
            mapView.view(for: annotation)?.isHidden = !showAnnotationType[annotation.type!]!
        }
    }
    
    func centerOnUser() {
        if let userLocation = locationManager.location?.coordinate {
            let viewRegion = MKCoordinateRegion(center: userLocation, latitudinalMeters: 20000, longitudinalMeters: 20000)
            mapView.setRegion(viewRegion, animated: true)
        }
    }
    
    func setAnnotationType(annotationView: MKMarkerAnnotationView, type: String){
        switch type {
        case "visited":
            annotationView.markerTintColor = .yellow
            break
        case "bucketlist":
            annotationView.markerTintColor = .green
            break
        default:
            break
        }
    }
    
    @IBAction func locationButtonTapped(_ sender: UIButton) {
        self.centerOnUser()
    }
}

extension MapViewController: MKMapViewDelegate {
    func mapView(
        _ mapView: MKMapView,
        viewFor annotation: MKAnnotation
    ) -> MKAnnotationView? {
        guard let annotation = annotation as? LighthouseAnnotation else {
            return nil
        }
        let identifier = "annotation"
        var view: MKMarkerAnnotationView
        if let dequeuedView = mapView.dequeueReusableAnnotationView(
            withIdentifier: identifier) as? MKMarkerAnnotationView {
            dequeuedView.annotation = annotation
            dequeuedView.titleVisibility = .hidden
            dequeuedView.displayPriority = .required
            view = dequeuedView
            view.glyphImage = UIImage(systemName: "lightbulb")
            setAnnotationType(annotationView: view, type: annotation.type!)
            view.isHidden = !showAnnotationType[annotation.type!]!
        } else {
            view = MKMarkerAnnotationView(
                annotation: annotation,
                reuseIdentifier: identifier)
            view.canShowCallout = true
            let btn = UIButton(type: .detailDisclosure)
            btn.setImage(UIImage(systemName: "car.circle"), for: .normal)
            view.rightCalloutAccessoryView = btn
            let imageView = UIImageView(frame: CGRect(x: 0, y: 0, width: 50, height: 50))
            imageView.image = annotation.image
            view.leftCalloutAccessoryView = imageView
        }
        return view
    }
    
    func mapView(_ mapView: MKMapView, didSelect view: MKAnnotationView) {
        self.mapView.setCenter(view.annotation!.coordinate, animated: true)
    }
    
    func mapView(_ mapView: MKMapView, annotationView view: MKAnnotationView, calloutAccessoryControlTapped control: UIControl) {
        guard let annotation = view.annotation as? LighthouseAnnotation else { return }
        guard let lighthouse = viewModel.lighthouses.first(where: { $0.id == annotation.id }) else { return }
        let vc = self.storyboard?.instantiateViewController(identifier: "detailVC") {
            return DetailViewController(coder: $0, viewModel: DetailViewModel(lighthouse: lighthouse))
        }
        self.show(vc!, sender: self)
    }
}
