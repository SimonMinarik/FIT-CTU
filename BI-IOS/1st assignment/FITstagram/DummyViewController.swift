//
//  DummyViewController.swift
//  FITstagram
//
//  Created by Lukáš Hromadník on 17/10/2020.
//

import UIKit

final class DummyViewController: UIViewController {
    let color: UIColor
    
    init(color: UIColor) {
        self.color = color
        print(#function)
        
        super.init(nibName: nil, bundle: nil)
    }
    
    @available(*, unavailable)
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    deinit {
        print(#function)
    }
    
    // MARK: - Lifecycle
    
    override func loadView() {
        super.loadView()
        print(#function)
        
        view.backgroundColor = color
        
        let button = UIButton(type: .system)
        button.setTitle("Dismiss", for: .normal)
        button.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(button)
        NSLayoutConstraint.activate([
            button.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            button.centerYAnchor.constraint(equalTo: view.centerYAnchor),
        ])
        
        button.addTarget(self, action: #selector(dismissTapped), for: .touchUpInside)
    }
    
//    override func viewDidLoad() {
//        super.viewDidLoad()
//        
//        print(#function)
//    }
//    
//    override func viewWillAppear(_ animated: Bool) {
//        super.viewWillAppear(animated)
//        
//        print(#function)
//    }
//    
//    override func viewDidAppear(_ animated: Bool) {
//        super.viewDidAppear(animated)
//        
//        print(#function)
//    }
//    
//    override func viewWillDisappear(_ animated: Bool) {
//        super.viewWillDisappear(animated)
//        
//        print(#function)
//    }
//    
//    override func viewDidDisappear(_ animated: Bool) {
//        super.viewDidDisappear(animated)
//        
//        print(#function)
//    }
    
    @objc private func dismissTapped() {
        dismiss(animated: true)
    }
}
