# AUROADAS ADAS Test Suite

## 1. Lane Keeping

- Scenario: straight + curved urban road
- Metrics:
  - Pose stability
  - Map consistency
  - Confidence score under mild occlusions

## 2. Adaptive Cruise / Following

- Scenario: ego follows lead vehicle
- Metrics:
  - Obstacle detection range
  - Track continuity
  - Confidence under stop-and-go

## 3. Emergency Braking

- Scenario: pedestrian or vehicle crossing
- Metrics:
  - Detection latency
  - Track initialization time
  - Confidence spike before event

## 4. Parking / Low-Speed Maneuvering

- Scenario: tight parking lot
- Metrics:
  - Short-range mapping
  - Pose drift at low speed
  - Obstacle detection near ego

## 5. Sensor Degradation

- Cases:
  - GPS dropout
  - Camera occlusion
  - IMU noise increase
- Metrics:
  - Fallback behavior
  - Confidence reduction
  - Pose robustness
