#include <functions.h>

// Initialize needed variables
int speedRight = 45;              // Variable speed for right wheel
int speedLeft = 135;              // Variable speed for left wheel
int sendVal[5] = {1, 90, 90, 90}; // Array for variable data to be stored in

// Command handler
esp_err_t cmd_handler(httpd_req_t *req)
{
  char *buf;
  size_t buf_len;
  char variable[32] = {
      0,
  };
  char value[32] = {
      0,
  };

  buf_len = httpd_req_get_url_query_len(req) + 1;
  if (buf_len > 1)
  {
    buf = (char *)malloc(buf_len);
    if (!buf)
    {
      httpd_resp_send_500(req);
      return ESP_FAIL;
    }
    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK)
    {
      if (httpd_query_key_value(buf, "var", variable, sizeof(variable)) == ESP_OK &&
          httpd_query_key_value(buf, "val", value, sizeof(value)) == ESP_OK)
      {
      }
      else
      {
        free(buf);
        httpd_resp_send_404(req);
        return ESP_FAIL;
      }
    }
    else
    {
      free(buf);
      httpd_resp_send_404(req);
      return ESP_FAIL;
    }
    free(buf);
  }
  else
  {
    httpd_resp_send_404(req);
    return ESP_FAIL;
  }

  int val = atoi(value);
  sensor_t *s = esp_camera_sensor_get();
  int res = 0;
  // Setting the servo wheel speed
  if (!strcmp(variable, "speed"))
  {
    if (val > 0)
      val = 0;
    else if (val < -90)
      val = -90;
    speedRight = abs(val);
    /* Speed is set for the right wheel. Converting the speed for the left
        wheel since it's orientated the opposite way of the right wheel */
    if (speedRight <= 90)
    {
      speedLeft = (90 - abs(val)) + 90;
    }
    else
    {
      speedLeft = 90 - (abs(val) - 90);
    }
  }
  // Setting Eddie's direction
  else if (!strcmp(variable, "car"))
  {
    if (val == 1)
    {
      // Forward
      sendVal[3] = speedLeft;  // speedRight;
      sendVal[2] = speedRight; // speedLeft;
    }
    else if (val == 2)
    {
      // Turn Left
      sendVal[3] = speedRight;
      sendVal[2] = speedRight;
    }
    else if (val == 3)
    {
      // Stop
      sendVal[3] = 90;
      sendVal[2] = 90;
    }
    else if (val == 4)
    {
      // Turn Right
      sendVal[3] = speedLeft;
      sendVal[2] = speedLeft;
    }
    else if (val == 5)
    {
      // Backward
      sendVal[3] = speedRight; // speedLeft;
      sendVal[2] = speedLeft;  // speedRight;
    }
    else if (val == 6)
    {
      // Switch back and forth between controlled and autonomous mode
      if (sendVal[0] == 1)
        sendVal[0] = 2;
      else if (sendVal[0] == 2)
        sendVal[0] = 1;
    }
  }
  // Sets Neck servo position
  else if (!strcmp(variable, "sight"))
  {
    if (val > 0)
      val = 0;
    else if (val < -180)
      val = -180;
    sendVal[1] = abs(val);
  }
  else
  {
    res = -1;
  }

  if (res)
  {
    return httpd_resp_send_500(req);
  }

  httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
  return httpd_resp_send(req, NULL, 0);
}
