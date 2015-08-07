<?php
    $videoId = $_POST['videoId'];
    $userId = $_POST['userId'];
    $videoDangerPoint = $_POST['videoDangerPoint'];
    $videoReason = $_POST['videoReason'];
    $visitorFace = $_FILES['vistiorFace']['name'];
    //$content = $_FILES['videofile']['name'];
    $date = new DateTime;
    $content = $date->format("y_m_d_h_i_s").".webm";
    $videoDate = $date ->format("y.m.d/h:i");
    
    $uploaddir='/var/www/html/upload/video/';
    //$uploadfile = $uploaddir.basename($_FILES['videofile']['name']);
    $uploadfile = $uploaddir.$content;
    
    //잘 들어왔는지 확인하기위해 writetest에 써준다 
    $fp = fopen("writetest2.dat","w");
    
    if(move_uploaded_file($_FILES['videofile']['tmp_name'],$uploadfile)){
      fwrite($fp,"upload success");
      echo '1';
    }
    fwrite($fp, $_FILES['videofile']['error']);
    
    //image(vistiorface) 를 지정한 경로에 저장
    $picuploaddir = '/var/www/html/upload/image/';
    $picuploadfile = $picuploaddir.basename($_FILES['visitorFce']['name']);
    if(move_uploaded_file ($_FILES['visitorFace']['tmp_name'],$picuploadfile)){
      fwrite($fp,"aupload success");
      echo 'image upload success';
    }
    fwrite($fp, $_FILES['visitorface']['error']);
    
    include"./logintest/dbconn.php";
    
    //날라온거 db에 insert 해줘
    $sql = "INSERT INTO video (userId, videoDangerPoint, videoDate, videoReason, vistorFace, content)
    VALUES ('$userId','$videoDangerPoint','$videoDate','$videoReason',$visitorFace', '$content')";
    
    fwrite($fp,$sql);
    $result = mysqli_query($link,$sql) or die (fwrite($fp,'die'));
    fclose($fp);
    chmod("writetest.dat",0777);
    mysqli_close($link);
?>
