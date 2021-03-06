<?php
$firstname = " ";
 $entry= array();			   
 
// Retrieve professor record
$entry = array();
$entries = array();

if (variable_get('recommends_student') != "") {
	$professor = variable_get('recommends_student_professor_email', 'FALSE');
	variable_set('recommends_professor_email', $professor);
	$entries = recommends_prof_entry_load_srch_email($entry,$professor);
}

if (empty($entries)) {
	$professor = "admin@demo.edu"; //for now, the default
	$flags = "NNN";   // for now, the default
	$altemail = 'admin@demo.edu'; //for now, the default
} else {
	$rows = array();
	foreach ($entries as $entry) {
	$rows[] = array_map('check_plain',(array) $entry);
	}
	$flags = $rows[0]['p_flags'];
	$altemail = $rows[0]['p_altemail'];
}
 
// set variables to values that are for the professor's

switch (substr($flags,1,1)) {
    case 'Y':
    	variable_set('recommends_req_bypass_prof_email', 'TRUE');
    	variable_set('recommends_req_alt_prof_email', 'FALSE');
      	break;
    case 'N':
        variable_set('recommends_req_bypass_prof_email', 'FALSE');
        variable_set('recommends_req_alt_prof_email', 'FALSE');
        break;
    case 'T':
        variable_set('recommends_req_bypass_prof_email', 'FALSE');
        variable_set('recommends_req_alt_prof_email', 'TRUE');
        variable_set('recommends_req_professor_email', $altemail);
        break;
  }

switch (substr($flags,2,1)) {
    case 'Y':
    	variable_set('recommends_req_bypass_student_email', 'TRUE');
    	variable_set('recommends_req_alt_student_email', 'FALSE');
      	break;
    case 'N':
    	variable_set('recommends_req_bypass_student_email', 'FALSE');
    	variable_set('recommends_req_alt_student_email', 'FALSE');
      	break;
    case 'T':
        variable_set('recommends_req_bypass_student_email', 'FALSE');
        variable_set('recommends_req_alt_student_email', 'TRUE');
        variable_set('recommends_req_student_email', $altemail);
        break;
  }
/**
 * Return the list of steps and their associated forms. This has been separated
 * to clarify and easy the understanding. You should edit this
 * function to include the steps your wizard/multistep form requires.
 *
 * @return $array
 */
function _recommends_req_steps() {
  return array(
      1 => array(
        'form' => 'recommends_req_addschools_student_info',
      ),
      2 => array(
        'form' => 'recommends_req_addschools_schools_info',
      ),
      3 => array(
        'form' => 'recommends_req_addschools_verification',
      ),
    );
}


function recommends_req_addschools($form, &$form_state) {

  // Initialize a description of the steps for the wizard.
  if (empty($form_state['step'])) {
    $form_state['step'] = 1;

    // This array contains the function to be called at each step to get the
    // relevant form elements. It will also store state information for each
    // step.
    $form_state['step_information'] = _recommends_req_steps();
  }
  $step = &$form_state['step'];
  drupal_set_title(t('Additional Recommendation Request: Step @step', array('@step' => $step)));

  // Call the function named in $form_state['step_information'] to get the
  // form elements to display for this step.
  $form = $form_state['step_information'][$step]['form']($form, $form_state);

  // Show the 'previous' button if appropriate. Note that #submit is set to
  // a special submit handler, and that we use #limit_validation_errors to
  // skip all complaints about validation when using the back button. The
  // values entered will be discarded, but they will not be validated, which
  // would be annoying in a "back" button.
/*  
  if ($step > 1) {
    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
      '#name' => 'prev',
      '#submit' => array('recommends_req_addschools_previous_submit'),
      '#limit_validation_errors' => array(),
    );
  }
*/

  // Show the Next button only if there are more steps defined.
  if ($step < count($form_state['step_information'])) {
    // The Next button should be included on every step
    $form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Proceed'),
      '#name' => 'next',
      '#submit' => array('recommends_req_addschools_next_submit'),
    );
  }
  else {
    // Just in case there are no more steps, we use the default submit handler of
    // the form wizard. Call this button Finish, Submit, or whatever you want to
    // show. When this button is clicked, the recommends_req_addschools_submit handler
    // will be called.
    $form['add_course'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('recommends_req_intro'),
  );
    $form['finish'] = array(
      '#type' => 'submit',
      '#value' => t('Finish'),
    );
  }

  // Include each validation function defined for the different steps.
  if (function_exists($form_state['step_information'][$step]['form'] . '_validate')) {
    $form['next']['#validate'] = array($form_state['step_information'][$step]['form'] . '_validate');
  }

  return $form;
}

