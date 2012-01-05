<?php
/**************************************************
*  Escape codes ar at: 
*   http://php.net/manual/en/language.types.string.php
*
****************************************************/
$out_array = array();
$entry = array();
/*$professor_name = "";*/

$tab = "\n" . str_repeat("\t", 8);
$nl = "\n";

$out_array[1] = str_repeat("\n", 5);
$out_array[1] .= $tab;
$out_array[1] .= $professor_name;
$out_array[1] .= $tab;
//letterhead in profile
$out_array[1] .= str_replace( "//", $tab, $professor_ext_address);
$out_array[1] .= $tab . $current_date;

// School Contact information 
$out_array[1] .= "\n\n";
if ($school_contact_postal <> "") {
  $out_array[1] .= str_replace( "//", $nl, $school_contact_postal);
}

$out_array[1] .= "

Dear Colleague,

Notes:
The applicant's extra-curricular mathematics work of which you are aware;
The applicant's persistence in tackling challenging problems;
When and in what capacity you have worked with the applicant.
 ";

$out_array[1] .= "\nI am currently a " . $professor_position . " in the " . $professor_program . " at " . $professor_school . ". ";

$out_array[0] = $student_full;
$out_array[2] = $student_full . $school_name;
	 
$out_array[1] .= "I would like to take this opportunity to recommend " . $student_full_text . " for acceptance into your " . $school_program . " program. ";

for ($i = 0; $i <= $course_total-1; $i++) {	 
  $out_array[1] .= $student_first . " enrolled in my ";
  $out_array[1] .= $course_name[$i] . " course in the " . $course_semester[$i] . " semester of " . $course_year[$i] . " with a grade of " . $course_grade[$i] . '.';
  
  $out_array[1] .= "The course objectives were:";
  $out_array[1] .= $course_objective[$i];
    	
  $out_array[1] .= "\n\nThe following are general comments made by the professor during the course: ";
  if ($course_comments[$i] <> "") {
    $out_array[1] .= $course_comments[$i]  . "\n";
  }
    	
  $out_array[1] .= "\nThe following statement is characeristics of a student at the grade attained: \n";
   
  $out_array[1] .= $course_grade_comments[$i];
 		 
}

$out_array[1] .= "\n\nThe following are overall comments made by the professor concerning the student:";
 
$out_array[1] .= $student_professor_comments;

$out_array[1] .= "\n\n";

$out_array[1] .= "In conclusion, I would like to reaffirm my enthusiastic recommendation for " . $student_pre_last . "'s acceptance into your " . $school_program . " program.";
$out_array[1] .= "\n";
$out_array[1] .= "If you have any further questions about " . $student_pre_last . "'s ability, or this recommendation, please do not hesitate to contact me.\n";

$out_array[1] .= $tab;
$out_array[1] .= "Sincerely,";
$out_array[1] .= $tab;
$out_array[1] .= $professor_name;
?>