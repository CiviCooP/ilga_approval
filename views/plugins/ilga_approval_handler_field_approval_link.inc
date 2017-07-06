<?php
/**
 *  Drupal view handler for making te approval link
 *  with the correct parameters for autofilling
 *
 * @author Klaas Eikelboom (CiviCooP)
 * @date 05 juli 2017
 * @license AGPL-3.0
 */
class ilga_approval_handler_field_approval_link extends views_handler_field {

  function construct() {
    parent::construct();
  }

  function query() {
    // do nothing -- to override the parent query.
  }

  private function currentUser(){
     civicrm_initialize();
     $session = CRM_Core_Session::singleton();
     return $session->get('userID');
  }

  function render($values) {

     $query = array(
     'cid1'=> $this->currentUser(),
     'cid2'=> $values->civicrm_contact_id)
     ;

     $result = ilga_approval_utils::commentActivity($values->civicrm_contact_id);
     if($result){
       $query['activity1']=$result['activity_id'];
     }
     return l('Approve',"node/22",array(
       "query" => $query
       )
     );
  }

}