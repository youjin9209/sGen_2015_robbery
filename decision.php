<?php
header('Content-Type: application/json; charset=UTF-8');
/*
$json = '{"head":{59,15},"left":{1,53},"right":{175,51},"center":{90,33},"hist":{145,145,145}}';

$decode = json_decode($json,true);

$array_a = $decode['head'];
echo $array_a;

 
// 컨텐츠 타입이 JSON 인지 확인한다
if(!in_array('application/json',explode(';',$_SERVER['CONTENT_TYPE']))){
	echo json_encode(array('result_code' => '400'));
	exit;
}
*/ 
$__rawBody = file_get_contents("php://input"); // 본문을 불러옴

//$decode = json_decode($__rawBody, true);
$__getData = array(json_decode($__rawBody));

/*
$array_a = $decode['hist'][0]['r']; 
echo $array_a;



   $array_c = $decode['head'];
   /*
    foreach($array_c as $key => $value)
   {
    echo $value['id']."<br/>";
    echo $value['active']."<br/>";
   }
*/

// $__getData = array(json_decode($__rawBody)); // 데이터를 변수에 넣고
// foreach($__getData as $key => $value){ echo $value; } 
/*
처리부
*/
 
 echo json_encode(array('result_code' => '200', 'result'=>$__getData));
 
?>
