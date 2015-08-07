<?php

session_start();
session_destroy();

header('Location:main_page_test.html');
exit();

?>
