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
    @IBOutlet weak var typeSegmentedControl: UISegmentedControl!
    @IBOutlet weak var descriptionLabel: UILabel!
    @IBOutlet weak var firstUserPhotoImageView: UIImageView!
    @IBOutlet weak var secondUserPhotoImageView: UIImageView!
    @IBOutlet weak var thirdUserPhotoImageView: UIImageView!
    @IBOutlet weak var addPhotoButton: UIButton!
    @IBOutlet weak var firstUserPhotoView: UIView!
    @IBOutlet weak var secondUserPhotoView: UIView!
    @IBOutlet weak var thirdUserPhotoView: UIView!
    @IBOutlet weak var thirdPhotoDeleteButton: UIButton!
    @IBOutlet weak var visitedLabel: UILabel!
    @IBOutlet weak var userPhotosStackView: UIStackView!
    @IBOutlet weak var userDescriptionTextView: UITextView!
    
    private let viewModel: DetailViewModeling
    
    // MARK: - Initialization
    
    init?(coder: NSCoder, viewModel: DetailViewModeling) {
        self.viewModel = viewModel
        super.init(coder: coder)
    }
    
    @available(*, unavailable, renamed: "init(coder:viewModel:)")
    required init?(coder: NSCoder) {
        fatalError("You must create this view controller with a viewModel.")
    }
    
    // MARK: - Life cycle
        
    override func loadView() {
        super.loadView()
        viewModel.loadUserData()
        
        self.title = viewModel.lighthouse.name
        descriptionLabel.text = viewModel.lighthouse.description
        locationButton.setTitle(viewModel.lighthouse.location, for: .normal)
        lighthouseNameLabel.text = viewModel.lighthouse.name
        lighthouseImageView.image = viewModel.lighthouse.image
        
        self.viewModel.viewModelDidChange = { [weak self] viewModel in
            guard let self = self else { return }
            self.setUserObjects()
        }
        
        setUserObjects()
        
        let segmentedTapGesture = UITapGestureRecognizer(target: self, action: #selector(onTapGestureSegment(_:)))
        typeSegmentedControl.addGestureRecognizer(segmentedTapGesture)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationItem.rightBarButtonItem = UIBarButtonItem(title: "Save", style: .plain, target: self, action: #selector(saveChanges))
        self.navigationItem.rightBarButtonItem?.isEnabled = false
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
        
        userDescriptionTextView.delegate = self
        
        lighthouseImageView.layer.borderWidth = 1
        lighthouseImageView.layer.borderColor = UIColor.lightGray.cgColor
        lighthouseImageView.layer.cornerRadius = lighthouseImageView.frame.width / 2
        
        setSegmentedControl(at: typeSegmentedControl.selectedSegmentIndex)
                        
        let notificationCenter = NotificationCenter.default
        notificationCenter.addObserver(self, selector: #selector(adjustForKeyboard), name: UIResponder.keyboardWillHideNotification, object: nil)
        notificationCenter.addObserver(self, selector: #selector(adjustForKeyboard), name: UIResponder.keyboardWillChangeFrameNotification, object: nil)
        
        self.hideKeyboardWhenTappedAround()
    }
    
    // MARK: - Actions
    
    @IBAction func addPhotoButtonTapped(_ sender: UIButton) {
        let imagePicker = UIImagePickerController()
        imagePicker.sourceType = .photoLibrary
        imagePicker.delegate = self
        present(imagePicker, animated: true)
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
    
    // MARK: - Private helpers
    
    @objc private func saveChanges() {
        viewModel.saveUserLighthouseData()
        self.navigationItem.rightBarButtonItem?.isEnabled = false
    }
    
    private func setUserObjects() {
        if viewModel.userLighthouseData.type == "visited" {
            visitedLabel.isHidden = false
            userDescriptionTextView.isHidden = false
            userPhotosStackView.isHidden = false
            
            userDescriptionTextView.text = viewModel.userLighthouseData.description
            visitedLabel.text = "Visited: \(viewModel.userPreferences.visited_dates["\(viewModel.lighthouse.id)"] ?? "")"
            switch viewModel.userLighthouseData.photos?.count {
            case 0:
                firstUserPhotoView.isHidden = true
                secondUserPhotoView.isHidden = true
                
                thirdUserPhotoImageView.image = UIImage()
                addPhotoButton.isHidden = false
                thirdPhotoDeleteButton.isHidden = true
                break
            case 1:
                firstUserPhotoImageView.image = viewModel.userLighthouseData.photos![0].toImage()
                secondUserPhotoView.isHidden = true
                break
            case 2:
                firstUserPhotoImageView.image = viewModel.userLighthouseData.photos![0].toImage()
                secondUserPhotoImageView.image = viewModel.userLighthouseData.photos![1].toImage()
                break
            case 3:
                firstUserPhotoImageView.image = viewModel.userLighthouseData.photos![0].toImage()
                secondUserPhotoImageView.image = viewModel.userLighthouseData.photos![1].toImage()
                thirdUserPhotoImageView.image = viewModel.userLighthouseData.photos![2].toImage()
                thirdPhotoDeleteButton.isHidden = false
                addPhotoButton.isHidden = true
                break
            default:
                break
            }
        } else {
            visitedLabel.isHidden = true
            userDescriptionTextView.isHidden = true
            userPhotosStackView.isHidden = true
        }
        
        switch viewModel.userLighthouseData.type {
        case "visited":
            typeSegmentedControl.selectedSegmentIndex = 0
            break
        case "bucketlist":
            typeSegmentedControl.selectedSegmentIndex = 1
        default:
            typeSegmentedControl.selectedSegmentIndex = -1
            break
        }
    }
        
    private func setSegmentedControl(at: Int) {
        typeSegmentedControl.setImage(UIImage(systemName: "eye"), forSegmentAt: 0)
        typeSegmentedControl.setImage(UIImage(systemName: "heart"), forSegmentAt: 1)
        if at == 0 {
            typeSegmentedControl.setImage(UIImage(systemName: "eye.fill"), forSegmentAt: 0)
        } else if at == 1 {
            typeSegmentedControl.setImage(UIImage(systemName: "heart.fill"), forSegmentAt: 1)
        }
    }
    
    @objc private func adjustForKeyboard(notification: Notification) {
        guard let keyboardValue = notification.userInfo?[UIResponder.keyboardFrameEndUserInfoKey] as? NSValue else { return }

        let keyboardScreenEndFrame = keyboardValue.cgRectValue
        let keyboardViewEndFrame = view.convert(keyboardScreenEndFrame, from: view.window)

        if notification.name == UIResponder.keyboardWillHideNotification {
            self.scrollView.contentInset = .zero
        } else {
            self.scrollView.contentInset = UIEdgeInsets(top: 0, left: 0, bottom: keyboardViewEndFrame.height - view.safeAreaInsets.bottom, right: 0)
        }

        // Doesn't work properly with small (unscrollable) scroll view
        self.scrollView.scrollIndicatorInsets = self.scrollView.contentInset

        let bottomOffset = CGPoint(x: 0, y: scrollView.contentSize.height - scrollView.bounds.height + scrollView.contentInset.bottom)
        scrollView.setContentOffset(bottomOffset, animated: true)
    }
    
    private func addPhoto(image: String) {
        viewModel.userLighthouseData.photos?.append(image)
        switch viewModel.userLighthouseData.photos?.count {
        case 1:
            self.firstUserPhotoView.isHidden = false
            self.firstUserPhotoImageView.image = viewModel.userLighthouseData.photos?[0].toImage()
            break
        case 2:
            self.secondUserPhotoView.isHidden = false
            self.secondUserPhotoImageView.image = viewModel.userLighthouseData.photos?[1].toImage()
            break
        case 3:
            self.thirdUserPhotoImageView.image = viewModel.userLighthouseData.photos?[2].toImage()
            self.thirdPhotoDeleteButton.isHidden = false
            self.addPhotoButton.isHidden = true
        default:
            fatalError("That shouldn't happen..")
        }
        self.navigationItem.rightBarButtonItem?.isEnabled = true
    }
    
    private func removePhoto(at: Int) {
        viewModel.userLighthouseData.photos?.remove(at: at)
        switch viewModel.userLighthouseData.photos?.count {
        case 2:
            self.firstUserPhotoImageView.image = viewModel.userLighthouseData.photos?[0].toImage()
            self.secondUserPhotoImageView.image = viewModel.userLighthouseData.photos?[1].toImage()
            self.thirdUserPhotoImageView.image = UIImage()
            self.addPhotoButton.isHidden = false
            self.thirdPhotoDeleteButton.isHidden = true
            break
        case 1:
            self.firstUserPhotoImageView.image = viewModel.userLighthouseData.photos?[0].toImage()
            self.secondUserPhotoView.isHidden = true
            break
        case 0:
            self.firstUserPhotoView.isHidden = true
            break
        default:
            fatalError("Well..")
        }
        self.navigationItem.rightBarButtonItem?.isEnabled = true
    }
    
    @objc private func onTapGestureSegment(_ tapGesture: UITapGestureRecognizer) {
        let point = tapGesture.location(in: typeSegmentedControl)
        let segmentSize = typeSegmentedControl.bounds.size.width / CGFloat(typeSegmentedControl.numberOfSegments)
        let touchedSegment = Int(point.x / segmentSize)

        if typeSegmentedControl.selectedSegmentIndex != touchedSegment {
            if typeSegmentedControl.selectedSegmentIndex == 0 {
                confirmAlert(from: typeSegmentedControl.selectedSegmentIndex, to: touchedSegment, delete: false)
            } else {
                setSegmentedControl(at: touchedSegment)
                viewModel.changeUserPreference(from: typeSegmentedControl.selectedSegmentIndex, to: touchedSegment)
                typeSegmentedControl.selectedSegmentIndex = touchedSegment
            }
        } else if touchedSegment == 0 {
            confirmAlert(from: typeSegmentedControl.selectedSegmentIndex, to: -1, delete: true)
        } else {
            setSegmentedControl(at: -1)
            viewModel.changeUserPreference(from: typeSegmentedControl.selectedSegmentIndex, to: -1)
            typeSegmentedControl.selectedSegmentIndex = -1
        }
    }
    
    private func confirmAlert(from: Int, to: Int, delete: Bool) {
        let alert = UIAlertController(title: "Are you sure?", message: "All personal data will be lost.", preferredStyle: .alert)

        alert.addAction(UIAlertAction(title: "Yes", style: .default, handler: { _ in
            if delete {
                self.typeSegmentedControl.selectedSegmentIndex = -1
                self.setSegmentedControl(at: -1)
            } else {
                self.typeSegmentedControl.selectedSegmentIndex = 1
                self.setSegmentedControl(at: 1)
            }
            self.viewModel.changeUserPreference(from: from, to: to)
        }))
        alert.addAction(UIAlertAction(title: "No", style: .cancel, handler: nil))

        self.present(alert, animated: true)
    }
}

extension DetailViewController: UIImagePickerControllerDelegate, UINavigationControllerDelegate, UITextViewDelegate {
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        picker.dismiss(animated: true)
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        let image = info[.originalImage] as? UIImage
        if let resizedImage = resizeImage(with: image, scaledToFill: CGSize(width: firstUserPhotoImageView.frame.width, height: firstUserPhotoImageView.frame.height))?.jpegData(compressionQuality: 0) {
            addPhoto(image: resizedImage.base64EncodedString())
        }
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
    
    func textViewDidChange(_ textView: UITextView) {
        switch (textView) {
            case userDescriptionTextView:
                self.navigationItem.rightBarButtonItem?.isEnabled = true
                self.viewModel.userLighthouseData.description = textView.text
                break
            default:
                break
        }
    }
}
