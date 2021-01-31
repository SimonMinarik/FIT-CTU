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
        //btn.addTarget(self, action: #selector(buttonTap), for: .touchUpInside)
        lighthouseAnnotationView.rightCalloutAccessoryView = btn
        lighthouseAnnotationView.displayPriority = .required
        lighthouseAnnotationView.isHidden = !showAnnotationType[annotation.type!]!
        return lighthouseAnnotationView
    }
    
    @objc func buttonTap(){
        let alert = UIAlertController(title: "Did it work?", message: "No..", preferredStyle: .alert)

        alert.addAction(UIAlertAction(title: "No", style: .default, handler: nil))
        alert.addAction(UIAlertAction(title: "No", style: .cancel, handler: nil))

        self.present(alert, animated: true)
    }
    
    func mapView(_ mapView: MKMapView, annotationView view: MKAnnotationView, calloutAccessoryControlTapped control: UIControl) {
        guard let annotation = view.annotation as? LighthouseAnnotation else { return }
        guard let lighthouse = viewModel.lighthouses.first(where: { $0.id == annotation.id }) else { return }
        let vc = self.storyboard?.instantiateViewController(identifier: "detailVC") {
            return DetailViewController(coder: $0, viewModel: DetailViewModel(lighthouse: lighthouse))
        }
        self.show(vc!, sender: self)
    }
    
    func mapView(_ mapView: MKMapView, didSelect view: MKAnnotationView) {
        self.mapView.setCenter(view.annotation!.coordinate, animated: true)
    }
}
