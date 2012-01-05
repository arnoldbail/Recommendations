<?php
/**************************************************
*  Escape codes ar at: 
*   http://php.net/manual/en/language.types.string.php
*
****************************************************/
$out_array = array();
$entry = array();
/*$professor_name = "";*/


$nl = "<br />";

$out_array[1] = "<div id='ClickWordList'>";
$out_array[1] .= str_repeat("\n", 5);


if ($professor_school_logo <> "") {
 $schooldir = str_replace( " ", "-", $professor_school_logo_url);
 $out_array[1] .= '<p><img alt="School Logo" src=' . $schooldir . '></p>';
}

if ($school_contact_postal <> "") {
 $out_array[1] .= '<p style="margin-left: 280px;">';
} else {
 $out_array[1] .= '<p style="margin-left: 280px;">';
}
$out_array[1] .= $professor_name . "<br/>";
//letterhead in profile
$out_array[1] .= str_replace( "//", "<br/>", $professor_ext_address);
$out_array[1] .= $nl . $current_date;
$out_array[1] .= '</p>';


// School Contact information 
$out_array[1] .= "\n\n";
if ($school_contact_postal <> "") {
  $out_array[1] .= str_replace( "//", $nl, $school_contact_postal);
}

$out_array[1] .= "<p>Dear Colleague,</p>";
$out_array[1] .= "<br/>";
$out_array[1] .= "<br/>";
$out_array[1] .= "<p align=center style='color:blue;'>Click 'Recommendlate Assistant' above and Drag'n Drop text to this document!</p>";
$out_array[1] .= "<br/>";
$out_array[1] .= "<br/>";
$out_array[1] .= "<br/>";
$out_array[1] .= "<br/>";
$out_array[1] .= "<br/>";
$out_array[1] .= "<br/>";
$out_array[0] = $student_full;
$out_array[2] = $student_full;
	 

$out_array[1] .= "<p>Sincerely,</p></div>";

$out_array[1] .= $professor_name;
?>