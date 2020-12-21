//
//  CreateViewController.swift
//  FITstagram
//
//  Created by Lukáš Hromadník on 26/10/2020.
//

import UIKit
import MapKit

final class CreateViewController: UIViewController {
    @IBOutlet weak var locationButton: UIButton!
    @IBOutlet weak var selectPhotoButton: UIButton!
    @IBOutlet weak var textView: UITextView!
    @IBOutlet weak var locationLabel: UILabel!
    @IBOutlet weak var imageView: UIImageView!
    
    private let viewModel: CreateViewModeling
    private let locationManager = CLLocationManager()
    private var requestLocation = false
    
    // MARK: - Initialization
    
    init?(coder: NSCoder, viewModel: CreateViewModeling) {
        self.viewModel = viewModel
        super.init(coder: coder)
    }
    
    @available(*, unavailable)
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // MARK: - Lifecycle
    
    override func loadView() {
        super.loadView()
        
        imageView.layer.cornerRadius = 4
        imageView.layer.borderWidth = 1
        imageView.layer.borderColor = UIColor.darkGray.cgColor
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        textView.delegate = self
        locationManager.delegate = self
        
        viewModel.viewModelDidChange = { [weak self] viewModel in
            DispatchQueue.main.async {
                self?.selectPhotoButton.isHidden = viewModel.image != nil
                self?.imageView.image = viewModel.image
                self?.locationLabel.text = viewModel.locationName
                self?.locationButton.setImage(viewModel.locationImage, for: .normal)
            }
        }
    }
    
    // MARK: - Actions
    
    @IBAction func cancelTapped() {
        dismiss(animated: true)
    }
    
    @IBAction func createTapped() {
        print(textView.text ?? "")
        view.endEditing(true)
        
        viewModel.createPost { success in
            if success {
                DispatchQueue.main.async { [weak self] in
                    self?.dismiss(animated: true)
                }
            }
        }
    }
    
    @IBAction func selectPhotoTapped() {
        let imagePicker = UIImagePickerController()
        imagePicker.sourceType = .photoLibrary
        imagePicker.delegate = self
        present(imagePicker, animated: true)
    }
    
    @IBAction func locationTapped() {
        switch viewModel.locationState {
        case .shown:
            viewModel.removeUserLocation()
        case .notShown:
            requestUserLocation()
        }
    }
    
    private func requestUserLocation() {
        switch locationManager.authorizationStatus {
        case .notDetermined:
            requestLocation = true
            locationManager.requestWhenInUseAuthorization()
        case .restricted, .denied:
            print("I need location!")
        case .authorizedAlways, .authorizedWhenInUse:
            locationManager.requestLocation()
        @unknown default:
            print("I need location")
        }
    }
}

extension CreateViewController: UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        picker.dismiss(animated: true)
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        viewModel.image = info[.originalImage] as? UIImage
        picker.dismiss(animated: true)
    }
}

extension CreateViewController: UITextViewDelegate {
    func textViewDidChange(_ textView: UITextView) {
        print(#function, textView.text ?? "")
        viewModel.caption = textView.text ?? ""
    }
}

extension CreateViewController: CLLocationManagerDelegate {
    func locationManagerDidChangeAuthorization(_ manager: CLLocationManager) {
        switch manager.authorizationStatus {
        case .notDetermined:
            break
        case .restricted, .denied:
            print("I need location!")
        case .authorizedAlways, .authorizedWhenInUse:
            guard requestLocation else { return }
            requestLocation = false
            manager.requestLocation()
        @unknown default:
            print("I need location")
        }
    }
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        guard let location = locations.first else { return }
        viewModel.showLocation(location.coordinate)
    }
    
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        print(error)
    }
}
