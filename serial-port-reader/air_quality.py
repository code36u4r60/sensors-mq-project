from enum import Enum


class AirQuality(Enum):
    green = {
        "air_quality": "Excellent",
        "impact": "Pure air; best for well-being",
        "suggested_action": "No measures needed"
    }

    dark_green = {
        "air_quality": "Good",
        "impact": "No irritation or impact on well-being",
        "suggested_action": "No measures needed"
    }

    yellow = {
        "air_quality": "Lightly polluted",
        "impact": "Reduction of well-being possible",
        "suggested_action": "Ventilation suggested"
    }

    orange = {
        "air_quality": "Moderately polluted",
        "impact": "More significant irritation possible",
        "suggested_action": "Increase ventilation with clean air"
    }

    red = {
        "air_quality": "Heavily polluted",
        "impact": "Exposition might lead to effects like headache depending on type of VOCs",
        "suggested_action": "Optimize ventilation"
    }

    purple = {
        "air_quality": "Severely polluted",
        "impact": "More severe health issue possible if harmful VOC present",
        "suggested_action": "Contamination should be identified if level is reached even w/o presence of people; "
                            "Maximize ventilation & reduce attendance"
    }

    brown = {
        "air_quality": "Extremely polluted",
        "impact": "Headache, additional neurotoxic effects possible",
        "suggested_action": "Contamination needs to be identified; Avoid presence in room and maximize ventilation"
    }

