import React, { useState } from "react";

const CarInterface = () => {
  const [mode, setMode] = useState("Manual");
  const [infraredSensors, setInfraredSensors] = useState([false, false]);
  const [lightSensors, setLightSensors] = useState([false, false]);
  const [ultrasonicSensor, setUltrasonicSensor] = useState(false);
  const [ultrasonicAngle, setUltrasonicAngle] = useState(0);

  const toggleMode = () => {
    setMode(mode === "Manual" ? "Automatic" : "Manual");
  };

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
      <button onClick={toggleMode}>{mode} Mode</button>

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

      <div className="car">
        <rect x="10" y="35" width="180" height="50" fill="gray" />

        <circle className="wheel front left" cx="40" cy="75" r="15" />
        <circle className="wheel front right" cx="160" cy="75" r="15" />
        <circle className="wheel rear left" cx="40" cy="25" r="15" />
        <circle className="wheel rear right" cx="160" cy="25" r="15" />

        {/* Infrared sensors */}
        <circle className={`sensor infrared left ${infraredSensors[0] ? "active" : ""}`} cx="20" cy="45" r="5" />
        <circle className={`sensor infrared right ${infraredSensors[1] ? "active" : ""}`} cx="180" cy="45" r="5" />

        {/* Light sensors */}
        <circle className={`sensor light left ${lightSensors[0] ? "active" : ""}`} cx="20" cy="75" r="5" />
        <circle className={`sensor light right ${lightSensors[1] ? "active" : ""}`} cx="180" cy="75" r="5" />

        {/* Ultrasonic sensor */}
        <circle className={`sensor ultrasonic ${ultrasonicSensor ? "active" : ""}`} cx="100" cy="45" r="5" style={{ transform: `rotate(${ultrasonicAngle}deg)` }} />
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
