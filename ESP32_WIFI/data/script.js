const button_on_ref = document.getElementById("btn_on_id");
const button_off_ref = document.getElementById("btn_off_id");

const temperature_ref = document.getElementById("temperature_id");
const lux_ref = document.getElementById("temperature_id");

const slider_ref = document.getElementById("slider_id");
const val_slider_ref = document.getElementById("servo_val_id");

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
  const xhttp = new XMLHttpRequest();
  xhttp.open("GET", "/action?led=1", true);
  xhttp.send();
}
//
function button_off_handler() {
  console.log("bonton off");
  const xhttp = new XMLHttpRequest();
  xhttp.open("GET", "/action?led=0", true);
  xhttp.send();
}

function temperature_Handler() {
  const xhttp = new XMLHttpRequest();
  //
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      const temperatureValue = this.responseText;
      console.log(temperatureValue);
      gaugeTemperature.refresh(temperatureValue);
    }
  }
  //
  xhttp.open("GET", "/temperatureValue", true);
  xhttp.send();
}

function Lux_Handler() {
  const xhttp = new XMLHttpRequest();
  //
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      const LuxValue = this.responseText;
      console.log(LuxValue);
      gaugeLux.refresh(LuxValue);
    }
  }
  //
  xhttp.open("GET", "/LuxValue", true);
  xhttp.send();
}

/* function set_gauge_value() {
  gaugeTemperature.refresh(temperatureValue);

  // gaugeHumidity.refresh();

  // gaugePressure.refresh();

  // gaugeLux.refresh();
} */
setInterval(temperature_Handler, 2000);
setInterval(Lux_Handler, 2000);

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
  value: 0,
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
  value: 0,
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
  value: 0,
  min: 0,
  max: 1000,
  decimals: 0,
  title: "",
  label: "Lux",
  relativeGaugeSize: true,
  gaugeWidthScale: 0.6,
});
