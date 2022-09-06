import Foundation

class CoolPlacesNearMe{

    let lat: Double
    let lng: Double
    let rad: Double
    let coords: [Any]
    init(json: Data, latitude: Double, longitude: Double, radius: Double) throws{
        let decoder = JSONDecoder()
        coords = try decoder.decode([Welcome].self, from: json)
        lat = latitude
        lng = longitude
        rad = radius
    }
}

let jsonData = """
    {
    "candidates": [
        {
            "geometry": {
                "location": {
                    "lat": 48.470247,
                    "lng": 35.036206
                }
            },
            "name": "Coffee Life"
        },
        {
            "geometry": {
                "location": {
                    "lat": 48.469434,
                    "lng": 35.038985
                }
            },
            "name": "Have Coffee"
        },
        {
            "geometry": {
                "location": {
                    "lat": 48.466561,
                    "lng": 35.045186
                }
            },
            "name": "AROMA KAVA"
        },
        {
            "geometry": {
                "location": {
                    "lat": 48.463783,
                    "lng": 35.042595
                }
            },
            "name": "Mr. Coffee"
        },
        {
            "geometry": {
                "location": {
                    "lat": 48.463516,
                    "lng": 35.048889
                }
            },
            "name": "DoubleDecker"
        },
        {
            "geometry": {
                "location": {
                    "lat": 48.425694,
                    "lng": 35.025487
                }
            },
            "name": "Mocco bar"
        },
        {
            "geometry": {
                "location": {
                    "lat": 48.451214,
                    "lng": 35.057789
                }
            },
            "name": "Confetti"
        },
        {
            "geometry": {
                "location": {
                    "lat": 48.460239,
                    "lng": 35.069301
                }
            },
            "name": "One dollar bar"
        },
        {
            "geometry": {
                "location": {
                    "lat": 48.459414,
                    "lng": 35.064731
                }
            },
            "name": "Heisenberg Coffee Lab"
        },
        {
            "geometry": {
                "location": {
                    "lat": 48.423311,
                    "lng": 35.058121
                }
            },
            "name": "Sopranos"
        }
    ]
}
""".data(using: .utf8)!

// MARK: - Welcome
struct Welcome: Codable {
    let candidates: [Candidate]
}

// MARK: - Candidate
struct Candidate: Codable {
    let geometry: Geometry
    let name: String
}

// MARK: - Geometry
struct Geometry: Codable {
    let location: Location
}

// MARK: - Location
struct Location: Codable {
    let lat, lng: Double
}

let obj = try? CoolPlacesNearMe(json: jsonData, latitude: 48.411207, longitude: 35.039910, radius: 1.5)