//
//  MainTapBarController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 29.01.2021.
//

import UIKit

final class MainTabBarController: UITabBarController {
    @IBSegueAction func profileTab(_ coder: NSCoder) -> ProfileViewController? {
        ProfileViewController(
            coder: coder,
            viewModel: ProfileViewModel()
        )
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        print("hm")
    }
}

extension String {
    func toImage() -> UIImage? {
        if let data = Data(base64Encoded: self, options: .ignoreUnknownCharacters){
            return UIImage(data: data)
        }
        return nil
    }
}

extension UIImage {
    func toString() -> String? {
        let data: Data? = self.pngData()
        return data?.base64EncodedString(options: .endLineWithLineFeed)
    }
}