/**
 * Submit handler for the "previous" button.
 * - Stores away $form_state['values']
 * - Decrements the step counter
 * - Replaces $form_state['values'] with the values from the previous state.
 * - Forces form rebuild.
 *
 * You are not required to change this function.
 */
function recommends_req_addschools_previous_submit($form, &$form_state) {
  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
  if ($current_step > 1) {
    $current_step--;
    $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the 'next' button.
 * - Saves away $form_state['values']
 * - Increments the step count.
 * - Replace $form_state['values'] from the last time we were at this page
 *   or with array() if we haven't been here before.
 * - Force form rebuild.
 *
 * You are not required to change this function.
 *
 * @param unknown_type $form
 * @param unknown_type $form_state
 */
function recommends_req_addschools_next_submit($form, &$form_state) {

  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
  
/////////////// 
if ($form_state['step'] == 1) {
  
    $format = variable_get('date_format_long', 'l, F j, Y - H:i');
  date_default_timezone_set('America/New_York');
  $date = date("c") ;
  $timestamp = substr($date,0,19); 
  
  $form_state['firstname'] = $form_state['values']['first_name'] ;
  $form_state['lastname'] = $form_state['values']['last_name'] ;
  $form_state['initial'] = $form_state['values']['initial'] ;
  $form_state['s_email'] = $form_state['values']['email'] ;
  $form_state['s_school'] = "Clayton";
  $form_state['s_req_date'] = $timestamp;
  $form_state['s_master_doc'] = $form_state['values']['reqby'] ;
  $form_state['s_timestamp'] = $timestamp;
  }
  
  if ($form_state['step'] == 2) {
   
   for ($i = 1; $i <= $form_state['num_schools']; $i++) {
  
  		$form_state['schoolname'][$i] = $form_state['values']['schname'][$i]['schoolname'];
  		$form_state['schoolprogram'][$i] = $form_state['values']['schname'][$i]['schoolprogram'];
  		
  		$form_state['r_school_contact_email'][$i] = $form_state['values']['schname'][$i]['school_contact_email'];
  		$form_state['r_school_contact_postal'][$i] = $form_state['values']['schname'][$i]['school_contact_postal'];
  		
  		$form_state['r_date_due'][$i]['month'] = $form_state['values']['schname'][$i]['r_date_due']['month'];
  		
  		$form_state['r_date_due'][$i]['day'] = $form_state['values']['schname'][$i]['r_date_due']['day'];
  		$form_state['r_date_due'][$i]['year'] = $form_state['values']['schname'][$i]['r_date_due']['year'];
  		
  		
   };
  }
  
/////////////////////////////////
  if ($current_step < count($form_state['step_information'])) {
    $current_step++;
    if (!empty($form_state['step_information'][$current_step]['stored_values'])) {
      $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
    }
    else {
      $form_state['values'] = array();
    }
    $form_state['rebuild'] = TRUE;  // Force rebuild with next step.
    return;
  }
}

function recommends_req_addschools_student_info($form, &$form_state) {
  $form = array();
  $form['student'] = array(
    '#type'  => 'fieldset',
    '#title' => variable_get('recommends_req_student_professor'),
  );
  $form['student']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#size' => 25,
      '#maxlength' => 50,
    '#required' => TRUE,
    '#default_value' => !empty($form_state['values']['first_name']) ? $form_state['values']['first_name'] : '',
  );
  $form['student']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#size' => 25,
      '#maxlength' => 50,
    '#required' => TRUE,
    '#default_value' => !empty($form_state['values']['last_name']) ? $form_state['values']['last_name'] : '',
  );
   $form['student']['initial'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial'),
    '#size' => 3,
      '#maxlength' => 20,
    '#default_value' => !empty($form_state['values']['initial']) ? $form_state['values']['initial'] : '',
  );
   $form['student']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 25,
      '#maxlength' => 50,
    '#required' => TRUE,
    '#default_value' => !empty($form_state['values']['email']) ? $form_state['values']['email'] : '',

  );
   $form['student']['reqby'] = array(
    '#type' => 'hidden',
    '#title' => t('Date recommendations required by'),
    '#size' => 10,
    '#maxlength' => 15,
    '#description' => t('Date in the form of yyyy/mm/dd.'),
    
  );
   
  return $form;
}


