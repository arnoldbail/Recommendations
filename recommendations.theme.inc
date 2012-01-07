<?php

/*******************************************************
*         Mobile Dashboard
*
*******************************************************/


function theme_recommendations_mob_dashboard() {
  $o = array('#markup' => t('
  
<div id=rpgwrapper>
 <div id=rprof>Professor ' . variable_get('recommends_professor') . '</div>
 
<ul class="rollover">

 <li> <a href="@sheet"> 
<img alt="Student Information Sheet"   src=sites/all/modules/recommendations/icons/Write.gif />InfoSheet</a>
</li>

<li><a href="@summary">   
<img alt="Summart/Aging Report"   src=sites/all/modules/recommendations/icons/summary.png />Reoort</a>
</li>

<li><a href="@contacts">  
<img alt="Contacts"   src=sites/all/modules/recommendations/icons/password.png />Contacts</a>
</li>
 
<li><a href="@professor">
<img alt="Professor Profile" src=sites/all/modules/recommendations/icons/newton.png />Profile</a>
</li>

<li><a href="@coursesinstr">   
<img alt="Courses Conducted by professor"   src=sites/all/modules/recommendations/icons/course48.gif />Conducted</a>
</li>


<li><a href="@recommendlates">   
<img alt="Recommendlates List"   src=sites/all/modules/recommendations/icons/snippetIcon.png />Rcndlates</a>
</li> 

 <li><a href="@online">  
<img alt="Student Online Recommendation Request"   src=sites/all/modules/recommendations/icons/Icon_RequestForm.png />Request</a>
</li>

<li><a href="@students">   
<img alt="Students"   src=sites/all/modules/recommendations/icons/college-students.gif />Students</a>
</li>

<li><a href="@schools">  
<img alt="Schools"   src=sites/all/modules/recommendations/icons/recs.jpeg />Schools</a>
</li>

<li><a href="@courses">   
<img alt="Courses enrolled by student"   src=sites/all/modules/recommendations/icons/classroom.png />Enrolled</a>
</li>

<li><a href="@advhelp">   
<img alt="Help popup"   src=sites/all/modules/recommendations/icons/help.png />Help</a>
</li>

</ul>

</div>', 
array(
'@online' => url('recommendations/recommends_req', array('absolute' => TRUE)), 
'@students' => url('recommendations/list/students', array('absolute' => TRUE)),
'@coursesinstr' => url('recommendations/cplist/coursesinstr', array('absolute' => TRUE)),
'@sheet' => url('recommendations/list/wrec', array('absolute' => TRUE)),
'@schools' => url('recommendations/list/schools', array('absolute' => TRUE)),
'@recommendlates' => url('recommendations/recommends_rcmd/recommendlate', array('absolute' => TRUE)),
'@courses' => url('recommendations/list/courses', array('absolute' => TRUE)),
'@summary' => url('recommendations/recommends_rpt/summary', array('absolute' => TRUE)),
'@contacts' => url('recommendations/cntlist/contacts', array('absolute' => TRUE)),
'@professor' => url('recommendations/recmd_prof/professors', array('absolute' => TRUE)),
'@advhelp' => url('recommendations/advhelp', array('absolute' => TRUE))
)));


if (in_array("administrator", variable_get('roles_array'))) {
$o = array('#markup' => t('
  
<div id=rpgwrapper>
 <div id=rprof>Professor ' . variable_get('recommends_professor') . '</div>
 
<ul class="rollover">

 <li><a href="@professor">
<img alt="Professor Profile" src=sites/all/modules/recommendations/icons/newton.png />Profile</a>
</li>
 
 <li> <a href="@setup"> 
<img alt="Demo setup"   src=sites/all/modules/recommendations/icons/drupalthumb.png />Femo Setup</a>
</li>

<li> <a href="@setup2"> 
<img alt="Demo 2 setup"   src=sites/all/modules/recommendations/icons/drupalthumb.png />Demo 2 Setup</a>
</li>

</ul>

</div>', 
array(
'@professor' => url('recommendations/recmd_prof/professors', array('absolute' => TRUE)),

'@setup' => url('recommendations/recommendations_setup', array('absolute' => TRUE)),

'@setup2' => url('recommendations/recommendations_setup2', array('absolute' => TRUE))
)));
}


  return $o;
}

