<?php
  $inputId = $_POST["id"];
  $inputPw = $_POST["passwd"];
  
  if(!$inputId){
    echo 'Please write your id';
  }
  if(!$inputPw){
    echo 'Please write your password';
  }
  
  include"./dbconn.php";
  
  $sql = "select * from customer where userId = '$inputId'";
  $result = mysqli_query($link,$sql)or dir('error querying database.');
  
  $num_match = mysqli_num_rows($result);
  
  if(!$num_match){
    echo("<script> 
      window.alert('id no exist')
      history.go(-1)
          </script>");
  }else{
    $row = mysqli_fetch_array($result);
    $db_passwd = $row[userPw];
      if($inputPw! = $db_passwd){
        echo ("<script> 
          window.alert('wrong password')
          history.go(-1)
              </script>");
              exit;
      }else{
        echo "success";
        $userId = $row[userId];
        session_start();
        session_register(userId);
        mysqli_close($link);
      }
  }
  
?>
