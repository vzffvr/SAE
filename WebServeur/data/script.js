const button_on_ref = document.getElementById("btn_on_id");
const button_off_ref = document.getElementById("btn_off_id");

const temperature_ref = document.getElementById("temperature_id");
const lux_ref = document.getElementById("temperature_id");

const slider_ref = document.getElementById("slider_id");
const val_slider_ref = document.getElementById("servo_val_id");
let temperatureValue = 0;
let sliderValue = 0;


//eventListener
slider_ref.addEventListener("change", slider_handler);
button_on_ref.addEventListener("click", button_on_handler);
button_off_ref.addEventListener("click", button_off_handler);

//
function slider_handler(event) {
  console.log(event.target.value);
  sliderValue = event.target.value;
  val_slider_ref.textContent = sliderValue.toString();
}

//
function button_on_handler() {
  console.log("bonton on");
}
//
function button_off_handler() {
  console.log("bonton off");
}

//
function set_gauge_value() {
  gaugeTemperature.refresh(Math.floor(Math.random() * 100));

  gaugeHumidity.refresh(Math.floor(Math.random() * 100));

  gaugePressure.refresh(Math.floor(Math.random() * 100));

  gaugeLux.refresh(Math.floor(Math.random() * 100));
}
setInterval(set_gauge_value, 5000);

//
const gaugeTemperature = new JustGage({
  id: "gauge_temperature",
  value: 0,
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
