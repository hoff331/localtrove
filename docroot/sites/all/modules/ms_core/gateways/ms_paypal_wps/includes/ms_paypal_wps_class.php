<?php
// Copyright 2009 Leighton Whiting http://www.moneyscripts.net

class ms_paypal_wps_class {
  var $lastError;
  var $ipnResult;
  var $ipn = array();
  var $values = array();

  function ms_paypal_wps_class($ipn_vars = NULL) {
    $this->ipnLink = (isset($ipn_vars['test_ipn']) AND $ipn_vars['test_ipn']) ? 'https://www.sandbox.paypal.com/cgi-bin/webscr' : 'https://www.paypal.com/cgi-bin/webscr';
    $this->ipn_vars = $ipn_vars;
    $this->lastError = '';
    $this->ipnResult = '';
  }

  function add($field, $value) {
    $this->values["$field"] = $value;
  }

  function submit($button_value) {
    $form = "<form id='paypalPaymentForm' target='_self' method='post' name='paypal_form' action='". $this->ipnLink ."'>";
    foreach ($this->values as $name => $value) {
      $form .= "<input type='hidden' name='$name' value='$value' />";
    }
    $form .= "<input type='submit' value='$button_value'></form>";
    return $form;
  }

  function verify() {
    $url_parsed=parse_url($this->ipnLink);
    $ipn_post = '';
    foreach ($this->ipn_vars as $field=>$value) {
      $this->ipn["$field"] = $value;
      $ipn_post .= $field.'='.urlencode(stripslashes($value)).'&';
    }
    $ipn_post.="cmd=_notify-validate"; // append ipn command
    //$fp = fsockopen($url_parsed['host'], "80", $err_num, $err_str, 30);
    $fp = fsockopen('ssl://'.$url_parsed['host'], "443", $err_num, $err_str, 30);
    if(!$fp) {
      $this->lastError = "fsockopen error no. $errnum: $errstr";
      return FALSE;
    }
    else {
      fputs($fp, "POST $url_parsed[path] HTTP/1.1\r\n");
      fputs($fp, "Host: $url_parsed[host]\r\n");
      fputs($fp, "Content-type: application/x-www-form-urlencoded\r\n");
      fputs($fp, "Content-length: ".strlen($ipn_post)."\r\n");
      fputs($fp, "Connection: close\r\n\r\n");
      fputs($fp, $ipn_post . "\r\n\r\n");
      while(!feof($fp)) {
        $this->ipnResult .= fgets($fp, 1024);
      }
      fclose($fp);
    }
    if (preg_match('/VERIFIED/',$this->ipnResult)) {
      return TRUE;
    }
    else {
      $this->lastError = 'IPN Validation Failed.';
      return FALSE;
    }
  }
}
