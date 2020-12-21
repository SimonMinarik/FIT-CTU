//
//  RandomExtensions.swift
//  FITstagram
//
//  Created by Jan Misar on 26/11/2020.
//

import UIKit
import func AVFoundation.AVMakeRect

extension UIImage {
    /// Resize image to target size keeping aspect ratio
    func imageResized(to size: CGSize) -> UIImage {
        let rect = AVMakeRect(aspectRatio: self.size, insideRect: CGRect(origin: .zero, size: size))
        return UIGraphicsImageRenderer(size: rect.size).image { _ in
            draw(in: CGRect(origin: .zero, size: rect.size))
        }
    }
}
