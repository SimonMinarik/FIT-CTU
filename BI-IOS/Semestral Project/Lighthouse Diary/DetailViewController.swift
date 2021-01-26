//
//  DetailViewController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 22.01.2021.
//

import UIKit

final class DetailViewController: UIViewController {
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
    @IBOutlet weak var userDescriptionTextField: UITextField!
    
    private var setUserPhotos:[UIImage] = [UIImage(named: "612664395a40232133447d33247d38313233393434333331.jpeg")!, UIImage(named: "leuchtturm-busum.jpg")!]
    
    private let descriptionText = "The Cape Arkona Lighthouse (German: Leuchtturm Kap Arkona) comprises two lighthouses and a radio navigation tower on the German Baltic Sea coast in Mecklenburg-Vorpommern, with the international serial number C 1062. It is located on Cape Arkona on the peninsula of Wittow on the northern tip of the island of Rügen."
    
    override func loadView() {
        super.loadView()
        self.descriptionLabel.text = descriptionText
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
        
        let notificationCenter = NotificationCenter.default
        notificationCenter.addObserver(self, selector: #selector(adjustForKeyboard), name: UIResponder.keyboardWillHideNotification, object: nil)
        notificationCenter.addObserver(self, selector: #selector(adjustForKeyboard), name: UIResponder.keyboardWillChangeFrameNotification, object: nil)
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
    }
    
    @IBAction func addPhotoButtonTapped(_ sender: UIButton) {
        let imagePicker = UIImagePickerController()
        imagePicker.sourceType = .photoLibrary
        imagePicker.delegate = self
        present(imagePicker, animated: true)
    }
    
    func addPhoto(image: UIImage) {
        self.setUserPhotos.append(image)
        switch self.setUserPhotos.count {
        case 1:
            self.firstUserPhotoView.isHidden = false
            self.firstUserPhotoImageView.image = setUserPhotos[0]
            break
        case 2:
            self.secondUserPhotoView.isHidden = false
            self.secondUserPhotoImageView.image = setUserPhotos[1]
            break
        case 3:
            self.thirdUserPhotoImageView.image = setUserPhotos[2]
            self.thirdPhotoDeleteButton.isHidden = false
            self.addPhotoButton.isHidden = true
        default:
            fatalError("That shouldn't happen..")
        }
    }
    
    func removePhoto(at: Int) {
        print("removed photo at:", at)
        self.setUserPhotos.remove(at: at)
        switch self.setUserPhotos.count {
        case 2:
            self.firstUserPhotoImageView.image = setUserPhotos[0]
            self.secondUserPhotoImageView.image = setUserPhotos[1]
            self.thirdUserPhotoImageView.image = UIImage()
            self.addPhotoButton.isHidden = false
            self.thirdPhotoDeleteButton.isHidden = true
            break
        case 1:
            self.firstUserPhotoImageView.image = setUserPhotos[0]
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
        
    }
}

extension DetailViewController: UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        picker.dismiss(animated: true)
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        addPhoto(image: (info[.originalImage] as? UIImage)!)
        picker.dismiss(animated: true)
    }
}
