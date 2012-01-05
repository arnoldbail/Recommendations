<?php
/*************************************************************
 * Build/display student information sheet
 ***************************************************************/
function recommends_wrec_infosheet($s_email,$name){
  global $user;
 
  // Search for the student record
 $search = $s_email;
  
 $entry = array();

$entries = recommends_st_entry_load_email($entry,$search);
$rows = array();
foreach ($entries as $entry) {
// Sanitize the data before handing it off to the theme layer.
	$rows[] = array_map('check_plain',(array) $entry);
}
  
 $msg ="Student: ";
 $msg .= $rows[0]['prefix'] . " ";
 $msg .= $rows[0]['lastname'] . ", ";
 $msg .= $rows[0]['firstname'] . " ";
 $msg .= $rows[0]['initial'] . "  ";
 $msg .= $rows[0]['suffix'] . "<br/>";
 $msg .="Email: ";
 $msg .= $rows[0]['s_email'] . "<br/>";
 $msg .="Date Requested: ";
 $msg .= $rows[0]['s_req_date'] . "<br/>";
 
 $msg .="Master Document: ";
 $msg .= $rows[0]['s_master_doc']; 
 
 $msg .= "<br/>Statement of intent/POV/Prof comments: ";
    	if ($rows[0]['s_comments'] == "") {
    		$msg .= " None"  . "\n";
    	} else {
    		$msg .= "<br/>" . $rows[0]['s_comments']  . "\n";
    	}
 
  $msg .= "<br/>Professor comments: ";
    	if ($rows[0]['s_prof_comments'] == "") {
    		$msg .= " None"  . "\n";
    	} else {
    		$msg .= "<br/>" . $rows[0]['s_prof_comments']  . "\n\n";
    	}
 

 $search = $rows[0]['s_email'];
 $msg .="Earliest Required by School: ";
 
 // Determine the earliest date

$earliest = " ";
if ($entries = recommends_rc_entry_load_jst($entry,$search)) {
    $rows = array();
    foreach ($entries as $entry) {
      // Sanitize the data before handing it off to the theme layer.
      $rows[] = array_map('check_plain', (array) $entry);
    }
    $ldate = "99999999";
    $edate = " ";
    
////
    for ($i = 0; $i <= sizeof($rows)-1; $i++) {
 		$emonth  = $rows[$i]['r_date_due_month'];
 		$m = str_pad($emonth,2,"0",STR_PAD_LEFT);
 		$eday    = $rows[$i]['r_date_due_day'];
 		$d = str_pad($eday,2,"0",STR_PAD_LEFT);
 		$eyear   = $rows[$i]['r_date_due_year'];
 		$edate = $eyear . $m . $d;
 		if ($edate < $ldate) {
 			$earliest = $edate;
 			$ldate = $edate;
 		} else {
 			$earliest = $ldate;
 		}		 
 	 }
 	 
 	 $msg .= substr($earliest,4,2) . "/" . substr($earliest,6,2) . "/" . substr($earliest,0,4) . "<br/>";	
  } else {
  		$msg .=  "Date not found<br/>";
  	}

/////// for course info
$msg .="<div align=center><h3>Course Info</h3> </div>";

recommends_cs_entry_load_jst($entry,$search);

$msg .="<br/>";


$output = '';

  // Get all entries in the recommends_cs table.
  if ($entries = recommends_cs_entry_load_jst($entry,$search)) {
    $rows = array();
    foreach ($entries as $entry) {
      // Sanitize the data before handing it off to the theme layer.
      $rows[] = array_map('check_plain', (array) $entry);
    }
    
    for ($i = 0; $i <= sizeof($rows)-1; $i++) {
    	$msg .= $rows[$i]['c_course'] . "     " . $rows[$i]['c_semester'] . 
    	"        " . $rows[$i]['c_year'] . "     " . $rows[$i]['c_grade'] . "<br/><br/>Comments: ";
    	if ($rows[$i]['c_comments'] == "") {
    		$msg .= " None"  . "\n";
    	} else {
    		$msg .= "<br/>" . $rows[$i]['c_comments']  . "\n";
    	}
    	$msg .= '<br/><br/>';
    }	
  }
  else {
   // drupal_set_message(t('No entries.'));
  }
  
  ////////// for schoole info  
  
   $msg .="<div align=center><h3>School Info</h3> </div>"; 
  
$output = '';

  // Get all entries in the recommends_cs table.
  if ($entries = recommends_rc_entry_load_jst($entry,$search)) {
    $rows = array();
    foreach ($entries as $entry) {
      // Sanitize the data before handing it off to the theme layer.
      $rows[] = array_map('check_plain', (array) $entry);
    }
    for ($i = 0; $i <= sizeof($rows)-1; $i++) {
    	
    	$msg .="School: ";
 		$msg .= $rows[$i]['r_school'] . "<br/>";
 		$msg .="Program/Position: ";
 		$msg .= $rows[$i]['r_program'] . "<br/>";
 		
 		$msg .="Contact Email Address: ";
 		$msg .= $rows[$i]['r_school_contact_email'] . "<br/>";
 		$msg .="Contact Postal Address: <br/>";
 		$msg .= $rows[$i]['r_school_contact_postal'];
 		$msg .="Status: ";
 		$msg .= $rows[$i]['r_status'] . "<br/>";
 		$msg .="Required by Date: ";
 		$msg .= $rows[$i]['r_date_due_month'] . "/";
 		$msg .= $rows[$i]['r_date_due_day'] . "/";
 		$msg .= $rows[$i]['r_date_due_year'] . "<br/>";
 		
 		$btext = $btext = $rows[$i]['lastname'] . $rows[$i]['firstname']  .  $rows[$i]['initial']  . "";
 		$student_title = $btext . '-' . $rows[$i]['r_school'] . '-' .$rows[$i]['r_date_due_year'];
 		$nid = find_recommendlate($student_title);
 		//save for add, if needed
 		variable_set('recommendlate_wrec_student_school',$rows[$i]['r_school']);
 		
    	if ($nid <> 'none') {
    	   $msg .="Recommendlate: <a href=?q=node/" . 
 		    $nid . ">node/" . $nid . "</a><br/>";
 		} else {
 		$msg .= '<a href=?q=recommends_wrec/arguments/' . rawurlencode ( $rows[$i]['r_school']) . '/' . $rows[$i]['r_email'] . '/>Create Recommendlate</a><br/><br/>'; 
 		}
 		//set session variables for recommendlate, if clicked
 		variable_set('recommendlate_student_school', $rows[$i]['r_school']);
 		variable_set('recommendlate_status', $rows[$i]['r_status']);
 		
    	$msg .= "Comments: ";
    	if ($rows[$i]['r_comments'] == "") {
    		$msg .= " None"  . "\n";
    	} else {
    		$msg .= "<br/>" . $rows[$i]['r_comments']  . "\n";
    	}
    	$msg .= "<br/><br/>";
    }
    	
  }
  else {
    drupal_set_message(t('No entries.'));
  }

$msg .= '<br/><br/><a href="?q=recommendations/list/wrec">Back to Student List</a><br/>';
return $msg;
}


function find_recommendlate($student_title) {
  
  $sql = 'SELECT nid FROM {node} n WHERE n.type = :type AND n.status = :status  AND n.title = :title';
  $result = db_query($sql,
    array(
      ':type' => 'recommendlate',
      ':status' => 1,
      ':title' =>$student_title,
    )
  );

  foreach ($result as $row) {
    $node = node_load($row->nid);
  }
  if(!empty($node)) {
    return $node->nid;
  }
  else {
    return 'none';
  }
  
}

// the goto will go here. The passed argument willl be the school
// /arguments/from module/school
function recommends_wrec_rcmdlink($school,$student_email) {
//set session variables for recommendlate, if clicked later
 variable_set('recommendlate_student_email', $student_email);

variable_set('recommendlate_wrec_student_school',$school);
drupal_goto('node/add/recommendlate');

   
}

