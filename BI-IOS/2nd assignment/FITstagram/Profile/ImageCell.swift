//
//  ImageCell.swift
//  FITstagram
//
//  Created by Jakub Olejník on 28.10.2020.
//

import UIKit

struct ImageConfiguration: UIContentConfiguration {
    let image: UIImage
    
    func makeContentView() -> UIView & UIContentView {
        ImageContentView(configuration: self)
    }
    
    func updated(for state: UIConfigurationState) -> ImageConfiguration {
        self
    }
}

private final class ImageContentView: UIView, UIContentView {
    var configuration: UIContentConfiguration {
        didSet {
            guard let imageConfiguration = configuration as? ImageConfiguration else { return }
            apply(imageConfiguration)
        }
    }
    
    private var imageView: UIImageView!
    
    // MARK: - Initializers
    
    init(configuration: ImageConfiguration) {
        self.configuration = configuration
        super.init(frame: .zero)
        
        let imageView = UIImageView()
        imageView.translatesAutoresizingMaskIntoConstraints = false
        imageView.clipsToBounds = true
        imageView.contentMode = .scaleAspectFill
        addSubview(imageView)
        NSLayoutConstraint.activate([
            imageView.leadingAnchor.constraint(equalTo: leadingAnchor),
            imageView.topAnchor.constraint(equalTo: topAnchor),
            imageView.bottomAnchor.constraint(equalTo: bottomAnchor),
            imageView.trailingAnchor.constraint(equalTo: trailingAnchor),
        ])
        self.imageView = imageView
        
        apply(configuration)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // MARK: - Private helpers
    
    private func apply(_ configuration: ImageConfiguration) {
        imageView.image = configuration.image
    }
}
