<?php
session_start();
session_unset();
   $inputId=$_POST["id"];
   $inputPw=$_POST["passwd"];
 
  if(!$inputId){
  echo(" <script> 
  window.alert('please write your id') 
  history.go(-1) 
  </script> "); 
  } 
 
  if(!$inputPw) {
  echo(" <script> 
  window.alert('please write your password') 
  history.go(-1) 
  </script> "); 
  }
  include"../logintest/dbconn.php"; 
 
  $sql = "select * from customer where userId='$inputId'"; 
  $result = mysqli_query($link, $sql)or dir('error querying database.'); 
   
  $num_match = mysqli_num_rows($result); 
   
  if(!$num_match) {
    echo(" <script> 
    window.alert('id no exist.') 
    history.go(-1) 
  </script> "); 
  }else{
    $row = mysqli_fetch_array($result); 
    $db_passwd = $row[userPw]; 
      if($inputPw != $db_passwd) {
        echo(" <script> 
            window.alert('wrong password') 
            history.go(-1) 
              </script> ");
        exit; 
      }
      else { 
        $sessionId = $inputId;
        session_start();
        $_SESSION['sessionId'] =$sessionId;
        mysqli_close($link);
        header("Location:./timeline_page.php");
        exit();
      }
  }
?>

