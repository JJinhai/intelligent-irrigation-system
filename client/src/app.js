import React, { useEffect, useState } from "react";
import { Switch } from 'antd';

const CarInterface = () => {
  // const [autoMode, setAutoMode] = useState(true);
  const [ motors, setMotors] = useState([0, 0, 0, 0]);
  const [lightSensors, setLightSensors] = useState([0, 0]);
  const [infraredSensors, setInfraredSensors] = useState([0, 0]);
  const [ultrasonicAngle, setUltrasonicAngle] = useState(0);
  const [ultrasonicSensor, setUltrasonicSensor] = useState(true);

  function fetchData(){
    fetch("/web/state", {
      "method": "GET",
      "mode": "cors",
      "credentials": "omit"
    })
    .then( res => res.json() )
    .then( res => {
      setMotors([res.motor1,res.motor2,res.motor3,res.motor4])
      setLightSensors([res.light1,res.light2])
      setInfraredSensors([res.infrared1,res.infrared2])
      setUltrasonicAngle(res.servo)
    });
  }
  useEffect(()=>{
    setInterval(()=>{
      fetchData()
    },1000)
  },[])

  const rotateUltrasonicSensor = (direction) => {
    setUltrasonicAngle(ultrasonicAngle + (direction === "left" ? -10 : 10));
  };

  return (
    <div className="car-interface">
      <h1>Car Interface</h1>
      <div className="overall">
        <div className="infrared-sensors front" style={{ left: 250,top: 65}}>
          <h3>Front Infrared Sensors</h3>
          <span> Detect: {infraredSensors[0] > 0 ? "human is closing" : "no one"}</span>
        </div>
        <div className="infrared-sensors back" style={{ left: 210,top: 495}}>
          <h3>Back Infrared Sensors</h3>
          <span> Detect: {infraredSensors[1] > 0 ? "human is closing" : "no one"}</span>
        </div>
        <div className="light-sensors left" style={{ left: 50,top: 95}}>
          <h3>Light Sensors</h3>
          <p>Light intensity:{lightSensors[0]||0}</p>
        </div>
        <div className="light-sensors right" style={{ left: 410,top: 95}}>
          <h3>Right Sensors</h3>
          <p>Right intensity:{lightSensors[1]||0}</p>
        </div>
        <div className="ultrasonic-sensor" style={{ left: 405,top: 230}}>
          <h3>Ultrasonic Sensor</h3>
          <button onClick={() => rotateUltrasonicSensor("left")}>Left</button>
          <button onClick={() => rotateUltrasonicSensor("right")}>Right</button>
          <p>Angle: {ultrasonicAngle}°</p>
        </div>

        <div className="motor left_upper" style={{ left: 50,top: 145}}>
          <h3>left upper motor</h3>
          <p>speed:{motors[0]||0}</p>
        </div>
        <div className="motor" style={{ left: 50,top: 445}}>
          <h3>left lower motor</h3>
          <p>speed:{motors[1]||0}</p>
        </div>
        <div className="motor" style={{ left: 410,top: 145}}>
          <h3>right upper motor</h3>
          <p>speed:{motors[2]||0}</p>
        </div>
        <div className="motor" style={{ left: 410,top: 445}}>
          <h3>right lower motor</h3>
          <p>speed:{motors[3]||0}</p>
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
            <line  className="sensor infrared left" x1="100" x2="100" y1="15" y2="0" stroke="black" strokeWidth="3" />
            <circle className={`sensor infrared right ${infraredSensors[1] ? "active" : ""}`} cx="100" cy="385" r="5" />
            <line  className="sensor infrared right" x1="100" x2="100" y1="385" y2="400" stroke="black" strokeWidth="3" />

            {/* Light sensors */}
            <circle className={`sensor light left ${lightSensors[0] ? "active" : ""}`} cx="20" cy="30" r="5" />
            <line  className="sensor infrared right" x1="20" x2="0" y1="30" y2="10" stroke="black" strokeWidth="3" />
            <circle className={`sensor light right ${lightSensors[1] ? "active" : ""}`} cx="180" cy="30" r="5" />
            <line  className="sensor infrared right" x1="180" x2="200" y1="30" y2="10" stroke="black" strokeWidth="3" />


            {/* Ultrasonic sensor */}
            <g style={{transform: `rotate(${ultrasonicAngle || 0}deg)`,transformOrigin: "100px 45px"}}>
              <circle className={`sensor ultrasonic`} cx="85" cy="45" r="10"/>
              <line  className={`sensor ultrasonic`} x1="85" x2="115" y1="45" y2="45" stroke="black" strokeWidth="2" />
              <circle className={`sensor ultrasonic`} cx="115" cy="45" r="10"/>
            </g>
            <line  className={`sensor ultrasonic`} x1="120" x2="200" y1="65" y2="145" stroke="black" strokeWidth="2" />

          </svg>
        </div>
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
