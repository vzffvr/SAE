const button_on_ref = document.getElementById("btn_on_id");
const button_off_ref = document.getElementById("btn_off_id");
//const temperature_ref = document.getElementById("temperature_id");
//let temperatureValue = 0;



//eventListener
button_on_ref.addEventListener("click", button_on_handler);
button_off_ref.addEventListener("click", button_off_handler);
function button_on_handler() {

}
function button_off_handler() {

}


//
const gaugeTemperature = new JustGage({
  id: "gauge_temperature",
  value: getRandomInt(0, 30),
  min: -10,
  max: 50,
  decimals: 2,
  title: "",
  label: "°C",
  relativeGaugeSize: true,
  gaugeWidthScale: 0.6,
});
//
const gaugeHumidity = new JustGage({
  id: "gauge_humidity",
  value: getRandomInt(0, 100),
  min: 0,
  max: 100,
  decimals: 2,
  title: "",
  label: "%",
  relativeGaugeSize: true,
  gaugeWidthScale: 0.6,
});
//
const gaugePressure = new JustGage({
  id: "gauge_pressure",
  value: getRandomInt(0, 1300),
  min: 0,
  max: 1300,
  decimals: 0,
  title: "",
  label: "hPa",
  relativeGaugeSize: true,
  gaugeWidthScale: 0.6,
});
//
const gaugeLux = new JustGage({
  id: "gauge_lux",
  value: getRandomInt(0, 1000),
  min: 0,
  max: 1000,
  decimals: 0,
  title: "",
  label: "Lux",
  relativeGaugeSize: true,
  gaugeWidthScale: 0.6,
});
