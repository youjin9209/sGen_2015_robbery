<?php
  die("1");
  // json string화 해서 POST해준거 받기
  $json = $_POST['jsondata'];
  $json = addslashes($json);
  
  // json 받은거 php에서 svm 돌리기
  $cmd = "/usr/bin/python /var/www/html/cctv_svm_divide.py 2>&1 ".$json;
  exec($cmd, $rtn);

?>
  
