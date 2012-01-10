DESCRIPTION
------------

 College professors often are requested by their students to write Recommendation Letters to other colleges for contnued graduate studies or for research opportunities. Professors who teaxh graduate courses need to expend a considerable effort at year's end writing these letters and sending them to their requested schools. The informaion the professor needs from the student is often incomplete and needs several iterations of emails to get the information. Then when there are many requests, the professor must keep the information organized for each student until the letters are written. The Recommendations application is meant to solve or alleviate much of this burden on the professor.. See the application features below. It can be seen that this application involves a multitude of Drupal API functions: Forms, Database, file, email, node creation, menu.


The following are features of the application:

1) The student enters online all the information that is required by the professor to write a recommendation and send it to the necessary schools.. This includes: Student information (Name, email address, statement of intent/point of view. Schools to receive the recommendation. Their contact information and dates requred, Course(s) that the student attended that were conducted by the professor. Any additional documents related to the recommendation.

2) Online  entry data validated in the following is checked: The "school required by date"  is audited to ensure that it is not within 30 days of the request. All required data (student, schools and attended courses) must be entered by the student or the request canot be subnitted.

3) Upon completion and submittal, The information is stored in tables which are accessible and alterable by the professor. An email is sent to the professor indicating the student request A confirmation email is sent to the student with the information that was entered.

4) A student can add schools to the requestonline at any time. The same notifications will be sent to the professor and student.

5) A job is scheduled daily to determine if any recommendations are required to be sent and were't witin a 6 day window. If any meet the criteria, an email is sent to the professor as a reminder.

6) A job is scheduled daily which sends an email to the professor when a recommendation is altered. This occurs when a student appends the request with an additional school or when the professor has altered any of the records.

7) An online summary/aging report that a professor can use to determine workload.

8) A "Student Information Worksheet" which contains all the information student has provided. From this sheet a "Recommendlate" can be creation or accessed. A recommendlate: is a basic template of all the information provided by the student and added by the professor in a Word document form. The professor information can be course objectives and grade level statements and comments intered abot the student attributes. is editable with a WYSIWYG online editor.
contains the ability add reference files and have revision levels. is stored and can be accesed online.

9) A Contacts database which contains sites which need to be accessed by certain schools to gather contact information for a particular school. Each entry has a username, password and any additional notes. 

10) The application is written in a "Mobile First" approach and is also easily used in an iPad or desktop environment.

11) The application runs a Drupal 7 environment and has all it's associated user authentification, logging and security capabilities.

INSTALLATION/DEPENDENCIES
--------------------------
See file INSTALL





