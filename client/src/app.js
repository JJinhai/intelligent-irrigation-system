import React, { useState } from "react";
import { Switch } from 'antd';

const CarInterface = () => {
  const [autoMode, setAutoMode] = useState(true);
  const [infraredSensors, setInfraredSensors] = useState([false, false]);
  const [lightSensors, setLightSensors] = useState([false, false]);
  const [ultrasonicSensor, setUltrasonicSensor] = useState(false);
  const [ultrasonicAngle, setUltrasonicAngle] = useState(0);

  const toggleInfraredSensor = (index) => {
    const newInfraredSensors = [...infraredSensors];
    newInfraredSensors[index] = !newInfraredSensors[index];
    setInfraredSensors(newInfraredSensors);
  };

  const toggleLightSensor = (index) => {
    const newLightSensors = [...lightSensors];
    newLightSensors[index] = !newLightSensors[index];
    setLightSensors(newLightSensors);
  };

  const toggleUltrasonicSensor = () => {
    setUltrasonicSensor(!ultrasonicSensor);
  };

  const rotateUltrasonicSensor = (direction) => {
    setUltrasonicAngle(ultrasonicAngle + (direction === "left" ? -10 : 10));
  };

  return (
    <div className="car-interface">
      <h1>Car Interface</h1>

      <p>
        <span>Manual Mode</span>
        <Switch checked={autoMode} onChange={setAutoMode} />
        <span>Automatic Mode</span>
      </p>

      <div className="sensors">
        <div className="infrared-sensors">
          <h3>Infrared Sensors</h3>
          {infraredSensors.map((sensor, index) => (
            <button key={index} onClick={() => toggleInfraredSensor(index)}>
              {sensor ? "ON" : "OFF"}
            </button>
          ))}
        </div>

        <div className="light-sensors">
          <h3>Light Sensors</h3>
          {lightSensors.map((sensor, index) => (
            <button key={index} onClick={() => toggleLightSensor(index)}>
              {sensor ? "ON" : "OFF"}
            </button>
          ))}
        </div>
        <div className="ultrasonic-sensor">
          <h3>Ultrasonic Sensor</h3>
          <button onClick={toggleUltrasonicSensor}>
            {ultrasonicSensor ? "ON" : "OFF"}
          </button>
          <button onClick={() => rotateUltrasonicSensor("left")}>Left</button>
          <button onClick={() => rotateUltrasonicSensor("right")}>Right</button>
          <p>Angle: {ultrasonicAngle}°</p>
        </div>
      </div>

      <div className="car_container">
        <svg viewBox="0 0 200 400" xmlns="http://www.w3.org/2000/svg">
          <rect x="10" y="10" width="180" height="380" fill="gray" />

          <circle className="wheel front left" cx="40" cy="60" r="18" />
          <line  className="wheel front left line" x1="40" x2="0" y1="60" y2="60" stroke="black" strokeWidth="3" />
          <circle className="wheel front right" cx="160" cy="60" r="18" />
          <line  className="wheel front right line" x1="160" x2="200" y1="60" y2="60" stroke="black" strokeWidth="3" />
          <circle className="wheel rear left" cx="40" cy="360" r="18" />
          <line  className="wheel rear left line" x1="40" x2="0" y1="360" y2="360" stroke="black" strokeWidth="3" />
          <circle className="wheel rear right" cx="160" cy="360" r="18" />
          <line  className="wheel rear right line" x1="160" x2="200" y1="360" y2="360" stroke="black" strokeWidth="3" />


          {/* Infrared sensors */}
          <circle className={`sensor infrared left ${infraredSensors[0] ? "active" : ""}`} cx="100" cy="15" r="5" />
          <circle className={`sensor infrared right ${infraredSensors[1] ? "active" : ""}`} cx="100" cy="385" r="5" />

          {/* Light sensors */}
          <circle className={`sensor light left ${lightSensors[0] ? "active" : ""}`} cx="20" cy="30" r="5" />
          <circle className={`sensor light right ${lightSensors[1] ? "active" : ""}`} cx="180" cy="30" r="5" />

          {/* Ultrasonic sensor */}
          <g style={{transform: "rotate(45deg)",transformOrigin: "100px 45px"}}>
            <circle className={`sensor ultrasonic ${ultrasonicSensor ? "active" : ""}`} cx="85" cy="45" r="10" style={{ transform: `rotate(${ultrasonicAngle}deg)` }} />
            <line  className={`sensor ultrasonic ${ultrasonicSensor ? "active" : ""}`} x1="85" x2="115" y1="45" y2="45" stroke="black" strokeWidth="2" />
            <circle className={`sensor ultrasonic ${ultrasonicSensor ? "active" : ""}`} cx="115" cy="45" r="10" style={{ transform: `rotate(${ultrasonicAngle}deg)` }} />
          </g>

        </svg>
      </div>
    </div>
  )
}

import "./app.less";

export default function App() {
  return (
    <div className="App">
      <CarInterface />
    </div>
  )
}