/**
 * Validate function for recommends_req_student_info().
 *
 * Adds logic to validate the form to check the validity of the new fields,
 * if they exist.
 */
function recommends_req_addschools_student_info_validate($form, &$form_state) {

$entry = array();
$email = $form_state['values']['email'];

$record = recommends_st_entry_load_email($entry, $email);
	
	if (empty($record)) {
		
    	form_set_error('', t('The student record was not found. Verify that you have entered the correct email address, Contact professor Bailey if not resolved.'));	
	} 
	
}

function recommends_req_addschools_schools_info($form, &$form_state) {



  // We will have many fields with the same name, so we need to be able to
  // access the form hierarchically.
  $form['#tree'] = TRUE;

  $form['schreq'] = array(
    '#type'  => 'fieldset',
    '#title' => variable_get('recommends_req_student_professor'),
  );
  $form['schreq']['description'] = array(
    '#type' => 'item',
    '#title' => t('Enter each school which is to receive the recommendation.'),
  );

  if (empty($form_state['num_schools'])) {
    $form_state['num_schools'] = 1;
  }

  // Build the number of name fieldsets indicated by $form_state['num_schools']
  for ($i = 1; $i <= $form_state['num_schools']; $i++) {
    $form['schname'][$i] = array(
      '#type' => 'fieldset',
      '#title' => t('School #@num', array('@num' => $i)),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['schname'][$i]['schoolname'] = array(
      '#type' => 'textfield',
      '#title' => t('School/Business'),
      '#size' => 25,
      '#maxlength' => 50,
      '#required' => TRUE,
       '#default_value' => !empty($form_state['values']['schoolname']) ? $form_state['values']['schoolname'] : '',

    );
     $form['schname'][$i]['schoolprogram'] = array(
      '#type' => 'textfield',
      '#title' => t('School Program/Position'),
      '#size' => 25,
      '#maxlength' => 50,
      '#description' => '<br/>Note: </b>If you have any special forms required by the school, email hard copy to <br/>via the "Email Professor" link or mail a soft copy to the professor. ',
       '#default_value' => !empty($form_state['values']['schoolname']) ? $form_state['values']['schoolname'] : '',

    );

  // School contact information.
  $form['schname'][$i]['school_contact_info'] = array(
    '#type' => 'checkboxes',
    '#options' => drupal_map_assoc(array(t('Contact Email'), t('Contact Postal Address'))),
    '#title' => t('School contact information, if known'),
    // This #states rule says that this checkboxes array will be visible only
    // when $form['student_type'] is set to t('High School').
    // It uses the jQuery selector :input[name=student_type] to choose the
    // element which triggers the behavior, and then defines the "High School"
    // value as the one that triggers visibility.

  
  );

  $form['schname'][$i]['school_contact_email'] = array(
    '#type' => 'textfield',
    '#title' => t('School email:'),
    '#size' => 25,

    // This #states rule limits visibility to when the $form['tests_taken']
    // 'school_contact_email' checkbox is checked."
    '#states' => array(
      'visible' => array(  // action to take.
        ':input[name="schname[' . $i . '][school_contact_info][Contact Email]"]'  => array('checked' => TRUE),
      ),
    ),
  );
  $form['schname'][$i]['school_contact_postal'] = array(
    '#type' => 'textarea',
    '#title' => t('Contact Postal address:'),
    '#size' => 3,

    // Set this element visible if the postal checkbox above is checked.
    '#states' => array(
      'visible' => array(  // action to take.
        ':input[name="schname[' . $i . '][school_contact_info][Contact Postal Address]"]'  => array('checked' => TRUE),
      ),
    ),
  );
  
    
    $form['schname'][$i]['r_date_due'] = array(
    '#type' => 'date',
    '#title' => t('Last Date due'),
/*
    '#default_value' => array('month' => "12",
    						  'day' => "31",
    						  'year' => date('Y')
    						),
*/
    '#required' => TRUE,
    '#size' => 10,
    
  );
    
  }
/*  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
*/
  // Adds "Add another school" button
  $form['add_school'] = array(
    '#type' => 'submit',
    '#value' => t('Add another school'),
    '#submit' => array('recommends_req_schtut_9_add_school'),
  );

  // If we have more than one school, this button allows removal of the
  // last name.
  if ($form_state['num_schools'] > 1) {
    $form['remove_school'] = array(
      '#type' => 'submit',
      '#value' => t('Remove latest school'),
      '#submit' => array('recommends_req_schtut_9_remove_school'),
      // Since we are removing a name, don't validate until later.
      '#limit_validation_errors' => array(),
    );
  }

  return $form;
}

/**
 * Submit handler for "Add another school" button on recommends_req_schtut_9().
 *
 * $form_state['num_schools'] tells the form builder function how many name
 * fieldsets to build, so here we increment it.
 *
 * All elements of $form_state are persisted, so there's no need to use a
 * particular key, like the old $form_state['storage']. We can just use
 * $form_state['num_schools'].
 */
function recommends_req_schtut_9_add_school($form, &$form_state) {
  // Everything in $form_state is persistent, so we'll just use
  // $form_state['add_school']
  $form_state['num_schools']++;

  // Setting $form_state['rebuild'] = TRUE causes the form to be rebuilt again.
  $form_state['rebuild'] = TRUE;
}


function recommends_req_schtut_9_remove_school($form, &$form_state) {
  if ($form_state['num_schools'] > 1) {
    $form_state['num_schools']--;
  }

  // Setting $form_state['rebuild'] = TRUE causes the form to be rebuilt again.
  $form_state['rebuild'] = TRUE;
}

/**
 * Validate function for recommends_req_schools_info().
 *
 * Adds logic to validate the form to check the validity of the new fields,
 * if they exist.
 */
function recommends_req_addschools_schools_info_validate($form, &$form_state) {

  for ($i = 1; $i <= $form_state['num_schools']; $i++) {
/*    $year_of_birth = $form_state['values']['schname'][$i]['year_of_birth'];*/
    
    $date_due_month = $form_state['values']['schname'][$i]['r_date_due']['month'];
    $date_due_day = $form_state['values']['schname'][$i]['r_date_due']['day'];
    $date_due_year = $form_state['values']['schname'][$i]['r_date_due']['year'];
    
    $d2=mktime(0,0,0,$date_due_month,$date_due_day,$date_due_year);
    $d1=time();
    $days_diff = floor(($d2-$d1)/86400);

    if ($days_diff < 30 ) {
      form_set_error("schname][$i][r_date_due", 'The due date must be at least 30 days from today. Please contact Dr. Bailey to discuss exceptions.');
    }

  }
}


/******************************************************
*  Student verifies entered data and save/cancels
*******************************************************/
function recommends_req_addschools_verification($form, &$form_state) {

  $output_info = array(
    'firstname'  => $form_state['firstname'],
    'lastname'   => $form_state['lastname'],
    'initial'    => $form_state['initial'],
    's_email'    => $form_state['s_email'],
    's_school'   => $form_state['s_school'],
    's_req_date'    => $form_state['s_req_date'],
    's_master_doc'    => $form_state['s_master_doc'],
  	);
  	
  	 $email_values = array(
    'email' => $form_state['s_email'],
    'message' => "\n" . "\n"  .
    "First Name: " . $output_info['firstname'] . "\n" .
    "Initial:    " . $output_info['initial'] . "\n" .
    "Last Name:  " . $output_info['lastname'] . "\n" .
    "Student Email:      " . $output_info['s_email'] . "\n"  . "\n"
  );
  
  for ($i = 1; $i <= $form_state['num_schools']; $i++) {
		
		$output_schools[$i] = array(
     	'r_email'=> $form_state['s_email'],
     	'num_schools'=> $form_state['num_schools'],
     	'r_school'=> $form_state['schoolname'][$i],
     	'r_program'=> $form_state['schoolprogram'][$i],
     	'r_program'=> $form_state['schoolprogram'][$i],
     	 'r_school_contact_email' => $form_state['r_school_contact_email'][$i],
     	 'r_school_contact_postal' => $form_state['r_school_contact_postal'][$i],
     	'r_school_contact'=> $form_state['r_school_contact_postal'][$i],
     	'r_date_due_month' => $form_state['r_date_due'][$i]['month'],
     'r_date_due_day'   => $form_state['r_date_due'][$i]['day'],
     'r_date_due_year'  => $form_state['r_date_due'][$i]['year'],
     	'r_status'=> "Initial",
		
    	);
    }
    $email_values['message'] = $email_values['message'] .
  "\n" . "Schools to receive recommendation." . "\n\n";
 
  $school_values = array(array());
  
   for ($i = 1; $i <= $output_schools[1]['num_schools']; $i++) {	
   	
   	$email_values['message'] = $email_values['message'] . $output_schools[$i]['r_school'] .  "\n" .
   	"School Program/Position: " .
   	
   	$output_schools[$i]['r_program'] .  "\n" .
   	"School contact postal: " .
   	$output_schools[$i]['r_school_contact_postal'] .  "\n" . 
   	"School contact email: " .
   	$output_schools[$i]['r_school_contact_email'] .  "\n" .    	
   	"Final Date required by school: " . 
   	$output_schools[$i]['r_date_due_month'] . "/" .    
   	$output_schools[$i]['r_date_due_day'] . "/" .   
   	$output_schools[$i]['r_date_due_year'] .  "\n\n";
   
   };
   
  
  $msg = "Please review the following information that you entered. Press Finish  to send the information or cancel to abort the operation";
    drupal_set_message('<pre id=rqmsgsize>' . print_r($msg, TRUE)  . print_r($email_values['message'], TRUE) . '</pre>');
    
  // We will have many fields with the same name, so we need to be able to
  // access the form hierarchically.
  $form['#tree'] = TRUE;

  $form['description'] = array(
    '#type' => 'item',
  );


  return $form;
}

function recommends_req_addschools_submit($form, &$form_state) {

  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
  $rc=0;
  
  $format = variable_get('date_format_long', 'l, F j, Y - H:i');
  date_default_timezone_set('America/New_York');
  $date = date("c") ;
  $timestamp = substr($date,0,19);
  
  
  	
  	$output_info = array(
    'firstname'  => $form_state['firstname'],
    'lastname'   => $form_state['lastname'],
    'initial'    => $form_state['initial'],
    's_email'    => $form_state['s_email'],
    's_school'   => $form_state['s_school'],
    's_req_date'    => $form_state['s_req_date'],
    's_master_doc'    => $form_state['s_master_doc'],
  	);
 
     $entry = array(
    'firstname'  => $form_state['firstname'],
    'lastname'   => $form_state['lastname'],
    'initial'    => $form_state['initial'],
    's_email'    => $form_state['s_email'],
    's_school'   => $form_state['s_school'],
    's_req_date' => $form_state['s_req_date'],
    's_master_doc'    => $form_state['s_master_doc'],
    's_prof_comments'    => " ",
    's_timestamp' => $form_state['s_timestamp'],
    
    );

	$record = recommends_st_entry_load_email($entry, $entry['s_email']);
	
	
	if (empty($record)) {
		
    	$msg = "The recommendation information was not entered due to the above student record not being found. <br/>Contact professor Bailey";
    drupal_set_message('<pre>' . print_r($msg, TRUE)   . '</pre>', 'error');
	} 
    else {
	 for ($i = 1; $i <= $form_state['num_schools']; $i++) {
		
		$output_schools[$i] = array(
     	'r_email'=> $form_state['s_email'],
     	'num_schools'=> $form_state['num_schools'],
     	'r_school'=> $form_state['schoolname'][$i],
     	'r_program'=> $form_state['schoolprogram'][$i],
     	'r_program'=> $form_state['schoolprogram'][$i],
     	 'r_school_contact_email' => $form_state['r_school_contact_email'][$i],
     	 'r_school_contact_postal' => $form_state['r_school_contact_postal'][$i],
     	
     	'r_date_due_month' => $form_state['r_date_due'][$i]['month'],
     'r_date_due_day'   => $form_state['r_date_due'][$i]['day'],
     'r_date_due_year'  => $form_state['r_date_due'][$i]['year'],
     	'r_status'=> "Initial",
		
    	);
    	
    	$format = variable_get('date_format_long', 'l, F j, Y - H:i');
  date_default_timezone_set('America/New_York');
  $date = date("c") ;
  $timestamp = substr($date,0,19);
		
		$entry = array(
     	'r_email'=> $form_state['s_email'],
     	'r_school'=> $form_state['schoolname'][$i],
     	'r_program'=> $form_state['schoolprogram'][$i],
     	'r_program'=> $form_state['schoolprogram'][$i],
     	 'r_school_contact_email' => $form_state['r_school_contact_email'][$i],
     	 'r_school_contact_postal' => $form_state['r_school_contact_postal'][$i],
     	
     	'r_date_due_month' => $form_state['r_date_due'][$i]['month'],
     'r_date_due_day'   => $form_state['r_date_due'][$i]['day'],
     'r_date_due_year'  => $form_state['r_date_due'][$i]['year'],
     	'r_status'=> "Initial",
     	'r_timestamp'=> $timestamp,
		'r_prof'     => variable_get('recommends_student_professor_email'),
    	);
    

	recommends_rc_entry_insert($entry);
	};
	
	$format = variable_get('date_format_long', 'l, F j, Y - H:i');
  date_default_timezone_set('America/New_York');
  $date = date("c") ;
  $timestamp = substr($date,0,19);
		

$msg ="Your information has been successfully entered.";
 drupal_set_message('<pre>' . print_r($msg, TRUE)); 
    

  // In this case we've completed the final page of the wizard, so process the
  // submitted information.
  
  /*
  drupal_set_message(t('This information was collected by this wizard:'));
  */
  
  foreach($form_state['step_information'] as $index => $value) {
    // Remove FAPI fields included in the values (form_token, form_id and form_build_id
    // This is not required, you may access the values using $value['stored_values']
    // but I'm removing them to make a more clear representation of the collected
    // information as the complete array will be passed through drupal_set_message().
    unset($value['stored_values']['form_id']);
    unset($value['stored_values']['form_build_id']);
    unset($value['stored_values']['form_token']);

    // Now show all the values.
    /*
    drupal_set_message(t('Step @num collected the following values: <pre>@result</pre>', array('@num' => $index, '@result' => print_r($value['stored_values'], TRUE))));
    */
  }
  
  
  $email_values = array(
    'email' => $output_info['s_email'],
    'message' => "The following is the information you entered that was required by Professsor Bailey to send recommendations:" . "\n" . "\n"  .
    "First Name: " . $output_info['firstname'] . "\n" .
    "Initial:    " . $output_info['initial'] . "\n" .
    "Last Name:  " . $output_info['lastname'] . "\n" .
    "Student Email:      " . $output_info['s_email'] . "\n"  . "\n"
  );
  
  $email_values['message'] = $email_values['message'] .
  "\n" . "Schools to receive recommendation." . "\n\n";
 
  $school_values = array(array());
  
   for ($i = 1; $i <= $output_schools[1]['num_schools']; $i++) {	
   	
   	$email_values['message'] = $email_values['message'] . $output_schools[$i]['r_school'] .  "\n" .
   	"School Program/Position: " .
   	
   	$output_schools[$i]['r_program'] .  "\n" .
   	"School contact email: " .
   	
   	$output_schools[$i]['r_school_contact_email'] .  "\n" . 
   	"School contact postal: " .
   	$output_schools[$i]['r_school_contact_postal'] .  "\n" . 
   	 "\n" .    	
   	"Final Date required by school: " . 
   	$output_schools[$i]['r_date_due_month'] . "/" .    
   	$output_schools[$i]['r_date_due_day'] . "/" .   
   	$output_schools[$i]['r_date_due_year'] .  "\n\n";
   
   }; 
 
  	email_mail_send($email_values);
  	
  	drupal_goto('recommendations/recommends_req');
  	
  } /* end of no errror in student information block  */
 
}

/************************************************
* List the entered values for verification.
*************************************************/
function list_entries($email_values) {

$msg = "list_entries, email_values - ";
    drupal_set_message('<pre>' . print_r($msg, TRUE)  . print_r($email_values['message'], TRUE) . '</pre>'); 

return drupal_get_form('test_myform');
}

function test_myform($form_state) {

  $form=array();
    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
      '#name' => 'prev',
      '#submit' => array('recommends_req_addschools_previous_submit'),
      '#limit_validation_errors' => array(),
    );
  $form['#submit'][] = 'test_myform_submit';


$form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
$form['submit'] = array('#type' => 'submit', '#value' => t('Cancel'));
  return $form;
}

