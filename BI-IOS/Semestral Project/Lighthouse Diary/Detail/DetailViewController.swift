//
//  DetailViewController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 22.01.2021.
//

import UIKit
import CoreLocation

final class DetailViewController: UIViewController {
    @IBOutlet weak var lighthouseImageView: UIImageView!
    @IBOutlet weak var lighthouseNameLabel: UILabel!
    @IBOutlet weak var scrollView: UIScrollView!
    @IBOutlet weak var locationButton: UIButton!
    @IBOutlet weak var descriptionLabel: UILabel!
    @IBOutlet weak var firstUserPhotoImageView: UIImageView!
    @IBOutlet weak var secondUserPhotoImageView: UIImageView!
    @IBOutlet weak var thirdUserPhotoImageView: UIImageView!
    @IBOutlet weak var addPhotoButton: UIButton!
    @IBOutlet weak var firstUserPhotoView: UIView!
    @IBOutlet weak var secondUserPhotoView: UIView!
    @IBOutlet weak var thirdUserPhotoView: UIView!
    @IBOutlet weak var thirdPhotoDeleteButton: UIButton!
    @IBOutlet weak var userPhotosStackView: UIStackView!
    @IBOutlet weak var userDescriptionTextView: UITextView!
    
    private let viewModel: DetailViewModeling
    
    init?(coder: NSCoder, viewModel: DetailViewModeling) {
        self.viewModel = viewModel
        super.init(coder: coder)
    }
    
    @available(*, unavailable, renamed: "init(coder:viewModel:)")
    required init?(coder: NSCoder) {
        fatalError("You must create this view controller with a viewModel.")
    }
        
