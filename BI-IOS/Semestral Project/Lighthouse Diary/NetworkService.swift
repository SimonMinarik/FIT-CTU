//
//  NetworkService.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import Foundation

protocol NetworkServicing {
    func fetch(url: String, completion: @escaping (Result<Data, Error>) -> Void)
    func fetch(urlRequest: URLRequest, completion: @escaping (Result<Data, Error>) -> Void)
}

struct NetworkService: NetworkServicing {
    func fetch(url: String, completion: @escaping (Result<Data, Error>) -> Void) {
        let urlRequest = URLRequest(url: URL(string: url)!)
        fetch(urlRequest: urlRequest, completion: completion)
    }
    
    func fetch(urlRequest: URLRequest, completion: @escaping (Result<Data, Error>) -> Void) {
        URLSession.shared
            .dataTask(with: urlRequest, completionHandler: { data, response, error in
                if let error = error {
                    print("[ERROR]", error)
                    completion(.failure(error))
                    return
                }
                
                guard let data = data else { assertionFailure(); return }
                
                completion(.success(data))
            })
            .resume()
    }
}