function test_myform_submit($form, &$form_state) {
$msg = "HELP!!!";
    drupal_set_message('<pre>' . print_r($msg, TRUE)  .  '</pre>'); 


}

function recommends_req_mail($key, &$message, $params) {
  global $user;

  // Each message is associated with a language, which may or may not be the
  // current user's selected language, depending on the type of e-mail being
  // sent. This $options array is used later in the t() calls for subject
  // and body to ensure the proper translation takes effect.
  $options = array(
    'langcode' => $message['language']->language,
  );

  switch ($key) {
    // Send a simple message from the contact form.
    case 'contact_message':
      $message['subject'] = t('Recommendations online entry copy sent from @site-name', array('@site-name' => variable_get('site_name', 'Drupal')), $options);
      
      // Note that the message body is an array, not a string.
      /*
      $message['body'][] = t('@name sent you the following message:', array('@name' => $user->name), $options);
      */
      
      $message['body'][] = t('The following us a confirmation of an addendun to your Recommendation Request made by you to Dr. Scott M. Bailey:');
      
      // Because this is just user-entered text, we do not need to translate it.

      // Since user-entered text may have unintentional HTML entities in it like
      // '<' or '>', we need to make sure these entities are properly escaped,
      // as the body will later be transformed from HTML to text, meaning
      // that a normal use of '<' will result in truncation of the message.
      $message['body'][] = check_plain($params['message']); 
      break;
  }
}

