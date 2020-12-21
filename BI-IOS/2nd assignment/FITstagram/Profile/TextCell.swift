//
//  TextCell.swift
//  FITstagram
//
//  Created by Lukáš Hromadník on 30/10/2020.
//

import UIKit

struct TextConfiguration: UIContentConfiguration {
    let text: String

    func makeContentView() -> UIView & UIContentView {
        TextContentView(configuration: self)
    }
    
    func updated(for state: UIConfigurationState) -> TextConfiguration {
        self
    }
}

final class TextContentView: UIView, UIContentView {
    var configuration: UIContentConfiguration {
        didSet {
            guard let textConfiguration = configuration as? TextConfiguration else { return }
            apply(textConfiguration)
        }
    }
    
    private var textLabel: UILabel!
    
    // MARK: - Initializers
    
    init(configuration: TextConfiguration) {
        self.configuration = configuration
        
        super.init(frame: .zero)
        
        let textLabel = UILabel()
        textLabel.translatesAutoresizingMaskIntoConstraints = false
        textLabel.numberOfLines = 0
        addSubview(textLabel)
        NSLayoutConstraint.activate([
            textLabel.topAnchor.constraint(equalTo: topAnchor),
            textLabel.leadingAnchor.constraint(equalTo: leadingAnchor, constant: 16),
            textLabel.bottomAnchor.constraint(equalTo: bottomAnchor),
            textLabel.trailingAnchor.constraint(equalTo: trailingAnchor, constant: -16)
        ])
        self.textLabel = textLabel
        
        apply(configuration)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // MARK: - Helpers
    
    private func apply(_ configuration: TextConfiguration) {
        textLabel.text = configuration.text
    }
}
