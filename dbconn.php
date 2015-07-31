<? php
 $link = mysqli_connect('localhost','root','0644','sgen');
     if(!link){
      die('Could not connect: ' .mysql_error());
     }else{
      echo 'Connected successfullly';
     }
     
?>     
     