/*******************************************************
*  Display a list of students for selection
*
********************************************************/
function theme_recommendations_select_list($variables) {
 
 // Build list html from rows passed.
 // List is in wrapper div below.
 
   $function = $variables['function'];
   
   variable_set('recommends_name',"");
   variable_set('recommends_s_email',"");
    
   $rows = $variables['rows'];

    $list = '<h3 align=center>Students</h3><ul class="rollover">';
    for ($i = 0; $i <= sizeof($rows)-1; $i++) {
    	
    	$strname = $rows[$i]['lastname'] . ", " . $rows[$i]['firstname'] . 
    	" " . $rows[$i]['initial'];
    	$name = str_replace( " ", "_", $strname);
    	
    	$list .= '<li><a href=@' . $function . '/' . $rows[$i]['s_email'] . '/' . $name . '>';
    	$list .= $rows[$i]['lastname'] . ", " . $rows[$i]['firstname'] . 
    	" " . $rows[$i]['initial'] . " " .  "<br/>";
    	$list .= '</a></li>';
    } 
    $list .= '</ul>';
    if (empty($rows)) {
     $list .= 'No entries!';
    }
    $list2 = '';
    if (variable_get('recommends_student_menu') == 'Y') {
      $list2 = '<div style="clear:both;"><a href=@' . $function . '/add/'  . '>Add a student?</a></div>';
      variable_set('recommends_student_menu','N');
    } 
// Wrapper div starts here
$o = array('#markup' => t('
  
<div id=selwrapper>
 <div id=rprof>Professor ' . variable_get('recommends_professor') . '</div>' . $list .
 
'<ul class="rollover">
</ul>
</div>'  . 
$list2 , 
array(
'@students' => url('recommendations/recmd_st/students', array('absolute' => TRUE)),

'@courses' => url('recommendations/cslist', array('absolute' => TRUE)),

'@schools' => url('recommendations/rclist', array('absolute' => TRUE)),

'@wrec' => url('recommendations/recmd_wrec/wrec', array('absolute' => TRUE)),

)));
  return $o;
}

/*******************************************************
*  Display a list of courses for a students for selection
* This creates a list of links to the course enrolled
* table maintenance rutine with the course number as a 
* added parameter. 
*
********************************************************/
function theme_recommendations_select_cslist($variables) {
 
 // Build list html from rows passed.
 // List is in wrapper div below.
 
 $strname = str_replace( " ", "_", variable_get('recommends_name'));  
  $function = $variables['function'];
  $rows = $variables['rows'];
  $list = '<h3 align=center>Courses Enrolled</h3><ul class="rollover">'; 
  for ($i = 0; $i <= sizeof($rows)-1; $i++) {
   /*  
     $strcourse = $rows[$i]->c_course . ", " . $rows[$i]->c_semester . 
     " " . $rows[$i]->c_year;
    */    	
     $strcourse = str_replace( " ", "_",$rows[$i]->c_course);
     
     $list .= '<li><a href=@' . $function . '/' . $rows[$i]->c_email .  '/' . $strname . '/' . $strcourse . '/' . $rows[$i]->c_semester . '/' . $rows[$i]->c_year . '>';
     
     $list .= $rows[$i]->c_course . ", " . $rows[$i]->c_semester . 
    	" " . $rows[$i]->c_year . " " .  "<br/>";
     $list .= '</a></li>';
    }
    $list .= '</ul>';
    if (empty($rows)) {
     $list .= 'No entries!';
    } 
    $list2 = '<div style="clear:both"><a href=@' . $function . '/add/' . variable_get('recommends_s_email') .  '/' . $strname  . '>Add an enrolled course?</a></div>';

// *****Wrapper div starts here **********
$o = array('#markup' => t('  
<div id=selwrapper>
 <div id=rprof>' . variable_get('recommends_name') . '</div>' . $list .
'<ul class="rollover">
</ul>
</div>'  . 
$list2 , 
array(
'@courses' => url('recommendations/recmd_cs/courses', array('absolute' => TRUE)),
)));
  return $o;
}

