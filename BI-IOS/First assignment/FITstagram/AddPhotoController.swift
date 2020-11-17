//
//  AddPhotoController.swift
//  FITstagram
//
//  Created by Šimon Minárik on 27/10/2020.
//

import UIKit

class AddPhotoController: UIViewController, UIImagePickerControllerDelegate & UINavigationControllerDelegate {
    
    @IBOutlet weak var photoDescriptionTextView: UITextView!
    @IBOutlet weak var imageView: UIImageView!
    @IBOutlet weak var selectPhotoButton: UIButton!
    
    @IBAction func cancelButtonTapped(_ sender: UIButton) {
        print("cancel tapped")
    }
    
    @IBAction func locationButtonTapped(_ sender: UIButton) {
        print("location tapped")
    }
    
    @IBAction func createButtonTapped(_ sender: UIButton) {
        print(photoDescriptionTextView.text!)
        photoDescriptionTextView.text = ""
        imageView.image = .none
        imageView.layer.borderWidth = 1
        selectPhotoButton.isHidden = false
        self.view.endEditing(true)
    }
    
    @IBAction func selectPhotoButtonTapped(_ sender: UIButton) {
        let vc = UIImagePickerController()
        vc.sourceType = .photoLibrary
        vc.allowsEditing = true
        vc.delegate = self
        present(vc, animated: true)
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        picker.dismiss(animated: true)

        guard let image = info[.editedImage] as? UIImage else {
            print("No image found")
            return
        }

        imageView.image = image
        imageView.layer.borderWidth = 0
        selectPhotoButton.isHidden = true
    }
    
    override func viewDidLoad() {
        photoDescriptionTextView.layer.borderWidth = 1
        photoDescriptionTextView.layer.borderColor = UIColor.lightGray.cgColor
        imageView.layer.borderWidth = 1
        imageView.layer.borderColor = UIColor.lightGray.cgColor
        super.viewDidLoad()
    }
}
