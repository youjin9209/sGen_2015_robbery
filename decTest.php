<?php

// $json = '{"champions":[{"id":266,"active":true},{"id":103,"active":true}]}';
// $json = '{"head":{"x":59,"y":15}}';


$json = $_POST['userId'];
echo $json;


/*
$decode = json_decode($json, true);

$array_a = $decode['head']['x']; 
echo $array_a;


echo "<br/><br/>";
/*
   $array_c = $decode['head'];
   foreach($array_c as $key => $value)
   {
    echo $value['x']."<br/>";
    echo $value['y']."<br/>";
   }

*/
?>
