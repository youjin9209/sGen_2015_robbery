<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8;" />
	<title>업로드 파일목록</title>
	<!--[if lt IE 9]>
	<script src="http://ie7-js.googlecode.com/svn/version/2.1(beta4)/IE9.js"></script>
	<![endif]-->
	<link rel="stylesheet" type="text/css" href="./css/timeline.css" />

</head>
<body>

<div class="group">
        <div class="group_header">
            <div id="header_logo">
       <a href="http://210.125.96.109/webpage/main_page_test.html"><img src="image/logo_btn.jpg" style ="width:80px">
    </a>        </div>
            <div class="header_menu">
                <div id="header_timeline">
                <a href="timeline_page.php"><img src="image/timeline_btn.jpg" style="margin-left:600px; margin-bottom:60px"  height="15px"></a>    
                </div>
                <div id="header_statistics">
                <img src="image/statistic_btn.jpg" height="15px" style= "margin-bottom:60px;" alt="timeline"> 
                </div>
            </div>
            <div id="header_login">
		<a href="logout.php"><img src = "image/logout_btn.jpg" height="15px" style="margin-bottom:60px; margin-right:10px" alt="logout" ></a>
            </div>
        </div>
	<div class="center">

	

<?
//session
session_start();
if(!isset($_SESSION['sessionId'])){
	echo "<meta http-equiv=\"refresh\" content=\"0;url='main_page_test.html'\">";
	}
else{
	$sessionId = $_SESSION['sessionId'];

	
}

include"../logintest/dbconn.php";

$sql = "select * from video where userId='".$sessionId."'";
$result = mysqli_query($link,$sql)or dir('error');

$num_match = mysqli_num_rows($result);
if (!$num_match) {
	echo "<div class=\"no_data\">";
	echo "<H1>There is no data....<H2>";
	echo "</div>";
} else {
	

while ( $row = mysqli_fetch_assoc($result)  ) {
 if ($row['Reason1'] == "1") $reasons[]= "손을 든다"; 
if ($row['Reason2'] == "1") $reasons[]= "돈통이 열린다"; 
if ($row['Reason3'] == "1") $reasons[]= "어두운 계열의 옷"; 
 $img= $row['visitorFace'];
// echo htmlentities($row['content']);
	echo "<div class=\"center_event\">";
		echo "<div class=\"video\">";
	//	echo "<embed src=\"http://210.125.96.109//upload//video//".$row['content']."\" type=\"application/x-mplayer2\" width=\"653\" height=\"393\"/>";	
		echo "<video width=\"653\" height=\"363\" controls> <source src=\"http://210.125.96.109//upload/video//".$row['content']."\" type=\"video/webm\"></video>";	
	echo "</div>";



		echo "<div class=\"description\">";



			echo "<div class=\"video_date\">";
				echo "<div class=\"date_title\">";
				echo "<div class=\"date_img\"><img src=\"image/orange_clock.png\" width=\"15.14\" height=\"15.14\" />";
				echo "</div>";
				echo "<div class=\"date_txt\">사건발생 날짜 / 시간";
				echo "</div>";
				echo "</div>";
				

				echo "<div class=\"date_value\">";
				echo substr($row['videoDate'],0,8);
				echo "</div>";
				echo "<div class=\"time_value\">";
				echo substr($row['videoDate'],9,16) ;
				echo "</div>";		
			echo "</div>";
			
			echo "<div class=\"videoReason\">";
			echo "<div class=\"reason_img\"><img src=\"image/orange_notice.png\" width=\"15.14\" height=\"15.14\" />";
			echo "</div>";
			echo "<div class=\"reason_txt\">위험감지 요소";
			echo "</div>";
echo "<div class=\"reason_counter\"> 동작감지 (종업원)";
echo "</div>";	




			echo "<div class=\"reasonValue\">양손을 머리위로 든다";
			echo "</div>";
			////////
			/*	
			$arr_size = count($reasons);
			for ($i = 0 ; $i  < $arr_size ; $i++) {
				echo "<div class=\"reason_value".$i."\">";
				
				echo $reasons[$i]; 
				echo "</div>";
			}

			//////
			echo "</div>";

			echo "<div class=\"videoDangerPoint\">";
				echo "<div class=\"Danger_txt\">총 위험 점수";
				echo "</div>";
				echo "<div class=\"Danger_value\">";
				echo htmlentities($row['videoDangerPoint']);
				echo "</div>";
			echo "</div>";
*/
	
			echo"</div>";

			echo "<div class=\"delete\"> <a href=\"#\"> <img src=\"image/delete.png\" width=\"103\" height=\"10\" /> </a> ";
			echo "</div>";

		echo "</div>";



	// end of center_event div
	echo "</div>";


} } 

?>
     
      <!--center div-->
      </div>
 <!--group div-->
</div>


</body>
</html>
