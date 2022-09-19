#include <functions.h>

// HTML code for web app
static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<!doctype html>
<html>

<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>Eddie</title>
  <style>
    body {
      font-family: Arial, Helvetica, sans-serif;
      background: #181818;
      color: #EFEFEF;
      font-size: 16px;
      -webkit-user-select: none;
      user-select: none;
    }

    .button {
      background-color: #ff3034;
      border: none;
      border-radius: 4px;
      color: white;
      padding: 22px 10px;
      text-align: center;
      font-size: 16px;
      margin: 4px 60px;
      cursor: pointer;
    }

    .slider1 {
      appearance: none;
      width: 50%;
      height: 15px;
      border-radius: 10px;
      background: #d3d3d3;
      outline: none;
    }

    .slider2 {
      appearance: none;
      width: 60%;
      height: 15px;
      border-radius: 10px;
      background: #d3d3d3;
      outline: none;
    }

    .slider1::-webkit-slider-thumb {
      appearance: none;
      width: 30px;
      height: 30px;
      border-radius: 50%;
      background: #ff3034;
    }

    .slider2::-webkit-slider-thumb {
      appearance: none;
      width: 30px;
      height: 30px;
      border-radius: 50%;
      background: #ff3034;
    }

    .label {
      color: #ff3034;
      font-size: 18px;
    }
  </style>
</head>

<body>
  <div align=center> <img id="camstream" src="" style='width:350px;'></div>
  <br />
  <br />
  <div align=center>
    <label class="label">Look Left</label>
    <input type="range" class="slider1" id="sight" min="-180" max="0" value="-90"
      oninput="try{fetch(document.location.origin+'/control?var=sight&val='+this.value);}catch(e){}">
    <label class="label">Look Right</label>
  </div>
  <br />
  <br />
  <div align=center>
    <button class="button" id="forward" ontouchstart="fetch(document.location.origin+'/control?var=car&val=1');"
      ontouchend="fetch(document.location.origin+'/control?var=car&val=3');">Forward</button>
  </div>
  <div align=center>
    <button class="button" id="turnleft" ontouchstart="fetch(document.location.origin+'/control?var=car&val=2');"
      ontouchend="fetch(document.location.origin+'/control?var=car&val=3');">Turn Left</button>
    <label class="label"></label>
    <!--<button class="button" id="stop" onclick="fetch(document.location.origin+'/control?var=car&val=3');">Stop</button>-->
    <button class="button" id="turnright" ontouchstart="fetch(document.location.origin+'/control?var=car&val=4');"
      ontouchend="fetch(document.location.origin+'/control?var=car&val=3');">Turn Right</button>
  </div>
  <div align=center>
    <button class="button" id="backward" ontouchstart="fetch(document.location.origin+'/control?var=car&val=5');"
      ontouchend="fetch(document.location.origin+'/control?var=car&val=3');">Backward</button>
  </div>
  <br />
  <br />
  <div align=center>
    <label class="label">Slower</label>
    <input type="range" class="slider2" id="speed" min="-90" max="0" value="-45"
      onchange="try{fetch(document.location.origin+'/control?var=speed&val='+this.value);}catch(e){}">
    <label class="label">Faster</label>
  </div>
  <br />
  <br />
  <div align=center>
    <button class="button" id="switch" onclick="fetch(document.location.origin+'/control?var=car&val=6');">Switch to:
      Autonomous</button>
  </div>
  <script>
    const btn = document.getElementById('switch');
    btn.addEventListener('click', function handleClick() {
      const initialText = 'Switch to: Controlled';
      if (btn.textContent.toLowerCase().includes(initialText.toLowerCase())) {
        btn.textContent = 'Switch to: Autonomous';
      } else {
        btn.textContent = initialText;
      }
    });
    window.onload = document.getElementById("camstream").src = window.location.href.slice(0, -1) + ":81/stream";
  </script>
</body>

</html>
)rawliteral";

// Send HTML code
esp_err_t index_handler(httpd_req_t *req)
{
  httpd_resp_set_type(req, "text/html");
  return httpd_resp_send(req, (const char *)INDEX_HTML, strlen(INDEX_HTML));
}