    override func loadView() {
        super.loadView()
        viewModel.loadUserData()
        
        self.descriptionLabel.text = viewModel.lighthouse.description
        self.locationButton.setTitle(viewModel.lighthouse.location, for: .normal)
        self.lighthouseNameLabel.text = viewModel.lighthouse.name
        self.lighthouseImageView.image = viewModel.lighthouse.image
        if viewModel.userData.visited != "" {
            self.userDescriptionTextView.text = viewModel.userData.description
        } else {
            self.userDescriptionTextView.isHidden = true
            self.userPhotosStackView.isHidden = true
        }
        
        self.title = viewModel.lighthouse.name
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        firstUserPhotoView.translatesAutoresizingMaskIntoConstraints = false
        secondUserPhotoView.translatesAutoresizingMaskIntoConstraints = false
        thirdUserPhotoView.translatesAutoresizingMaskIntoConstraints = false
        let width = (view.frame.width - 16) / 3
        NSLayoutConstraint.activate([
            firstUserPhotoView.widthAnchor.constraint(equalToConstant: width),
            secondUserPhotoView.widthAnchor.constraint(equalToConstant: width),
            thirdUserPhotoView.widthAnchor.constraint(equalToConstant: width)
        ])
        
        userDescriptionTextView.layer.borderWidth = 1
        userDescriptionTextView.layer.borderColor = UIColor.lightGray.cgColor
        userDescriptionTextView.layer.cornerRadius = 4
        
        lighthouseImageView.layer.borderWidth = 1
        lighthouseImageView.layer.borderColor = UIColor.lightGray.cgColor
        lighthouseImageView.layer.cornerRadius = lighthouseImageView.frame.width / 2
                        
        let notificationCenter = NotificationCenter.default
        notificationCenter.addObserver(self, selector: #selector(adjustForKeyboard), name: UIResponder.keyboardWillHideNotification, object: nil)
        notificationCenter.addObserver(self, selector: #selector(adjustForKeyboard), name: UIResponder.keyboardWillChangeFrameNotification, object: nil)
        
        self.hideKeyboardWhenTappedAround()
    }
    
    @objc func adjustForKeyboard(notification: Notification) {
        guard let keyboardValue = notification.userInfo?[UIResponder.keyboardFrameEndUserInfoKey] as? NSValue else { return }

        let keyboardScreenEndFrame = keyboardValue.cgRectValue
        let keyboardViewEndFrame = view.convert(keyboardScreenEndFrame, from: view.window)

        if notification.name == UIResponder.keyboardWillHideNotification {
            self.scrollView.contentInset = .zero
        } else {
            self.scrollView.contentInset = UIEdgeInsets(top: 0, left: 0, bottom: keyboardViewEndFrame.height - view.safeAreaInsets.bottom, right: 0)
        }

        self.scrollView.scrollIndicatorInsets = self.scrollView.contentInset
        
        let bottomOffset = CGPoint(x: 0, y: scrollView.contentSize.height - scrollView.bounds.height + scrollView.contentInset.bottom)
        scrollView.setContentOffset(bottomOffset, animated: true)
    }
    
    @IBAction func addPhotoButtonTapped(_ sender: UIButton) {
        let imagePicker = UIImagePickerController()
        imagePicker.sourceType = .photoLibrary
        imagePicker.delegate = self
        present(imagePicker, animated: true)
    }
    
    func addPhoto(image: UIImage) {
        viewModel.userData.photos?.append(image.toString() ?? "")
        switch viewModel.userData.photos?.count {
        case 1:
            self.firstUserPhotoView.isHidden = false
            self.firstUserPhotoImageView.image = viewModel.userData.photos?[0].toImage()
            break
        case 2:
            self.secondUserPhotoView.isHidden = false
            self.secondUserPhotoImageView.image = viewModel.userData.photos?[1].toImage()
            break
        case 3:
            self.thirdUserPhotoImageView.image = viewModel.userData.photos?[2].toImage()
            self.thirdPhotoDeleteButton.isHidden = false
            self.addPhotoButton.isHidden = true
        default:
            fatalError("That shouldn't happen..")
        }
    }
    
    func removePhoto(at: Int) {
        viewModel.userData.photos?.remove(at: at)
        switch viewModel.userData.photos?.count {
        case 2:
            self.firstUserPhotoImageView.image = viewModel.userData.photos?[0].toImage()
            self.secondUserPhotoImageView.image = viewModel.userData.photos?[1].toImage()
            self.thirdUserPhotoImageView.image = UIImage()
            self.addPhotoButton.isHidden = false
            self.thirdPhotoDeleteButton.isHidden = true
            break
        case 1:
            self.firstUserPhotoImageView.image = viewModel.userData.photos?[0].toImage()
            self.secondUserPhotoView.isHidden = true
            break
        case 0:
            self.firstUserPhotoView.isHidden = true
            break
        default:
            fatalError("Well..")
        }
    }
    
    @IBAction func firstPhotoDeleteButtonTapped(_ sender: UIButton) {
        removePhoto(at: 0)
    }
    
    @IBAction func secondPhotoDeleteButtonTapped(_ sender: UIButton) {
        removePhoto(at: 1)
    }
    
    @IBAction func thirdPhotoDeleteButtonTapped(_ sender: UIButton) {
        removePhoto(at: 2)
    }
    
    @IBAction func locationButtonTapped(_ sender: UIButton) {
        let vc = storyboard?.instantiateViewController(identifier: "DetailMapVC") { DetailMapViewController(
                coder: $0,
                viewModel: DetailMapViewModel(
                    coordinate: CLLocationCoordinate2D(latitude: CLLocationDegrees(self.viewModel.lighthouse.lat), longitude: CLLocationDegrees(self.viewModel.lighthouse.lon)),
                    name: self.viewModel.lighthouse.name))
        }
        self.present(vc!, animated: true)
    }
}

extension DetailViewController: UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        picker.dismiss(animated: true)
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        addPhoto(image: (info[.originalImage]) as! UIImage)
        picker.dismiss(animated: true)
    }
    
    func hideKeyboardWhenTappedAround() {
        let tap = UITapGestureRecognizer(target: self, action: #selector(DetailViewController.dismissKeyboard))
        tap.cancelsTouchesInView = false
        view.addGestureRecognizer(tap)
    }
    
    @objc func dismissKeyboard() {
        view.endEditing(true)
    }
}
