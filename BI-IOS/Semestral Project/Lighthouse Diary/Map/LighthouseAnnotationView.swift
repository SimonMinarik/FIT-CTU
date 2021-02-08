//
//  LighthouseAnnotationView.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 31.01.2021.
//

import UIKit
import MapKit

final class LighthouseAnnotationView: MKMarkerAnnotationView {
    
    override var annotation: MKAnnotation? {
        willSet {
            guard let lighthouseAnnotation = newValue as? LighthouseAnnotation else { return }
            
            self.glyphImage = UIImage(named: "noun_Lighthouse_314521-2-2.png")
            
            let lighthouseImageView = UIImageView(frame: CGRect(x: 0, y: 0, width: 50, height: 50))
            lighthouseImageView.image = lighthouseAnnotation.image
            self.leftCalloutAccessoryView = lighthouseImageView
            
            switch lighthouseAnnotation.type {
            case "visited":
                self.markerTintColor = .yellow
                break
            case "bucketlist":
                self.markerTintColor = .green
                break
            default:
                break
            }
        }
    }
    
    @objc func buttonTap() {
        let alert = UIAlertController(title: "This should be Google Maps navigation link..", message: "But it's not..", preferredStyle: .alert)

        alert.addAction(UIAlertAction(title: "Yes", style: .default, handler: nil))
        alert.addAction(UIAlertAction(title: "No", style: .cancel, handler: nil))

        print("button tapped")
    }
}
