<?php
$out_array = array();
$entry = array();
$professor_name = "";

$out_array[1] = "
% !TEX TS-program = pdflatex
\documentclass[12pt]{letter}

\usepackage{urstandard}\n";

$out_array[1] .= "\address{" . $professor_name . "\\\\"  .
	  $professor_ext_address . "}";
$out_array[1] .= "
%\signature{\vspace{-3pc}\includegraphics[width=2in]{../e-sig}\\" . $professor_name . "}\n";
$out_array[1] .= "
\signature{" . $professor_name . "}";
$out_array[1] .= "
\begin{document}

\begin{letter}{}

\opening{Dear Colleague,}

%1-The applicant's extra-curricular mathematics work of which you are aware;
%2-The applicant's persistence in tackling challenging problems;
%3-When and in what capacity you have worked with the applicant.
% ";

$out_array[1] .= "\nI am currently an " . $professor_position . " in the " . $professor_program . " at " . $professor_school;

$out_array[0] = $student_full;
$out_array[2] = $student_full . $school_name;
	 
$out_array[1] .= "I would like to take this opportunity to recommend " . $student_full_text . " for acceptance into your " . $school_program . " program. ";

for ($i = 0; $i <= $course_total-1; $i++) {	 
  $out_array[1] .= $student_first . " enrolled in my ";
  $out_array[1] .= $course_name[$i] . " course in the " . $course_semester[$i] . " semester of " . $course_year[$i] . " with a grade of " . $course_grade[$i] . '.';
    	
  $out_array[1] .= "\n\n%       <------ COURSE ATTENDED (" . $course_name[$i] . ") COMMENTS ------>\n";
  if ($course_comments[$i] <> "") {
    $out_array[1] .= $course_comments[$i]  . "\n";
  }
    	
  $out_array[1] .= "\n\n%       <------ COURSE ATTENDED (" . $course_name[$i] . ") GRADE COMMENTS ------>\n";
   
  $out_array[1] .= "%\n" . $course_grade_comments[$i];
 		
  $out_array[1] .= "\n\n%       <------ COURSE CONDUCED (" . $course_name[$i] . ") OBJECTIVE ------>\n";
  
  $out_array[1] .= "%\n";
  $out_array[1] .= $course_objective[$i];
}

$out_array[1] .= "\n\n%       <------ PROFESSOR OVERALL COMMENTS ON STUDENT ------>\n";
 
$out_array[1] .= "%\n";
$out_array[1] .= $student_professor_comments;

$out_array[1] .= "\n\n%       <------ CLOSING ------>\n";

$out_array[1] .= "
I would like to reaffirm my enthusiastic recommendation for " . $student_pre_last . "'s acceptance into your " . $school_program . " program. 
\n\n
If you have any further questions about " . $student_pre_last . "'s ability, or this recommendation, please do not hesitate to contact me. 
\n\n
\closing{Sincerely,}

\end{letter}


\end{document}";

?>