import Foundation
import MapKit

final class PostMapViewController: UIViewController {
    
    private weak var mapView: MKMapView!
    
    private let locationManager = CLLocationManager()
    private let viewModel: PostMapViewModeling
    
    // MARK: - Initialization
    
    init(viewModel: PostMapViewModeling) {
        self.viewModel = viewModel
        super.init(nibName: nil, bundle: nil)
    }
    
    @available(*, unavailable)
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
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
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let postLocationAnnotation = PostLocationAnnotation(
            coordinate: viewModel.coordinate,
            title: viewModel.locationTitle,
            subtitle: viewModel.locationTitle
        )
        mapView.addAnnotation(
            postLocationAnnotation
        )
        
        mapView.register(PostLocationAnnotationView.self, forAnnotationViewWithReuseIdentifier: "PostLocationAnnotationView")
        
        mapView.delegate = self

        locationManager.requestWhenInUseAuthorization()
        mapView.showsUserLocation = true
        
        mapView.setRegion(
            MKCoordinateRegion(
                center: viewModel.coordinate,
                span: MKCoordinateSpan(latitudeDelta: 0.5, longitudeDelta: 0.5)
            ),
            animated: true
        )
    }
}
extension PostMapViewController: MKMapViewDelegate {
    func mapView(_ mapView: MKMapView, viewFor annotation: MKAnnotation) -> MKAnnotationView? {
        guard !(annotation is MKUserLocation) else { return nil }
        let postLocationAnnotationView = mapView.dequeueReusableAnnotationView(
            withIdentifier: "PostLocationAnnotationView"
        ) as! PostLocationAnnotationView
        postLocationAnnotationView.canShowCallout = true
        postLocationAnnotationView.postImage = viewModel.postImage
        return postLocationAnnotationView
    }
}
