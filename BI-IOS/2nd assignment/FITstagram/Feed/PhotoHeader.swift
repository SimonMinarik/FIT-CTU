//
//  PhotoHeader.swift
//  FITstagram
//
//  Created by Jakub Olejník on 01.10.2020.
//

import UIKit

class PhotoHeader: UIView {
    weak var usernameLabel: UILabel!
    weak var locationButton: UIButton!
    
    var locationTapped: (() -> Void)?
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        setup()
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
        setup()
    }
    
    // MARK: - Private helpers
    
    private func setup() {
        let usernameLabel = UILabel()
        usernameLabel.translatesAutoresizingMaskIntoConstraints = false
        usernameLabel.text = "Username"
        usernameLabel.textAlignment = .center
        usernameLabel.font = .boldSystemFont(ofSize: 16)
        addSubview(usernameLabel)

        let margin = self.safeAreaLayoutGuide
        NSLayoutConstraint.activate([
            usernameLabel.leftAnchor.constraint(equalTo: margin.leftAnchor),
            usernameLabel.rightAnchor.constraint(equalTo: margin.rightAnchor),
            usernameLabel.topAnchor.constraint(equalTo: margin.topAnchor)
        ])

        self.usernameLabel = usernameLabel
        
        let locationButton = UIButton()
        locationButton.translatesAutoresizingMaskIntoConstraints = false
        locationButton.setTitle("Location", for: .normal)
        locationButton.setTitleColor(.black, for: .normal)
        locationButton.titleLabel?.textAlignment = .center
        locationButton.titleLabel?.font = .systemFont(ofSize: 14)
        locationButton.addTarget(self, action: #selector(locationButtonTapped), for: .touchUpInside)
        addSubview(locationButton)
        NSLayoutConstraint.activate([
            locationButton.topAnchor.constraint(equalTo: usernameLabel.bottomAnchor),
            locationButton.centerXAnchor.constraint(equalTo: margin.centerXAnchor),
            locationButton.bottomAnchor.constraint(equalTo: bottomAnchor),
        ])
        self.locationButton = locationButton
    }
    
    @objc
    private func locationButtonTapped() {
        locationTapped?()
    }
}