/**--------------------------------------------------------  
 * Send an e-mail.
 *
 * @param $email_values
 *   An array of values from the contact form fields that were submitted.
 *   There are just two relevant items: $email_values['email'] and
 *   $email_values['message'].
 */
function email_mail_send($email_values) {
  // All system mails need to specify the module and template key (mirrored from
  // hook_mail()) that the message they want to send comes from.
  
  $module = 'recommends_req';
  $key = 'contact_message';

  // Specify 'to' and 'from' addresses.
  
  $to = $email_values['email']; 
  
  $from = variable_get('recommends_professor_email','bailey@clayton.edu');
  

  // "params" loads in additional context for email content completion in
  // hook_mail(). In this case, we want to pass in the values the user entered
  // into the form, which include the message body in $email_values['message'].
  
  $params = $email_values;

  // The language of the e-mail. This will one of three values:
  // * user_preferred_language(): Used for sending mail to a particular website
  //   user, so that the mail appears in their preferred language.
  // * global $language: Used when sending a mail back to the user currently
  //   viewing the site. This will send it in the language they're currently
  //   using.
  // * language_default(): Used when sending mail to a pre-existing, 'neutral'
  //   address, such as the system e-mail address, or when you're unsure of the
  //   language preferences of the intended recipient.
  //
  // Since in our case, we are sending a message to a random e-mail address that
  // is not necessarily tied to a user account, we will use the site's default
  // language.
  
  $language = language_default();

  // Whether or not to automatically send the mail when drupal_mail() is
  // called. This defaults to TRUE, and is normally what you want unless you
  // need to do additional processing before drupal_mail_send() is called.
  
  $send = TRUE;
  
  // Send the mail, and check for success. Note that this does not guarantee
  // message delivery; only that there were no PHP-related issues encountered
  // while sending.
  //STUDENT
  
  if (variable_get('recommends_req_alt_student_email', 'FALSE') == 'TRUE') {
  	$to = variable_get('recommends_req_student_email');
  }
  if (variable_get('recommends_req_bypass_student_email', 'FALSE') == 'FALSE' ) {
    $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
    if ($result['result'] == TRUE) {
      drupal_set_message(t('An Email confirmation has been sent to ') . $to);
  }
    else {
      drupal_set_message(t('There was a problem sending your message and it was not sent.'), 'error');
  }
  }
  
  //PROFESSOR
  
  if (variable_get('recommends_req_alt_prof_email', 'FALSE') == 'TRUE') {
  	$to = variable_get('recommends_req_professor_email');
  } else {
  	$to = variable_get('recommends_professor_email', 'FALSE');
  }
  if (variable_get('recommends_req_bypass_prof_email', 'FALSE') == 'FALSE') {
 
 // send to professor
    $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
    if ($result['result'] == TRUE) {
      drupal_set_message(t('The Request has been sent to the Professor '));
    }
    else {
      drupal_set_message(t('There was a problem sending your message and it was not sent.'), 'error');
    }
 }
}

/**
 * Implement hook_mail_alter().
 *
 * This function is not required to send an email using Drupal's mail system.
 *
 * Hook_mail_alter() provides an interface to alter any aspect of email sent by
 * Drupal. You can use this hook to add a common site footer to all outgoing
 * email, add extra header fields, and/or modify the email in anyway. HTML-izing
 * the outgoing email is one possibility.
 */
function email_mail_alter(&$message) {
  
  $options = array(
    'langcode' => $message['language']->language,
  );

  $signature = t("\n--\nMail altered by email_example module.", array(), $options);
  if (is_array($message['body'])) {
    $message['body'][] = $signature;
  }
  else {  // Some modules use the body as a string, erroneously.
    $message['body'] .= $signature;
  }
}


