<?php
/***************************************************
* Build the body text from the recommendations tables.
* - Read the database fields and load variables
* - build out_array based on the document type.
****************************************************/

function recommends_wrec_assist($s_email,$name){

$current_date = date("F") . " " . date("j") . ", " . date("Y");

// Professor fields/Heading
$entryp = array();
$email = variable_get('recommends_professor_email');
$entries = recommends_prof_entry_load_srch_email($entryp,$email);
if (!empty($entries)) {
	$rows = array();
	foreach ($entries as $entry) {
	// Sanitize the data before handing it off to the theme layer.
	  $rows[] = array_map('check_plain',(array) $entry);
	}
	for ($i = 0; $i <= sizeof($rows)-1; $i++) {
	 
	 $professor_name        = $rows[$i]['p_name'];
	 $professor_ext_address = $rows[$i]['p_school_letter'];
	 $professor_position    = $rows[$i]['p_position']; 
	 $professor_program     = $rows[$i]['p_program'];
	 $professor_school      = $rows[$i]['p_school'];
	 
	 $xschool = str_replace( " ", "-", $professor_school);
	 
	 $professor_school_logo = 'sites/default/files/' . $xschool . '/' . variable_get('recommends_professor') . "/" . $rows[$i]['p_school_logo']; 
	 } 
}

//School fields
$email = variable_get('recommendlate_student_email');
$school = variable_get('recommendlate_wrec_student_school');

$entries = recommends_rc_entry_load_rcmd($entry, $email, $school);
if (!empty($entries)) {
	$rows = array();
	foreach ($entries as $entry) {
	// Sanitize the data before handing it off to the theme layer.
	  $rows[] = array_map('check_plain',(array) $entry);
	}
	for ($i = 0; $i <= sizeof($rows)-1; $i++) {
	 
	 $student_prefix    = $rows[$i]['prefix'];
	 $student_full_text    = $rows[$i]['prefix'] . " " . $rows[$i]['firstname'] . " " . $rows[$i]['initial']  . " " . $rows[$i]['lastname'] .  " " . $rows[$i]['suffix'];
	 
	 $student_full = $rows[$i]['lastname'] . $rows[$i]['firstname']  .  $rows[$i]['initial']  . '-' . $rows[$i]['r_school'] . '-' .$rows[$i]['r_date_due_year'];
	 
	 
	 //title field in recommendlate
	 $student_first   = $rows[$i]['firstname'];
	 $student_pre_last = $rows[$i]['prefix']  . " " . $rows[$i]['lastname'];
	 $student_last =  $rows[$i]['lastname'];
	 $student_professor_comments   = $rows[$i]['s_prof_comments'];
	 
	 $school_program  = $rows[$i]['r_program'];
	 $school_contact_postal  = $rows[$i]['r_school_contact_postal'];
	 }
}

//Course(s)
// Get all entries in the recommends_cs table.
  if ($entries = recommends_cs_entry_load_rcmd($entry,$email)) {
    $rows = array();
    foreach ($entries as $entry) {
      // Sanitize the data before handing it off to the theme layer.
      $rows[] = array_map('check_plain', (array) $entry);
    }

    $course_total = sizeof($rows);
    for ($i = 0; $i <= sizeof($rows)-1; $i++) {
    	$course_name[$i]      = $rows[$i]['i_coursename'];
    	$course_semester[$i]  = $rows[$i]['c_semester'];
    	$course_year[$i]      = $rows[$i]['c_year'];
    	$course_grade[$i]     = $rows[$i]['c_grade'];
    	$course_comments[$i]  = $rows[$i]['c_comments'];
    	$course_objective[$i]  = $rows[$i]['i_objective'];

 		switch (substr($rows[$i]['c_grade'],0,1)) {
    		case 'A':
     		 $course_grade_comments[$i]  = $rows[$i]['i_grade_a'];
     		 break;
    		case 'B':
      		 $course_grade_comments[$i]  = $rows[$i]['i_grade_b'];
      		 break;
    		default:
      		 $course_grade_comments[$i]  = $rows[$i]['i_grade_other'];
      		 break;
  		}
  	} 
  }

/**************************************************
*  Escape codes ar at: 
*   http://php.net/manual/en/language.types.string.php
*
****************************************************/
$out_array = array();
$entry = array();
$course_total = 0;
/*$professor_name = "";*/

$nl = "<br>";

$poss = 'His/Her';
if ($student_prefix == 'Ms.' || $student_prefix == 'Mrs.') {
 $poss = 'Her';
 $possL = 'her';
 $nom = 'She';
 $nomL = 'she';
 $obj = 'Her';
 $objL = 'her';
}
if ($student_prefix == 'Mr.' ) {
 $poss = 'His';
 $possL = 'his';
 $nom = 'He';
 $nomL = 'he';
 $obj = 'Him';
 $objL = 'him';
}


$out_array[1] = "<em>Tips</em><ul>

<li>The applicant's extra-curricular work, in " . $poss . " discipline, of which you are aware;</li>
<li>The applicant's persistence in tackling challenging problems;</li>
<li>When and in what capacity you have worked with the applicant.</li>
</ul>";

$out_array[1] .= "<em>Introductions</em>";
$out_array[1] .= "<p>I am currently a " . $professor_position . " in the " . $professor_program . " at " . $professor_school . ". ";

$out_array[0] = $student_full;
$out_array[2] = $student_full . $school;
drupal_set_title('');	 
$out_array[1] .= "I would like to take this opportunity to recommend " . $student_full_text . " for acceptance into your " . $school_program . " program. </p>";


$out_array[1] .= "<p>As a " . $professor_position . " in the " . $professor_program . " at " . $professor_school . ", I have had the pleasure of knowing " . $student_full . " for the last xxx years. " . $nom . " has been a tremendous student and an asset to our school . I would like to take this opportunity to recommend " . $student_first . " for your " . $school_program . " program. </p>";

$out_array[1] .= "<p>" . $student_first . " " . $student_last .  " is an extraordinary young xxx. As " . $possL . " "  . " "; 

if ($course_total > 0) {
  for ($i = 0; $i <= $course_total-1; $i++) {
   $out_array[1] .= $course_name[$i];
   if ($i > 1) {
   	 $out_array[1] .=  " | ";
   }
   }
}

$out_array[1] .= " Professor, I have seen many examples of " . $poss . " talent and have long been impressed by " . $poss . " diligence and work ethic. I understand that " . $student_first . " is applying to the undergraduate business program at your school. I would like to recommend her for admission."; 

$out_array[1] .= "<p><em>Courses Taken</em</p>";

if ($course_total > 0) {
  for ($i = 0; $i <= $course_total-1; $i++) {	 
    $out_array[1] .= "<p>";
    $out_array[1] .= $course_name[$i] . "  " . $course_semester[$i] . "  " . $course_year[$i] . "  Grage: " .  $course_grade[$i] . '</p>';
  
    $out_array[1] .= "<ul><li>Ccourse objectives: </li></ul><p>";
    $out_array[1] .= $course_objective[$i] . "</p>";
    	
    $out_array[1] .= "<ul><li>Course Comments: </li></ul><p>" .  $course_comments[$i] . "</p>";
$out_array[1] .= "<ul><li>The typical characeristics of a student at grade level " . $course_grade[$i] . " is: " .  $course_grade_comments[$i] . "</li></ul>";
  }
 } else {
   $out_array[1] .= "<p>There were no enrolled courses.</p>";
}
 
 
 $out_array[1] .= "<p><em>Overall comments</em</p>";
 
 
$out_array[1] .= "<p> " .  $student_professor_comments . "</p>";


$out_array[1] .= "<p><em>Concluson</em</p>";
$out_array[1] .= "<p>";

$out_array[1] .= "In conclusion, I would like to reaffirm my enthusiastic recommendation for " . $student_pre_last . "'s acceptance into your " . $school_program . " program.";

$out_array[1] .= "If you have any further questions about " . $student_pre_last . "'s ability, or this recommendation, please do not hesitate to contact me.</p>";
	
return $out_array[1];
}


