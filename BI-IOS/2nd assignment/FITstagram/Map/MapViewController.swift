//
//  MapViewController.swift
//  FITstagram
//
//  Created by Šimon Minárik on 12.12.2020.
//

import UIKit
import MapKit

final class MapViewController: UIViewController {
    
    private let viewModel: MapViewModeling
    private weak var mapView: MKMapView!
    
    // MARK: - Initialization
    
    init(viewModel: MapViewModeling) {
        self.viewModel = viewModel
        
        super.init(nibName: nil, bundle: nil)
    }
    
    @available(*, unavailable)
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // MARK: - Lifecycle
    
    override func loadView() {
        super.loadView()
        
        let mapView = MKMapView()
        mapView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(mapView)
        NSLayoutConstraint.activate([
            mapView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            mapView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            mapView.bottomAnchor.constraint(equalTo: view.bottomAnchor),
            mapView.topAnchor.constraint(equalTo: view.topAnchor),
        ])
        self.mapView = mapView
        
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        print("ViewWillAppear")

        viewModel.loadPhotos()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        print("ViewDidAppear")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        mapView.delegate = self
        
        viewModel.viewModelDidChange = { [weak self] viewModel in
            print("did change")
            for post in viewModel.posts {
                let annotation = PostAnnotation(
                    author: post.author,
                    locationName: post.location,
                    image: post.image,
                    coordinate: CLLocationCoordinate2D(latitude: post.lat!, longitude: post.lon!),
                    postId: post.id)
                self?.mapView.addAnnotation(annotation)
            }
            guard let annotations = self?.mapView.annotations else { return }
            self?.mapView.showAnnotations(annotations, animated: true)
        }
    }
}

extension MapViewController: MKMapViewDelegate {
    func mapView(
        _ mapView: MKMapView,
        viewFor annotation: MKAnnotation
    ) -> MKAnnotationView? {
        guard let annotation = annotation as? PostAnnotation else {
            return nil
        }
        let identifier = "annotation"
        var view: MKMarkerAnnotationView
        if let dequeuedView = mapView.dequeueReusableAnnotationView(
            withIdentifier: identifier) as? MKMarkerAnnotationView {
            dequeuedView.annotation = annotation
            view = dequeuedView
            view.glyphImage = UIImage(systemName: "camera")
        } else {
            view = MKMarkerAnnotationView(
                annotation: annotation,
                reuseIdentifier: identifier)
            view.canShowCallout = true
            let btn = UIButton(type: .detailDisclosure)
            btn.setImage(UIImage(systemName: "chevron.right"), for: .normal)
            view.rightCalloutAccessoryView = btn
            view.glyphImage = UIImage(systemName: "camera")
            
            let imageView = UIImageView(frame: CGRect(x: 0, y: 0, width: 50, height: 50))
            imageView.image = annotation.image
            view.leftCalloutAccessoryView = imageView
        }
        return view
    }
    
    func mapView(_ mapView: MKMapView, didSelect view: MKAnnotationView) {
        self.mapView.setCenter(view.annotation!.coordinate, animated: true)
    }
    
    func mapView(
        _ mapView: MKMapView,
        annotationView view: MKAnnotationView,
        calloutAccessoryControlTapped control: UIControl
        ) {
        if control == view.rightCalloutAccessoryView {
            guard let annotation = view.annotation as? PostAnnotation else {
                return
            }
            
            let storyboard = UIStoryboard(name: "Main", bundle: nil)
            let controller = storyboard.instantiateViewController(identifier: "FeedViewController") {
                FeedViewController(coder: $0, viewModel: FeedViewModel(postId: annotation.postId!))
            }
            let navigationController = UINavigationController(rootViewController: controller)
            present(navigationController, animated: true)
        }
    }
}
