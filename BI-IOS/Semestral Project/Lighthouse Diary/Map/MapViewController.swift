//
//  MapViewController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 16.11.2020.
//

import UIKit
import MapKit

class MapViewController: UIViewController {
    @IBOutlet weak var mapView: MKMapView!
    @IBOutlet weak var searchButton: UIButton!
    @IBOutlet weak var layersButton: UIButton!
    @IBOutlet weak var layersStackView: UIStackView!
    @IBOutlet weak var bucketlistSwitch: UISwitch!
    @IBOutlet weak var visitedSwitch: UISwitch!
    @IBOutlet weak var notvisitedSwitch: UISwitch!
    
    fileprivate let locationManager = CLLocationManager()
    
    let lighthouseDB:[(name: String, location: String, coordinate: CLLocationCoordinate2D, image: UIImage, id: Int)] = [
        ("Lighthouse Arkona", "Puttgarten, Germany", CLLocationCoordinate2D(latitude: CLLocationDegrees(54.679564), longitude: CLLocationDegrees(13.432574)), UIImage(named: "612664395a40232133447d33247d38313233393434333331.jpeg")!, 1),
        ("Lighthouse Busum", "Busum, Germany", CLLocationCoordinate2D(latitude: CLLocationDegrees(54.126885), longitude: CLLocationDegrees(8.858477)), UIImage(named: "leuchtturm-busum.jpg")!, 2),
        ("Lighthouse Darsser", "Born auf dem Darß, Germany", CLLocationCoordinate2D(latitude: CLLocationDegrees(54.472806), longitude: CLLocationDegrees(12.502328)), UIImage(named: "lighthouse-at-darsser-ort-with-museum-called-natureum-on-the-darss-peninsula-western-pomerania-lagoon-area-national-park-germany-R3PD9B.jpg")!, 3)
    ]
    
    let userVisited:[Int] = [1]
    let userBucketlist:[Int] = [2]
    
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
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        mapView.delegate = self
        
        for lighthouse in lighthouseDB {
            var type = ""
            if self.userVisited.contains(lighthouse.id) {
                type = "visited"
            } else if self.userBucketlist.contains(lighthouse.id) {
                type = "bucketlist"
            }
            let annotation = LighthouseAnnotation(
                    name: lighthouse.name,
                    location: lighthouse.location,
                    coordinate: lighthouse.coordinate,
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
        changeAnnotations(type: "bucketlist", show: !sender.isOn)
    }
    
    @IBAction func visitedSwitchTapped(_ sender: UISwitch) {
        changeAnnotations(type: "visited", show: !sender.isOn)
    }
    
    @IBAction func notvisitedSwitchTapped(_ sender: UISwitch) {
        changeAnnotations(type: "", show: !sender.isOn)
    }
    
    func changeAnnotations(type: String, show: Bool) {
        for annotation in mapView.annotations {
            guard let annotation = annotation as? LighthouseAnnotation else {
                break
            }
            if annotation.type == type {
                mapView.view(for: annotation)?.isHidden = show
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
            view = dequeuedView
            view.glyphImage = UIImage(systemName: "lightbulb")
            switch annotation.type {
            case "visited":
                view.markerTintColor = .yellow
                break
            case "bucketlist":
                view.markerTintColor = .green
                break
            default:
                break
            }
        } else {
            view = MKMarkerAnnotationView(
                annotation: annotation,
                reuseIdentifier: identifier)
            view.canShowCallout = true
            let btn = UIButton(type: .detailDisclosure)
            btn.setImage(UIImage(systemName: "chevron.right"), for: .normal)
            view.rightCalloutAccessoryView = btn
            view.glyphImage = UIImage(systemName: "lightbulb")
            switch annotation.type {
            case "visited":
                view.markerTintColor = .yellow
                break
            case "bucketlist":
                view.markerTintColor = .green
                break
            default:
                break
            }
            
            let imageView = UIImageView(frame: CGRect(x: 0, y: 0, width: 50, height: 50))
            imageView.image = annotation.image
            view.leftCalloutAccessoryView = imageView
        }
        return view
    }
    
    func mapView(_ mapView: MKMapView, didSelect view: MKAnnotationView) {
        self.mapView.setCenter(view.annotation!.coordinate, animated: true)
    }
}