/*******************************************************
*  Display a list of schools for a students for selection
* This creates a list of links to the course enrolled
* table maintenance rutine with the course number as a 
* added parameter. 
*
********************************************************/
function theme_recommendations_select_rclist($variables) {
 
 // Build list html from rows passed.
 // List is in wrapper div below.
 
 $strname = str_replace( " ", "_", variable_get('recommends_name'));  
  $function = $variables['function'];
  $rows = $variables['rows'];
  $list = '<h3 align=center>Schools Requested</h3><ul class="rollover">'; 
  for ($i = 0; $i <= sizeof($rows)-1; $i++) {    	
     $strschool= str_replace( " ", "_",$rows[$i]->r_school);
     $list .= '<li><a href=@' . $function . '/' . $rows[$i]->r_email .  '/' . $strname . '/' . $strschool . '>';
     $list .= $rows[$i]->r_school . "<br/>";
     $list .= '</a></li>';
    
   } 
   $list .= '</ul>';
   if (empty($rows)) {
     $list .= 'No entries! ';
   }
   $list2 = '<div style="clear:both;"><a href=@' . $function . '/add/' . variable_get('recommends_s_email') .  '/' . $strname  . '>Add a school?</a></div>';
    
    
// *****Wrapper div starts here **********
$o = array('#markup' => t('  
<div id=selwrapper>
 <div id=rprof>' . variable_get('recommends_name') . '</div>' . $list .
'<ul class="rollover">
</ul>
</div>'  . 
$list2 , 
array(
'@schools' => url('recommendations/recmd_rc/schools', array('absolute' => TRUE)),
)));
  return $o;
}

/*******************************************************
*  Display a list of courses conducted by the professor 
* for selection
*
********************************************************/
function theme_recommendations_select_cplist($variables) {
 
 // Build list html from rows passed.
 // List is in wrapper div below.
 
   $function = $variables['function'];
   $rows = $variables['rows']; 

    $list = '<h3 align=center>Courses Conducted</h3><ul class="rollover">';
    for ($i = 0; $i <= sizeof($rows)-1; $i++) { 	
     $strcourse = str_replace( " ", "_",$rows[$i]->i_course);
     $list .= '<li><a href=@' . $function  . $strcourse  . "/" . $rows[$i]->i_semester . "/" . $rows[$i]->i_year  . '>';
     $list .= $rows[$i]->i_course . " " . $rows[$i]->i_semester . 
    	" " . $rows[$i]->i_year . " " .  "<br/>";
     $list .= '</a></li>';
    	
    } 
    $list .= '</ul>';
    
    if (empty($rows)) {
     $list .= 'No entries!<br/><br/>';
    }
    $list2 = '<div style="clear:both;"><a href=@' . $function . 'add>Add a conducted course?</a></div>';
 
// Wrapper div starts here
 
$o = array('#markup' => t('
  
<div id=selwrapper>
 <div id=rprof>Professor ' . variable_get('recommends_professor') . '</div>' . $list .
 
'<ul class="rollover">
</ul>

</div>'  . 
$list2 , 
array(

'@coursesinstr' => url('recommendations/recmd_cp/coursesinstr/', array('absolute' => TRUE)),
)));
  return $o;
}


/*******************************************************
*  Display a list of coContacts for the professor 
* for selection
*
********************************************************/
function theme_recommendations_select_cntlist($variables) {
 
 // Build list html from rows passed.
 // List is in wrapper div below.
 
   $function = $variables['function'];
   $rows = $variables['rows']; 

    $list = '<h3 align=center>Contacts</h3><ul class="rollover">';
    for ($i = 0; $i <= sizeof($rows)-1; $i++) { 	
     $strsite = str_replace( " ", "_",$rows[$i]->n_site);
     $list .= '<li><a href=@' . $function  . $strsite  . '>';
     $list .= $rows[$i]->n_site  .  "<br/>";
     $list .= '</a></li>';
    	
    } 
    $list .= '</ul>';
    
    if (empty($rows)) {
     $list .= 'No entries!<br/><br/>';
    }
    $list2 = '<div style="clear:both;"><a href=@' . $function . 'add>Add a Contact?</a></div>';
 
// Wrapper div starts here
 
$o = array('#markup' => t('
  
<div id=selwrapper>
 <div id=rprof>Professor ' . variable_get('recommends_professor') . '</div>' . $list .
 
'<ul class="rollover">
</ul>

</div>'  . 
$list2 , 
array(

'@contacts' => url('recommendations/recmd_cnt/contacts/', array('absolute' => TRUE)),
)));
  return $o;
}





