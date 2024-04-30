const button_on_ref = document.getElementById("btn_on_id");
const button_off_ref = document.getElementById("btn_off_id");

const slider_ref = document.getElementById("slider_id");
const val_slider_ref = document.getElementById("servo_val_id");

const button_city_ref = document.getElementById("validationville");
const CityName = document.getElementById("city_text");

const TempAPI_ref = document.getElementById("val_TempAPI");
const PresAPI_ref = document.getElementById("val_PresAPI");
const HumAPI_ref = document.getElementById("val_HumAPI");
const IconAPI_ref = document.getElementById("val_IconAPI");
const DescriptionAPI_ref = document.getElementById("val_DescriptionAPI");

const ChangeImg = document.getElementById("change_img");
const url_image = document.getElementById("icon_saison");
const mydate = document.getElementById("thedate");


let sliderValue = 0;
let cityName = "Paris";
let TempAPI = 0.0;
let PresAPI = 0;
let HumAPI = 0;
let IconAPI = 0;
let Description_API = "";
let month = new Date().getMonth();


//eventListener
slider_ref.addEventListener("change", slider_handler);
button_on_ref.addEventListener("click", button_on_handler);
button_off_ref.addEventListener("click", button_off_handler);
button_city_ref.addEventListener("click", city_handler);
//ChangeImg.addEventListener("click", changeImg_Handler);
//
window.addEventListener("load", changeImg_Handler);

function changeImg_Handler() {


  switch (month) {
    case 0://Galette
      url_image.src = "https://cdn.pixabay.com/photo/2015/01/10/16/14/galette-des-rois-595465_640.jpg";
      break;
    case 1://Crepes
      url_image.src = "https://cdn.pixabay.com/photo/2019/08/16/16/18/pancakes-4410606_1280.jpg";
      break;
    case 2://oiseau
      url_image.src = "https://cdn.pixabay.com/photo/2017/05/08/13/15/bird-2295431_640.jpg";
      break;
    case 3://paques
      url_image.src = "https://cdn.pixabay.com/photo/2017/02/23/21/58/easter-2093315_640.jpg";
      break;
    case 4://muguet
      url_image.src = "https://cdn.pixabay.com/photo/2019/05/30/16/13/lilies-of-the-valley-4240129_640.jpg";
      break;
    case 5://
      url_image.src = "https://cdn.pixabay.com/photo/2022/06/12/02/11/family-7257182_1280.jpg";
      break;
    case 6://14 juillet
      url_image.src = "https://cdn.pixabay.com/photo/2018/07/28/17/11/paris-3568523_1280.jpg";
      break;
    case 7://plage
      url_image.src = "https://cdn.pixabay.com/photo/2014/12/16/22/25/sunset-570881_640.jpg";
      break;
    case 8://école
      url_image.src = "https://cdn.pixabay.com/photo/2017/08/25/16/58/back-to-school-2680730_640.jpg";
      break;
    case 9://automne
      url_image.src = "https://cdn.pixabay.com/photo/2018/11/06/00/30/leaf-3797129_640.jpg";
      break;
    case 10://halloween
      url_image.src = "https://cdn.pixabay.com/photo/2017/08/06/18/05/pumpkin-2594747_640.jpg";
      break;
    case 11://noel
      url_image.src = "https://cdn.pixabay.com/photo/2020/12/08/17/15/christmas-5815034_640.jpg";
      break;

    default: url_image.src = "https://cdn.pixabay.com/photo/2019/05/30/16/13/lilies-of-the-valley-4240129_640.jpg";
      break;
  }
  month = month + 1;
}

function Json_Handler() {
  const xhttp = new XMLHttpRequest();
  //
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      const theJson = JSON.parse(this.responseText);
      //console.log(theJson);
    }
  }
  //
  xhttp.open("GET", "/weather/", true);
  xhttp.send();
}


function city_handler(event) {
  cityName = CityName.value;
  //val_slider_ref.textContent = cityName;

  const xhttp = new XMLHttpRequest();
  xhttp.open("GET", "/weather?city=" + cityName, true);
  xhttp.send();

  //console.log(cityName)
}

//
function slider_handler(event) {
  // console.log(event.target.value);
  sliderValue = event.target.value;
  val_slider_ref.textContent = sliderValue.toString();

  const xhttp = new XMLHttpRequest();
  xhttp.open("GET", "/servo?angle=" + sliderValue, true);
  xhttp.send();
}

//
function button_on_handler() {
  // console.log("bonton on");
  const xhttp = new XMLHttpRequest();
  xhttp.open("GET", "/action?led=1", true);
  xhttp.send();
}
//
function button_off_handler() {
  // console.log("bonton off");
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
      // console.log(temperatureValue);
      gaugeTemperature.refresh(temperatureValue);
    }
  }
  console.log(month);
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
      // console.log(LuxValue);
      gaugeLux.refresh(LuxValue);
    }
  }
  //
  xhttp.open("GET", "/LuxValue", true);
  xhttp.send();
}

function HUM_Handler() {
  const xhttp = new XMLHttpRequest();
  //
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      const HumValue = this.responseText;
      // console.log(HumValue);
      gaugeHumidity.refresh(HumValue);
    }
  }
  //
  xhttp.open("GET", "/Humvalue", true);
  xhttp.send();
}

function Pres_Handler() {
  const xhttp = new XMLHttpRequest();
  //
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      const PresValue = this.responseText;
      // console.log(PresValue);
      gaugePressure.refresh(PresValue);
    }
  }
  //
  xhttp.open("GET", "/Presvalue", true);
  xhttp.send();
}
//Renvoie HTML info API
function TEMP_API_Handler() {
  const xhttp = new XMLHttpRequest();
  //
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      TempAPI = this.responseText;
      //console.log(TempAPI);
      TempAPI_ref.textContent = TempAPI;
    }
  }
  //
  xhttp.open("GET", "/TempAPI", true);
  xhttp.send();
}

function Pres_API_Handler() {
  const xhttp = new XMLHttpRequest();
  //
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      PresAPI = this.responseText;
      //console.log(PresAPI);
      PresAPI_ref.textContent = PresAPI;
    }
  }
  //
  xhttp.open("GET", "/PresAPI", true);
  xhttp.send();
}

function Hum_API_Handler() {
  const xhttp = new XMLHttpRequest();
  //
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      HumAPI = this.responseText;
      //console.log(HumAPI);
      HumAPI_ref.textContent = HumAPI;
    }
  }
  //
  xhttp.open("GET", "/HumAPI", true);
  xhttp.send();
}

function Icon_API_Handler() {
  const xhttp = new XMLHttpRequest();
  //
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      IconAPI = this.responseText;
      //console.log(IconAPI);
      IconAPI_ref.src = IconAPI;
    }
  }
  //
  xhttp.open("GET", "/IconAPI", true);
  xhttp.send();
}

function Description_API_Handler() {
  const xhttp = new XMLHttpRequest();
  //
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      Description_API = this.responseText;
      //console.log(Description_API);
      DescriptionAPI_ref.textContent = Description_API;
    }
  }
  //
  xhttp.open("GET", "/DescriptionAPI", true);
  xhttp.send();
}

setInterval(temperature_Handler, 2000);
setInterval(Lux_Handler, 2000);
setInterval(Pres_Handler, 2000);
setInterval(HUM_Handler, 2000);

setInterval(TEMP_API_Handler, 2000);
setInterval(Hum_API_Handler, 2000);
setInterval(Pres_API_Handler, 2000);
setInterval(Icon_API_Handler, 2000);
setInterval(Description_API_Handler, 2000);

setInterval(changeImg_Handler, 60000);

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
