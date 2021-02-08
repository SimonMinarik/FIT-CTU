//
//  DetailMapViewController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit
import MapKit

final class DetailMapViewController: UIViewController {
    
    @IBOutlet weak var mapView: MKMapView!
    
    private let viewModel: DetailMapViewModeling
    
    // MARK: - Initialization
    
    init?(coder: NSCoder, viewModel: DetailMapViewModeling) {
        self.viewModel = viewModel
        super.init(coder: coder)
    }
    
    @available(*, unavailable)
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // MARK: - Life cycle
    
    override func viewDidLoad() {
        super.viewDidLoad()
        mapView.delegate = self
        let annotation = MKPointAnnotation()
        annotation.title = viewModel.name
        annotation.coordinate = viewModel.coordinate
        self.mapView.addAnnotation(annotation)
        
        self.mapView.showAnnotations(self.mapView.annotations, animated: true)
        mapView.setRegion(MKCoordinateRegion(center: viewModel.coordinate, latitudinalMeters: 10000, longitudinalMeters: 10000), animated: true)
    }
    
    // MARK: - Actions
    
    @IBAction func cancelButtonTapped(_ sender: UIBarButtonItem) {
        self.dismiss(animated: true)
    }
}

extension DetailMapViewController: MKMapViewDelegate {
    func mapView(_ mapView: MKMapView, viewFor annotation: MKAnnotation) -> MKAnnotationView? {
        guard annotation is MKPointAnnotation else { return nil }

        let identifier = "Annotation"
        var annotationView = mapView.dequeueReusableAnnotationView(withIdentifier: identifier)

        if annotationView == nil {
            annotationView = MKPinAnnotationView(annotation: annotation, reuseIdentifier: identifier)
            annotationView!.canShowCallout = true
        } else {
            annotationView!.annotation = annotation
        }

        return annotationView
    }
}
