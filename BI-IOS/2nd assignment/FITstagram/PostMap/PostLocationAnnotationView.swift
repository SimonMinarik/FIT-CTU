import Foundation
import UIKit
import MapKit

final class PostLocationAnnotationView: MKAnnotationView {
    var postImage: UIImage? {
        get { postImageView.image }
        set { postImageView.image = newValue }
    }
    
    private weak var postImageView: UIImageView!
    
    override init(annotation: MKAnnotation?, reuseIdentifier: String?) {
        super.init(annotation: annotation, reuseIdentifier: reuseIdentifier)
        translatesAutoresizingMaskIntoConstraints = false
        
        let imageView = UIImageView(image: UIImage(systemName: "mappin.and.ellipse"))
        imageView.translatesAutoresizingMaskIntoConstraints = false
        addSubview(imageView)
        NSLayoutConstraint.activate([
            imageView.leadingAnchor.constraint(equalTo: leadingAnchor),
            imageView.trailingAnchor.constraint(equalTo: trailingAnchor),
            imageView.bottomAnchor.constraint(equalTo: bottomAnchor),
            imageView.topAnchor.constraint(equalTo: topAnchor),
            imageView.heightAnchor.constraint(equalToConstant: 40),
            imageView.widthAnchor.constraint(equalToConstant: 40),
        ])
        
        let postImageView = UIImageView()
        postImageView.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            postImageView.heightAnchor.constraint(equalToConstant: 100),
            postImageView.widthAnchor.constraint(equalToConstant: 100),
        ])
        self.postImageView = postImageView
    
                
        detailCalloutAccessoryView = postImageView
        rightCalloutAccessoryView = UIButton(type: .infoDark)
    }
    
    @available(*, unavailable)
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
