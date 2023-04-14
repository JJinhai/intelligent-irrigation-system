import React, { useState } from "react";
import "./CarInterface.css";

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
        {/* Car body */}
<rect x="10" y="35" width="180" height="50" fill="gray" />

{/* Wheels */}
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



// SVG
.car-interface {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.sensors {
  display: flex;
  justify-content: space-around;
  width: 100%;
}

.infrared-sensors,
.light-sensors,
.ultrasonic-sensor {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.car {
  position: relative;
  width: 200px;
  height: 100px;
  border: 1px solid black;
  margin-top: 20px;
}

.wheel {
  position: absolute;
  width: 30px;
  height: 30px;
  border-radius: 50%;
  background-color: black;
}

.wheel.front {
  top: 60px;
}

.wheel.rear {
  top: 10px;
}

.wheel.left {
  left: 20px;
}

.wheel.right {
  right: 20px;
}

.sensor {
  position: absolute;
  width: 10px;
  height: 10px;
  border-radius: 50%;
}

.sensor.infrared {
  background-color: red;
}

.sensor.light {
  background-color: yellow;
}

.sensor.ultrasonic {
  background-color: blue;
  transform-origin: 50% 50%;
}


//SRC
import React from "react";
import "./App.css";
import CarInterface from "./CarInterface";

function App() {
  return (
    <div className="App">
      <CarInterface />
   
